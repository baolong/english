#include "head.h"
#include "fun.h"
#include "keyboard.h"

char choose[8][12] = {"","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m"};
char choose_test[30][12];
int choose_test_num=0;
unsigned int sign = 1,sign_last = 0;

void Init()
{
    FILE *fp;
    int a = 0;
    for (a=0;a<30;a++)
        strcpy(choose_test[a],"\033[34m");
    if ((fp = fopen("date","rb")) == NULL)
    {
        printf("1\n");
        exit(1);
    }
    a = 0;
    while(!feof(fp))
    {
        fread(En[choose_test_num][a],sizeof(En[choose_test_num][a]),1,fp);
        a++;
    }
    fclose(fp);
}

void Menu_Display()
{
    unsigned int ASCII = 0;
    strcpy(choose[sign],"\033[47;30m");
    strcpy(choose[sign_last],"\033[34m");
    printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",cc_clear,set_xy(7,20),red,cc_close);
    printf("%s%s☆%s%s       %s1. 测试（汉译英）%s       %s☆%s\n",set_xy(8,20),\
                red,cc_close,blue,choose[1],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s2. 测试（英译汉）%s       %s☆%s\n",set_xy(9,20),\
                red,cc_close,blue,choose[2],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s3. 查看学习进度%s         %s☆%s\n",set_xy(10,20),\
                red,cc_close,blue,choose[3],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s4. 录入新词汇组%s         %s☆%s\n",set_xy(11,20),\
                red,cc_close,blue,choose[4],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s5. 删除词汇组%s           %s☆%s\n",set_xy(12,20),\
                red,cc_close,blue,choose[5],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s6. 导        入%s         %s☆%s\n",set_xy(13,20),\
                red,cc_close,blue,choose[6],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s7. 退        出%s         %s☆%s\n",set_xy(14,20),\
                red,cc_close,blue,choose[7],cc_close,red,cc_close);
    printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",set_xy(15,20),red,cc_close);
    ASCII = check_kb();
    if (ASCII == 66)             //按下方向键↑
    {
        sign_last = sign;
        sign++;
        if (sign == 8)
          sign = 1;
    }
    else if (ASCII == 65)        //按下方向键↓
    {
        sign_last = sign;
        sign--;
        if (sign ==0)
          sign = 7;
    }
    else if (ASCII == 10)        //按下回车
    {
       printf("你好。欢迎。");
       getchar();
    }
}

int En_to_Ch()
{
    
}
