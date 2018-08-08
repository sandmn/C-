#include<iostream>
#include<list>
#include<assert.h>
using namespace std;
//实现双向，循环带头节点的链表

//自定义一个数据类型
typedef struct DataType
{
    int a1;
    int a2;
}Type;

//对自定义类型的<<运算符进行重载
ostream& operator<<(ostream& out,Type& d)
{
    out<<"("<<d.a1<<","<<d.a2<<") ";
    return out;
}

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

//定义一个const类型的迭代器
template<class T>
struct Const_ListIterator
{
    typedef ListNode<T> Node;
    //定义该类型的构造函数
    Const_ListIterator(Node* node)
        :_Node(node)
    {
    }
    //该类型的拷贝和赋值都是浅拷贝，所以直接使用默认的成员函数即可
    //在该类型中，没有需要释放的空间，所以使用默认的析构函数即可
    
    //对于const类型的对象，返回的是const类型的迭代器
    //在容器类型中调用的是const类型的Begin，End函数，然后返回一个迭代器
    //但是此时仍然可以通过迭代器来改变对象的值，没有达到const迭代器的效果
    //所以为实现const迭代器的效果，需要在解引用迭代器时，不能改变对象的值
    //也就是说对于const类型的迭代器，需要重新编写解引用函数,所以可以直接在定义一个const类型的迭代器
    //来实现迭代器的基本操作
    
    //因为对于const类型的迭代器，不能改变对象的值
    //因为迭代器的返回值就是对象的值，所以只需要将迭代器的返回值设置为const即可
    //注意，不能将迭代器设置为const类型，如果设置了，迭代器的指向就不能改变了
    ////对于const类型的对象，返回const类型的迭代器

    //对const类型的迭代器进行*运算符重载
    const T& operator*()
    {
        return _Node->data;
    }

    //同理对const类型的->进行运算符重载
    const T* operator->()
    {
        return &(_Node->data);
    }
    //前置++运算符重载
    Const_ListIterator& operator++()
    {
        _Node = _Node->next;
        return *this;
    }
    //后置++运算符重载
    Const_ListIterator operator++(int)
    {
        //首先将为改变之前的迭代器拷贝构造一份
        Const_ListIterator tmp(*this);
        //然后改变迭代器中的内容
        _Node = _Node->next;
        //最后返回改变之前的迭代器
        return tmp;
    }
    //==运算符重载
    bool operator==(const Const_ListIterator& con)
    {
        return _Node == con._Node;
    }
    //!=运算符重载
    bool operator!= (const Const_ListIterator&  con)
    {
        return _Node != con._Node;
    }
    //因为迭代器是对结点指针的封装，所以该类型中有一个节点的指针类型变量
    private:
        Node* _Node;
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
    //前置--运算符重载
    Self& operator--()
    {
        _Node = _Node->prev;
        return *this;
    }
    //后置--运算符重载
    Self operator--(int)
    {
        ListIterator tmp(*this);
        _Node = _Node->prev;
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
    typedef Const_ListIterator<T> Const_Iterator;
        Iterator Begin()
        {
            return Iterator(_head->next);
        }
        //返回const类型的迭代器
        //与普通类型构成函数重载
        Const_Iterator Begin() const
        {
            return Const_Iterator(_head->next);
        }
        Iterator End()
        {
            return Iterator(_head);
        }
        //返回const类型的迭代器
        //与普通类型构成函数重载
        Const_Iterator End() const
        {
            return Const_Iterator(_head);
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

          //Begin:10
          //pos:10
          //0
          //pos:10
          //0
          //pos:0
          //next_node:0
          //it:0
          //打印基本类型的非const对象


        ////删除节点，返回删除节点的下一个位置
        //Iterator Erase(Iterator pos)
        //{
        //    //首先判断待删除的位置是否合法
        //    assert(_head->next != _head && pos != End());
        //    //将待删除位置保存下来
        //    Iterator tmp = pos;
        //    //寻找待删除位置的上一个元素
        //    Iterator prev_node = --pos;
        //    ++pos;
        //    //寻找待删除元素的下一个元素
        //    Iterator next_node = ++pos;

        //    //修改上一个和下一个元素的指针域
        //    prev_node._Node->next = next_node._Node;
        //    next_node._Node->prev = prev_node._Node;
        //    //删除待删除元素
        //    delete tmp._Node;
        //    //返回删除元素的下一个元素
        //    return next_node;
        //}


        //Iterator Erase(Iterator pos)
        //{
        //    assert(_head->next != _head && pos != End());
        //    Iterator to_delete = pos;
        //    Node* prev_node = pos._Node->prev;
        //    Node* next_node = pos._Node->next;
        //    prev_node->next = next_node;
        //    next_node->prev = prev_node;
        //    delete to_delete._Node;
        //    Iterator tmp(next_node);
        //    return tmp;
        //}

        //优化源代码，使迭代器不失效
        //删除节点
        void Erase(Iterator& pos)
        {
            //首先保证链表不为空，且删除的位置合法（不为头结点且不超过尾节点）
            assert(_head->next != _head && pos != _head);
            //Node* next_node = pos._Node->next;

            Iterator to_delete = pos;
            Node* prev_node = pos._Node->prev;
            Node* next_node = pos._Node->next;
            prev_node->next = next_node;
            next_node->prev = prev_node;
            delete to_delete._Node;
            pos._Node = next_node;
            return;

        }
        //void Erase(Iterator& pos) const
        //{
        //       
        //}
    private:
        Node* _head;
};

//基本类型：打印非const对象的数据,利用容器来实现
template<class Container>
void Basic_Print(Container& con)
{
    cout<<"打印基本类型的非const对象"<<endl;
    //定义一个容器类型的迭代器
    class Container::Iterator it = con.Begin();
    while(it != con.End())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}

//基本类型：根据迭代器打印const对象的数据
template<class Container>
void Basic_Print_Const(const Container& con)
{
    cout<<"打印基本类型的const对象"<<endl;
    class Container::Const_Iterator it = con.Begin();
    while(it != con.End())
    {
        //*it = 10;
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}

//自定义类型：打印非const的自定义类型
template<class T>
void Self_Print(List<T>& l)
{
    class List<T>::Iterator it = l.Begin();
    cout<<"打印非const类型的自定义类型"<<endl;
    while(it != l.End())
    {
        //此处it->相当于：it.operator->(),该函数的返回值是一个自定义类型的指针
        //要输出自定义类型的各个数据成员
        //此时，要么在自定义类型中重载"<<"运算符重载
        //要么，根据对象的指针，对各个数据成员进行解引用输出，假如返回的是add，add是一个对象的指针
        //      此时，要输出数据成员，可以使用->运算符，相当于：add->a1
        //      所以，以上两步合在一起就可以表示为：it->->a1,在这里，为提高代码的可读性，编译器会进行处理
        //      将两个->默认为一个，所以可以直接调用it->a1即可达到同样的效果
        

        ////方法一：对自定义类型的<<进行运算符重载
        //cout<<*it<<" ";

        //方法二：
        //在迭代器类型中对->进行运算符重载
        cout<<"("<<it->a1<<" "<<it->a2<<") ";
        it++;
    }
    cout<<endl;
}

//自定义类型：打印容器const类型的自定义类型
template<class Container>
void Self_Print_Const(const Container& con)
{
    class Container::Const_Iterator it = con.Begin();
    cout<<"打印自定义类型的const对象"<<endl;
    while(it != con.End())
    {
        cout<<"("<<it->a1<<" "<<it->a2<<")"<<" ";
        it++;
    }
    cout<<endl;
}


int main()
{
    //链表结点的数据域为自定义类型
    //List<Type> l1;
    //Type d = {10,4};
    int i = 0;
    //for(i = 0;i < 5;i++)
    //{
    //    l1.PushBack(d);
    //}
    //Self_Print(l1);
    //Self_Print_Const(l1);

    //链表结点数据域为基本类型
    List<int> l2;
    l2.PushBack(10);
    for(i = 0;i < 5;i++)
    {
        l2.PushBack(i);
    }
//    Basic_Print(l2);
//    Basic_Print_Const(l2);

    //验证删除任意位置的结点，返回值为删除结点的下一个位置
    List<int>::Iterator it = l2.Begin();
    //通过返回值使删除节点时迭代器不失效
    //while(it != l2.End())
    //{
    //    it = l2.Erase(it);
    //    Basic_Print(l2);
    //}
    //优化源代码,通过传引用的方式使迭代器不失效
    while(it != l2.End())
    {
        l2.Erase(it);
        Basic_Print(l2);
    }
    //it = l2.Erase(it);
    //Basic_Print(l2);
    //it = l2.Erase(it);
    //Basic_Print(l2);
    return 0;
}
