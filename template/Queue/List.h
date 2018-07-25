#include<iostream>
#include<stdio.h>
#include<assert.h>
using namespace std;

//利用模板类实现带头，循环的双向链表

//链表节点的结构
template<class T>
struct ListNode
{
    //注意此时的结点类型为ListNode<T>
    T data;//结点的数据域
    ListNode<T>* next;//结点的next指针域
    ListNode<T>* prev;//结点的prev指针域
    //构造函数
    //注意将引用设置为const引用
    ListNode(const T& d = T())
        :data(d)//将数据域设置为该类型的一个匿名对象
         ,next(NULL)//两个指针域均置为空指针
         ,prev(NULL)
    {
    }
};

//链表的结构及相关操作
//链表由一个头指针来表示，所以有一个head指针的成员变量
template<class T>
class List
{
    //注意类型替换的格式
    typedef ListNode<T> Node;
    public:
        //构造函数:因为链表是带头结点的，所以，在构造函数中要创建一个头结点,由head指向
        List()
            :head(new Node(T()))//此处创建Node结点时，会调用Node的构造函数进行初始化
        {
         //   cout<<"List()"<<endl;
            head->next = head;
            head->prev = head;
        }
        //拷贝构造函数
        //首先要创建一个头结点，然后遍历链表，将链表中的各个节点尾插到新链表上
        List(const List<T>& l)
            :head(new Node)
        {
         //   cout<<"List(const List<T>&)"<<endl;
            head->next = head;
            head->prev = head;
            Node* cur = l.head->next;
            while(cur != l.head)
            {
                PushBack(cur->data);
                cur = cur->next;
            }
        }
        //赋值运算符重载（现代写法）
        List<T>& operator=(List<T> l)
        {
         //   cout<<"List<T>& operator="<<endl;
           //将当前链表的头指针与链表l的头指针进行交换即可
           swap(head,l.head);
           return *this;
        }

        void Clear()
        {
            //遍历链表，释放除头结点之外的其余所有节点
            Node* to_delete = head->next;
            while(to_delete != head)
            {
                //保存cur的下一个节点
                Node* next_node = to_delete->next;
                delete to_delete;
                to_delete = next_node;
            }
        }
        //析构函数
        ~List()
        {
            //cout<<"~List()"<<endl;
            //先将链表的有效节点全部释放
            Clear();
            //再释放链表的头结点
            delete head;
        }

        ////尾插一个节点
        //void PushBack(const T& d)
        //{
        //    //首先创建一个节点
        //    Node* new_node = new Node(d);
        //    //然后将结点进行插入
        //    //last为未插入前的最后一个节点
        //    Node* last = head->prev;
        //    last->next = new_node;
        //    new_node->prev = last;
        //    new_node->next = head;
        //    head->prev = new_node;
        //}

        //任意位置插入一个元素:在pos结点之前进行插入
        void Insert(Node* pos,const T& d)
        {
            //首先判断pos是否为空
            assert(pos != NULL);
            //首先创建一个结点
            Node* new_node = new Node(d);
            //找到pos的前一个节点
            Node* prev_node = pos->prev;
            prev_node->next = new_node;
            new_node->prev = prev_node;
            new_node->next = pos;
            pos->prev = new_node;

        }
        //任意位置删除一个元素
        void Erase(Node* pos)
        {
            //不能删除空节点且删除结点的位置不能为头结点
            assert(head->next != head && pos != NULL && pos != head);
            //首先找到pos之前的结点和之后的结点
            Node* prev_node = pos->prev;
            Node* next_node = pos->next;
            prev_node->next = next_node;
            next_node->prev = prev_node;
            delete pos;
        }
        //尾插一个节点
        void PushBack(const T& d)
        {
            //尾插一个节点相当于在head之前插入一个结点
            Insert(head,d);
        }
        //尾删一个节点
        void PopBack()
        {
            assert(head->next != head);
            //相当于删除head->prev
            Erase(head->prev);
        }
        //头插一个结点
        void PushFront(const T& d)
        {
            //头插一个结点相当于在head->next之前插入一个结点
            Insert(head->next,d);
        }
        //头删一个节点
        void PopFront()
        {
            assert(head->next != head);
            //相当于删除head->next
            Erase(head->next);
        }
        //取首元素
        T& Front() const
        {
            assert(head->next != head);
            return head->next->data;
        }
        //取尾元素
        T& Back() const
        {
            //首先判断链表中有界定啊
            assert(head->next != head);
            return head->prev->data;
        }
        //计算大小
        size_t Size() const
        {
            //需从头遍历数组
            Node* cur = head->next;
            size_t size = 0;
            while(cur != head)
            {
                size++;
                cur = cur->next;
            }
            return size;
        }
        //判断是否为空
        bool Empty() const
        {
            return head->next == head;
        }

        void Display()
        {
            Node* cur = head->next;
            while(cur != head)
            {
                cout<<cur->data<<" ";
                cur = cur->next;
            }
            cout<<endl;
        }
    private:
        Node* head;
};

#if 0
int main()
{

    //测试在链表中插入string类型数据
    List<string> l1;
    List<string> l2(l1);
    //List<string> l3;
    //l3 = l1;

    //测试尾插一个元素
    l1.PushBack("yanxuechun");
    l1.PushBack("hujiangqi");
    l1.PushBack("hudameinv");
    l1.Display();
    l2 = l1;
    l2.Display();
    List<string> l3(l2);
    l3.Display();
//    l2.PushBack("yanxuechun");
//    l2.PushBack("hujiangqi");
//    l2.PushBack("hudameinv");
//    l2.Display();
//    l3.PushBack("yanxuechun");
//    l3.PushBack("hujiangqi");
//    l3.PushBack("hudameinv");
//    l3.Display();
//
    //测试头插一个插入一个结点
    l1.PushFront("ha");
    l1.PushFront("haha");
    l1.PushFront("hahaha");
    l1.Display();
    l2.PushFront("ha");
    l2.PushFront("haha");
    l2.PushFront("hahaha");
    l2.Display();
    l3.PushFront("ha");
    l3.PushFront("haha");
    l3.PushFront("hahaha");
    l3.Display();

    //测试头删一个节点
    l1.PopFront();
    l1.Display();
    //测试尾删一个节点
    l1.PopBack();
    l1.Display();
    l2.PopFront();
    l2.Display();
    l2.PopBack();
    l2.Display();
    l3.PopFront();
    l3.Display();
    l3.PopBack();
    l3.Display();

    //测试取队首，队尾，长度，是否为空
    cout<<l1.Front()<<endl;
    cout<<l1.Back()<<endl;
    cout<<l1.Size()<<endl;
    cout<<l1.Empty()<<endl;
    cout<<l2.Front()<<endl;
    cout<<l2.Back()<<endl;
    cout<<l2.Size()<<endl;
    cout<<l2.Empty()<<endl;
    cout<<l3.Front()<<endl;
    cout<<l3.Back()<<endl;
    cout<<l3.Size()<<endl;
    cout<<l3.Empty()<<endl;



    ////测试在链表中插入int类型数据
    //List<int> l1;
    //List<int> l2(l1);
    //List<int> l3;
    //l3 = l1;

    ////测试尾插一个元素
    //l1.PushBack(1);
    //l1.PushBack(2);
    //l1.PushBack(3);
    //l1.Display();
    //l2.PushBack(1);
    //l2.PushBack(2);
    //l2.PushBack(3);
    //l2.Display();
    //l3.PushBack(1);
    //l3.PushBack(2);
    //l3.PushBack(3);
    //l3.Display();


    ////测试头插一个插入一个结点
    //l1.PushFront(4);
    //l1.PushFront(5);
    //l1.PushFront(6);
    //l1.Display();
    //l2.PushFront(4);
    //l2.PushFront(5);
    //l2.PushFront(6);
    //l2.Display();
    //l3.PushFront(4);
    //l3.PushFront(5);
    //l3.PushFront(6);
    //l3.Display();
    //
    ////测试头删一个节点
    //l1.PopFront();
    //l1.Display();
    ////测试尾删一个节点
    //l1.PopBack();
    //l1.Display();
    //l2.PopFront();
    //l2.Display();
    //l2.PopBack();
    //l2.Display();
    //l3.PopFront();
    //l3.Display();
    //l3.PopBack();
    //l3.Display();

    ////测试取队首，队尾，长度，是否为空
    //cout<<l1.Front()<<endl;
    //cout<<l1.Back()<<endl;
    //cout<<l1.Size()<<endl;
    //cout<<l1.Empty()<<endl;
    //cout<<l2.Front()<<endl;
    //cout<<l2.Back()<<endl;
    //cout<<l2.Size()<<endl;
    //cout<<l2.Empty()<<endl;
    //cout<<l3.Front()<<endl;
    //cout<<l3.Back()<<endl;
    //cout<<l3.Size()<<endl;
    //cout<<l3.Empty()<<endl;


    return 0;
}
#endif


////实现双向循环带头节点的 链表
//typedef int DataType;
//
//struct ListNode
//{
//    struct ListNode* _next;
//    struct ListNode* _prev;
//    DataType _data;
//
//    //构造函数
//    ListNode(DataType data = DataType())
//    {
//        _data = data;
//        _next = NULL;
//        _prev = NULL;               
//    }
//};
//
//class List
//{
//    typedef ListNode Node;
//    public:
//        //构造函数
//        List()
//        {
//            //在构造函数中对链表进行初始化，创建头结点
//            _head = new Node;
//            _head->_next = _head;
//            _head->_prev = _head;
//        }
//        //拷贝构造函数
//        List(const List& l)
//        {
//            //首先创建一个头结点
//            //注意将_head的两个指针域也要进行初始化
//            //否则在后面的clear函数中会出现段错误
//            _head = new Node;
//            _head->_next = _head;
//            _head->_prev = _head;
//            //然后遍历链表l将l中的各节点依次插入到tmp中
//            Node* cur = (l._head)->_next;
//            while(cur != l._head)
//            {
//                this->PushBack(cur->_data);
//                cur = cur->_next;
//            }
//        }
//
//        //在链表中尾插一个节点
//        void PushBack(DataType data)
//        {
//            //首先创建一个节点
//            Node* newnode = new Node(data);
//            Node* tail = (this->_head)->_prev;
//            tail->_next = newnode;
//            newnode->_prev = tail;
//            newnode->_next = _head;
//            _head->_prev = newnode;
//        }
//
//        //赋值运算符重载
//        List& operator=(List l)
//        {
//            swap(_head,l._head);
//            return *this;
//        }
//
//        //清除除头节点之外的其余所有节点
//        void Clear()
//        {
//            //如果有其余节点
//            Node* cur = _head->_next;
//            while(cur != _head)
//            {
//                //保存要删除元素的下一个节点
//                Node* next_node = cur->_next;
//                delete cur;
//                cur = next_node;
//            }
//        }
//
//        //计算链表中的结点个数
//        //此时需要遍历数组，时间复杂度为：O(n)
//        size_t Size()
//        {
//            size_t size = 0;
//            Node* cur = _head->_next;
//            while(cur != _head)
//            {
//                size++;
//                cur = cur->_next;
//            }
//            return size;
//        }
//
//        //在任意位置之前插入一个结点
//        //Insert一般都指的是在pos之前进行插入
//        //void Insert(size_t pos,DataType data)
//        //{
//        //}
//
//        //在任意位置删除一个节点
//        void Erase();
//        //尾删一个元素
//        void PopBack()
//        {
//            assert(_head->_next != _head);
//            Node* to_delete = _head->_prev;
//            Node* prev_node = to_delete->_prev;
//            _head->_prev = prev_node;
//            prev_node->_next = _head;
//            delete to_delete;
//        }
//
//        //判断链表是否为空
//        bool Empty()
//        {
//            return _head->_next == _head;
//        }
//
//        //头插一个结点
//        void PushFront(DataType data)
//        {
//            //首先创建一个节点
//            Node* newnode = new Node(data);
//            Node* next_node = _head->_next;
//            _head->_next = newnode;
//            newnode->_prev = _head;
//            newnode->_next = next_node;
//            next_node->_prev = newnode;
//        }
//
//        //头删一个结点
//        void PopFront()
//        {
//            assert(_head->_next != _head);
//            Node* to_delete = _head->_next;
//            Node* next_node = to_delete->_next;
//            _head->_next = next_node;
//            next_node->_prev = _head;
//            delete to_delete;
//        }
//
//
//        void Display()
//        {
//            Node* cur = _head->_next;
//            while(cur != _head)
//            {
//                cout<<cur->_data<<endl;
//                cur = cur->_next;
//            }
//        }
//
//        //析构函数
//        ~List()
//        {
//            //先删除链表中的其余节点
//            Clear();
//            //再删除头节点
//            delete _head;
//        }
//    private:
//        Node* _head;
//};
//
//int main()
//{
//    List l1;
//    List l2(l1);
//    List l3;
//    l3 = l1;
//
//    //验证尾插，尾删
//    //l1.PushBack(10);
//    //l1.PushBack(20);
//    //l1.PushBack(30);
//    //l1.PushBack(40);
//    //l1.Display();
//    //cout<<l1.Size()<<endl;
//    //l1.PopBack();
//    //l1.Display();
//    //cout<<l1.Size()<<endl;
//    //l2 = l1;
//    //l2.Display();
//    //cout<<l2.Size()<<endl;
//    //List l4(l1);
//    //l4.Display();
//    //cout<<l4.Size()<<endl;
//
//    //验证头插，头删结点
//    l1.PushFront(10);
//    l1.PushFront(20);
//    l1.PushFront(30);
//    l1.PushFront(40);
//    l1.Display();
//    cout<<l1.Size()<<endl;
//    l1.PopFront();
//    l1.Display();
//    cout<<l1.Empty()<<endl;
//    return 0;
//}
