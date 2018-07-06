#include<iostream>
using namespace std;

//const修饰成员函数中this指向的对象
//1. 若同时有const和非const的成员函数，则const对象自动调用const成员函数，非const对象自动调用非const成员函数
//2. 若只有const成员函数，则const和非const成员变量均可以调用，因为权限可以缩小
//3. 若只有非const成员函数，则非const对象可以调用，但const对象不可以调用，因为权限不能放大
class Date
{
    public:
        Date()
        {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
        void Display()
        {
            cout<<"非const"<<endl;
            cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
        }
       // void Display() const
       // {
       //     cout<<"cout"<<endl;
       //     cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
       // }
    private:
        int _year;
        int _month;
        int _day;
};

int main()
{
    Date d1;
    d1.Display();

    const Date d2;
    d2.Display();

    return 0;
}
