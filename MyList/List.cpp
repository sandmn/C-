#include<iostream>
using namespace std;
//实现双向，循环带头节点的链表

//自定义一个数据类型
typedef struct DataType
{
    int a1;
    int a2;
}Type;


//链表节点的定义
template<class T>
struct ListNode
{
    ListNode<T>* next;
    ListNode<T>* prev;
    T data;
    //结点的构造函数
    ListNode(const T& d = T())
    {
        data = d;
        next = NULL;
        prev = NULL;
    }
};

//定义一个迭代器类型
template<class T>
struct ListIterator
{
    //迭代器是对链表节点的一层封装，所以该类型中有一个链表节点的成员变量
    typedef ListNode<T> Node;
    typedef ListIterator<T> Self;

    //构造函数
    ListIterator(Node* node)
        :_Node(node)
    {
    }
    //对于该迭代器类型来说，对于成员变量的赋值和拷贝都是浅拷贝
    //所以利用默认成员函数即可，不用在自己写赋值和拷贝构造函数
    //另外，迭代器类型的成员变量也没有空间可以析构
    //所以也可以直接使用默认的析构函数，不用自己来编写析构函数
    ////拷贝构造函数
    //ListIterator(const Self& it)
    //{
    //    _Node = it._Node;
    //}
    ////赋值运算符重载
    //Self& operator=(const Self& it)
    //{
    //    _Node = it._Node;
    //    return *this;
    //}
    ////析构函数
    //~ListIterator()
    //{
    //}

    //*运算符重载
    T& operator*()
    {
        return _Node->data;
    }
    //->运算符重载
    //针对于结点的数据域是自定义类型的情形
    T* operator->()
    {
        return &(_Node->data);
    }
    //前置++运算符重载
    Self& operator++()
    {
        _Node = _Node->next;
        return *this;
    }
    //后置++运算符重载
    Self operator++(int)
    {
        ListIterator tmp(*this);
        _Node = _Node->next;
        return tmp;
    }
    //!=运算符重载
    bool operator != (const Self& it)
    {
        return _Node != it._Node;
    }
    //==运算符重载
    bool operator==(const Self& it)
    {
        return _Node == it._Node;
    }
    Node* _Node;
};

template<class T>
class List
{
    typedef ListNode<T> Node;
    public:
    typedef ListIterator<T> Iterator;
        Iterator Begin()
        {
            return Iterator(_head->next);
        }
        Iterator End()
        {
            return Iterator(_head);
        }
        //在构造函数中利用结点的匿名构造函数创建一个头结点
        List()
        {
            _head = new Node(T());
            _head->next = _head;
            _head->prev = _head;
        }

        //尾插一个节点
        void PushBack(const T& d)
        {
            //首先创建一个节点
            Node* new_node = new Node(d);
            //然后将该节点尾插进链表中
            Node* tail = _head->prev;
            tail->next = new_node;
            new_node->prev = tail;
            new_node->next = _head;
            _head->prev = new_node;
        }

        //拷贝构造函数
        //注意拷贝构造函数中不能进行值传递，否则会引发无穷递归
        List(const List<T>& l)
        {
            //首先创建一个头结点，然后与参数链表进行交换
            _head = new Node(T());
            _head->next = _head;
            _head->prev = _head;
         
            if(l._head != NULL)
            {
                Node* cur = l._head->next;
                while(cur != l._head)
                {
                    PushBack(cur->data);
                    cur = cur->next;
                }
            }
        }
        //赋值运算符重载
        List<T>& operator=(List<T> l)
        {
        //    cout<<"operator="<<endl;
            if(&l != this)
            {
                swap(_head,l._head);
            }
            return *this;
        }

        void Clear()
        {
            if(_head != NULL)
            {
                Node* to_delete = _head->next;
                while(to_delete != _head)
                {
                    Node* next_node = to_delete->next;
                    delete to_delete;
                    to_delete = next_node;
                }
            }
        }

        //析构函数
        ~List()
        {
            Clear();
            if(_head != NULL)
            {
                delete _head;
            }
        }
    private:
        Node* _head;
};
template<class T>
void Print1(List<T>& l)
{
    class List<T>::Iterator it = l.Begin();
    //ListIterator<T> it = l.Begin();
    while(it != l.End())
    {
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
}

//打印自定义类型
template<class T>
void Print2(List<T>& l)
{
    class List<T>::Iterator it = l.Begin();
    while(it != l.End())
    {
        //此处it->相当于：it.operator->(),该函数的返回值是一个自定义类型的指针
        //要输出自定义类型的各个数据成员
        //此时，要么在自定义类型中重载"<<"运算符重载
        //要么，根据对象的指针，对各个数据成员进行解引用输出，假如返回的是add，add是一个对象的指针
        //      此时，要输出数据成员，可以使用->运算符，相当于：add->a1
        //      所以，以上两步合在一起就可以表示为：it->->a1,在这里，为提高代码的可读性，编译器会进行处理
        //      将两个->默认为一个，所以可以直接调用it->a1即可达到同样的效果
        cout<<it->a1<<" "<<it->a2<<",";
        it++;
    }
    cout<<endl;
}

int main()
{

    //链表结点的数据域为自定义类型
    List<Type> l1;
    Type d = {10,4};
    int i = 0;
    for(i = 0;i < 5;i++)
    {
        l1.PushBack(d);
    }

    Print2(l1);

    //链表结点数据域为基本类型
    //List<int> l1;
    //l1.PushBack(10);

    //int i = 0;
    //for(i = 0;i < 5;i++)
    //{
    //    l1.PushBack(i);
    //}

    //Print1(l1);
    //List<int> l2(l1);
    //Print2(l2);
    return 0;
}
