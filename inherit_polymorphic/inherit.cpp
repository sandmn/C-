#include<iostream>
#include<stdio.h>
using namespace std;

class Person
{
    public:
        void Display()
        {
            cout<<"haha"<<endl;
        }
        int _n1;
    protected:
        int _n2;
    private:
        int _n3;
};

//公有继承：除私有成员不可见（存在但不能访问）外，其余成员的属性不变
//          父类中的公有成员在子类中还是公有成员(公有成员在类内外均可访问)
//          父类中的受保护成员在子类中还是受保护成员（受保护成员只在子类/本类中可访问，类外不能访问）
class Student1:public Person
{
    public:
        void Display()
        {
            _n1 = 10;
            _n2 = 20;
           // _n3 = 30;
            _s = 40;
            cout<<_n1<<endl;
            cout<<_n2<<endl;
           // cout<<_n3<<endl;
            cout<<_s<<endl;
        }
    int _s;
};

//保护继承:除父类的私有成员外父类的其余成员均变为受保护成员（类和子类中可以访问，类外不可以访问）
class Student2:protected Person
{
    public:
        void Display()
        {
            _n1 = 10;
            _n2 = 20;
            //_n3 = 30;
            cout<<_n1<<endl;
            cout<<_n2<<endl;
            //cout<<_n3<<endl;
        }
};

//私有继承
class Student3 : private Person
{
    public:
        void Display()
        {
            _n1 = 10;
            _n2 = 20;
            //_n3 = 30;
            cout<<_n1<<endl;
            cout<<_n2<<endl;
            //cout<<_n3<<endl;
        }

};

int main()
{
    //Person p;
    //cout<<sizeof(p)<<endl;
    
    //Student1 s1;
    //cout<<sizeof(s1)<<endl;
    //s1.Display();
    //s1._n1 = 1;
    ////s1._n2 = 2;
    ////s1._n3 = 3;
    //cout<<s1._n1<<endl;
    ////cout<<s1._n2<<endl;
    ////cout<<s1._n3<<endl;

    //Student2 s2;
    //cout<<sizeof(s2)<<endl;
   // s2.Display();
   // s2._n1 = 1;
   // s2._n2 = 2;
   //// s2._n3 = 3;
   // cout<<_s2._n1<<endl;
   // cout<<_s2._n2<<endl;
   //// cout<<_s2._n3<<endl;

    Student3 s3;
    cout<<sizeof(s3)<<endl;
    s3.Display();
    //s3._n1 = 1;
    //s3._n2 = 2;
   //// s2._n3 = 3;
    //cout<<_s3._n1<<endl;
    //cout<<_s3._n2<<endl;
   //// cout<<_s2._n3<<endl;
    return 0;
}



//class Person
//{
//    public:
//        //对于默认的构造函数，此时就类似于：
//        //Person()
//        //:_name();//此处会调用string的缺省构造函数
//        //{
//        //
//        //}
//        //构造函数
//        //如果调用构造函数时，没有传递参数，此时在参数中就会使用默认参数来调用string类的构造函数构造参数name
//        //如果传参时，传递时C风格的字符串，此时参数就会根据传参的字符串来调用string类的构造函数来构造参数name
//        //如果传参时，传递的是string风格的字符串，此时就会调用string类的拷贝构造函数来构造参数name
//        Person(const string& name = "yanxuechun")
//            :_name(name)//此处调用string类的拷贝构造函数
//            {
//                cout<<"Person"<<endl;
//                _name = name;//此处调用string类的赋值运算符重载函数
//            }
//        //拷贝构造函数
//        Person(const Person& p)
//            :_name(p._name)
//        {
//            cout<<"Person(const Person& p)"<<endl;
//        }
//        //赋值运算符重载
//        Person& operator=(const Person& p)
//        {
//            if(this != &p)
//            {
//                _name = p._name;//此处调用string类的赋值运算符重载
//            }
//        }
//        //析构函数
//        ~Person()
//        {
//            cout<<"~Person()"<<endl;
//        }//此处会调用string类的析构函数
//
//        void Display()
//        {
//            cout<<_name<<endl;//此处调用string类的"<<"重载函数
//        }
//    protected:
//        string _name;
//};
//
//class Student:public Person
//{
//    protected:
//        int _num;
//};
//
//
//int main()
//{
//    Person p;
//    p.Display();
//    Person p1("hujiangqi");
//    p1.Display();
//    return 0;
//}
