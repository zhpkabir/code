#include "ac97.h"
#include "common.h"

unsigned int music_addr;
unsigned int music_len;
unsigned int music_offset;

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
	wm9714_write(0x0c, (0x7 << 8) | (0x7));
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

void __attribute__((interrupt("IRQ"))) do_ac97(void)
{
	if(AC_GLBSTAT & (1 << 21)){
		AC_GLBCTRL |= 1 << 29;//clear int
		//FIFO EMPTY
		AC_PCMDATA = *(unsigned int *)(music_addr + music_offset);
		music_offset += 4;
		if(music_offset > music_len)
			//over
			music_offset = 0;
	}
	clear_int();//clear address0/1
}

void play_music(unsigned int addr, unsigned int len)
{
	music_addr = addr;
	music_len = len;
	music_offset = 0;

	AC_GLBCTRL |= (1 << 12) | (1 << 21);//pio interrupt
	request_irq(36, do_ac97);
	enable_irq();
}
