#include<iostream>
using namespace std;

////内存对齐求类的大小
//class A
//{
//    char ch;
//    double d;
//};
//class B
//{
//    char ch;
//    A a;
//    char c;
//};
//
//int main()
//{
//    cout<<sizeof(A)<<endl;
//    cout<<sizeof(B)<<endl;
//    return 0;
//}




///空类的大小（没有成员变量的类，成员函数可有可无）
//lass A
//
//   public:
//       void Display()
//       {
//           cout<<"hello"<<endl;
//       }
//;
//nt main()
//
//   cout<<sizeof(A)<<endl;
//   return 0;
//



////类的大小：类的大小只考虑成员变量，不考虑成员函数
////类的多个对象有不同的成员变量，但是只有一个公共的成员函数，该成员函数存在于公共代码区
//class Person
//{
//    public:
//        void Display()
//        {
//            cout<<_name<<"-"<<_sex<<"-"<<_age<<endl;
//        }
//    public:
//        char* _name;
//        char _sex;
//        int _age;
//};
//int main()
//{
//    Person p;
//    cout<<sizeof(p)<<endl;
//    return 0;
//}



//类成员函数的声明和定义
//类内定义成员函数
//class Person
//{
//    public:
//        void Display()
//        {
//            cout<<_name<<"-"<<_sex<<"-"<<_age<<endl;
//        }
//    public:
//        char* _name;
//        char* _sex;
//        int _age;
//};

////类内声明成员函数，类外定义成员函数
//class Person
//{
//    public:
//        void Display();//类内声明成员函数
//    public:
//        char* _name;
//        char* _sex;
//        int _age;
//};
////类外定义成员函数,需使用::指定成员函数所在的类域
//void Person::Display()
//{
//    cout<<_name<<"-"<<_sex<<"-"<<_age<<endl;
//}
//int main()
//{
//    Person p;
//    p._name = "张三";
//    p._sex = "女";
//    p._age = 20;
//    p.Display();
//
//    Person* pp = &p;
//    pp->_name = "李四";
//    pp->_sex = "男";
//    pp->_age = 29;
//    pp->Display();
//    return 0;
//}


////定义一个类域
////类的成员变量和成员函数都在类域中
//class Person
//{
//    //访问限定符可以使用多次，它的作用域是从定义的位置到下一个访问限定符或者类结束前
//    public://public成员可在类外直接访问
//        void Display()
//        {
//            cout<<_name<<"-"<<_sex<<"-"<<_age<<endl;//类域中的成员函数可以任意的访问类的成员变量
//        }
//    private://private在类外不能直接访问
//        char* _name;
//        char* _sex;
//        char* _age;
//};
//
//int main()
//{
//    Person p;
//    p.Display();//类外定义的对象通过"."的形式访问类的公有成员
//    Person* pp = &p;//在类外定义的类对象的指针通过"->"的形式访问类的公有成员
//    pp->Display();
//    return 0;
//}
