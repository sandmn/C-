
#include<iostream>
#include"Vector.cpp"
#include"List.h"
using namespace std;

//模板类做参数：实现容器适配器

//因为栈是后进先出，需要进行尾插，尾删，所以此时顺序表vector比较适合做适配器
//当然，链表也可以

template<class T,class Container = Vector<T> >
class Stack
{
    public:
        //尾插入栈
        void Push(const T& data)
        {
            _con.PushBack(data);
        }
        //尾删出栈
        void Pop()
        {
            _con.PopBack();
        }
        //取栈顶元素
        const T& Top()
        {
            _con.Back();
        }
        //判断栈是否为空
        bool Empty()
        {
            return _con.Empty();
        }
        //计算栈中元素个数
        size_t Size()
        {
            return _con.Size();
        }
        void Display()
        {
            _con.Display();
        }
    private:
        Container _con;//适配器类型的变量
};


int main()
{
    Stack<int > s1;

    s1.Push(10);
    s1.Push(20);
    s1.Push(30);
    s1.Display();
    s1.Pop();
    s1.Display();
   // Stack<int,List<int> > s2;


   // s2.Push(10);
   // s2.Push(20);
   // s2.Push(30);
   // s2.Display();
   // s2.Pop();
   // s2.Display();
   // cout<<s2.Size()<<endl;
   // cout<<s2.Empty()<<endl;


    //溢出
    //Stack<int,List<char> > s3;
    //s3.Push(1111);
    //cout<<s3.Top()<<endl;
    //s3.Display();
    



    return 0;
}
