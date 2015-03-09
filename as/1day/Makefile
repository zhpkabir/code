TARGET=$(basename $(shell ls *.s))

$(TARGET):%:%.o
	@ld   -m elf_i386 -dynamic-linker /lib/ld-linux.so.2 -lc $< -o $@
	@echo LD 	$@
	@rm -fr *.o

%.o:%.s
	@as --32 -o $@  $<
	@echo AS	$@
	
clean:
	@rm -fr $(TARGET) 
