#include<iostream>
using namespace std;

//无缺省
int fun(int a,int b)
{
    return a + b;
}

////半缺省
//int fun(int a,int b = 5)
//{
//    return a + b;
//}
//半缺省，正只能从右往左缺省，该情形错误
//int fun(int a = 5,int b)
//{
//    return a + b;
//}

////全缺省
//int fun(int a = 1,int b = 5)
//{
//    return a + b;
//}
//函数的重载
int fun(double a,int b)
{

}

//函数的重载
//函数的重载与缺省参数的重载函数冲突时，会报错
int fun(int a)
{
    return a;
}

int main()
{
    //对于缺省的函数来说，如果有传实参，则使用实参
    //否则用默认的行参
    cout<<fun(2)<<endl;
    return 0;
}
