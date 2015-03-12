
hostprogs-y := user_ioctl
obj-m := char_test01.o char_test02.o
always += $(hostprogs-y)
all: 
	@make  -j8 --no-print-directory -C /lib/modules/${shell uname -r}/build/ M=`pwd` modules

clean:
	@rm  $(obj-m) $(hostprogs-y) *mod.*  *.ko  Module.symvers modules.order .tmp_versions/ .*.cmd -fr
