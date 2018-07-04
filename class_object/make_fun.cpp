#include<iostream>
using namespace std;



//匿名对象的使用
//见下面的使用







////使用默认的构造函数不保证对基本类型的成员变量进行初始化（由编译器决点）
////但会对自定义类型的成员变量进行初始化
//class Time
//{
//    public:
//        //通过该构造函数判断是否对自定义类型的成员函数进行初始化,若输出了"time()",说明进行了初始化,否则没有进行
//        Time()
//        {
//            cout<<"time()"<<endl;
//            _time = 0;
//        }
//    private:
//        int _time;
//};
//class Date
//{
//    public:
//        void Display()
//        {
//            cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
//        }
//    private:
//        int _year;
//        int _month;
//        int _day;
//        Time _t;
//};
//int main()
//{
//    Date d;
//    d.Display();
//    return 0;
//}
//






////使用带缺省参数的构造函数对类对象进行实例化
//class Date
//{
//    public:
//        //定义全缺省的构造函数
//        //Date(int year,int month,int day);
//        ////定义半缺省的构造函数
//        Date(int year = 2019,int month = 3,int day = 20);
//        //{
//        //    _year = year;
//        //    _month = month;
//        //    _day = day;
//        //}
//        //定义普通的公有成员函数
//        void Display()
//        {
//            cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
//        }
//    private:
//        int _year;
//        int _month;
//        int _day;
//};
//Date::Date(int year,int month,int day)
//{
//    _year = year;
//    _month = month;
//    _day = day;
//}
//
//int main()
//{
//    Date d1(2013,7);
//    Date d2;//全缺省构造函数等价于无参构造函数，二者只能取其一
//
//    d1.Display();
//    d2.Display();
//    return 0;
//}





//使用不带缺省参数的构造函数对类对象进行初始化（实例化）
class Date
{
    public:
        //定义无参的构造函数
        Date()
        {

        }
        //定义有参的构造函数:类内声明，类外定义
        Date(int year,int month,int day);
        //定义普通的公有成员函数:类内声明，类外定义
        void Display();
    private:
        //定义私有成员变量
        int _year;
        int _month;
        int _day;
};

//类外定义成员函数时，可以直接使用类的成员变量
//类外定义有参的构造函数
Date::Date(int year,int month,int day)
{
    _year = year;
    _month = month;
    _day = day;
}
//类外定义普通的成员函数
void Date::Display()
{
    cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
}

int main()
{
    //利用成员函数对类对象进行初始化
    Date d1;
    //Date d2();
    Date d3(2018,3,12);
    Date (2013,4,17).Display();//匿名对象的使用，只是为了调用Display

    d1.Display();
    //d2.Display();
    d3.Display();
    return 0;
}






////利用公有成员函数对类的私有成员进行初始化
//class Date
//{
//    public:
//        void Display();//类内声明成员函数，类外定义
//        void SetData(int year,int month,int day)//类内定义成员函数
//        {
//            _year = year;
//            _month = month;
//            _day = day;
//        }
//    private:
//        int _year;
//        int _month;
//        int _day;
//};
////类外定义成员函数，需使用域作用符
//void Date::Display()
//{
//    cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
//}
//
//int main()
//{
//    Date d;
//    //使用公有成员函数对类的私有成员变量进行设置
//    d.SetData(2018,3,12);
//    d.Display();
//    return 0;
//}
//

