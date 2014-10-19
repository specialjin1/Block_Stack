#include "BlockGame.h"
char block_shape[4][4] = {"◇","☆","○","□"};
int block_stack[box_length*2+2] = {0,};
int x,y;
int key;

void intro_game(void)
{
	system("cls");
	printf("블록 쌓기 \n\n");
	printf("블록이 좌우로 움직일 떄 스페이스키를 누르면\n");
	printf("블록이 떨어져 바닥에 쌓입니다. \n\n");
	printf("아무키나 누르면 게임을 시작합니다. \n");
	getch();
}
void *Input_direct(void *flag)	// 인자값이 있어야만 작동
{	// 입력을 받을 때까지 대기하는 스레드 함수
	while(1)
		key = getch();
	return NULL;
}
void game_control(void)
{
	int count=1,status;
	pthread_t thread;
	
	system("cls");
	draw_rectangle(box_length, box_height);
	gotoxy(box_length*2+5,3);
	printf("블록의 개수 : %2d",box_height);
	gotoxy(1,box_height+3);
	printf("스페이스키를 누르면 블록이 떨어지고\n");
	printf("바닥에 쌓입니다.\n");
	pthread_create(&thread,NULL,Input_direct,NULL);
	pthread_detach(thread);
	while(count < box_height)
	{
		gotoxy(box_length*2+5,4);
		printf("시도한 횟수 : %2d",count);
		gotoxy(box_length*2+5,5);
		printf("싸인 블록수 : %2d",max_block());
		x = left_right_move();
		for(y=2;y<box_height+2-block_stack[x];y++)
		{
			move_down(y);
			//key=0;
		}
		gotoxy(x, box_height+1-block_stack[x]);
		printf("□");
		block_stack[x]+=1;
		count++;
		//getch();
	}
}
void gotoxy(int x, int y)
{
	COORD Pos = {x-1,y-1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int left_right_move(void)
{
	int x=3, y=2, temp=2;
	do
	{
		x+=temp;
		if(x>(box_length*2))
			temp-=2;
		if(x<3)
		{
			x=3;
			temp=2;
		}

		gotoxy(x,y);
		printf("□");
		Sleep(100);	// 블록이 좌우로 움직이는 속도를 조절
		gotoxy(x,y);
		printf("  ");
	} while(!key);
	return x;
}
void move_down(int y)
{	
	if(key == MY_LEFT) {
		x-=2;
		if(x<3) x=3;
		if(y>15-block_stack[x]) x+=2;
		key=0;
	}
	else if( key == MY_RIGHT) {
		x+=2;
		if(x>box_length*2) x = box_length*2+1;
		if(y>15-block_stack[x]) x-=2;
		key=0;
	}
	else key=0;
	gotoxy(x,y);
	printf("□");
	Sleep(50);
	gotoxy(x,y);
	printf("  ");
	Sleep(50);
	//key=0;
}
void draw_rectangle(int c, int r)
{
	int i, j;
	unsigned char a=0xa6, b[7];
	for(i=1;i<7;i++)
		b[i]=0xa0+i;
	printf("%c%c", a, b[3]);
	for(i=0;i<c;i++)
		printf("%c%c", a, b[1]);
	printf("%c%c", a, b[4]);
	printf("\n");
	for(i=0;i<r;i++)
	{
		printf("%c%c", a, b[2]);
		for(j=0;j<c;j++)
			printf("  ");
		printf("%c%c", a, b[2]);
		printf("\n");
	}
	printf("%c%c", a, b[6]);
	for(i=0;i<c;i++)
		printf("%c%c", a, b[1]);
	printf("%c%c", a, b[5]);
	printf("\n");
}
int max_block(void)
{
	int i, max=0;
	for(i=1;i<=box_height*2+1;i++)
	{
		if(max<=block_stack[i])
			max = block_stack[i];
	}
	return max;
}