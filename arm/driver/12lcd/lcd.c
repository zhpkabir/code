#include "common.h"
#include "regs.h"
#include "lcd.h"

void lcd_init(void)
{
	GPICON = 0xaaaaaaaa;
	GPJCON = 0xaaaaaa;
	
	GPECON &= ~0xf;
	GPECON |= 1;
	GPEDAT |= 1;

	GPFCON &= ~(0x3 << 28);
	GPFCON |= 1 << 28;
	GPFDAT |= 1 << 14;

	MIFPCON &=~(1 << 3);
	SPCON &= ~3;
	SPCON |= 1;

	VIDCON0 = (14 << 6) | (1 << 4) | (3);
	VIDCON1 = (1 << 6) | (1 << 5);
	VIDTCON0 = (1 << 16) | (1 << 8) | (9);	
	VIDTCON1 = (1 << 16) | (1 << 8) | (40);
	VIDTCON2 = (271 << 11) | (479);
	
	//window0
#ifdef BPP565
	WINCON0 = (1 << 16) | (5 << 2) | (1);
	VIDOSD0C = (480 * 272) >> 1;
#else
	WINCON0 = (11 << 2) | (1);
	VIDOSD0C = (480 * 272);
#endif
	VIDOSD0A = 0;
	VIDOSD0B = (479 << 11) | (271);
	VIDW00ADD0B0 = FRAMEBUFFER;
	VIDW00ADD1B0 = FRAMEBUFFER + VIDOSD0C * 4;
}

void draw_point(int x, int y, int red, int green, int blue)
{
#ifdef BPP565
	unsigned short *v = (void *)FRAMEBUFFER;
	
	*(v + y * 480 + x) = (red << 11) | (green << 5) | (blue);
#else
	unsigned int *v = (void *)FRAMEBUFFER;

	*(v + y * 480 + x) = (red << 16) | (green << 8) | (blue);
#endif
}

