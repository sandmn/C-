

#include<iostream>
#include<stdlib.h>
using namespace std;


//有问题
//当类中有清理工作需要做时，需定以析构函数在对象的生命周期结束时进行清理
class Array
{
    public:
        Array()
        {
            _ptr = (char*)malloc(10*sizeof(char));
            _ptr = "hello";
        }
        ~Array()
        {
            if(_ptr)
            {
                free(_ptr);
                _ptr = 0;
            }
        }
        void Display()
        {
            cout<<_ptr<<endl;
        }
    private:
        char* _ptr;
};
int main()
{
    Array a;
    //a.Display();
    return 0;
}





////当类中没有清理工作需要做时，可以不用定义析构函数，而是用默认的析构函数
////默认的析构函数什么也不做
//class Date
//{
//    public:
//        Date()//定义无参的构造函数
//        {
//            _year = 1029;
//        }
//        ~Date()//定义析构函数
//        {
//
//        }
//        void Display()
//        {
//            cout<<_year<<endl;
//        }
//    private:
//        int _year;
//};
//int main()
//{
//    Date d;
//    d.Display();
//    return 0;
//}
