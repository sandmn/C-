#include<iostream>
#include<stdio.h>
#include<assert.h>
using namespace std;

//实现双向循环带头节点的 链表

typedef int DataType;

struct ListNode
{
    struct ListNode* _next;
    struct ListNode* _prev;
    DataType _data;

    //构造函数
    ListNode(DataType data = DataType())
    {
        _data = data;
        _next = NULL;
        _prev = NULL;               
    }
};

class List
{
    typedef ListNode Node;
    public:
        //构造函数
        List()
        {
            //在构造函数中对链表进行初始化，创建头结点
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
        }
        //拷贝构造函数
        List(const List& l)
        {
            //首先创建一个头结点
            //注意将_head的两个指针域也要进行初始化
            //否则在后面的clear函数中会出现段错误
            _head = new Node;
            _head->_next = _head;
            _head->_prev = _head;
            //然后遍历链表l将l中的各节点依次插入到tmp中
            Node* cur = (l._head)->_next;
            while(cur != l._head)
            {
                this->PushBack(cur->_data);
                cur = cur->_next;
            }
        }

        //在链表中尾插一个节点
        void PushBack(DataType data)
        {
            //首先创建一个节点
            Node* newnode = new Node(data);
            Node* tail = (this->_head)->_prev;
            tail->_next = newnode;
            newnode->_prev = tail;
            newnode->_next = _head;
            _head->_prev = newnode;
        }

        //赋值运算符重载
        List& operator=(List l)
        {
            swap(_head,l._head);
            return *this;
        }

        //清除除头节点之外的其余所有节点
        void Clear()
        {
            //如果有其余节点
            Node* cur = _head->_next;
            while(cur != _head)
            {
                //保存要删除元素的下一个节点
                Node* next_node = cur->_next;
                delete cur;
                cur = next_node;
            }
        }

        //计算链表中的结点个数
        //此时需要遍历数组，时间复杂度为：O(n)
        size_t Size()
        {
            size_t size = 0;
            Node* cur = _head->_next;
            while(cur != _head)
            {
                size++;
                cur = cur->_next;
            }
            return size;
        }

        //在任意位置之前插入一个结点
        //Insert一般都指的是在pos之前进行插入
        //void Insert(size_t pos,DataType data)
        //{
        //}

        //在任意位置删除一个节点
        void Erase();
        //尾删一个元素
        void PopBack()
        {
            assert(_head->_next != _head);
            Node* to_delete = _head->_prev;
            Node* prev_node = to_delete->_prev;
            _head->_prev = prev_node;
            prev_node->_next = _head;
            delete to_delete;
        }

        //判断链表是否为空
        bool Empty()
        {
            return _head->_next == _head;
        }

        //头插一个结点
        void PushFront(DataType data)
        {
            //首先创建一个节点
            Node* newnode = new Node(data);
            Node* next_node = _head->_next;
            _head->_next = newnode;
            newnode->_prev = _head;
            newnode->_next = next_node;
            next_node->_prev = newnode;
        }

        //头删一个结点
        void PopFront()
        {
            assert(_head->_next != _head);
            Node* to_delete = _head->_next;
            Node* next_node = to_delete->_next;
            _head->_next = next_node;
            next_node->_prev = _head;
            delete to_delete;
        }


        void Display()
        {
            Node* cur = _head->_next;
            while(cur != _head)
            {
                cout<<cur->_data<<endl;
                cur = cur->_next;
            }
        }

        //析构函数
        ~List()
        {
            //先删除链表中的其余节点
            Clear();
            //再删除头节点
            delete _head;
        }
    private:
        Node* _head;
};

int main()
{
    List l1;
    List l2(l1);
    List l3;
    l3 = l1;

    //验证尾插，尾删
    //l1.PushBack(10);
    //l1.PushBack(20);
    //l1.PushBack(30);
    //l1.PushBack(40);
    //l1.Display();
    //cout<<l1.Size()<<endl;
    //l1.PopBack();
    //l1.Display();
    //cout<<l1.Size()<<endl;
    //l2 = l1;
    //l2.Display();
    //cout<<l2.Size()<<endl;
    //List l4(l1);
    //l4.Display();
    //cout<<l4.Size()<<endl;

    //验证头插，头删结点
    l1.PushFront(10);
    l1.PushFront(20);
    l1.PushFront(30);
    l1.PushFront(40);
    l1.Display();
    cout<<l1.Size()<<endl;
    l1.PopFront();
    l1.Display();
    cout<<l1.Empty()<<endl;
    return 0;
}
