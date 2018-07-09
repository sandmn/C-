
//测试C++为什么可以进行函数重载
//测试函数重载
//测试缺省参数函数
//测试函数重载与缺省参数函数的冲突问题
#include<iostream>
using namespace std;

#define N 20
int c = 30;

////无缺省
//int fun(int a,int b)
//{
//    return a + b;
//}

//int fun(int a,int b);
//int fun(int a,int b = c);
////半缺省，正只能从右往左缺省，该情形错误
//int fun(int a = 5,int b)
//{
//    return a + b;
//}

////全缺省
//int fun(int a = 1,int b = 5)
//{
//    return a + b;
//}
////函数的重载
//int fun(double a,int b)
//{
//    return b;
//}

////函数的重载
////函数的重载与缺省参数的重载函数冲突时，会报错
//int fun(int a)
//{
//    return a;
//}

int main()
{
    int fun(int a,int b = c);
    //对于缺省的函数来说，如果有传实参，则使用实参
    //否则用默认的行参
    cout<<fun(1,2)<<endl;//调用全缺省或半缺省，当两者共存时，会发生错误
    cout<<fun(1)<<endl;//调用半缺省参数
    //cout<<fun(1.0,2)<<endl;
    return 0;
}
////半缺省
//int fun(int a,int b = 5)
//{
//    return a + b;
//}
//无缺省
int fun(int a,int b)
{
    return a + b;
}
