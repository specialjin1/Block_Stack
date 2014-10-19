#include "BlockGame.h"
char block_shape[4][4] = {"��","��","��","��"};
int block_stack[box_length*2+2] = {0,};
int x,y;
int key;

void intro_game(void)
{
	system("cls");
	printf("��� �ױ� \n\n");
	printf("����� �¿�� ������ �� �����̽�Ű�� ������\n");
	printf("����� ������ �ٴڿ� ���Դϴ�. \n\n");
	printf("�ƹ�Ű�� ������ ������ �����մϴ�. \n");
	getch();
}
void *Input_direct(void *flag)	// ���ڰ��� �־�߸� �۵�
{	// �Է��� ���� ������ ����ϴ� ������ �Լ�
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
	printf("����� ���� : %2d",box_height);
	gotoxy(1,box_height+3);
	printf("�����̽�Ű�� ������ ����� ��������\n");
	printf("�ٴڿ� ���Դϴ�.\n");
	pthread_create(&thread,NULL,Input_direct,NULL);
	pthread_detach(thread);
	while(count < box_height)
	{
		gotoxy(box_length*2+5,4);
		printf("�õ��� Ƚ�� : %2d",count);
		gotoxy(box_length*2+5,5);
		printf("���� ��ϼ� : %2d",max_block());
		x = left_right_move();
		for(y=2;y<box_height+2-block_stack[x];y++)
		{
			move_down(y);
			//key=0;
		}
		gotoxy(x, box_height+1-block_stack[x]);
		printf("��");
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
		printf("��");
		Sleep(100);	// ����� �¿�� �����̴� �ӵ��� ����
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
	printf("��");
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