
注意:
	printf地址
	主机MAC地址
	主机IP地址

host:
	make
	arp -s 192.168.1.253 11:22:33:44:55:66
board:
	tftp 50000000 arm.bin
	go 50000000 LoadAddress FileName

	注意: LoadAddress不能超过0x55000000


