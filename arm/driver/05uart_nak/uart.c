#include "common.h"
#include "regs.h"
#include <stdarg.h>

#define TRAN_BUSY while(!(UTRSTAT0 & 2))
#define RECV_BUSY while(!(UTRSTAT0 & 1))

void uart_init(void)
{
	GPACON &= ~(0xff);
	GPACON |= 0x22;

	ULCON0 = 3;//8N1
	UCON0 |= (1 << 2) | (1);//polling
	UFCON0 = 0;
	UMCON0 = 0;

	UBRDIV0 = 34;
	UDIVSLOT0 = 0xdfdd;//115200
}

void uputchar(char c)
{
	TRAN_BUSY;
	UTXH0 = c;
}

char ugetchar(void)
{
	RECV_BUSY;
	return URXH0;
}

void _uputs(char *buf)
{
	while(*buf != '\0'){
		uputchar(*buf);
		if(*buf == '\n')	
			uputchar('\r');
		buf++;
	}
}

void uputs(char *buf)
{
	_uputs(buf);
	uputchar('\n');
	uputchar('\r');
}

char *ugets(char *buf)
{
	char c;
	char *save = buf;

	while((c = ugetchar()) != '\r'){
		*buf = c;
		uputchar(c);
		buf++;	
	}
	*buf = '\0';
	uputchar('\n');
	uputchar('\r');

	return save;
}

//12345 1234 123 12  1
//buf   buf  buf buf buf{'1', 0}
//buf   buf  buf buf{1, 2, 0}
void itoa(unsigned int n, char buf[])
{
	int i;

	if(n < 10){
		buf[0] = n + '0';
		buf[1] = '\0';
		return;
	}
	itoa(n / 10, buf);
	for(i = 0; buf[i] != '\0'; i++)
		;
	buf[i] = (n % 10) + '0';
	buf[i + 1] = '\0';
}

void xtoa(unsigned int n, char buf[])
{
	int i;

	if(n < 16){
		if(n < 10)
			buf[0] = n + '0';
		else
			buf[0] = n - 10 + 'a';
		buf[1] = '\0';
		return;
	}		
	xtoa(n / 16, buf);
	for(i = 0; buf[i] != '\0'; i++)
		;
	if((n % 16) < 10)
		buf[i] = (n % 16) + '0';
	else
		buf[i] = (n % 16) - 10 + 'a';
	buf[i + 1] = '\0';
}

#if 0
printf("abcd %d %c %s %x %%\n", 10, 'a', "dfsf", 0x1200);
va_list 
va_start
va_end
va_arg(ap, type)
#endif
int uprintf(const char *fmt, ...)
{
	int count = 0;
	char c;
	char *s;
	int n;
	char buf[65];
	va_list ap;
	
	va_start(ap, fmt);
	while(*fmt != '\0'){
		if(*fmt == '%'){
			fmt++;
			switch(*fmt){
				case 'd':
					n = va_arg(ap, int);
					if(n < 0){
						uputchar('-');
						n = -n;
					}	
					itoa(n, buf);
					_uputs(buf);
					break;		
				case 'c':
					c = va_arg(ap, int);
					uputchar(c);
					break;
				case 'x':
					n = va_arg(ap, int);
					xtoa(n, buf);
					_uputs(buf);
					break;
				case 's':
					s = va_arg(ap, char *);
					_uputs(s);
					break;
				case '%':
					uputchar('%');
					break;
				default:
					break;
			}	
		}else{
			uputchar(*fmt);
			if(*fmt == '\n')
				uputchar('\r');
		}
		fmt++;
	}

	va_end(ap);

	return count;
}
