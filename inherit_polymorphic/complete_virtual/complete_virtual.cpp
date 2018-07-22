#include<iostream>
using namespace std;

//纯虚函数：在类成员函数的形参列表后面加上=0，此时的成员函数就是纯虚函数
//包含纯虚函数的类为抽象类，抽象类不能实例化出对象。
//必须通过子类对该纯虚函数重写，才能实例化出对象
class Person
{
    public:
        virtual void Display() = 0;
};
class Student:public Person
{
    public:
        void Display()
        {
            cout<<"hello world"<<endl;
        }
};


int main()
{
    //包含纯虚函数的类为抽象类，抽象类不能实例化出对象
    //Person p1;
    Student s1;
    s1.Display();

    return 0;
}
