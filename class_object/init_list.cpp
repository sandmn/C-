#include<iostream>
using namespace std;


//1.当没有显示的写出初始化列表时，系统也会自动调用初始化列表，定义成员变量并进行初始化
//  所以说初始化列表时成员变量定义的地方
//2. 如果没有定义初始化列表，系统会自动调用成员变量的无参或缺省的构造函数对成员变量进行定义
//   对于自定义类型的变量来说，如果没有无参或缺省的构造函数，此时就会因为找不到构造函数而发生错误
//   所以，如果没有显式的写出自定义类型变量的初始化列表，就一定要有无参或缺省的构造函数
//3. 如果定义了初始化列表，则会根据初始化列表调用相应的构造函数或者拷贝构造函数
//4. 如果定义了初始化列表，但是没有对应的构造函数，也会报错
//
//
//
//总之，对于自定义类型来说：
//如果没有定义初始化列表，则会调用无参或全缺省的构造函数
//如果定义了初始化列表，则会根据初始化列表的形式调用相应的构造函数
//如果找不到对应的构造函数，则报错
class Time
{
    public:
        //自定义构造函数
        Time(int hour = 0,int min = 0,int sec = 0)
        {
            cout<<"time"<<endl;
            _hour = hour;
            _min = min;
            _sec = sec;
        }
        //自定义拷贝构造函数
        Time(const Time& t)
        {
            cout<<"const time"<<endl;
            _hour = t._hour;
            _min = t._min;
            _sec = t._sec;
        }
    private:
        int _hour;
        int _min;
        int _sec;
};
class Date
{
    public:
        //自定义构造函数
        Date(int year,int month,int day,const Time& t)
        {
            _year = year;
            _month = month;
            _day = day;
            _t = t;
        }
  //     Date(int year,int month,int day,const Time& t)
  //         :_year(year)
  //          ,_month(month)
  //          ,_day(day)
  //          ,_t(t)
  //  {}
    private:
        int _year;
        int _month;
        int _day;
        Time _t;
};

int main()
{
    Time t;
    Date(1900,1,1,t);
    return 0;

}




//验证初始化列表的形式比构造函数体内赋值的方式高效
//class Time
//{
//    public:
//        //自定义构造函数
//        Time(int hour,int min = 0,int sec = 0)
//        {
//            cout<<"time"<<endl;
//            _hour = hour;
//            _min = min;
//            _sec = sec;
//        }
//        //赋值运算符重载
//        Time& operator=(const Time& d)
//        {
//            cout<<"operator="<<endl;
//            if(this != &d)
//            {
//                _hour = d._hour;
//                _min = d._min;
//                _sec = d._sec;
//            }
//            return *this;
//        }
//    private:
//        int _hour;
//        int _min;
//        int _sec;
//};
//class Date
//{
//    public:
//       // //自定义构造函数
//       // Date(int year = 1900,int month = 1,int day = 1,int hour = 0,int min = 0,int sec = 0)
//       // {
//       //     _year = year;
//       //     _month = month;
//       //     _day = day;
//       //     Time temp(hour,min,sec);//此处相对于初始化列表的形式，会多一次的拷贝和赋值运算，效率会相对降低
//       //     _t = temp;
//       // }
//
//        //Date(int year = 1900,int month = 1,int day = 1,int hour = 0,int min = 0,int sec = 0)
//        Date(int year,int month,int day,int hour,int min,int sec)
//            :_year(year)
//            ,_month(month)
//             ,_day(day)
//             ,_t(hour,min,sec)
//        {}
//    private:
//        int _year;
//        int _month;
//        int _day;
//        Time _t;
//};
//
//
//int main()
//{
//    Date d1;
//    d1.Display();
//    return 0;
//}
