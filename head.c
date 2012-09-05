#include "head.h"

int sum_of_list = 0;
int sum_of_words[31]= {0};
char En[30][100][40]={""};
char Ch[30][100][40]={""};
int Sign[30][100][10] = {0};
int Sign_Test_Count_Ch[30]={0};
int Sign_Test_Count_En[30]={0};

//background colours define
char *back_black={"\033[40m"};
char *back_red={"\033[41m"};
char *back_green={"\033[42m"};
char *back_yellow={"\033[43m"};
char *back_blue={"\033[44m"};
char *back_purple={"\033[45m"};
char *back_deep_green={"\033[46m"};
char *back_write={"\033[47m"};

//the word colours define
char *black={"\033[30m"};
char *red={"\033[31m"};
char *green={"\033[32m"};
char *yellow={"\033[33m"};
char *blue={"\033[34m"};
char *purple={"\033[35m"};
char *deep_green={"\033[36m"};
char *white={"\033[37m"};

//control code
char *cc_close={"\033[0m"};  //关闭所有属性
char *cc_highlight={"\033[1m"};  //设置高亮度
char *cc_underline={"\033[4m"};   //下划线
char *cc_flicker={"\033[5m"};    //闪烁
char *cc_contrary={"\033[7m"};  //反显
char *cc_blanking={"\033[8m"};  //消隐

char *cc_clear_line={"\033[K"};
char *cc_clear={"\033[2J"};
char *cc_hide={"\033[?25l"};
char *cc_show={"\033[?25h"};


char* move_up(unsigned int);
char* move_down(unsigned int);
char* move_left(unsigned int);
char* move_right(unsigned int);

//move cursor
char* move_up(unsigned int num)
{
	char *code = malloc(sizeof(char)*8);
    memset(code,0,sizeof(code));
    strcpy(code,"\033[");
    char code1[4];
    sprintf(code1,"%d",num);
    strcat(code,code1);
    strcat(code,"A");
    return code;
}

char* move_down(unsigned int num)
{
    char *code = malloc(sizeof(char)*8);
    memset(code,0,sizeof(code));
    strcpy(code,"\033[");
    char code1[4];
    sprintf(code1,"%d",num);
    strcat(code,code1);
    strcat(code,"B");
    return code;

}

char* move_left(unsigned int num)
{
    char *code = malloc(sizeof(char)*8);
    memset(code,0,sizeof(code));
    strcpy(code,"\033[");
    char code1[4];
    sprintf(code1,"%d",num);
    strcat(code,code1);
    strcat(code,"D");
    return code;
}

char* move_right(unsigned int num)
{
    char *code = malloc(sizeof(char)*8);
    memset(code,0,sizeof(code));
    strcpy(code,"\033[");
    char code1[4];
    sprintf(code1,"%d",num);
    strcat(code,code1);
    strcat(code,"C");
    return code;
}

char* set_xy(unsigned int x,unsigned int y)
{
    char *code = malloc(sizeof(char)*11);
    char code1[7] = {""};
    memset(code,0,sizeof(code));
    strcpy(code,"\033[");
    sprintf(code1,"%d",x);
    strcat(code,code1);
    strcat(code,";");
    sprintf(code1,"%d",y);
    strcat(code,code1);
    strcat(code,"H");
    return code;
}

