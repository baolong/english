#include <stdio.h>
#include "fun.h"

int main(void)  
{
    int a,b;
    Init();
   while(1)
    {
        Menu_Display();
        printf("%d %d %d %d %d %d\n",sum_of_list,sum_of_words[0],sum_of_words[1],\
            sum_of_words[2],sum_of_words[3],sum_of_words[4]);
        for (a=0;a<=sum_of_list;a++)
        {

            printf("List %d\n",a);
            for (b=0;b<=sum_of_words[a];b++)
            {
                printf("%s %s\n",En[a][b],Ch[a][b]);
            }
            printf("\n");
        }
        getchar();
    }
//    Save();
//    printf("%d %d\n",sum_of_list,sum_of_words[0]);
//    printf("%s %s\n",En[0][0],En[0][1]);
    return 0;
}  

