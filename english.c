#include <stdio.h>
#include "fun.h"

int main(void)  
{
    Init();
    printf("%d %d %d %d %d %d\n",sum_of_list,sum_of_words[0],sum_of_words[1],sum_of_words[2],sum_of_words[3],sum_of_words[4]);
//    Save();
   while(1)
    {
        Menu_Display();
    }
//    Save();
//    printf("%d %d\n",sum_of_list,sum_of_words[0]);
//    printf("%s %s\n",En[0][0],En[0][1]);
    return 0;
}  

