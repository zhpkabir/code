#include "regs.h"
#include "common.h"

struct{
	unsigned int src_addr;
	unsigned int dst_addr;
	unsigned int next_dma;
	unsigned int control0;
	unsigned int control1;
}next_work;

int sound_index = 0;

void delay(int n);

void ac97_init(void)
{
	sound_index = 0x1f;

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
	if((AC_GLBSTAT & 0x7) == 0x3){
		//uprintf("AC97 init OK!\n");
	}else{
		uprintf("The error status is %d\n", (AC_GLBSTAT & 0x7));
	}
}

void write_wm9714(unsigned int reg, unsigned int val)
{
	AC_CODEC_CMD = (reg << 16) | (val);
	delay(1);
}

void wm9714_init(void)
{
	write_wm9714(0x0c, (0x1f << 8) | (0x1f));
	write_wm9714(0x5c, (1 << 7));
	write_wm9714(0x2a, 1);
	write_wm9714(0x2c, 0xac44);
	write_wm9714(0x1c, (2 << 4) | (2 << 6) | (3 << 11) | (3 << 8));
	write_wm9714(0x04, 0);
	write_wm9714(0x02, 0);
	write_wm9714(0x24, (1 << 4));
	write_wm9714(0x5a, (0 << 6));
	write_wm9714(0x26, 0);
	write_wm9714(0x3c, 0);
	write_wm9714(0x3e, 0);
}

void ac97_dma_init(unsigned int addr, unsigned int len)
{
	next_work.src_addr = addr;
	next_work.dst_addr = (unsigned int)(&AC_PCMDATA);
	next_work.next_dma = (unsigned int)(&next_work);
	next_work.control0 = (1 << 26) | (1 << 25) | (2 << 21) | (2 << 18);
	next_work.control1 = (len + 3) >> 2;

	DMACC0LLI = (unsigned int)(&next_work);

	SDMA_SEL |= 1 << 22;

	DMACC0SrcAddr = addr;
	DMACC0DestAddr = (unsigned int)(&AC_PCMDATA);
	DMACC0Control0 = (1 << 26) | (1 << 25) | (2 << 21) | (2 << 18);
	DMACC0Control1 = (len + 3) >> 2;
	DMACC0Configuration = (1 << 11) | (6 << 6) | (1);
}

void play_music(unsigned int addr, unsigned int len)
{
	ac97_dma_init(addr, len);
	AC_GLBCTRL |= (2 << 12);
	DMACConfiguration |= 1;
}

void delay(int n)
{
	int i, j;

	for(i = 0; i < n; i++){
		for(j = 0; j < 10000; j++){
			;
		}
	}
}

void sound_updown(int n)
{
	if(n == 0){
		sound_index++;
		if(sound_index > 0x1f){
			sound_index = 0x1f;
		}
	}else{
		sound_index--;
		if(sound_index < 0){
			sound_index = 0;	
		}
	}
	write_wm9714(0x0c, (sound_index << 8) | (sound_index));	
}
