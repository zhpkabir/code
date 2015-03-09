/**************************************
UART原理图参考S3C6410手册P1081
UART的硬件电路参考开发板原理图
UART配置的基本步骤：
	1、参考开发板原理图，确定UART所
	使用的管脚，并把这些管脚设置为
	UART专用
	2、由minicom的配置确定串行数据的
	格式和波特率，比如8N1和115200
	3、查看S3C6410手册UART章节，确定
	UART工作原理
	4、通过配置寄存器ULCON0和UCON0来
	确定串行数据的格式，UBRDIV0和
	UDIVSLOT0来确定波特率
	5、把想要发送的数据写到UTXH0中，
	UART接收到的数据自动放到URXH0中
***************************************/

#include "common.h"
#include "regs.h"

/**************************************
在该头文件中包含了一些printf实现时使用的
宏定义，因为这些宏的实现就写在这个头文件
中，所以即使是裸板程序也能包含
***************************************/
#include "stdarg.h"

/**************************************
下面的两个宏定义用于检测上一次的数据是否
发送完成，或者检测本次数据是否收到
***************************************/
#define	TRAN_BUSY while(!(UTRSTAT0 & 2)) 
#define RECV_BUSY while(!(UTRSTAT0 & 1))

void uart_init(void)
{
/****************************************
因为UART的com0使用的发送和接收数据的管脚是
和GPA0、GPA1复用的，所以要把这两个端口设置
为UART所用，参考S3C6410手册P312
****************************************/
	GPACON &= ~(0xff);
	GPACON |= 0x22;

/****************************************
因为配置PC机上的minicom的时候，配置minicom
解释其所收到的数据格式是8N1，即一次数据有8
个有效数据，没有校验位，1个停止位，所以UART
发送数据的格式也必须配置为这个格式，参考
S3C6410手册P1091
****************************************/
	ULCON0 = 3;
	UCON0 |= (1 << 2) | (1);
	UFCON0 = 0;
	UMCON0 = 0;

/****************************************
PC机的minicom捕捉数据的波特率是115200bps
所以UART发送数据的波特率也要设置为115200
参考S3C6410手册P1101
****************************************/
	UBRDIV0 = 34;
	UDIVSLOT0 = 0xdfdd;	
}

/****************************************
使用UART的com0发送一个字符，参考S3C6410
手册P1110
****************************************/
void uputchar(char c)
{
	TRAN_BUSY;
	UTXH0 = c;
}

/****************************************
使用UART的com0接收一个字符，参考S3C6410
手册P1110
****************************************/
char ugetchar(void )
{
	RECV_BUSY;
	return URXH0;
}

void _uputs(char *buf)
{
	while(*buf != '\0'){
		if(*buf == '\n'){
			uputchar('\r');
		}
		uputchar(*buf);
		buf++;
	}
}

void uputs(char *buf)
{
	_uputs(buf);
	uputchar('\r');	
	uputchar('\n');	
}

char *ugets(char *buf)
{
	char *save = buf;

	while((*buf = ugetchar()) != '\r'){
		uputchar(*buf);
		buf++;
	}
	*buf = 0;
	uputchar('\r');
	uputchar('\n');

	return save;
}

void itoa(unsigned int n, char *buf)
{
	int i;

	if(n < 10){
		buf[0] = n + '0';
		buf[1] = '\0';
		return;
	}
	itoa(n / 10, buf);
	for(i = 0; buf[i] != '\0'; i++){
		;
	}
	buf[i] = (n % 10) + '0';
	buf[i + 1] = '\0';
}

/****************************************
upintf中所使用的宏定义都包含在stdarg.h中
va_start() 建立对应关系
va_end()   结束的时候要释放
va_arg()   取出对应特殊字符的参数
****************************************/
int uprintf(const char *fmt, ...)
{
	va_list ap;
	int n;
	char *s;
	char buf[64];
	
	va_start(ap, fmt);		
	while(*fmt != '\0'){
		if(*fmt == '%'){
			fmt++;
			switch(*fmt){
				case 'c':
					n = va_arg(ap, int);	
					uputchar(n);
					break;
				case 's':
					s = va_arg(ap, char *);
					_uputs(s);
					break;
				case 'd':
					n = va_arg(ap, int);
					if(n < 0){
						uputchar('-');
						n = -n;
					}
					itoa(n, buf);
					_uputs(buf);
					break;
				case 'x':
					break;
				case '%':
					break;
				default:
					break;
			}
		}else{
			uputchar(*fmt);
			if(*fmt == '\n'){
				uputchar('\r');
			}
		}
		fmt++;
	}
	va_end(ap);

	return 0;
}










