#include "ac97.h"
#include "common.h"

void ac97_init(void)
{
	GPDCON = 0x44444;

	AC_GLBCTRL |= 1;
	delay(1);
	AC_GLBCTRL &= ~1;

	AC_GLBCTRL |= 1 << 1;
	delay(1);
	AC_GLBCTRL &= ~(1 << 1);

	AC_GLBCTRL |= 1 << 2;
	delay(1);
	AC_GLBCTRL |= 1 << 3;

	AC_CODEC_CMD |= 1 << 23;
	delay(10);
	if((AC_GLBSTAT & 7) == 3)
		;//printf("AC97 Init Ok!\n");
	else
		;//printf("The Error status: %x\n", AC_GLBSTAT & 7);
}

void wm9714_write(char reg, unsigned int data)
{
	AC_CODEC_CMD = (reg << 16) | data;
	delay(1);
}

void wm9714_init(void)
{
	wm9714_write(0x0c, (0x11 << 8) | (0x11));
	wm9714_write(0x5c, 1 << 7);
	wm9714_write(0x2a, 1);
	wm9714_write(0x2c, 0xac44);//44100HZ
	wm9714_write(0x1c, (2 << 6) | (2 << 4) | (3 << 11) | (3 << 8));
	wm9714_write(0x04, 0);
	wm9714_write(0x02, 0);
	wm9714_write(0x24, 1 << 4);//insert headphone
	wm9714_write(0x5a, 0 << 6);
	
	//power
	wm9714_write(0x26, 0);
	wm9714_write(0x3c, 0);
	wm9714_write(0x3e, 0);
}

void play_music(unsigned int addr, unsigned int len)
{
	AC_GLBCTRL |= (2 << 12);//dma
	ac97_dma_init(addr, len, &AC_PCMDATA);
	enable_dma();
}
