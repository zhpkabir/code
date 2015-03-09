
TAGERT :=d.o
all:${TAGERT}
	ld -m elf_i386 -dynamic-linker /lib/ld-linux.so.2  -lc ${TAGERT} -o go
	rm ${TAGERT} -fr

%.o:%.s
	as --32 -o $@ $^

clean:
	rm *.o go -fr
