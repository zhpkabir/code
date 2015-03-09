TARGET		:=arm
START_OBJ	:=start.o
OBJS		:=main.o dm9000.o net.o pack.o irq.o unpack.o tftp.o lib.o
BIN		:=$(TARGET).bin
ADDR		:=0x00

CC		:=arm-linux-gcc
LD		:=arm-linux-ld
AS		:=arm-linux-as
OBJCOPY		:=arm-linux-objcopy

##############################################################

all:$(TARGET)
	$(OBJCOPY) -O binary $(TARGET) /tftpboot/$(BIN)
	rm $(TARGET) $(START_OBJ) $(OBJS) -rf

$(TARGET):$(START_OBJ) $(OBJS)
	$(LD) $(START_OBJ) $(OBJS) -o $@ -T ld.lds

%o:%c
	$(CC) -c -o $@ $<
%o:%s
	$(AS) -o $@ $<
