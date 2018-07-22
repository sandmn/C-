#include<iostream>
using namespace std;

class Person
{
    public:
        Person()
        {
            count++;
        }
        static void Display()
        {
            cout<<count<<endl;
        }
    protected:
        string _name;
    private:
        static int count;
    //因为static成员属于整个继承体系的各个类，所以，即使被定义为private，也可以被同类中的公有static成员函数进行访问
    //可以理解为继承体系中的各个类为一个大类，static为这个大类中的一个成员，所以可通过公有的static成员函数进行访问
};

int Person::count = 0;

class Student:public Person
{
    public:
        ////重写成员函数之后，因为static为私有成员，在子类中不可见，所以不能访问
        //static void Display()
        //{
        //    cout<<count<<endl;
        //}
    protected:
        int _num;
};

class Teacher:public Person
{
    protected:
        int _id;
};

int main()
{
    Person p;
    Student s1;
    Student s2;
    Teacher t1;
    Teacher t2;

    Person::Display();
    s1.Display();
    Teacher::Display();

    

   // cout<<p.count<<endl;
   // cout<<Person::count<<endl;
   // cout<<Student::count<<endl;
   // cout<<Teacher::count<<endl;

   // Teacher::count = 0;
   // cout<<p.count<<endl;
   // cout<<Person::count<<endl;
   // cout<<Student::count<<endl;
   // cout<<Teacher::count<<endl;

    return 0;
}
