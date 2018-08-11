#include<iostream>
#include<assert.h>
using namespace std;

//Auto_Ptr
template<class T>
class Auto_Ptr
{
    public:
        //RAII:资源的获得即初始化
        //构造函数
        Auto_Ptr(T* ptr)
            :_ptr(ptr)
        {
            cout<<"Auto_Ptr"<<endl;
        }

        //像指针一样：重载*,->
        T& operator*()
        {
            assert(_ptr != NULL);
            return *_ptr;
        }
        T& operator->()
        {
            return _ptr;
        }

        //管理权转移：拷贝构造和赋值运算符
        
        //拷贝构造函数
        Auto_Ptr(Auto_Ptr<T>& ap)
        {
            _ptr = ap._ptr;
            ap._ptr = NULL;
        }

        //赋值运算符重载
        Auto_Ptr<T>& operator=(Auto_Ptr<T>& ap)
        {
            //如果是自己给自己赋值
            if(this != &ap)
            {
                //如果指向不同空间的指针间进行赋值，赋值后要对空间进行释放，否则会造成资源泄漏
                if(_ptr != NULL)
                {
                    delete _ptr;
                }
                _ptr = ap._ptr;
                ap._ptr = NULL;
            }
            return *this;
        }

        //析构函数：出了作用域后自动释放资源
        ~Auto_Ptr()
        {
            cout<<"～Auto_Ptr()"<<endl;
            if(_ptr)
            {
                delete _ptr;
            }
        }
    private:
        T* _ptr;
};

int main()
{
    Auto_Ptr<int> ap1(new int(10));
    cout<<*ap1<<endl;
    Auto_Ptr<int> ap2(new int(20));
    cout<<*ap2<<endl;
    ap1 = ap2;
    cout<<*ap1<<endl;
    ap1 = ap1;
    cout<<*ap1<<endl;
    //cout<<*ap2<<endl;
    return 0;
}
