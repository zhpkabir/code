#include "common.h"
#include "regs.h"

#ifdef BPP565
	#define BYTE_BPP	2
#else
	#define BYTE_BPP	4
#endif

void gpio_init(void);
void common_init(void);
void window0_init(void);
void window1_init(void);

int pic_index = 0; 
int flow_index = 0;
int auto_flow_flag = 0;

void lcd_init(void)
{
	pic_index = 0;
	flow_index = 0;
	auto_flow_flag = 1;

	gpio_init();

	common_init();

	window0_init();
	window1_init();
}

void draw_point(int x, int y, int red, int green, int blue)
{
#ifdef BPP565
	unsigned short *p = (void *)FRAMEBUFFER;
	*(p + WIDE * y + x) = (red << 11) | (green << 5) | (blue);
#else
	unsigned int *p = (void *)FRAMEBUFFER;
	*(p + WIDE * y + x) = (red << 16) | (green << 8) | (blue);
#endif
}

void gpio_init(void)
{
	GPICON = 0xaaaaaaaa;
	GPJCON = 0xaaaaaa;
	GPECON &= ~(0xf);
	GPECON |= 1;
	GPEDAT |= 1;
	GPFCON &= ~(3 << 28);
	GPFCON |= 1 << 28;
	GPFDAT |= 1 << 14;
}

void common_init(void)
{
	MIFPCON &= ~(1 << 3);
	SPCON &= ~(3);
	SPCON |= 1;

	VIDCON0 = (14 << 6) | (1 << 4) | (1 << 1) | (1 << 0);
	VIDCON1 = (1 << 6) | (1 << 5);
	VIDTCON0 = (1 << 16) | (1 << 8) | (9);
	VIDTCON1 = (1 << 16) | (1 << 8) | (40);
	VIDTCON2 = (271 << 11) | (479);
}

void window0_init(void)
{
#ifdef BPP565
	WINCON0 = (1 << 16) | (5 << 2) | (1);
	VIDOSD0C = (WIDE * LONG) >> 1;
	VIDW00ADD1B0 = FRAMEBUFFER + WIDE * LONG * BYTE_BPP;
#else
	WINCON0 = (0xb << 2) | (1);
	VIDOSD0C = WIDE * LONG;
	VIDW00ADD1B0 = FRAMEBUFFER + WIDE * LONG * BYTE_BPP;
#endif
	VIDOSD0A = 0;
	VIDOSD0B = (479 << 11) | (271);
	VIDW00ADD0B0 = FRAMEBUFFER;
}

void window1_init(void)
{
#ifdef BPP565
	WINCON1 = 1 | (0x5 << 2) | (1 << 16);           /*启动窗口1，显示图片格式为565，半字交换*/
        VIDOSD1D = (100 * 40) >> 1;                    /*要显示的实际的大小（单位是字）*/
        VIDW01ADD2 = (100*BYTE_BPP) | ((380*BYTE_BPP) << 13);/*[0:12]表示实际窗口的宽度,[13:25]offsize的大小(四字节对奇),字节为单位*/
#else
	WINCON1 = (0xb << 2) | (1);
        VIDOSD1D = (190 * 50);                        /*要显示的实际的大小（单位是字）*/
        VIDW01ADD2 = (190*BYTE_BPP) | ((290*BYTE_BPP) << 13);/*[0:12]表示实际窗口的宽度,[13:25]offsize的大小(四字节对奇),字节为单位*/
#endif
        VIDOSD1A = (290 << 11 | 222);                             /*要显示的实际位置*/
        VIDOSD1B = (479 << 11) | 271;                           /*低11位是众坐标，其他为横坐标*/

        VIDOSD1C = (0Xfff << 12);                               /*WIN1的透明度0为全透明，15为不透明*/

        VIDW01ADD0B0 = FRAMEBUFFER1 + (222 * 480 + 290) * 4; 		/*要显示的图形部分的首地址*/
//        VIDW01ADD1B0 = FRAMEBUFFER1 + 480 * 272;              /*存的是图片本来的大小的内存末地址*/

        VIDCON0 |= 1 | (1 << 1);	
}

void change_pic(int n)
{
	static onece = 1;

	if(onece == 1){
		onece = 2;
		return;
	}

	if(n == 1){
		pic_index++;
		flow_index += WIDE * LONG * BYTE_BPP;
		if(pic_index == MAX_NUM){
			pic_index = 0;
			flow_index = 0;
		}
	}else if(n == 0){
		pic_index--;
		flow_index -= WIDE * LONG * BYTE_BPP;
		if(pic_index < 0){
			pic_index = MAX_NUM - 1;
			flow_index = WIDE * LONG * BYTE_BPP * (MAX_NUM - 1);
		}
	}

	VIDW00ADD0B0 = FRAMEBUFFER + pic_index * WIDE * LONG * BYTE_BPP;
	VIDW00ADD1B0 = VIDW00ADD0B0 + WIDE * LONG * BYTE_BPP;
}

void pic_flow(int n)
{
	int i;

	if(n == 1){
		pic_index--;
		for(i = 0; i < LONG; i++){
			flow_index -= WIDE * BYTE_BPP;
			if(flow_index < 0){
				flow_index = WIDE * LONG * BYTE_BPP * MAX_NUM - WIDE * BYTE_BPP;
				pic_index = MAX_NUM - 1;
			}
			VIDW00ADD0B0 = FRAMEBUFFER + flow_index;
			VIDW00ADD1B0 = VIDW00ADD0B0 + WIDE * LONG * BYTE_BPP;
			delay(1);
		}
	}else if(n == 0){
		pic_index++;
		for(i = 0; i < LONG; i++){
			flow_index += WIDE * BYTE_BPP;
			if(flow_index > WIDE * LONG * BYTE_BPP * MAX_NUM){
				flow_index = 0 + WIDE * BYTE_BPP;
				pic_index = 1;
			}
			VIDW00ADD0B0 = FRAMEBUFFER + flow_index;
			VIDW00ADD1B0 = VIDW00ADD0B0 + WIDE * LONG * BYTE_BPP;
			delay(1);
		}
	}
}
