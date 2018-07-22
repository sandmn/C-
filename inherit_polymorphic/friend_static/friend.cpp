#include<iostream>
#include<string>
using namespace std;

class Person
{
    //friend void Display(Person& p,Student& s);
    friend void Display1(Person& p);
    
    protected:
        string _name;
};

class Student:public Person
{
    protected:
        int _num;
};

//有问题
//void Display(Person& p,Student& s)
//{
//    p._name = "yanxuechun";
//    cout<<p._name<<endl;
//    //s._num = 0;
//    //cout<<s._num<<endl;
//    //s._name = "hujiangqi";
//    //cout<<s._name<<endl;
//}
void Display1(Person& p)
{
    p._name = "yanxuechun";
    cout<<p._name<<endl;
}
void Display2(Student& s)
{
    //友元不能继承
    //s._name = "hujiangqi";
    //cout<<s._name<<endl;
    //类外不能访问类的受保护成员
    //s._num = 1;
    //cout<<s._num<<endl;
}
int main()
{
    Person p;
    Student s;
   // Display(p,s);
    Display1(p);
    Display2(s);
    return 0;
}
