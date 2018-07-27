#include<stdio.h>
int main()
{
    int a = 3;
    //printf的计算顺序为从右往左
    //后置--,在计算之前先保存一份
    printf("%d %d %d\n",a--,a--,a--);//1,2,3
    //前置--：待整个表达式计算完毕后才给出结果，之前的结果都不保存
    printf("%d %d %d\n",--a,--a,--a);//-3,-3,-3
    printf("%d %d %d\n",a--,--a,a--);//-5,-6,-3
    return 0;
}
