#include<iostream>
using namespace std;

//class AA
//{
//    public:
//        //自定义构造函数
//        AA()
//        {
//            cout<<"AA"<<endl;
//            count++;
//        }
//        //自定义拷贝构造函数
//        AA(const AA& a)
//        {
//            cout<<"AA(const AA& a)"<<endl;
//            count++;
//        }
//        //赋值运算符重载
//        AA& operator=(const AA& a)
//        {
//            cout<<"operator="<<endl;
//        }
//        //自定义析构函数
//        ~AA()
//        {
//            cout<<"~AA()"<<endl;
//        }
//
//        //打印构造函数调用的次数
//        static void PrintCount()
//        {
//            cout<<count<<endl;
//        }
//    private:
//        static int count;
//};
//int AA::count = 0;
//
//AA fun(AA a)
//{
//    return a;//传参时进行1次拷贝构造，返回时进行1次拷贝构造
//}
//
//void Test1()
//{
//    AA a1;//1次构造
//    a1 = fun(a1);//1次拷贝构造，1次拷贝构造，1次赋值
//    //3次析构
//}
//
//void Test2()
//{
//    AA a1;//1次构造
//    AA a2 = fun(a1);//1次拷贝构造，1次拷贝构造，
//    //3次析构
//}
//
//void Test3()
//{
//    AA a1;//1次构造
//    AA a2 = fun(fun(a1));//1次拷贝构造，1次拷贝构造，1次拷贝构造
//    //4次析构
//}
//
//int main()
//{
//    //Test1();
//    //AA::PrintCount();
//
//    //Test2();
//    //AA::PrintCount();
//
//    Test3();
//    AA::PrintCount();
//
//    return 0;
//}


class Date
{
    public:
        //自定义构造函数
        Date(int year = 1900,int month = 1,int day = 1)
            :_year(year)
             ,_month(month)
             ,_day(day)
        {
            cout<<"Date"<<endl;
            count++;
        }
        //自定义拷贝构造函数
        Date(const Date& d)
        :_year(d._year)
         ,_month(d._month)
         ,_day(d._day)
    {
        count++;
        cout<<"Date(const Date& d)"<<endl;
    }
        //赋值运算符重载
        Date& operator=(const Date& d)
        {
            if(this != &d)
            {
                cout<<"operator="<<endl;
                _year = d._year;
                _month = d._month;
                _day = d._day;
            }
            return *this;
        }
        //定义析构函数
        ~Date()
        {
            cout<<"~Date()"<<endl;
        }
        //定义公有成员函数访问count
        static void PrintCount()
        {
            cout<<count<<endl;
        }
    private:
        int _year;
        int _month;
        int _day;
        static int count;
};

int Date::count = 0;

//参数传值
void fun1(Date d)
{
    
}
//参数传引用
void fun2(Date& d)
{

}
//返回值传值
//此时编译器会进行优化，将构造和拷贝构造合为1次构造
Date fun3()
{
    Date d;//1次构造
    return d;
    
}

//返回值传值
//此时编译器会进行优化，将构造和拷贝构造合为1次构造
Date fun4()
{
    return Date();
}



int main()
{
    //Date d;
    //fun1(d);
    //Date::PrintCount();//1次构造，1次拷贝构造，2次析构
   
    //Date d;
    //fun2(d);
    //Date::PrintCount();//1次构造
    

    //fun3();//1次构造，1次析构
    //Date::PrintCount();

    //fun4();//1次构造，1次析构
    //Date::PrintCount();

    //Date d;//1次构造
    //d = fun3();//1次构造，1次赋值，2次析构
    //Date::PrintCount();
    
    ////1次构造，1次析构
    //Date d = fun3();
    //Date::PrintCount();

    //Date d;//1次构造
    //d = fun4();//1次构造，1次赋值
    //Date::PrintCount();

    //Date d = fun4();//1次构造
    //Date::PrintCount();

    return 0;
}
