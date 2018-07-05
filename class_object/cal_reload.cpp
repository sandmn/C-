#include<iostream>
using namespace std;








int GetMonDay(int year,int month)
{
    static int mon_day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(month == 2&&
            (year % 4 == 0 && year % 100 != 0)
            ||(year % 400 == 0))
    {
        return 29;
    }
    return mon_day[month];
}


//对"<"进行重载
class Date
{
    public:
        //定义缺省的构造函数
        Date(int year = 1997,int month = 2,int day = 11)
        {
            _year = year;
            _month = month;
            _day = day;
        }
        //定义拷贝构造函数
        Date(const Date& d)
        {
            _year = d._year;
            _month = d._month;
            _day = d._day;
        }
        //定义析构函数
        ~Date()
        {
            cout<<"xigou"<<endl;
        }
        //定义运算符重载函数，对<进行重载
        //类的成员函数除构造函数外都有一隐含的this指针
        bool operator<(const Date& b)
        {
            if(_year < b._year)
            {
                return true;
            }
            else if(_year == b._year)
            {
                if(_month < b._month)
                {
                    return true;
                }
                else if(_month == b._month)
                {
                    if(_day < b._day)
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        //对"+="进行重载
        Date& operator+=(int day)
        {
            _day = _day + day;
            while(_day > GetMonDay(_year,_month))
            {
                _month++;
                if(_month == 13)
                {
                    _year++;
                    _month = 1;
                }
            }
            return *this;
        }
        //对"+"进行重载
        Date operator+(int day)
        {
            Date ret(*this);
            ret += day;
            return ret;
        }
        //对"-="进行重载（写另一种方法）
        Date& operator-=(int day)
        {
            while(_day <= day)
            {
                --_month;
                if(_month == 0)
                {
                    _year--;
                    _month = 12;
                }
                day = day - _day;
                _day = GetMonDay(_year,_month);
            }
            _day = _day - day;
            return *this;
        }
        //对"-"进行重载
        Date operator-(int day)
        {
            Date ret(*this);
            ret -= day;
            return ret;
        }
        void Display()
        {
            cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
        }
    private:
        int _year;
        int _month;
        int _day;
};

int main()
{
    Date d1;//调用缺省的构造函数进行初始化
    Date d2(2021,4,5);//调用自定义拷贝构造函数对d2进行初始化

    Date d3 = d2 - 1000;
    d3.Display();
    Date d4 = d3 + 1000;
    d4.Display();
    cout<<(d1<d2)<<endl;
    
    return 0;
}
