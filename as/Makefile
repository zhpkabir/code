
OUT=b.o
all:$(OUT)
	ld   -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc $(OUT) -o go

%.o:%.s
	as --32 -o $@  $<
