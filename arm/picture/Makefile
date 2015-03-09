TARGET		:=arm
START_OBJ	:=start.o
OBJS		:=clock.o ddr.o nand.o led.o boot.o main.o uart.o irq.o ac97.o lcd.o key.o touch.o wdt.o
BIN		:=$(TARGET).bin
ADDR		:=0x57000000
LDS		:=ld.lds

CC		:=arm-linux-gcc
AS		:=arm-linux-as
LD		:=arm-linux-ld
OBJCOPY		:=arm-linux-objcopy

##########################################

all:$(TARGET)
	$(OBJCOPY) -O binary $(TARGET) /tftpboot/$(BIN)
$(TARGET):$(START_OBJ) $(OBJS)
	$(LD) $(START_OBJ) $(OBJS) -o $(TARGET) -T $(LDS)

##########################################

%o:%c
	$(CC) -c -o $@ $<
%o:%s
	$(AS) -o $@ $<
							     
#########################################

clean:
	rm $(START_OBJ) $(OBJS) $(TARGET) -rf
