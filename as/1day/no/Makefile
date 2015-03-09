TARGET=$(basename $(shell ls *.s))

$(TARGET):%:%.o
	@ld  -O2 -m elf_i386 $< -o $@
	@echo "LD           $@"
	@strip 				$@
	@echo "STRIP        $@"
	@rm -fr *.o

%.o:%.s
	@as --32 -o $@  $<
	@echo "AS           $@"
	
clean:
	@rm -fr $(TARGET) 
