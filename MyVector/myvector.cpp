#include<iostream>
#include<assert.h>
using namespace std;

//迭代器实现vector的基本操作

//定义一个自定义类型
struct Type
{
    int a1;
    int a2;
};


//定义一个const迭代器类型
template<class T>
struct Const_VectorIterator
{
    //构造函数
    Const_VectorIterator(T* p)
        :point(p)
    {}
    //拷贝构造，赋值运算符重载，析构均使用默认成员函数即可
    //*运算符重载
    const T& operator*()
    {
        return *point;
    }
    //->运算符重载
    const T* operator->()
    {
        return point;
    }
    //前置++运算符重载
    Const_VectorIterator<T>& operator++()
    {
        return ++point;
    }
    //后置++运算符重载
    Const_VectorIterator<T> operator++(int)
    {
        return point++;
    }
    //==运算符重载
    bool operator==(const Const_VectorIterator<T>& it)
    {
        return point == it.point;
    }
    //!=运算符重载
    bool operator!=(const Const_VectorIterator<T>& it)
    {
        return point != it.point;
    }
    private:
        T* point;
};

//定义一个非const迭代器类型
template<class T>
struct VectorIterator
{
    //构造函数
    VectorIterator(T* t)
        :point(t)
    {}
    //因为；拷贝和赋值运算符重载都是浅拷贝，所以使用默认的拷贝构造和赋值运算符重载即可
    //析构函数也使用默认即可
    
    //对*运算符重载
    T& operator*()
    {
        return *point;
    }
    //对->运算符重载
    T* operator->()
    {
        return point;
    }
    //对前置++运算符重载
    VectorIterator<T>& operator++()
    {
        return ++point;
    }
    //对后置++运算符重载
    VectorIterator<T> operator++(int)
    {
        return point++;
    }
    //对==运算符重载
    bool operator==(const VectorIterator<T>& it)
    {
        return point == it.point;
    }
    //对!=运算符重载
    bool operator!=(const VectorIterator<T>& it)
    {
        return point != it.point;
    }
    //迭代器中是对数组原始指针的封装
    T* point;   
};


template<class T>
class Vector
{
    public:
        typedef VectorIterator<T> Iterator;
        typedef Const_VectorIterator<T> Const_Iterator;
        //构造函数
        Vector()
            :_start(NULL)
             ,_finish(NULL)
             ,_endofstarge(NULL)
    {
//        cout<<"构造"<<endl;
    }

        Vector(const Vector<T>& v)
        {
            //cout<<"Vector(const Vector<T>& v)"<<endl;
            size_t _capacity = v._endofstarge - v._start;
            size_t _size = v._finish - v._start;
            _start = new T[_capacity];

            //类型萃取
            //基本类型+自定义类型（浅拷贝）
            //memcpy(_start,v._start,sizeof(T)*_capacity);
            //自定义类型（深拷贝）
            int index = 0;
            for(;index < _size;index++)
            {
                _start[index] = v._start[index];
            }
            _finish = _start + _size;
            _endofstarge = _start + _capacity;
        }

        //自定义交换函数
        void Swap(Vector<T>& v)
        {
            swap(_start,v._start);
            swap(_finish,v._finish);
            swap(_endofstarge,v._endofstarge);
        }
        //赋值运算符重载
        Vector<T>& operator=(Vector<T> v)
        {
  //          cout<<"赋值运算符重载"<<endl;
            Swap(v);
            return *this;
        }
        //析构函数
        ~Vector()
        {
    //        cout<<"析构"<<endl;
            if(_endofstarge != NULL)
            {
                delete[] _start;
            }
        }

        //尾插一个元素
        void PushBack(const T& data)
        {
            Insert(Size(),data);
        }


        void Expand(size_t n)
        {
            if(n > Capacity())
            {
                size_t size = Size();
                size_t cap = Capacity();
                //开空间
                T* tmp = new T[n];
                //拷贝数据
                int i = 0;
                for(;i < Size();i++)
                {
                    tmp[i] = _start[i];
                }
                //释放原空间
                delete[] _start;
                _start = tmp;
                _finish = _start + size;
                _endofstarge = _start + n;
            }
        }

        //在任意位置插入一个元素
        void Insert(size_t pos,const T& data)
        {
            //注意插入的位置要合法
            assert(pos <= Size());
            //如果容量不够，此时就需要进行扩容
            if(_finish == _endofstarge)
            {
                Expand(2*Capacity() + 1);
            }
            //在容量已经足够的情况下，在数组中进行插入
            //首先需要将pos及之后的元素均后移一个位置，然后进行插入，最后改变_finish的值
            int end = Size() - 1;
            for(;end >= (int)pos;end--)
            {
                _start[end + 1] = _start[end];
            }
            _start[pos] = data;
            _finish++;
        }

        //计算Vector中的实际元素个数
        size_t Size()
        {
            return _finish - _start;
        }
        //计算Vector中的容量
        size_t Capacity()
        {
            return _endofstarge - _start;
        }

        void Display()
        {
            size_t size = Size();
            size_t i = 0;
            for(;i < size;i++)
            {
                cout<<_start[i]<<" ";
            }
            cout<<endl;
        }

        //返回非const迭代器类型
        Iterator Begin()
        {
            return Iterator(_start);
        }
        Iterator End()
        {
            return Iterator(_finish);
        }
        //返回const迭代器类型
        Const_Iterator Begin() const
        {
            return Const_Iterator(_start);
        }
        Const_Iterator End() const
        {
            return Const_Iterator(_finish);
        }

    //vector中有三个成员变量
    private:
        T* _start;
        T* _finish;
        T* _endofstarge;
};

//打印非const类型数组元素
template<class Container>
void Print(Container& con)
{
    class Container::Iterator it = con.Begin();
    while(it != con.End())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}

//打印const类型数组元素
template<class Container>
void Print_Const(const Container& con)
{
    class Container::Const_Iterator it = con.Begin();
    while(it != con.End())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}

//打印非const自定义类型
template<class Container>
void Self_Print(Container& con)
{
    class Container::Iterator it = con.Begin();
    while(it != con.End())
    {
        cout<<"("<<it->a1<<","<<it->a2<<") ";
        it++;
    }
    cout<<endl;
}

//打印const自定义类型
template<class Container>
void Self_Print_Const(const Container& con)
{
    class Container::Const_Iterator it = con.Begin();
    while(it != con.End())
    {
        cout<<"("<<it->a1<<","<<it->a2<<") ";
        it++;
    }
    cout<<endl;
}

int main()
{
    Vector<int> v1;
    cout<<v1.Size()<<endl;
    v1.PushBack(10);
    v1.PushBack(20);
    v1.Display();
    Vector<int> v2 = v1;
    v2.Display();
    v1 = v2;
    v1.Display();
    Print(v1);
    Print_Const(v1);

    Vector<string> s1;
    s1.PushBack("yanxuechun");
    s1.PushBack("hujiangqi");
    Print(s1);
    Print_Const(s1);


    Type d = {1,10};
    Vector<Type> t1;
    t1.PushBack(d);
    t1.PushBack(d);
    t1.PushBack(d);

    Self_Print(t1);
    Self_Print_Const(t1);
    return 0;
}
