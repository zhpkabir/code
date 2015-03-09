#include "common.h"

int main(int argc, char *argv[])
{
	ac97_init();
	wm9714_init();
	
	play_music(0x53000000, 48374828);

	return 0;
}
