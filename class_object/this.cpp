

#include<iostream>
using namespace std;


//1.每个成员函数都有一隐含的固定名字的形参指针，称为this指针，但构造函数除外
//2.在调用成员函数时，编译器会自动处理将类对象的地址作为实参传递给行参this指针
//3.this指针是隐含的：不能在成员函数的行参列表中显示的声明
//                  不能将对象的地址显式的传递给this指针
//                  但可以在成员函数的函数体中显式的使用this指针
//4.this指针是形参，存在于栈区。但在VS中，因为this指针可能会被频繁的使用，为提高效率，会将this指针优化保存到寄存器ecx中 
//                              在Linux下，还是会正常的进行压栈
//5, 因为this指针的存在，所以不同的对象调用同一成员函数时，会有不同的结果
class Date
{
    public:
        void Display()
        {
            cout<<this<<endl;
            //cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
            cout<<this->_year<<"-"<<this->_month<<"-"<<this->_day<<endl;
        }
    public:
        int _year;
        int _month;
        int _day;
};

int main()
{
    Date d1;
    d1._year = 2018;
    d1._month = 3;
    d1._day = 12;
    d1.Display();
    return 0;
}
