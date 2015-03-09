#include "common.h"
#include "regs.h"

int main(int argc, char *argv[])
{
	button_init();

	while(1){
		switch(GPNDAT & 0x3f){
			case 0x3e:
				printf("button 0\n");
				break;
			case 0x3d:
				printf("button 1\n");
				break;
			case 0x3b:
				printf("button 2\n");
				break;
			case 0x37:
				printf("button 3\n");
				break;
			case 0x2f:
				printf("button 4\n");
				break;
			case 0x1f:
				printf("button 5\n");
				break;
			default:
				break;

		}
	}

	return 0;
}
