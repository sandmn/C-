#include<iostream>
using namespace std;

//取地址运算符重载
class Date
{
    public:
        Date()
        {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
        //取地址运算符重载
        Date* operator&()
        {
            return this;
        }
        //const对象取地址运算符重载
        const Date* operator&() const
        {
            return this;
        }
    private:
        int _year;
        int _month;
        int _day;
};



int main()
{
    Date d1;
    const Date d2; 
    cout<<&d1<<endl;
    cout<<&d2<<endl;
    return 0;
}
