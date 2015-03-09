O=a.o
all:$(O)
	ld   -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc $(O) -o go
	strip go
	rm -fr *.o

%.o:%.s
	as --32 -o $@  $<
	
clean:
	rm -fr *.o  go
