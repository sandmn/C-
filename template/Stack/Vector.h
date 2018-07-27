#include<iostream>
#include<string.h>
#include<assert.h>
#include<string>
using namespace std;


//模板类的使用
template<class T>
class Vector
{
    public:
        //构造函数
        Vector();
        //拷贝构造函数
        Vector(const Vector<T>& v);
        //赋值运算符重载（现代写法）
        Vector<T>& operator=(Vector<T> v);
        //析构函数
        ~Vector();
        //交换函数
        void Swap(Vector<T>& v);
        //尾插一个元素
        void PushBack(const T& data);
        //尾删一个元素
        void PopBack();
        //扩容函数
        void Expand(size_t n);
        //任意位置插入一个元素
        void Insert(size_t pos,const T& data);
        //任意位置删除一个元素
        void Erase(size_t pos);
        //取数组首元素
        T& Front() const;
        //取数组尾元素
        T& Back() const;
        //计算数组的实际大小
        size_t Size() const;
        //计算数组的容量
        size_t Capacity() const;
        //判断数组是否为空
        bool Empty() const;
        //保留
        void Reserve(size_t n);
        //重新设置数组的大小
        void Resize(size_t n,const T& flag = T());
        //[]运算符重载
        T& operator[](size_t n) const;
        void Display();
    private:
        T* _start;
        T* _finish;
        T* _endofstarge;
};
