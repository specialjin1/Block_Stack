#include "BlockGame.h"

int main(void)
{
	srand(time(NULL));
	intro_game();
	game_control();
	gotoxy(1,box_height+5);
	printf("game ����\n");
	return 0;
}
