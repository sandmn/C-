

#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

////调用析构函数对动态申请的内存进行清理
//class MyVector
//{
//    public:
//        //定义缺省的构造函数
//        MyVector(int capacity = 0)
//        {
//            if(capacity == 0)
//            {
//                _a = NULL;
//                _capacity = 0;
//                _size = 0;
//            }
//            else
//            {
//                _a = (char*)malloc(capacity*sizeof(char));
//                strcpy(_a,"hello world");
//                _capacity = capacity;
//                _size = 0;
//            }
//        }
//        //定义析构函数在对象生命周期结束时进行清理工作
//        ~MyVector()
//        {
//            if(_a != NULL)
//            {
//                free(_a);
//                _a = NULL;
//                _capacity = 0;
//                _size = 0;
//                cout<<"h"<<endl;
//            }
//        }
//        //定义普通的公有函数
//        void Display()
//        {
//            cout<<_a<<endl;
//        }
//    private:
//        char* _a;
//        int _capacity;
//        int _size;
//};
//int main()
//{
//    MyVector v1;
//    v1.Display();
//    return 0;
//}
//



//使用析构函数在对象生命周期结束的时候进行清理
//class Date
//{
//    public:
//        Date(int year = 2018,int month = 2,int day = 11)
//        {
//            _year = year;
//            _month = month;
//            _day = day;
//        }
//        ~Date()
//        {
//            cout<<"cout()"<<endl;
//        }
//        void Display()
//        {
//            cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
//        }
//    private:
//        int _year;
//        int _month;
//        int _day;
//};
//int main()
//{
//    //调用缺省的构造函数进行初始化
//    Date d;
//    d.Display();
//    return 0;
//}
//



////当类中有清理工作需要做时，需定以析构函数在对象的生命周期结束时进行清理
//class Array
//{
//    public:
//        Array()
//        {
//            _ptr = (char*)malloc(10*sizeof(char));
//            strcpy(_ptr,"hello");
//        }
//        ~Array()
//        {
//            if(_ptr)
//            {
//                free(_ptr);
//                _ptr = 0;
//            }
//        }
//        void Display()
//        {
//            cout<<_ptr<<endl;
//        }
//    private:
//        char* _ptr;
//};
//int main()
//{
//    Array a;
//    a.Display();
//    return 0;
//}
//
//



////当类中没有清理工作需要做时，可以不用定义析构函数，而是用默认的析构函数
////默认的析构函数什么也不做
//class Date
//{
//    public:
//        Date()//定义无参的构造函数
//        {
//            _year = 1029;
//        }
//        ~Date()//定义析构函数
//        {
//
//        }
//        void Display()
//        {
//            cout<<_year<<endl;
//        }
//    private:
//        int _year;
//};
//int main()
//{
//    Date d;
//    d.Display();
//    return 0;
//}
