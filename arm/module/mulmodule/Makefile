
obj-m := a.o b.o
KBUILD_EXTMOD := /home/zhp/test/code/src/work/kernel/module/mulmodule
all: 
	@make  -j8 --no-print-directory -C /lib/modules/${shell uname -r}/build/ M=`pwd` modules

clean:
	@rm  $(obj-m) $(hostprogs-y) *mod.*  *.ko  Module.symvers modules.order .tmp_versions/ .*.cmd -fr
