MADE BY ZHIYONGLI

注意：该程序默认支持8张相片，如果想支持更多或者更少请修改common.h中的MUX_NUM
      该程序默认支持的是888格式的图片，如需要改变格式请修改common.h中的BPP565宏

1.make

2.tftp 50000000 image
3.nand erase 4500000 b00000
4.nand write 50000000 4500000 b00000

5.tftp 50000000 beyond.raw
6.nand erase 40000 4000000
7.nand write 50000000 40000 4000000

8.tftp 50000000 arm.bin
9.nand erase 0 40000
10.nand write 50000000 0 40000

11.tftp 50000000 logol
12.nand erase 5000000 40000
13.nand write 50000000 5000000 40000
