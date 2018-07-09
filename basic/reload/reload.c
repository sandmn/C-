
//测试C语言为什么不可以进行函数重载
//C++可以进行函数重载
#include<stdio.h>

int fun(int a,int b)
{
    return a + b;
}

//int fun(double a,int b)
//{
//
//}

int main()
{
    fun(1,2);
    return 0;
}
