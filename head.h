#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
char *write={"\033[37m"};

//control code
char *cc_close={"\033[0m"};
char *cc_highlight={"\033[1m"};
char *cc_underline={"\033[4m"};
char *cc_flicker={"\033[5m"};
char *cc_contrary={"\033[7m"};
char *cc_blanking={"\033[8m"};

//move cursor
char *move_up(unsigned int num)
{
	char *code = malloc(sizeof(char)*8);
    menset(code,0,sizeof(code));
    code = {"\033["};
	if (num<10)
    {
        code[5] = 48+num;
        code[6] = 'A';
    }
    else
    {
        code[5] = 48+num/10;
        code[6] = 48+num%10;
        code[7] = 'A';
    }
    return code;
}

char* move_down(unsigned int num)
{
    char code[8]={""};
}

