#include "BlockGame.h"

int main(void)
{
	intro_game();
	game_control();
	gotoxy(1,box_height+5);
	printf("game ����\n");
	return 0;
}
