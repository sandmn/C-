#include<iostream>
using namespace std;



//静态成员函数可以通过类或者对象来访问
//静态成员函数不能访问非静态成员（因为非静态成员函数的访问需要对象来调用，而静态成员函数没有this指针，也就没有指针）
//非静态成员函数可以访问静态成员函数，因为可以通过对象调用静态成员
class Date
{
    public:
        //自定义缺省构造函数
        Date(int year = 1900,int month = 1,int day = 1)
            :_year(year)
             ,_month(month)
             ,_day(day)
    {
        count++;
    }
        //自定义公有成员函数来访问私有成员变量
        void Display()
        {
            cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
            cout<<count<<endl;
        }
        //自定义公有成员函数来访问私有成员变量，将其声明为static，来通过类访问该函数
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

int main()
{
    Date d;
    d.Display();
    d.PrintCount();
    Date::PrintCount();
    return 0;
}



//将count定义为static，且是私有的
//所以对count的访问只能通过公有成员函数
//如果是一般的公有成员，必须通过对象来调用
//但是要想通过类来调用，就不能传递对象
//但是普通的成员函数必有一个this指针，也就是必须通过对象来调用
//所以，将该成员函数声明为static，此时该成员函数就没有this指针了
//也就可以通过类来调用了
//class Date
//{
//    public:
//        Date(int year = 1900,int month = 1,int day = 1)
//            :_year(year)
//             ,_month(month)
//             ,_day(day)
//        {
//            count++;
//        }
//        static void GetCount()
//        {
//            cout<<count<<endl;
//        }
//    private:
//        int _year;
//        int _month;
//        int _day;
//        static int count;
//};
//
//int Date::count = 0;
//
//int main()
//{
//    Date d;
//    d.GetCount();
//    Date::GetCount();
// //   cout<<Date::count<<endl;
//    return 0;
//}

//为使count被类的所有对象所共有，即count属于该类
//所以应该将count声明为static
//若将count定义为公有成员变量
//此时count便可读可写，不能进行封装
//所以要将其封装为私有的
//class Date
//{
//    public:
//        static int count;
//    public:
//        Date(int year = 1900,int month = 1,int day = 1)
//            :_year(year)
//             ,_month(month)
//             ,_day(day)
//        {
//            count++;
//        }
//    private:
//        int _year;
//        int _month;
//        int _day;
//};
//
//int Date::count = 0;
//
//int main()
//{
//    Date d;
//    cout<<d.count<<endl;
//    cout<<Date::count<<endl;
//    return 0;
//}
//

//统计构造函数被调用的次数
//若将计数变量count定义为全局，则在main函数中就可以任意改变
//相当于公有变量，为防止在main函数中对count进行任意修改
//因为count只是为了计数构造函数调用的次数，所有只需为该类所有即可
//因此，将count定义为类成员变量
//因为count要被该类的所有对象所共有，所以需要定义为类的共有成员变量
//即count属于该类，而不只属于类的某一个对象
//int count = 0;
//class Date
//{
//    public:
//        Date(int year = 1900,int month = 1,int day = 1)
//            :_year(year)
//             ,_month(month)
//             ,_day(day)
//    {
//        count++;
//    }
//        void Display()
//        {
//            cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
//        }
//    private:
//        int _year;
//        int _month;
//        int _day;
//};
//
//int main()
//{
//    Date d;
//    d.Display();
//    cout<<count<<endl;
//    return 0;
//}
