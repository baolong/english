#include <stdlib.h>
#include "head.h"
#include "fun.h"
#include "keyboard.h"

char choose_show[8][12] = {"","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m"};
char choose_test_show[31][12];
unsigned int sign = 1,sign_last = 0;
int choose_test_sign=1,choose_test_sign_last = 0;

void Init()
{
    FILE *fp;
    int a = 0;
    unsigned int num_list=0,num_word=0;
    size_t word_len=0;
    for (a=1;a<31;a++)
        strcpy(choose_test_show[a],"\033[34m");
    if ((fp = fopen("date","rb")) != NULL)
    {
        fread(&sum_of_list,sizeof(sum_of_list),1,fp);
        fread(sum_of_words,sizeof(sum_of_words),1,fp);
        while(num_list <= sum_of_list)
        {
            num_word=0;
            while(num_word <= sum_of_words[num_list])
            {
                fread(&word_len,sizeof(word_len),1,fp);
                fread(En[num_list][num_word],word_len,1,fp);
                fread(&word_len,sizeof(word_len),1,fp);
                fread(Ch[num_list][num_word],word_len,1,fp);

                num_word++;
            }
            num_list++;
        }
        fclose(fp);
    }
}

void Save()
{
    FILE *fp;
    size_t word_len=0;
    unsigned int num_list=0,num_word=0;
    if ((fp = fopen("date","wb")) == NULL)
    {
        printf("error\n");
        exit(1);
    }
    fwrite(&sum_of_list,sizeof(sum_of_list),1,fp);
    fwrite(sum_of_words,sizeof(sum_of_words),1,fp);
    while(num_list <= sum_of_list)
    {
        num_word=0;
        while(num_word <= sum_of_words[num_list])
        {
            word_len = strlen(En[num_list][num_word]);
            fwrite(&word_len,sizeof(size_t),1,fp);
            fwrite(En[num_list][num_word],word_len,1,fp);
            word_len = strlen(Ch[num_list][num_word]);
            fwrite(&word_len,sizeof(size_t),1,fp);
            fwrite(Ch[num_list][num_word],word_len,1,fp);

            num_word++;
        }
        num_list++;
    }
    fclose(fp);
}

void Show_Frame()
{
    int x = 8;
    printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",cc_clear,set_xy(7,20),red,cc_close);
    while(x < 15)
    {
        printf("%s%s☆%s                               %s%s☆%s",set_xy(x,20),\
        red,cc_close,set_xy(x,52),red,cc_close);
        x++;
    }
    printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(15,20),red,cc_close);
 
}

void Menu_Display()
{
    unsigned int ASCII = 0;
    strcpy(choose_show[sign],"\033[47;30m");
    strcpy(choose_show[sign_last],"\033[34m");
    printf("%s%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",cc_hide,cc_clear,set_xy(7,20),red,cc_close);
    printf("%s%s☆%s%s       %s1. 测试（汉译英）%s       %s%s☆%s",set_xy(8,20),\
                red,cc_close,blue,choose_show[1],cc_close,set_xy(8,52),red,cc_close);
    printf("%s%s☆%s%s       %s2. 测试（英译汉）%s       %s%s☆%s",set_xy(9,20),\
                red,cc_close,blue,choose_show[2],cc_close,set_xy(9,52),red,cc_close);
    printf("%s%s☆%s%s       %s3. 查看学习进度%s         %s%s☆%s",set_xy(10,20),\
                red,cc_close,blue,choose_show[3],cc_close,set_xy(10,52),red,cc_close);
    printf("%s%s☆%s%s       %s4. 录入新词汇组%s         %s%s☆%s",set_xy(11,20),\
                red,cc_close,blue,choose_show[4],cc_close,set_xy(11,52),red,cc_close);
    printf("%s%s☆%s%s       %s5. 删除词汇组%s           %s%s☆%s",set_xy(12,20),\
                red,cc_close,blue,choose_show[5],cc_close,set_xy(12,52),red,cc_close);
    printf("%s%s☆%s%s       %s6. 导        入%s         %s%s☆%s",set_xy(13,20),\
                red,cc_close,blue,choose_show[6],cc_close,set_xy(13,52),red,cc_close);
    printf("%s%s☆%s%s       %s7. 退        出%s         %s%s☆%s",set_xy(14,20),\
                red,cc_close,blue,choose_show[7],cc_close,set_xy(14,52),red,cc_close);
    printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(15,20),red,cc_close);
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
    else if (ASCII == 'q')
    {
        printf("%s%s%s",cc_show,set_xy(0,0),cc_clear);
        exit(1);
    }
    else if (ASCII == 10)        //按下回车
    {
        if (sign == 1)
        {
            Show_List(1);
        }
        else if(sign == 2)
        {
            ;
        }
        else if (sign == 3)
        {
            Show_List(3);
        }
        else if (sign == 4)
        {
            Add_list();
        }
        else if (sign == 5)
        {
            ;
        }
        else if (sign == 6)
        {
            ;
        }
        else if (sign ==7)
        {
            printf("%s%s%s",cc_show,set_xy(0,0),cc_clear);
            exit(1);
        }
    }
}

void Show_(int temp)
{
    int temp1=0,word_num=1,x=8;
    char a;
    int num=1;
    printf("%s%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",cc_hide,cc_clear,set_xy(7,20),red,cc_close);
    while(x < 20)
    {
        printf("%s%s☆%s                               %s%s☆%s",set_xy(x,20),\
        red,cc_close,set_xy(x,52),red,cc_close);
        x++;
    }
    printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(20,20),red,cc_close);
    x = 9;
    if (temp != 0)
    {
        printf("%s%s该列表单词数：%d ↑:上翻 ↓:下翻%s",set_xy(8,22),yellow,sum_of_words[temp]-1,cc_close);
//        while(word_num < sum_of_words[temp])
        while(1)
        {
            printf("%s%s%s%s☆%s%s%s单词：%s%s%s%s☆%s",set_xy(9,20),cc_clear_line,set_xy(9,20),red,cc_close,\
                        set_xy(9,22),blue,En[temp][num],cc_close,set_xy(9,52),red,cc_close);
            printf("%s%s%s%s☆%s%s%s解释：%s%s%s%s☆%s",set_xy(10,20),cc_clear_line,set_xy(10,20),red,cc_close,\
                        set_xy(10,22),green,Ch[temp][num],cc_close,set_xy(10,52),red,cc_close);
            if (strcmp(En[temp][num+1],""))
            {
                printf("%s%s%s%s☆%s%s%s单词：%s%s%s%s☆%s",set_xy(12,20),cc_clear_line,set_xy(12,20),red,cc_close,\
                        set_xy(12,22),blue,En[temp][num+1],cc_close,set_xy(12,52),red,cc_close);
                printf("%s%s%s%s☆%s%s%s解释：%s%s%s%s☆%s",set_xy(13,20),cc_clear_line,set_xy(13,20),red,cc_close,\
                        set_xy(13,22),green,Ch[temp][num+1],cc_close,set_xy(13,52),red,cc_close);

            }
            if (strcmp(En[temp][num+2],""))
            {
                printf("%s%s%s%s☆%s%s%s单词：%s%s%s%s☆%s",set_xy(15,20),cc_clear_line,set_xy(15,20),red,cc_close,\
                        set_xy(15,22),blue,En[temp][num+2],cc_close,set_xy(15,52),red,cc_close);
                printf("%s%s%s%s☆%s%s%s解释：%s%s%s%s☆%s",set_xy(16,20),cc_clear_line,set_xy(16,20),red,cc_close,\
                        set_xy(16,22),green,Ch[temp][num+2],cc_close,set_xy(16,52),red,cc_close);
            }
            if (strcmp(En[temp][num+3],""))
            {
                printf("%s%s%s%s☆%s%s%s单词：%s%s%s%s☆%s",set_xy(18,20),cc_clear_line,set_xy(18,20),red,cc_close,\
                        set_xy(18,22),blue,En[temp][num+3],cc_close,set_xy(18,52),red,cc_close);
                printf("%s%s%s%s☆%s%s%s解释：%s%s%s%s☆%s",set_xy(19,20),cc_clear_line,set_xy(19,20),red,cc_close,\
                        set_xy(19,22),green,Ch[temp][num+3],cc_close,set_xy(19,52),red,cc_close);
            }
            temp1 = check_kb();
            if (temp1 == 66)
            {
                if ((num+3) < sum_of_words[temp]-1)
                  num++;
            }
            else if (temp1 == 65)
            {
                if (num > 1)
                  num--;
            }
            else if (temp1 == 'q')
              return;
        }
    }
    else
        return;
    scanf("%s",&a);

}

int Show_List(int menu_choose)
{
    unsigned int list_num=1;
    int x=8;
    int ASCII = 0;
    while(1)
    {
        int num = 0;
        x = 8;
        ASCII = 0;
        list_num = 1;
        strcpy(choose_test_show[choose_test_sign],"\033[47;30m");
        strcpy(choose_test_show[choose_test_sign_last],"\033[34m");
        printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",cc_clear,set_xy(7,20),red,cc_close);
        if (sum_of_list == 0)
        {
            while(num < 8)
            {
                printf("%s%s☆%s                               %s%s☆%s",set_xy(x,20),\
                    red,cc_close,set_xy(x,52),red,cc_close);
                num++;
                x++;
            }
            printf("%s%s列表为空！%s",set_xy(11,30),blue,cc_close);
            printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(x,20),red,cc_close); 
            getchar();
            return 0;
        }
        else
        {
            while(list_num <= sum_of_list)
            {
                printf("%s%s☆%s%s       %s List %d%s                 %s%s☆%s",set_xy(x,20),\
                    red,cc_close,blue,choose_test_show[list_num],list_num,cc_close,set_xy(x,52),red,cc_close);
                list_num++;
                x++;
            }
            printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(x,20),red,cc_close);
            ASCII = check_kb();
            if (ASCII == 66)             //按下方向键↑
            {
                choose_test_sign_last = choose_test_sign;
                choose_test_sign++;
                if (choose_test_sign == sum_of_list + 1)
                    choose_test_sign = 1;
            }
            else if (ASCII == 65)        //按下方向键↓
            {
                choose_test_sign_last = choose_test_sign;
                choose_test_sign--;
                if (choose_test_sign == 0)
                    choose_test_sign = sum_of_list;
            }
            else if (ASCII == 'q')
                return 0;
            else if (ASCII == 10)        //按下回车
            {
                if (menu_choose == 1)
                    EntoCh(choose_test_sign);
                else if (menu_choose == 2);
                else if (menu_choose == 3)
                    Show_(choose_test_sign);
                else if (menu_choose == 5);
            }
        }
    }
    return 0;
}

int Add_list()
{
    char temp[40];
    int word_num=1;
    printf("%s",cc_show);
    while(1)
    {
        Show_Frame();  
        printf("%s%s录入新词汇组：%s",set_xy(8,25),blue,cc_close);
        printf("%s%s单词：%s",set_xy(10,25),blue,cc_close);
        printf("%s%s解释：%s",set_xy(11,25),blue,cc_close);
        printf("%s",set_xy(10,31));
        scanf("%s",temp);
        if (!strcmp(temp,"q"))
        {
            if (word_num != 1)
            {
                getchar();
                sum_of_words[sum_of_list+1] = word_num;
                sum_of_list++;
                Save();
                return;
            }
            else
            {
                getchar();
                return;
            }
        }
        printf("%s",set_xy(11,31));
        scanf("%s",Ch[sum_of_list+1][word_num]);
        printf("%s%s",set_xy(14,20),temp);
        strcpy(En[sum_of_list+1][word_num],temp);
        word_num++;
    }
}

void EntoCh(int temp)
{
    unsigned int Rand_num[100] = {0},num_temp=0;
    int num=0,sign=0;
    srand((int)time(0));
    while(num < sum_of_words[temp]-1)
    {
        sign = 0;
        int a=0;
        num_temp = rand()%(sum_of_words[temp]-1);
        while(a < num)
        {
            if (num_temp == Rand_num[a])
            {
                sign++;
                break;
            }
            a++;
        }
        if (sign == 0)
        {
            Rand_num[num] = num_temp;
            num++;
        }
    }
    num = 0;
    printf("\n单词数:%d",sum_of_words[temp]-1);
    while(num < sum_of_words[temp]-1)
    {
        if (num%30 == 0)
          printf("\n");
        printf("%d ",Rand_num[num]);
        num++;
    }
    getchar();
}
