TYPE := 3
ifeq ($(TYPE), 3)
LINUX_PATH := /root/smdk6410_lzy/src/linux3.4
else
LINUX_PATH := /root/smdk6410_lzy/src/linux
endif

obj-m += led_drv.o
obj-m += led_dev.o

all:
	make -C $(LINUX_PATH) M=`pwd` modules
	arm-linux-gcc test_app.c -o app
clean:
	make -C $(LINUX_PATH) M=`pwd` modules clean
	rm modules.order -rf
	rm app -rf
install:
	make -C $(LINUX_PATH) M=`pwd` modules_install MOD_INSTALL_PATH=/nfsroot



