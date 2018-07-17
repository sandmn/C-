#include<iostream>
#include<string.h>
#include<assert.h>
#include<string>
using namespace std;

//因为数组中可能存放不同类型的数据，所以用一个泛型表示
typedef int DataType;

class Vector
{
    public:
        //构造函数
        Vector()
            :_start(DataType())
        {
            _finish = _start;
            _endofstarge = _start;
        }
        //拷贝构造函数
        Vector(const Vector& v)
        {
            //首先计算v中的数组容量大小
            size_t size = v._endofstarge - v._start;
            //创建一个与v容量大小相同的空间
            DataType* tmp = new DataType[size];
            //将v中的内容拷贝至tmp中
            memcpy(tmp,v._start,size*sizeof(DataType));
            //将三个指针设置在对应的位置
            _start = tmp;
            _finish = _start + (v._finish - v._start);
            _endofstarge = _start + size;
        }

        //交换函数
        void Swap(Vector& v)
        {
            swap(_start,v._start);
            swap(_finish,v._finish);
            swap(_endofstarge,v._endofstarge);
        }

        //赋值运算符重载
        //v1 = v2
        Vector& operator=(Vector v)
        {
            this->Swap(v);
            return *this;            
        }
        //析构函数
        ~Vector()
        {
            delete[] _start;
            _start = NULL;
            _finish = NULL;
            _endofstarge = NULL;
        }

        //扩容函数
        void Expand(size_t n)
        {
            //数组的实际容量大小
            int size = _endofstarge - _start;
            if(n > size)
            {
                DataType* tmp = new DataType[n];
                memcpy(tmp,_start,size*sizeof(DataType));
                delete[] _start;
                _start = tmp;
                _finish = _start + size;
                _endofstarge = _start + n;
            }
        }

        ////尾插一个元素(方法1)
        //void PushBack(const DataType data)
        //{
        //    size_t size = _endofstarge - _start;
        //    if(_finish == _endofstarge)
        //    {
        //        Expand(2*size + 1);
        //    }
        //    *_finish = data;
        //    _finish++;
        //}
        //尾插一个元素（方法2）
        void PushBack(const DataType data)
        {
            int size = _finish - _start;
            Insert(size,data);
        }
        ////尾删一个元素(方法1)
        //void PopBack()
        //{
        //    assert(_start < _finish);
        //    _finish--;
        //}
        //尾删一个元素（方法2）
        void PopBack()
        {
            int size = _finish - _start;
            Erase(size - 1);
        }
        //在任意位置插入一个元素
        void Insert(size_t pos,DataType data)
        {
            //首先判断插入位置是否正确
            //数组中的实际元素个数
            int _size = _finish - _start;
            //数组中的容量大小
            size_t _capacity = _endofstarge - _start;
            assert(pos <= _size);
            //判断数组的容量是否足够，不够就进行扩容
            if(_finish == _endofstarge)
            {
                Expand(_capacity*2 + 1);
            }
            //遍历数组将pos之后的元素均后移
            int end = _size - 1;
            for(;end >= (int)pos;end--)
            {
                _start[end + 1] = _start[end];
            }
            _start[pos] = data;
            _finish++;
        }
        //任意位置删除一个元素
        void Erase(size_t pos)
        {
            //首先判断数组中是否有元素以及删除的位置是否正确
            //计算数组的实际大小
            size_t _size = _finish - _start;
            assert(_start < _finish && pos < _size);
            int begin = pos;
            for(;begin < _size - 1;begin++)
            {
                _start[begin] = _start[begin + 1];
            }
            _finish--;
        }
        //"[]"运算符重载
        DataType& operator[](size_t pos)
        {
            //数组元素的实际长度
            size_t _size = _finish - _start;
            assert(_start < _finish && pos < _size);
            return _start[pos];
        }
        //获取数组首元素
        DataType& Front()
        {
            assert(_start < _finish);
            return *_start;
        }
        //获取数组尾元素
        DataType& Back()
        {
            assert(_start < _finish);
            return *(_finish - 1);
        }
        //获取数组大小
        size_t Size()
        {
            return (_finish - _start);
        }
        //判断数组是否为空
        bool Empty()
        {
            return _finish == _start;
        }
        //重新设置数组的大小
        void Resize(size_t n,DataType data = DataType())
        {
            size_t _size = _finish - _start;
            //if(n < _size)
            //{
            //    _finish = _start + n;
            //    return;
            //}
            //数组的容量大小
            size_t _capacity = _endofstarge - _start;
            if(n > _capacity)
            {
                Expand(n);
            }
            size_t begin = _size;
            for(;begin < n;begin++)
            {
                _start[begin] = data;
            }
            _finish = _start + n;
        }
        //保留
        void Reserve(size_t n)
        {
            Expand(n);
        }
        void Display()
        {
            DataType* cur = _start;
            while(cur != _finish)
            {
                cout<<*cur<<" ";
                cur++;
            }
            cout<<endl;
        }
    private:
        DataType* _start;//指向数组头部
        DataType* _finish;//数组实际元素的结束位置
        DataType* _endofstarge;//数组实际容量结束的位置
};

int main()
{
    //调用构造函数
    Vector v1;
    //调用拷贝构造函数
    Vector v2(v1);
    Vector v3;
    //调用赋值运算符重载
    v3 = v1;




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

    //测试尾插尾删一个元素
    //v1.PushBack(3);
    //v1.PushBack(7);
    //v1.Display();
    //v1.PopBack();
    //v1.Display();
    //v2.PushBack(5);
    //v2.PushBack(2);
    //v2.PushBack(4);
    //v2.Display();
    //v2.PopBack();
    //v2.PopBack();
    //v2.Display();
    //v3.PushBack(5);
    //v3.PushBack(2);
    //v3.PushBack(4);
    //v3.Display();
    //v3.PopBack();
    //v3.PopBack();
    //v3.Display();
    

    

    //测试插入一个元素
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

    //测试Erase函数
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

    //cout<<v1[0]<<endl;
    //cout<<v1[2]<<endl;
    //cout<<v1[3]<<endl;
    ////cout<<v1[4]<<endl;
    //cout<<v2[0]<<endl;
    //cout<<v2[2]<<endl;
    //cout<<v2[3]<<endl;
    ////cout<<v1[4]<<endl;

    //测试Front Back Size Empty
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

    //测试Resize
    //v1.Resize(2);
    //v1.Display();
    //v1.Resize(5,100);
    //v1.Display();
    //v1.Resize(9,100);
    //v1.Display();
    return 0;
}
