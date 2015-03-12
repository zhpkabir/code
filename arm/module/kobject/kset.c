#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/stat.h>
 
MODULE_AUTHOR("haoyu");
MODULE_LICENSE("Dual BSD/GPL");
 
struct my_kobject
{
    int value;
    struct kobject kobj;
};
    
struct my_kobject my_kobj;
 
void kobject_release(struct kobject *kobject);
ssize_t kobject_attr_show(struct kobject *kobject, struct attribute *attr,char *buf);
ssize_t kobject_attr_store(struct kobject *kobject,struct attribute *attr,const char *buf, size_t count);
 
struct attribute kobject_attr1 = {
    .name = "name",
    .mode = S_IRWXUGO,
};
 
struct attribute kobject_attr2 = {
    .name = "value",
    .mode = S_IRWXUGO,
};
 
static struct attribute *kobject_def_attrs[] = {
    &kobject_attr1,
    &kobject_attr2,
    NULL,
};
 
struct sysfs_ops kobject_sysfs_ops =
{
    .show = kobject_attr_show,
    .store = kobject_attr_store,
};
 
struct kobj_type ktype =
{
    .release = kobject_release,
    .sysfs_ops = &kobject_sysfs_ops,
    .default_attrs = kobject_def_attrs,
};
 
void kobject_release(struct kobject *kobject)
{
    printk("kobject release.\n");
}
 
ssize_t kobject_attr_show(struct kobject *kobject, struct attribute *attr,char *buf)
{
    int count = 0;
    struct my_kobject *my_kobj = container_of(kobject, struct my_kobject, kobj);
    printk("kobject attribute show.\n");
    if(strcmp(attr->name, "name") == 0)
        count = sprintf(buf, "%s\n", kobject->name);
    else if(strcmp(attr->name, "value") == 0)
        count = sprintf(buf, "%d\n", my_kobj->value);
    else
        printk("no this attribute.\n");
    
    return count;
}
 
ssize_t kobject_attr_store(struct kobject *kobject,struct attribute *attr,const char *buf, size_t count)
{
    int val;
    struct my_kobject *my_kobj = container_of(kobject, struct my_kobject, kobj);
    printk("kobject attribute store.\n");
    if(strcmp(attr->name, "name") == 0)
        printk("Can not change name.\n");
    else if(strcmp(attr->name, "value") == 0)
    {
        val = buf[0] - '0';
        if(val == 0 || val == 1)
            my_kobj->value = val;
        else
            printk("value is '0' or '1'\n");
    }
    else
        printk("no this attribute.\n");
        
    return count;
}
 
int kset_filter(struct kset *kset, struct kobject *kobj)
{
    printk("UEVENT: filter. kobj %s.\n",kobj->name);
    return 1;
}
 
const char *kset_name(struct kset *kset, struct kobject *kobj)
{
    static char buf[20];
    printk("UEVENT: name. kobj %s.\n",kobj->name);
    sprintf(buf,"%s","kset_test");
    return buf;
}
 
int kset_uevent(struct kset *kset, struct kobject *kobj,
                struct kobj_uevent_env *env)
{
    int i = 0;
    printk("UEVENT: uevent. kobj %s.\n",kobj->name);
 
    while( i< env->envp_idx){
        printk("%s.\n",env->envp[i]);
        i++;
    }
 
    return 0;
}
 
struct kset_uevent_ops uevent_ops =
{
    .filter = kset_filter,
    .name   = kset_name,
    .uevent = kset_uevent,
};
 
struct kset *kset_parent;
struct kset kset_child;
 
static int kset_test_init(void)
{
    printk("kboject test init.\n");
    kset_parent = kset_create_and_add("kset_parent", &uevent_ops, NULL);
    my_kobj.kobj.kset = kset_parent;
    kobject_init_and_add(&my_kobj.kobj,&ktype,NULL,"kobject_test");
 
    kobject_set_name(&kset_child.kobj,"kset_child");
    kset_child.kobj.kset = kset_parent;
    kset_register(&kset_child);
    
    return 0;
}
 
static void kset_test_exit(void)
{
    printk("kobject test exit.\n");
    kobject_del(&my_kobj.kobj);
    kset_unregister(kset_parent);
    kset_unregister(&kset_child);
}
 
module_init(kset_test_init);
module_exit(kset_test_exit);
