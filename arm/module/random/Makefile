obj-m := random.o
hostprogs-y := main
always :=$(hostprogs-y)
all: 
	@make  -j8 --no-print-directory -C /lib/modules/${shell uname -r}/build/ M=`pwd` modules

clean:
	@rm  $(obj-m) $(hostprogs-y) *mod.*  *.ko  Module.symvers modules.order .tmp_versions/ .*.cmd -fr
