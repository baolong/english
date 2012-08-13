#include <stdio.h>
#include <stdio.h>
#include <termios.h>  
#include <unistd.h>  
#include <fcntl.h>
#include "head.h"
#include "keyboard.h"

int kbhit(void)  
{  
    struct termios oldt, newt;  
    int ch;  
    int oldf;  
    tcgetattr(STDIN_FILENO, &oldt);  
    newt = oldt;  
    newt.c_lflag &= ~(ICANON | ECHO);  
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);  
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);  
    ch = getchar();  
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF)  
    {  
        ungetc(ch, stdin);  
        return 1;  
    }  
    return 0;  
}

int check_kb(void)  
{
    int a=-1,b=-1;
    while(!kbhit());
    if ((b = getchar()) == 27)
    {
        getchar();
        a = getchar();
        printf("%s%s%s",move_left(10),cc_clear_line,cc_close);
        return a;
    }
    printf("%s%s%s",move_left(10),cc_clear_line,cc_close);
    return b;  
}  

