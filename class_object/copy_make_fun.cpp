#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;


//调用自定义的拷贝构造函数来实现深拷贝
//验证在成员函数内同类型的对象可以使用类的成员函数
//无论成员函数在类内定义，还是类中声明，类外定义
class MyVector
{
    public:
        //定义缺省的构造函数
        MyVector(int capacity = 0)
        {
            if(capacity == 0)
            {
                _a = NULL;
                _capacity = 0;
                _size = 0;
            }
            else
            {
                _a = (char*)malloc(capacity*sizeof(char*));
                strcpy(_a,"hello world");
                _capacity = capacity;
                _size = 0;
            }
        }
        //自定义拷贝构造函数来进行深拷贝
        //在类内声明，类外定义
        MyVector(const MyVector& m);
        //定义析构函数
        ~MyVector()
        {
            cout<<this<<endl;
            if(_a != NULL)
            {
                free(_a);
                _capacity = 0;
                _size = 0;
            }
        }
        //定义普通的公有成员函数
        void Display()
        {
            cout<<_a<<endl;
        }
    private:
        char* _a;
        int _capacity;
        int _size;
};

//在类的成员函数中可以直接访问类的私有成员变量
MyVector::MyVector(const MyVector& m)
{
    //在类中属于该类的对象可以直接访问类的私有成员
    //在类外不可以
    if(m._a != NULL)
    {
        _a = (char*)malloc(m._capacity*sizeof(char));
        strcpy(_a,m._a);
        _capacity = m._capacity;
        _size = m._size;
    }
}

int main()
{
    MyVector v1(20);//调用缺省的构造函数
    MyVector v2(v1);//调用默认的拷贝构造函数

    v1.Display();
    v2.Display();

    cout<<&v2<<endl;
    cout<<&v1<<endl;

    return 0;
}





////调用自定义的拷贝构造函数来实现深拷贝
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
//                _a = (char*)malloc(capacity*sizeof(char*));
//                strcpy(_a,"hello world");
//                _capacity = capacity;
//                _size = 0;
//            }
//        }
//        //自定义拷贝构造函数来进行深拷贝
//        MyVector(const MyVector& m)
//        {
//            //在类中属于该类的对象可以直接访问类的私有成员
//            //在类外不可以
//            if(m._a != NULL)
//            {
//                _a = (char*)malloc(m._capacity*sizeof(char));
//                strcpy(_a,m._a);
//                _capacity = m._capacity;
//                _size = m._size;
//
//            }
//        }
//        //定义析构函数
//        ~MyVector()
//        {
//            cout<<this<<endl;
//            if(_a != NULL)
//            {
//                free(_a);
//                _capacity = 0;
//                _size = 0;
//            }
//        }
//        //定义普通的公有成员函数
//        void Display()
//        {
//            cout<<_a<<endl;
//        }
//    private:
//        char* _a;
//        int _capacity;
//        int _size;
//};
//
//int main()
//{
//    MyVector v1(20);//调用缺省的构造函数
//    MyVector v2(v1);//调用默认的拷贝构造函数
//
//    v1.Display();
//    v2.Display();
//
//    cout<<&v2<<endl;
//    cout<<&v1<<endl;
//
//    return 0;
//}
//






////调用默认缺省的拷贝构造函数
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
//                _a = (char*)malloc(capacity*sizeof(char*));
//                strcpy(_a,"hello world");
//                _capacity = capacity;
//                _size = 0;
//            }
//        }
//        //定义析构函数
//        ~MyVector()
//        {
//            cout<<this<<endl;
//            if(_a != NULL)
//            {
//                free(_a);
//                _capacity = 0;
//                _size = 0;
//            }
//        }
//        //定义普通的公有成员函数
//        void Display()
//        {
//            cout<<_a<<endl;
//        }
//    private:
//        char* _a;
//        int _capacity;
//        int _size;
//};
//
//int main()
//{
//    MyVector v1(20);//调用缺省的构造函数
//    MyVector v2(v1);//调用默认的拷贝构造函数
//
//    v1.Display();
//    v2.Display();
//
//    cout<<&v2<<endl;
//    cout<<&v1<<endl;
//
//    //因为默认的拷贝构造函数为值拷贝即浅拷贝
//    //所以对于v1和v2都会指向同一块动态申请的内存_a
//    //当v2调用析构函数将_a释放之后，v1在调用析构函数在进行释放就会发生段错误
//    //因为已经释放的内存不能在进行释放
//    //所以，此时可以自定义拷贝构造函数来进行深拷贝
//    return 0;
//}
//



////调用自定义的拷贝构造函数
//class Date
//{
//    public:
//        //定义缺省的构造函数
//        Date(int year = 2018,int month = 2,int day = 11)
//        {
//            _year = year;
//            _month = month;
//            _day = day;
//        }
//        //定义拷贝构造函数,拷贝构造函数是构造函数的重载
//        Date(const Date& d)
//        {
//            _year = d._year;
//            _month = d._month;
//            _day = d._day;
//        }
//        //定义析构函数
//        ~Date()
//        {
//            cout<<this<<endl;
//            cout<<"xigou"<<endl;
//        }
//        //定义公有的成员函数
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
//    Date d1;//调用缺省的构造函数
//    Date d2(d1);//调用拷贝构造函数
//    Date d3 = d2;//调用拷贝构造函数的另一种形式
//
//    d1.Display();
//    d2.Display();
//    d3.Display();
//
//    cout<<&d3<<endl;
//    cout<<&d2<<endl;
//    cout<<&d1<<endl;
//    return 0;
//}
