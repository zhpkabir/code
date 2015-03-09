0.修改Makefile中的变量
	第3行LINUX_PATH=(开发版运行的3.4)内核源码的目录
	第5行LINUX_PATH=(开发版运行的2.6)内核源码的目录
1.make TYPE=2(如果启动的是2.6内核)
  make TYPE=3(如果启动的是3.4内核)
2.cp led_drv.ko led_dev.ko /nfsroot
board:
	
	3.[u-boot-xx]# tftp 50008000 zImage
          [u-boot-xx]# bootm 50008000
	  #insmod led_drv.ko
	  #insmod led_dev.ko
          #mdev -s(如果已经移植udev则不用这步)
          #./app /dev/s3c-led
