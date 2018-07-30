#include<iostream>
using namespace std;

template<class T>
struct Greater
{
    bool operator()(const T& l,const T& r)
    {
        return l > r;
    }
};

template<class T>
struct Less
{
    bool operator()(const T& l,const T& r)
    {
        return l < r;
    }
};

int main()
{
    Greater<int> g;
    //利用模板类中对()进行运算符重载来实现仿函数
    //像函数，但实际不是函数，而是根据类的对象调用类的成员函数
    cout<<g(1,2)<<endl;

    Less<float> l;
    cout<<l(3.2,9.3)<<endl;
    return 0;

}
