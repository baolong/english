#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef _HEAD_H
#define _HEAD_H

extern unsigned int sum_of_list;
extern unsigned int sum_of_words[];
extern char En[30][100][40];
extern char Ch[30][100][40];

//background colours define
extern char *back_black;
extern char *back_red;
extern char *back_green;
extern char *back_yellow;
extern char *back_blue;
extern char *back_purple;
extern char *back_deep_green;
extern char *back_write;

//the word colours define
extern char *black;
extern char *red;
extern char *green;
extern char *yellow;
extern char *blue;
extern char *purple;
extern char *deep_green;
extern char *white;

//control code
extern char *cc_close;  //关闭所有属性
extern char *cc_highlight;  //设置高亮度
extern char *cc_underline;   //下划线
extern char *cc_flicker;    //闪烁
extern char *cc_contrary;  //反显
extern char *cc_blanking;  //消隐

extern char *cc_clear_line;
extern char *cc_clear;

char* move_up(unsigned int);
char* move_down(unsigned int);
char* move_left(unsigned int);
char* move_right(unsigned int);
char* set_xy(unsigned int ,unsigned int);
#endif
