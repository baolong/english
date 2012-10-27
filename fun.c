#include <stdlib.h>
#include "head.h"
#include "fun.h"
#include "keyboard.h"

char choose_show[8][12] = {"","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m","\033[34m"};
char choose_test_show[31][12];
unsigned int sign = 1,sign_last = 0;
int choose_word_sign = 1,choose_word_sign_last = 0;

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
        fread(Sign_En,sizeof(Sign_En),1,fp);
        fread(Sign_Ch,sizeof(Sign_Ch),1,fp);
        fread(Sign_Test_Count_En,sizeof(Sign_Test_Count_En),1,fp);
        fread(Sign_Test_Count_Ch,sizeof(Sign_Test_Count_Ch),1,fp);
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
    fwrite(Sign_En,sizeof(Sign_En),1,fp);
    fwrite(Sign_Ch,sizeof(Sign_Ch),1,fp);
    fwrite(Sign_Test_Count_En,sizeof(Sign_Test_Count_En),1,fp);
    fwrite(Sign_Test_Count_Ch,sizeof(Sign_Test_Count_Ch),1,fp);
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
    printf("%s%s%sQ:后退 ↑:上翻 ↓:下翻 回车:选择%s",cc_clear,set_xy(6,20),green,cc_close);
    printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(7,20),red,cc_close);
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
    printf("%s%s%sQ:退出 ↑:上翻 ↓:下翻 回车:选择%s",cc_clear,set_xy(6,20),green,cc_close);
    printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",cc_hide,set_xy(7,20),red,cc_close);
    printf("%s%s☆%s%s%s☆%s",set_xy(8,20),\
                red,cc_close,set_xy(8,52),red,cc_close);
    printf("%s%s☆%s%s       %s1. 测试（汉译英）%s       %s%s☆%s",set_xy(9,20),\
                red,cc_close,blue,choose_show[1],cc_close,set_xy(9,52),red,cc_close);
    printf("%s%s☆%s%s       %s2. 测试（英译汉）%s       %s%s☆%s",set_xy(10,20),\
                red,cc_close,blue,choose_show[2],cc_close,set_xy(10,52),red,cc_close);
    printf("%s%s☆%s%s       %s3. 查看学习进度  %s         %s%s☆%s",set_xy(11,20),\
                red,cc_close,blue,choose_show[3],cc_close,set_xy(11,52),red,cc_close);
    printf("%s%s☆%s%s       %s4. 录入新词汇组  %s         %s%s☆%s",set_xy(12,20),\
                red,cc_close,blue,choose_show[4],cc_close,set_xy(12,52),red,cc_close);
    printf("%s%s☆%s%s       %s5. 退        出  %s           %s%s☆%s",set_xy(13,20),\
                red,cc_close,blue,choose_show[5],cc_close,set_xy(13,52),red,cc_close);
    printf("%s%s☆%s%s%s☆%s",set_xy(14,20),\
                red,cc_close,set_xy(14,52),red,cc_close);
    printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(15,20),red,cc_close);
    ASCII = check_kb();
    if (ASCII == 66)             //按下方向键↑
    {
        sign_last = sign;
        sign++;
        if (sign == 6)
          sign = 1;
    }
    else if (ASCII == 65)        //按下方向键↓
    {
        sign_last = sign;
        sign--;
        if (sign ==0)
          sign = 5;
    }
    else if (ASCII == 'q')
    {
        printf("%s%s%s",cc_show,set_xy(0,0),cc_clear);
        Save();
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
            Show_List(2);
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
            printf("%s%s%s",cc_show,set_xy(0,0),cc_clear);
            Save();
            exit(1);
        }
    }
}

void Show_log(int temp,int word_num,int choose_num)
{
    int num = 0,num_=1,num_temp=0;;
    int word_num_temp=1;
    char c[2];
    if (word_num == 4)
        word_num_temp = choose_num;
    else
        word_num_temp = word_num - (4 - choose_num);
    printf("%s%s%s单词%s%s%s%s%s%s的最近10次测试结果:%s",set_xy(21,20),cc_clear_line,green,cc_close,green,cc_contrary,En[temp][word_num_temp],cc_close,green,cc_close);
    printf("%s%s英译汉:%s",set_xy(23,20),cc_clear_line,set_xy(23,28));
    while(num < 10)
    {
        if (Sign_En[temp][word_num_temp][num] == 0)
            break;
        else if (Sign_En[temp][word_num_temp][num] == 1)
            strcpy(c,"√");
        else
            strcpy(c,"X");
        printf(" %s",c);
        num++;
    }
    num_temp = num;
    num = 0;
    printf("%s%s汉译英:%s",set_xy(24,20),cc_clear_line,set_xy(24,28));
    while(num < 10)
    {
        if (Sign_Ch[temp][word_num_temp][num] == 0)
            break;
        else if (Sign_Ch[temp][word_num_temp][num] == 1)
            strcpy(c,"√");
        else
            strcpy(c,"X");
        printf(" %s",c);
        num++;
    }
    if (num > num_temp)
        num_temp = num;
    printf("%s%s",set_xy(22,28),green);
    while(num_ < num_temp)
    {
        printf(" %d",num_);
        num_++;
    }
    if (num_temp != 0)
        printf("%s ↓最后一次测试",green);
    else
        printf("对不起，该单词尚未测试过。");
    printf("%s",cc_close);
}

void Show_(int temp)
{
    char choose_sign[sum_of_words[temp]][9];//={"\033[32m"};
    char choose_word[5][12]={"","\033[34m","\033[34m","\033[34m","\033[34m"};
    choose_word_sign = 1;
    choose_word_sign_last = 0;
    int temp1=0,word_num=1,x=8;
    int num=4;
    printf("%s%s%sQ:后退 ↑:上翻 ↓:下翻%s",cc_clear,set_xy(6,20),green,cc_close); 
    printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",cc_hide,set_xy(7,20),red,cc_close);
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
        while(1)
        {
            strcpy(choose_word[choose_word_sign],"\033[45;37m");
            strcpy(choose_word[choose_word_sign_last],"\033[34m");
            {
                printf("%s%s%s%s☆%s%s%s单词：%s%s  %s%s%s☆%s",set_xy(9,20),cc_clear_line,set_xy(9,20),red,cc_close,\
                    set_xy(9,22),choose_word[1],En[temp][num-3],set_xy(9,50),cc_close,set_xy(9,52),red,cc_close);
                printf("%s%s%s%s☆%s%s%s解释：%s%s  %s%s%s☆%s",set_xy(10,20),cc_clear_line,set_xy(10,20),red,cc_close,\
                            set_xy(10,22),choose_word[1],Ch[temp][num-3],set_xy(10,50),cc_close,set_xy(10,52),red,cc_close);
                if (strcmp(En[temp][num-2],""))
                {
                    printf("%s%s%s%s☆%s%s%s单词：%s%s  %s%s%s☆%s",set_xy(12,20),cc_clear_line,set_xy(12,20),red,cc_close,\
                        set_xy(12,22),choose_word[2],En[temp][num-2],set_xy(12,50),cc_close,set_xy(12,52),red,cc_close);
                    printf("%s%s%s%s☆%s%s%s解释：%s%s  %s%s%s☆%s",set_xy(13,20),cc_clear_line,set_xy(13,20),red,cc_close,\
                        set_xy(13,22),choose_word[2],Ch[temp][num-2],set_xy(13,50),cc_close,set_xy(13,52),red,cc_close);
                }
                if (strcmp(En[temp][num-1],""))
                {
                    printf("%s%s%s%s☆%s%s%s单词：%s%s  %s%s%s☆%s",set_xy(15,20),cc_clear_line,set_xy(15,20),red,cc_close,\
                        set_xy(15,22),choose_word[3],En[temp][num-1],set_xy(15,50),cc_close,set_xy(15,52),red,cc_close);
                    printf("%s%s%s%s☆%s%s%s解释：%s%s  %s%s%s☆%s",set_xy(16,20),cc_clear_line,set_xy(16,20),red,cc_close,\
                        set_xy(16,22),choose_word[3],Ch[temp][num-1],set_xy(16,50),cc_close,set_xy(16,52),red,cc_close);
                }
                if (strcmp(En[temp][num],""))
                {
                    printf("%s%s%s%s☆%s%s%s单词：%s%s  %s%s%s☆%s",set_xy(18,20),cc_clear_line,set_xy(18,20),red,cc_close,\
                        set_xy(18,22),choose_word[4],En[temp][num],set_xy(18,50),cc_close,set_xy(18,52),red,cc_close);
                    printf("%s%s%s%s☆%s%s%s解释：%s%s  %s%s%s☆%s",set_xy(19,20),cc_clear_line,set_xy(19,20),red,cc_close,\
                        set_xy(19,22),choose_word[4],Ch[temp][num],set_xy(19,50),cc_close,set_xy(19,52),red,cc_close);
                }   
            }
            Show_log(temp,num,choose_word_sign);
            temp1 = check_kb();
            if (temp1 == 66)
            {
                if (choose_word_sign<4 && choose_word_sign < sum_of_words[temp]-1)
                {
                    choose_word_sign_last = choose_word_sign;
                    choose_word_sign++;
                }
                else if (choose_word_sign == 4)
                {
                    if (num < sum_of_words[temp]-1)
                        num++;
                }
            }
            if (temp1 == 65)
            {
                if (choose_word_sign>1)
                {
                    choose_word_sign_last = choose_word_sign;
                    choose_word_sign--;
                }
                else if (choose_word_sign == 1 && num > 4)
                    num--;
            }
            else if (temp1 == 'q')
                return;
        }
    }
    else
        return;
    scanf("%d",&x);
}

int Show_List(int menu_choose)
{
    int choose_test_sign=1,choose_test_sign_last = 0;
    unsigned int list_num=1;
    int x=8,a;
    int ASCII = 0;
    for (a=1;a<31;a++)
        strcpy(choose_test_show[a],"\033[34m"); 
    while(1)
    {
        int num = 0;
        x = 8;
        ASCII = 0;
        list_num = 1;
        strcpy(choose_test_show[choose_test_sign],"\033[47;30m");
        strcpy(choose_test_show[choose_test_sign_last],"\033[34m");
        printf("%s%s%sQ:后退 ↑:上翻 ↓:下翻 回车:选择%s",cc_clear,set_xy(6,20),green,cc_close);
        printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(7,20),red,cc_close);
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
                if (sum_of_list > 1)
                {
                    choose_test_sign_last = choose_test_sign;
                    choose_test_sign++;
                    if (choose_test_sign == sum_of_list + 1)
                        choose_test_sign = 1;
                }
            }
            else if (ASCII == 65)        //按下方向键↓
            {
                if (sum_of_list > 1)
                {
                    choose_test_sign_last = choose_test_sign;
                    choose_test_sign--;
                    if (choose_test_sign == 0)
                        choose_test_sign = sum_of_list;
                }
            }
            else if (ASCII == 'q')
                return 0;
            else if (ASCII == 10)        //按下回车
            {
                if (menu_choose == 1)
                    EntoCh(choose_test_sign);
                else if (menu_choose == 2)
                    ChtoEn(choose_test_sign);
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
                getchar();
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
    int temp1=0;
    int x = 8;
    printf("%s%s%s测试中途不能退出%s",cc_clear,set_xy(6,20),green,cc_close);
    printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",cc_hide,set_xy(7,20),red,cc_close);
    while(x < 20)
    {
        printf("%s%s☆%s                               %s%s☆%s",set_xy(x,20),\
        red,cc_close,set_xy(x,52),red,cc_close);
        x++;
    }
    printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(20,20),red,cc_close);
 
    unsigned int Rand_num[100] = {0},num_temp=0;
    char date[40];
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
    printf("%s%s英译汉测试:%s",set_xy(8,22),green,cc_close);
    while(num < sum_of_words[temp]-1)
    {
        int num_sign=1;
        printf("%s%s%2d/%d%s",set_xy(8,47),yellow,num+1,sum_of_words[temp]-1,cc_close);
        printf("%s%s%s%s英文:%s%s%s%s☆%s",set_xy(10,22),cc_clear_line,\
            set_xy(10,22),yellow,En[temp][Rand_num[num]+1],cc_close,set_xy(10,52),red,cc_close);
        printf("%s%s%s%s中文:%s%s%s☆%s%s",set_xy(11,22),cc_clear_line,\
            set_xy(11,22),blue,cc_close,set_xy(11,52),red,cc_close,set_xy(11,27));
        scanf("%s",date);
        if (!strcmp(date,Ch[temp][Rand_num[num]+1]))
        {
            printf("%s%s%s恭喜，答对啦.%s%s%s☆%s",set_xy(19,22),\
                cc_clear_line,set_xy(19,22),cc_close,set_xy(19,52),red,cc_close);
            if (Sign_Test_Count_En[temp] < 10)
                Sign_En[temp][Rand_num[num]+1][Sign_Test_Count_En[temp]] = 1;
            else
            {
                while(num_sign < 10)
                {
                    Sign_En[temp][Rand_num[num]+1][num_sign-1] = \
                        Sign_En[temp][Rand_num[num]+1][num_sign];
                    num_sign++;
                }
                Sign_En[temp][Rand_num[num]+1][9] = 1;
            }
        }
        else
        {
            printf("%s%s%s对不起，答错了。%s%s%s☆%s",set_xy(19,22),\
                cc_clear_line,set_xy(19,22),cc_close,set_xy(19,52),red,cc_close);
            if (Sign_Test_Count_En[temp] < 10)
                Sign_En[temp][Rand_num[num]+1][Sign_Test_Count_En[temp]] = 2; 
            else
            {
                while(num_sign < 10)
                {
                    Sign_En[temp][Rand_num[num]+1][num_sign-1] = \
                        Sign_En[temp][Rand_num[num]+1][num_sign];
                    num_sign++;
                }
                Sign_En[temp][Rand_num[num]+1][9] = 2;
            }
        }
        num++;
    }
    if (Sign_Test_Count_En[temp] < 10)
        Sign_Test_Count_En[temp]++;
    while(1)
    {
        printf("%s",set_xy(21,0));
        if (check_kb() == 10)
        {
            Show_(temp);
            return;
        }
    }
}

void ChtoEn(int temp)
{
    int temp1=0;
    int x = 8;
    printf("%s%s%s测试中途不能退出%s",cc_clear,set_xy(6,20),green,cc_close);
    printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",cc_hide,set_xy(7,20),red,cc_close);
    while(x < 20)
    {
        printf("%s%s☆%s                               %s%s☆%s",set_xy(x,20),\
        red,cc_close,set_xy(x,52),red,cc_close);
        x++;
    }
    printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s",set_xy(20,20),red,cc_close); 
    unsigned int Rand_num[100] = {0},num_temp=0;
    char date[40];
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
    printf("%s%s汉译英测试:%s",set_xy(8,22),green,cc_close);
    while(num < sum_of_words[temp]-1)
    {
        int num_sign=1;
        printf("%s%s%2d/%d%s",set_xy(8,47),yellow,num+1,sum_of_words[temp]-1,cc_close);
        printf("%s%s%s%s中文:%s%s%s%s☆%s",set_xy(10,22),cc_clear_line,\
            set_xy(10,22),yellow,Ch[temp][Rand_num[num]+1],cc_close,set_xy(10,52),red,cc_close);
        printf("%s%s%s%s英文:%s%s%s☆%s%s",set_xy(11,22),cc_clear_line,\
            set_xy(11,22),blue,cc_close,set_xy(11,52),red,cc_close,set_xy(11,27));
        scanf("%s",date);
        if (!strcmp(date,En[temp][Rand_num[num]+1]))
        {
            printf("%s%s%s恭喜，答对啦.%s%s%s☆%s",set_xy(19,22),\
                cc_clear_line,set_xy(19,22),cc_close,set_xy(19,52),red,cc_close);
            if (Sign_Test_Count_Ch[temp] < 10)
                Sign_Ch[temp][Rand_num[num]+1][Sign_Test_Count_Ch[temp]] = 1;
            else
            {
                while(num_sign < 10)
                {
                    Sign_Ch[temp][Rand_num[num]+1][num_sign-1] = \
                        Sign_Ch[temp][Rand_num[num]+1][num_sign];
                    num_sign++;
                }
                Sign_Ch[temp][Rand_num[num]+1][9] = 1;
            }
        }
        else
        {
            printf("%s%s%s对不起，答错了。%s%s%s☆%s",set_xy(19,22),\
                cc_clear_line,set_xy(19,22),cc_close,set_xy(19,52),red,cc_close);
            if (Sign_Test_Count_Ch[temp] < 10)
                Sign_Ch[temp][Rand_num[num]+1][Sign_Test_Count_Ch[temp]] = 2; 
            else
            {
                while(num_sign < 10)
                {
                    Sign_Ch[temp][Rand_num[num]+1][num_sign-1] = \
                        Sign_Ch[temp][Rand_num[num]+1][num_sign];
                    num_sign++;
                }
                Sign_Ch[temp][Rand_num[num]+1][9] = 2;
            }
        }
        num++;
    }
    if (Sign_Test_Count_Ch[temp] < 10)
        Sign_Test_Count_Ch[temp]++;
    while(1)
    {
        printf("%s",set_xy(21,0));
        if (check_kb() == 10)
        {
            Show_(temp);
            return; 
        }
    }
}

