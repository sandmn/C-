
//因为队列是先进先出，所以需要尾插头删，所以，利用链表做适配器效率高
#include"List.h"

//利用模板类做参数实现：容器适配器

template<class T,class Container = List<T> >
class Queue
{
    public:
        //尾插入队列
        void Push(const T& data)
        {
            _con.PushBack(data);
        }
        //头删出队列
        void Pop()
        {
            _con.PopFront();
        }
        //取队首元素
        T& Front()
        {
            return _con.Front();
        }
        //计算队列中的元素个数
        size_t Size()
        {
            return _con.Size();
        }
        //判断队列是否为空
        bool Empty()
        {
            return _con.Empty();
        }
        void Display()
        {
            _con.Display();
        }
    private:
        Container _con;//定义一个Container类型的变量_con
};

int main()
{
    Queue<string,List<string> > q1;
    q1.Push("yanxuechun");
    q1.Push("hujiangqi");
    q1.Push("haha");
    q1.Display();

    q1.Pop();
    q1.Display();
    //q1.Pop();
    //q1.Display();
    //q1.Pop();
    //q1.Display();
    //q1.Pop();
    //q1.Display();

    cout<<q1.Front()<<endl;
    cout<<q1.Size()<<endl;
    cout<<q1.Empty()<<endl;
    return 0;
}
