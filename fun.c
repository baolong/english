#include <stdlib.h>
#include "head.h"
#include "fun.h"
#include "keyboard.h"

char choose_show[8][12] = {"","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m"};
char choose_test_show[31][12];
int choose_test_sign=1,choose_test_sign_last = 0;
unsigned int sign = 1,sign_last = 0;

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

void Menu_Display()
{
    unsigned int ASCII = 0;
    strcpy(choose_show[sign],"\033[47;30m");
    strcpy(choose_show[sign_last],"\033[34m");
    printf("%s%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",cc_hide,cc_clear,set_xy(7,20),red,cc_close);
    printf("%s%s☆%s%s       %s1. 测试（汉译英）%s       %s☆%s\n",set_xy(8,20),\
                red,cc_close,blue,choose_show[1],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s2. 测试（英译汉）%s       %s☆%s\n",set_xy(9,20),\
                red,cc_close,blue,choose_show[2],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s3. 查看学习进度%s         %s☆%s\n",set_xy(10,20),\
                red,cc_close,blue,choose_show[3],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s4. 录入新词汇组%s         %s☆%s\n",set_xy(11,20),\
                red,cc_close,blue,choose_show[4],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s5. 删除词汇组%s           %s☆%s\n",set_xy(12,20),\
                red,cc_close,blue,choose_show[5],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s6. 导        入%s         %s☆%s\n",set_xy(13,20),\
                red,cc_close,blue,choose_show[6],cc_close,red,cc_close);
    printf("%s%s☆%s%s       %s7. 退        出%s         %s☆%s\n",set_xy(14,20),\
                red,cc_close,blue,choose_show[7],cc_close,red,cc_close);
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
        if (sign == 1)
            En_to_Ch_Show();
        else if (sign == 3)
        {
            Show_();
        }
        else if (sign == 4)
            Add_list();
        else if (sign ==7)
        {
            printf("%s",cc_show);
            exit(1);
        }
    }
}

int En_to_Ch_Show()
{
    unsigned int list_num=0;
    int x=8;
    int ASCII = 0;
    while(1)
    {
        ASCII = 0;
        strcpy(choose_test_show[choose_test_sign],"\033[47;30m");
        strcpy(choose_test_show[choose_test_sign_last],"\033[34m");
        printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",cc_clear,set_xy(7,20),red,cc_close);
        while(list_num < sum_of_list)
        {
            printf("%s%s☆%s%s       %s List %d%s                 %s☆%s\n",set_xy(x++,20),\
                red,cc_close,blue,choose_test_show[list_num],list_num,cc_close,red,cc_close);
            list_num++;
        }
        printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",set_xy(x,20),red,cc_close);
        ASCII = check_kb();
        if (ASCII == 66)             //按下方向键↑
        {
            choose_test_sign_last = choose_test_sign;
            choose_test_sign++;
            if (choose_test_sign== 8)
                choose_test_sign = 1;
        }
        else if (ASCII == 65)        //按下方向键↓
        {
            choose_test_sign_last = choose_test_sign;
            choose_test_sign--;
            if (choose_test_sign ==0)
                choose_test_sign = 7;
        }
        else if (ASCII == 10)        //按下回车
        {
            if (choose_test_sign == 1)
                printf("你好\n");
        }
    }
    return 0;
}

int Add_list()
{
    char temp[40];
    int word_num=0;
    printf("%s",cc_show);
    while(1)
    {
        printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",cc_clear,set_xy(7,20),red,cc_close);
        printf("%s%s☆%s                                 %s☆%s\n",set_xy(8,20),\
            red,cc_close,red,cc_close);
        printf("%s%s☆%s                                 %s☆%s\n",set_xy(9,20),\
            red,cc_close,red,cc_close);
        printf("%s%s☆%s                                 %s☆%s\n",set_xy(10,20),\
            red,cc_close,red,cc_close);
        printf("%s%s☆%s                                 %s☆%s\n",set_xy(11,20),\
            red,cc_close,red,cc_close);
        printf("%s%s☆%s                                 %s☆%s\n",set_xy(12,20),\
            red,cc_close,red,cc_close);
        printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",set_xy(13,20),red,cc_close);
    
        printf("%s%s录入新词汇组：%s",set_xy(8,25),blue,cc_close);
        printf("%s%s单词：%s",set_xy(10,25),blue,cc_close);
        printf("%s%s解释：%s",set_xy(11,25),blue,cc_close);
        printf("%s",set_xy(10,31));
        scanf("%s",temp);
        if (!strcmp(temp,"q"))
        {
            getchar();
            sum_of_words[sum_of_list] = word_num;
            sum_of_list++;
            Save();
            return;
        }
        printf("%s",set_xy(11,31));
        scanf("%s",Ch[sum_of_list][word_num]);
        printf("%s%s",set_xy(14,20),temp);
        strcpy(En[sum_of_list][word_num],temp);
        word_num++;
    }
}

void Show_()
{
    while(1)
    {
        printf("%s%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",cc_hide,cc_clear,set_xy(7,20),red,cc_close);
        printf("%s%s☆%s                               %s☆%s\n",set_xy(8,20),\
                red,cc_close,red,cc_close);
        printf("%s%s☆%s                               %s☆%s\n",set_xy(9,20),\
                red,cc_close,red,cc_close);
        printf("%s%s☆%s                               %s☆%s\n",set_xy(10,20),\
                red,cc_close,red,cc_close);
        printf("%s%s☆%s                               %s☆%s\n",set_xy(11,20),\
                red,cc_close,red,cc_close);
        printf("%s%s☆%s                               %s☆%s\n",set_xy(12,20),\
                red,cc_close,red,cc_close);
        printf("%s%s☆%s                               %s☆%s\n",set_xy(13,20),\
                red,cc_close,red,cc_close);
        printf("%s%s☆%s                               %s☆%s\n",set_xy(14,20),\
                red,cc_close,red,cc_close);
        printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",set_xy(15,20),red,cc_close);
        getchar(); 
    }
    for (a=0;a<=sum_of_list;a++)
    {
        printf("List %d\n",a);
        for (b=0;b<=sum_of_words[a];b++)
        {
            printf("%s %s\n",En[a][b],Ch[a][b]);
        }
        printf("\n");
    }
} 
