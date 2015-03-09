TARGET		:= arm
START_OBJ	:= start.o
OBJS		:= main.o irq.o wdt.o uart.o ddr.o clock.o
BIN		:= $(TARGET).bin
ADDR		:= 0x00000000

CROSS_COMPILE	:= arm-linux-
CC		:= $(CROSS_COMPILE)gcc
AS		:= $(CROSS_COMPILE)as
LD		:= $(CROSS_COMPILE)ld
OBJCOPY		:= $(CROSS_COMPILE)objcopy

-include args.mk
#Q := @

################################################
.PHONY:all
all:$(TARGET)
	$(Q)$(OBJCOPY) -O binary $(TARGET) /tftpboot/$(BIN)
	$(Q)echo OBJCOPY	$(TARGET)
$(TARGET):$(START_OBJ) $(OBJS)
	$(Q)$(LD) $(START_OBJ) $(OBJS) -o $(TARGET) -Ttext $(ADDR)
	$(Q)echo LD		$(TARGET)
%.o:%.c %.h common.h regs.h
	$(Q)$(CC) -c -o $@ $<
	$(Q)echo CC $@
%.o:%.s
	$(Q)$(AS) -o $@ $<
	$(Q)echo AS $@

.PHONY:clean
clean:
	$(Q)rm $(OBJS) $(START_OBJ) $(TARGET) -rf
	$(Q)echo .CLEARN
