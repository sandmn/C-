#include<iostream>
using namespace std;


template<class T>
T Sum(const T& a,const T& b)
{
    //此处不加";"时（未调用该函数时），编译器不会报错
    //因为，编译器不会检查模具，只有实例化之后才会生成真正程序代码，才会进行语法检错
    return a+b;
}


int Sum1(int a,int b)
{
    //这里即使没有调用该函数，不加";"时，也会报错
    //因为编译器会进行语法检错
    return a + b;
}

template<class T>
class Test
{
    public:
        void Print()
        {
            cout<<"haha"<<endl
        }
};


int main()
{
    //只有实例化模板之后，编译器才会进行语法检错
    Sum(1.2,4.5);
    return 0;
}
