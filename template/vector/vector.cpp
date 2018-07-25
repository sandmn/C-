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
        Vector()
            :_start(NULL)
             ,_finish(NULL)
             ,_endofstarge(NULL)
    {
       // cout<<"Vector()"<<endl;
    }
        //拷贝构造函数
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

        //涉及深拷贝的自定义类型一般都要自己编写交换函数
        void Swap(Vector<T>& v)
        {
            swap(_start,v._start);
            swap(_finish,v._finish);
            swap(_endofstarge,v._endofstarge);
        }

        //赋值运算符重载（现代写法）
        Vector<T>& operator=(Vector<T> v)
        {
           // cout<<"Vector<T>& operator="<<endl;
            this->Swap(v);
            return *this;
        }
        //析构函数
        ~Vector()
        {
           // cout<<"~Vector()"<<endl;
            if(_start)
            {
                delete[] _start;
                _start = NULL;
                _finish = NULL;
                _endofstarge = NULL;
            }
        }
        //尾插一个元素
        void PushBack(const T& data)
        {
            //计算数组的实际大小
            size_t _size = _finish - _start;
            Insert(_size,data);
        }
        //尾删一个元素
        void PopBack()
        {
            //计算数组的实际大小
            size_t _size = _finish - _start;
            Erase(_size - 1);
        }

        //扩容函数
        void Expand(size_t n)
        {
            size_t _capacity = _endofstarge - _start;
            size_t _size = _finish - _start;
            if(n > _capacity)
            {
                T* tmp = new T[n];
                //如果自定义类型（深拷贝）需要进行扩容时，就要进行元素的赋值，而不能进行浅拷贝
                int index = 0;
                for(;index < _size;index++)
                {
                    tmp[index] = _start[index];
                }
                //memcpy(tmp,_start,sizeof(T)*_capacity);
                delete[] _start;
                _start = tmp;
                _finish = _start + _size;
                _endofstarge = _start + n;
            }
        }

        //任意位置插入一个元素
        void Insert(size_t pos,const T& data)
        {
            //首先计算数组的实际大小
            size_t _size = _finish - _start;
            size_t _capacity = _endofstarge - _start;
            //判断插入的位置是否合法
            assert(pos <= _size);
            //判断数组的容量是否足够
            if(_endofstarge == _finish)//此时数组容量不足，需要扩容
            {
                //因为数组初始的 容量可能为0，所以在扩容时不能单纯的扩大倍数
                //size_t newcapacity = _capacity == 0? 3:2*_capacity;
                //Expand(newcapacity);
                Expand(_capacity*2 + 1);
            }
            //此时容量已经足够，可以进行元素的插入了
            //在对数组进行元素插入时，需要后移插入位置之后的各元素
            int end = _size - 1;
            for(;end >= (int)pos;end--)
            {
                _start[end + 1] = _start[end];
            }
            //元素后移结束之后，进行插入
            _start[pos] = data;
            //修改插入元素之后的实际大小值
            _finish++;
        }
        //任意位置删除一个元素
        void Erase(size_t pos)
        {
            //首先计算数组的实际大小
            size_t _size = _finish - _start;
            //判断删除的位置是否正确,以及数组是否有元素
            assert(_size > 0 && pos < _size);
            //此时需要将pos之后的元素依次前移
            int end = pos;
            for(;end < _size - 1;end++)
            {
                _start[end] = _start[end + 1];
            }
            //数据前移之后，更改实际的数组的实际大小
            _finish--;
        }

        //取数组首元素
        T& Front() const
        {
            assert(_start < _finish);
            return *_start;
        }
        //取数组尾元素
        T& Back() const
        {
            assert(_start < _finish);
            return *(_finish - 1);
        }

        //计算数组的实际大小
        size_t Size() const
        {
            return _finish - _start;
        }
        //计算数组的容量
        size_t Capacity() const
        {
            return _endofstarge - _start;
        }
        //判断数组是否为空
        bool Empty() const
        {
            return _start == _finish;
        }
        //保留
        void Reserve(size_t n)
        {
            Expand(n);
            _finish = _start + n;
        }
        //重新设置数组的大小
        void Resize(size_t n,const T& flag = T())
        {
            //计算数组的实际大小
            size_t _size = _finish - _start;
            //计算数组的容量
            size_t _capacity = _endofstarge - _start;
            //如果要求的大小小于数组实际的大小
            if(n < _size)
            {
                //此时指直接修改_finish指针即可
                _finish = _start + n;
                return;
            }
            //如果要求的大小大于数组实际的大小
            //如果数组的容量不足以存放要求的大小，此时就需要扩容
            if(n > _capacity)
            {
                Expand(n);
            }
            //此时数组的容量已经能够满足要求的大小
            //此时需要将_finish之后到n之间的元素值设置为要求的数据
            T* begin = _finish;
            while(begin < _start + n)
            {
                *begin = flag;
                begin++;
            }
            //最后修改_finish的值
            _finish = _start + n;
            return;
        }

        //[]运算符重载
        T& operator[](size_t n) const
        {
            assert(_start < _finish && n < Size());
            //cout<<_start[n]<<endl;
            return _start[n];
        }

        void Display()
        {
            T* index = _start;
            while(index < _finish)
            {
                cout<<(*index)<<" ";
                index++;
            }
            cout<<endl;
        }
    private:
        T* _start;
        T* _finish;
        T* _endofstarge;
};

int main()
{
    //此时插入字符串
    Vector<string> s1;
    Vector<string> s2(s1);
    Vector<string> s3;
    s3 = s1;
    
    //测试尾插一个元素
    s1.PushBack("hello");
    s1.PushBack("world");
    s1.PushBack("!!");
    s1.PushBack("@@");
    s1.Display();
    s2.PushBack("hello");
    s2.PushBack("world");
    s2.PushBack("!!");
    s2.PushBack("@@");
    s2.Display();
    s3.PushBack("hello");
    s3.PushBack("world");
    s3.PushBack("!!");
    s3.PushBack("@@");
    s3.Display();

    //测试任意位置插入一个元素
    s1.Insert(0,"im");
    s1.Insert(2,"a");
    s1.PopBack();
    s1.Insert(4,"chinese");
    //v1.Insert(7,9);
    s1.Display();
    
    s2.Insert(0,"im");
    s2.Insert(2,"a");
    s2.PopBack();
    s2.Insert(4,"chinese");
    //v1.Insert(7,9);
    s2.Display();

    s3.Insert(0,"im");
    s3.Insert(2,"a");
    s3.PopBack();
    s3.Insert(4,"chinese");
    //v1.Insert(7,9);
    s3.Display();

    s1.Erase(1);
    s1.Display();
    s1.Erase(0);
    s1.Display();
    s1.Erase(1);
    s1.Display();
    s2.Erase(1);
    s2.Display();
    s2.Erase(0);
    s2.Display();
    s2.Erase(1);
    s2.Display();
    s3.Erase(1);
    s3.Display();
    s3.Erase(0);
    s3.Display();
    s3.Erase(1);
    s3.Display();

    //测试Front Back Size Empty
    cout<<s1.Front()<<endl;
    cout<<s1.Back()<<endl;
    cout<<s1.Size()<<endl;
    cout<<s1.Empty()<<endl;
    cout<<s2.Front()<<endl;
    cout<<s2.Back()<<endl;
    cout<<s2.Size()<<endl;
    cout<<s2.Empty()<<endl;
    cout<<s3.Front()<<endl;
    cout<<s3.Back()<<endl;
    cout<<s3.Size()<<endl;
    cout<<s3.Empty()<<endl;

    //测试Resize
    s1.Resize(2);
    s1.Display();
    s1.Resize(5,"aa");
    s1.Display();
    s1.Resize(9,"aa");
    s1.Display();
    s2.Resize(2);
    s2.Display();
    s2.Resize(5,"aa");
    s2.Display();
    s2.Resize(9,"aa");
    s2.Display();

    cout<<s1[0]<<endl;
    cout<<s1[2]<<endl;
    cout<<s1[3]<<endl;
    cout<<s1[4]<<endl;
    cout<<s2[0]<<endl;
    cout<<s2[2]<<endl;
    cout<<s2[3]<<endl;
    cout<<s1[4]<<endl;
    

    //验证存放int的数组
    //Vector<int> v1;
    //Vector<int> v2(v1);

    //Vector<int> v3;
    //v3 = v1;

    //v1.PushBack(1);
    //v1.PushBack(2);
    //v1.PushBack(3);
    //v1.PushBack(4);
    //v2.PushBack(1);
    //v2.PushBack(2);
    //v2.PushBack(3);
    //v2.PushBack(4);
    //v3.PushBack(1);
    //v3.PushBack(2);
    //v3.PushBack(3);
    //v3.PushBack(4);
    //
    ////测试插入一个元素
    //v1.Insert(0,6);
    //v1.Insert(2,7);
    //v1.PopBack();
    //v1.Insert(4,8);
    ////v1.Insert(7,9);
    //v1.Display();
    //
    //v2.Insert(0,6);
    //v2.Insert(2,7);
    //v2.PopBack();
    //v2.Insert(4,8);
    ////v1.Insert(7,9);
    //v2.Display();
    //
    //v3.Insert(0,6);
    //v3.Insert(2,7);
    //v3.PopBack();
    //v3.Insert(4,8);
    ////v1.Insert(7,9);
    //v3.Display();

    ////测试Erase函数
    //v1.Erase(1);
    //v1.Display();
    //v1.Erase(0);
    //v1.Display();
    //v1.Erase(1);
    //v1.Display();
    //v2.Erase(1);
    //v2.Display();
    //v2.Erase(0);
    //v2.Display();
    //v2.Erase(1);
    //v2.Display();
    //v3.Erase(1);
    //v3.Display();
    //v3.Erase(0);
    //v3.Display();
    //v3.Erase(1);
    //v3.Display();
    ////测试Front Back Size Empty
    //cout<<v1.Front()<<endl;
    //cout<<v1.Back()<<endl;
    //cout<<v1.Size()<<endl;
    //cout<<v1.Empty()<<endl;
    //cout<<v2.Front()<<endl;
    //cout<<v2.Back()<<endl;
    //cout<<v2.Size()<<endl;
    //cout<<v2.Empty()<<endl;
    //cout<<v3.Front()<<endl;
    //cout<<v3.Back()<<endl;
    //cout<<v3.Size()<<endl;
    //cout<<v3.Empty()<<endl;

    ////测试Resize
    //v1.Resize(2);
    //v1.Display();
    //v1.Resize(5,100);
    //v1.Display();
    //v1.Resize(9,100);
    //v1.Display();
    return 0;
}




////因为数组中可能存放不同类型的数据，所以用一个泛型表示
//typedef int DataType;
//
//class Vector
//{
//    public:
//        //构造函数
//        Vector()
//            :_start(DataType())
//        {
//            _finish = _start;
//            _endofstarge = _start;
//        }
//        //拷贝构造函数
//        Vector(const Vector& v)
//        {
//            //首先计算v中的数组容量大小
//            size_t size = v._endofstarge - v._start;
//            //创建一个与v容量大小相同的空间
//            DataType* tmp = new DataType[size];
//            //将v中的内容拷贝至tmp中
//            memcpy(tmp,v._start,size*sizeof(DataType));
//            //将三个指针设置在对应的位置
//            _start = tmp;
//            _finish = _start + (v._finish - v._start);
//            _endofstarge = _start + size;
//        }
//
//        //交换函数
//        void Swap(Vector& v)
//        {
//            swap(_start,v._start);
//            swap(_finish,v._finish);
//            swap(_endofstarge,v._endofstarge);
//        }
//
//        //赋值运算符重载
//        //v1 = v2
//        Vector& operator=(Vector v)
//        {
//            this->Swap(v);
//            return *this;            
//        }
//        //析构函数
//        ~Vector()
//        {
//            delete[] _start;
//            _start = NULL;
//            _finish = NULL;
//            _endofstarge = NULL;
//        }
//
//        //扩容函数
//        void Expand(size_t n)
//        {
//            //数组的实际容量大小
//            int size = _endofstarge - _start;
//            if(n > size)
//            {
//                DataType* tmp = new DataType[n];
//                memcpy(tmp,_start,size*sizeof(DataType));
//                delete[] _start;
//                _start = tmp;
//                _finish = _start + size;
//                _endofstarge = _start + n;
//            }
//        }
//
//        ////尾插一个元素(方法1)
//        //void PushBack(const DataType data)
//        //{
//        //    size_t size = _endofstarge - _start;
//        //    if(_finish == _endofstarge)
//        //    {
//        //        Expand(2*size + 1);
//        //    }
//        //    *_finish = data;
//        //    _finish++;
//        //}
//        //尾插一个元素（方法2）
//        void PushBack(const DataType data)
//        {
//            int size = _finish - _start;
//            Insert(size,data);
//        }
//        ////尾删一个元素(方法1)
//        //void PopBack()
//        //{
//        //    assert(_start < _finish);
//        //    _finish--;
//        //}
//        //尾删一个元素（方法2）
//        void PopBack()
//        {
//            int size = _finish - _start;
//            Erase(size - 1);
//        }
//        //在任意位置插入一个元素
//        void Insert(size_t pos,DataType data)
//        {
//            //首先判断插入位置是否正确
//            //数组中的实际元素个数
//            int _size = _finish - _start;
//            //数组中的容量大小
//            size_t _capacity = _endofstarge - _start;
//            assert(pos <= _size);
//            //判断数组的容量是否足够，不够就进行扩容
//            if(_finish == _endofstarge)
//            {
//                Expand(_capacity*2 + 1);
//            }
//            //遍历数组将pos之后的元素均后移
//            int end = _size - 1;
//            for(;end >= (int)pos;end--)
//            {
//                _start[end + 1] = _start[end];
//            }
//            _start[pos] = data;
//            _finish++;
//        }
//        //任意位置删除一个元素
//        void Erase(size_t pos)
//        {
//            //首先判断数组中是否有元素以及删除的位置是否正确
//            //计算数组的实际大小
//            size_t _size = _finish - _start;
//            assert(_start < _finish && pos < _size);
//            int begin = pos;
//            for(;begin < _size - 1;begin++)
//            {
//                _start[begin] = _start[begin + 1];
//            }
//            _finish--;
//        }
//        //"[]"运算符重载
//        DataType& operator[](size_t pos)
//        {
//            //数组元素的实际长度
//            size_t _size = _finish - _start;
//            assert(_start < _finish && pos < _size);
//            return _start[pos];
//        }
//        //获取数组首元素
//        DataType& Front()
//        {
//            assert(_start < _finish);
//            return *_start;
//        }
//        //获取数组尾元素
//        DataType& Back()
//        {
//            assert(_start < _finish);
//            return *(_finish - 1);
//        }
//        //获取数组大小
//        size_t Size()
//        {
//            return (_finish - _start);
//        }
//        //判断数组是否为空
//        bool Empty()
//        {
//            return _finish == _start;
//        }
//        //重新设置数组的大小
//        void Resize(size_t n,DataType data = DataType())
//        {
//            size_t _size = _finish - _start;
//            //if(n < _size)
//            //{
//            //    _finish = _start + n;
//            //    return;
//            //}
//            //数组的容量大小
//            size_t _capacity = _endofstarge - _start;
//            if(n > _capacity)
//            {
//                Expand(n);
//            }
//            size_t begin = _size;
//            for(;begin < n;begin++)
//            {
//                _start[begin] = data;
//            }
//            _finish = _start + n;
//        }
//        //保留
//        void Reserve(size_t n)
//        {
//            Expand(n);
//        }
//        void Display()
//        {
//            DataType* cur = _start;
//            while(cur != _finish)
//            {
//                cout<<*cur<<" ";
//                cur++;
//            }
//            cout<<endl;
//        }
//    private:
//        DataType* _start;//指向数组头部
//        DataType* _finish;//数组实际元素的结束位置
//        DataType* _endofstarge;//数组实际容量结束的位置
//};
//
//int main()
//{
//    //调用构造函数
//    Vector v1;
//    //调用拷贝构造函数
//    Vector v2(v1);
//    Vector v3;
//    //调用赋值运算符重载
//    v3 = v1;
//
//
//
//
//    //v1.PushBack(1);
//    //v1.PushBack(2);
//    //v1.PushBack(3);
//    //v1.PushBack(4);
//    //v2.PushBack(1);
//    //v2.PushBack(2);
//    //v2.PushBack(3);
//    //v2.PushBack(4);
//    //v3.PushBack(1);
//    //v3.PushBack(2);
//    //v3.PushBack(3);
//    //v3.PushBack(4);
//
//    //测试尾插尾删一个元素
//    //v1.PushBack(3);
//    //v1.PushBack(7);
//    //v1.Display();
//    //v1.PopBack();
//    //v1.Display();
//    //v2.PushBack(5);
//    //v2.PushBack(2);
//    //v2.PushBack(4);
//    //v2.Display();
//    //v2.PopBack();
//    //v2.PopBack();
//    //v2.Display();
//    //v3.PushBack(5);
//    //v3.PushBack(2);
//    //v3.PushBack(4);
//    //v3.Display();
//    //v3.PopBack();
//    //v3.PopBack();
//    //v3.Display();
//    
//
//    
//
//    //测试插入一个元素
//    //v1.Insert(0,6);
//    //v1.Insert(2,7);
//    //v1.PopBack();
//    //v1.Insert(4,8);
//    ////v1.Insert(7,9);
//    //v1.Display();
//    //
//    //v2.Insert(0,6);
//    //v2.Insert(2,7);
//    //v2.PopBack();
//    //v2.Insert(4,8);
//    ////v1.Insert(7,9);
//    //v2.Display();
//    //
//    //v3.Insert(0,6);
//    //v3.Insert(2,7);
//    //v3.PopBack();
//    //v3.Insert(4,8);
//    ////v1.Insert(7,9);
//    //v3.Display();
//
//    //测试Erase函数
//    //v1.Erase(1);
//    //v1.Display();
//    //v1.Erase(0);
//    //v1.Display();
//    //v1.Erase(1);
//    //v1.Display();
//    //v2.Erase(1);
//    //v2.Display();
//    //v2.Erase(0);
//    //v2.Display();
//    //v2.Erase(1);
//    //v2.Display();
//    //v3.Erase(1);
//    //v3.Display();
//    //v3.Erase(0);
//    //v3.Display();
//    //v3.Erase(1);
//    //v3.Display();
//
//    //cout<<v1[0]<<endl;
//    //cout<<v1[2]<<endl;
//    //cout<<v1[3]<<endl;
//    ////cout<<v1[4]<<endl;
//    //cout<<v2[0]<<endl;
//    //cout<<v2[2]<<endl;
//    //cout<<v2[3]<<endl;
//    ////cout<<v1[4]<<endl;
//
//    //测试Front Back Size Empty
//    //cout<<v1.Front()<<endl;
//    //cout<<v1.Back()<<endl;
//    //cout<<v1.Size()<<endl;
//    //cout<<v1.Empty()<<endl;
//    //cout<<v2.Front()<<endl;
//    //cout<<v2.Back()<<endl;
//    //cout<<v2.Size()<<endl;
//    //cout<<v2.Empty()<<endl;
//    //cout<<v3.Front()<<endl;
//    //cout<<v3.Back()<<endl;
//    //cout<<v3.Size()<<endl;
//    //cout<<v3.Empty()<<endl;
//
//    //测试Resize
//    //v1.Resize(2);
//    //v1.Display();
//    //v1.Resize(5,100);
//    //v1.Display();
//    //v1.Resize(9,100);
//    //v1.Display();
//    return 0;
//}
