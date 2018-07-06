#include<iostream>
using namespace std;




////重载输入输出运算符
////输出运算符重载
//class Date
//{
//    friend ostream& operator<<(ostream& out,const Date& d);
//    friend istream& operator>>(istream& in,Date& d);
//    public:
//        Date()
//        {
//            _year = 1900;
//            _month = 1;
//            _day = 1;
//        }
//    private:
//        int _year;
//        int _month;
//        int _day;
//};
//
//
////输入运算符重载
//istream& operator>>(istream& in,Date& d)
//{
//    in>>d._year>>d._month>>d._day;
//    return in;
//}
//
//
////输出运算符重载
//ostream& operator<<(ostream& out,const Date& d)
//{
//    out<<d._year<<"-"<<d._month<<"-"<<d._day;
//    return out;
//}
//
//
//int main()
//{
//    Date d;
//    cin>>d;
//    cout<<d<<endl;
//    return 0;
//}

////友元类的应用
//
//class Time
//{
//    friend void Display(const Date& d);
//    //Date类中的每个成员函数都可以访问Time类的私有成员变量
//    friend class Date;
//    //friend void Display(const Date& d);
//    private:
//    int _hour;
//    int _min;
//    int _sec;
//};
//
//class Date
//{
//    public:
//        Date()
//        {
//            _year = 1900;
//            _month = 1;
//            _day = 1;
//            _t._hour = 0;
//            _t._min = 0;
//            _t._sec = 0;
//        }
//        friend void Display(const Date& d);
//    private:
//        int _year;
//        int _month;
//        int _day;
//        Time _t;
//};
//
//void Display(const Date& d)
//{
//    cout<<d._year<<"-"<<d._month<<"-"<<d._day<<"-"<<d._t._hour<<"-"<<d._t._min<<"-"<<d._t._sec<<endl;
//}
//int main()
//{
//    Date d;
//    Display(d);
//    return 0;
//}
//
////友元函数的应用
//class Date
//{
//    public:
//        Date()
//        {
//            _year = 1900;
//            _month = 1;
//            _day = 1;
//        }
//        //声明Display为友元函数，但不是类成员函数，此时在类外，Display函数就可以访问类的私有成员变量
//        friend void Display(const Date& d);
//    private:
//        int _year;
//        int _month;
//        int _day;
//};
//
//void Display(const Date& d)
//{
//    cout<<d._year<<"-"<<d._month<<"-"<<d._day<<endl;
//}
//int main()
//{
//    Date d;
//    Display(d);
//    return 0;
//}
