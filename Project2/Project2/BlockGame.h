#ifndef _BLOCKGAME_H__
#define _BLOCKGAME_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <pthread.h>

#define box_length 15
#define box_height 15
#define MY_LEFT 75
#define MY_RIGHT 77
#define MY_SPACE 32

void intro_game(void);
void game_control(void);
void gotoxy(int x, int y);
int left_right_move(void);
void move_down(int y);
void draw_rectangle(int c, int r);
int max_block(void);
void move_arrow_key(char key, int *x1);
#endif