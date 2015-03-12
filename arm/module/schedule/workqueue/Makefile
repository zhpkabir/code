
obj-m := work1.o work2.o work3.o init_work.o init_delay_work.o single.o single_queue.o
hostprogs-y :=
always :=$(hostprogs-y)
CFLAGS_exec.o := -D'EXECPATH="$(kbuild-dir)/exe.txt"'
all: 
	@make  -j8 --no-print-directory -C /lib/modules/${shell uname -r}/build/ M=`pwd` modules

clean:
	@rm  $(obj-m) $(hostprogs-y) *mod.*  *.ko  Module.symvers modules.order .tmp_versions/ .*.cmd -fr
