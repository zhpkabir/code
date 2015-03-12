
hostprogs-y := app demon_test
obj-m := cdev_test1.o cdev_test2.o cdev_test3.o demon.o cdev_hot.o mul_dev.o
always += $(hostprogs-y)
all: 
	@make  -j8 --no-print-directory -C /lib/modules/${shell uname -r}/build/ M=`pwd` modules

clean:
	@rm  $(obj-m) $(hostprogs-y) *mod.*  *.ko  Module.symvers modules.order .tmp_versions/ .*.cmd -fr
