#include "fun.h"

void Menu_Display()
{
    printf("%s%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",cc_clear,set_xy(7,20),red,cc_close);
    printf("%s%s☆%s%s       1. 测试（汉译英）%s       %s☆%s\n",set_xy(8,20),red,cc_close,blue,cc_close,red,cc_close);
    printf("%s%s☆%s%s       2. 测试（英译汉）%s       %s☆%s\n",set_xy(9,20),red,cc_close,blue,cc_close,red,cc_close);
    printf("%s%s☆%s%s       3. 查看学习进度%s         %s☆%s\n",set_xy(10,20),red,cc_close,blue,cc_close,red,cc_close);
    printf("%s%s☆%s%s       4. 录入新词汇组%s         %s☆%s\n",set_xy(11,20),red,cc_close,blue,cc_close,red,cc_close);
    printf("%s%s☆%s%s       5. 删除词汇组%s           %s☆%s\n",set_xy(12,20),red,cc_close,blue,cc_close,red,cc_close);
    printf("%s%s☆%s%s       6. 导        入%s         %s☆%s\n",set_xy(13,20),red,cc_close,blue,cc_close,red,cc_close);
    printf("%s%s☆%s%s       7. 退        出%s         %s☆%s\n",set_xy(14,20),red,cc_close,blue,cc_close,red,cc_close);
    printf("%s%s☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆ ☆%s\n",set_xy(15,20),red,cc_close);

}

