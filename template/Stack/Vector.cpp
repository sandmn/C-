


#include"Vector.h"



//模板不支持定义与声明分离,因为，分离之后:
//编译器对定义进行编译，模板此时没有实例化，所以会忽略，不会进行编译
//而在主函数中，因为只包含了模板函数的头文件，编译器看到函数的声明时，会认为有这个函数存在而编译通过
//在链接的时候就会因为找不到方法实现（模板没有实例化，所以没有生成对应的代码进行编译）而链接错误
//解决方法：1. 可以在方法文件中对模板进行显示实例化：此时在编译时就会生成一份实例化之后的代码，然后进行编译
//             但是，一次实例化只能实例一个类型的代码，下一次要使用另一类型作为模板参数时，还要再实例化一次
//             也就是说，要用到几种类型的模板参数，就要显示实例化几次。这样做比较复杂
//          2. 可以将声明和定义放在一个文件中(如.h或.hpp)，然后将该文件包含在主函数中。
//             当编译器对主函数进行编译时，头文件会展开。在调用模板函数时，因为模板函数的定义就存放在该文件中
//             所以，在编译时就会进行模板的实例化生成一份代码，然后对这份代码进行编译。
//             Linux下不以后缀区分文件，所以任何后缀均可以。但windows下以后缀来区分文件类型。
//             所以模板方法和定义放在一起的文件最好以.h或.hpp结尾。

template <class T>
Vector<T>::Vector()
    :_start(NULL)
    ,_finish(NULL)
     ,_endofstarge(NULL)
{
    // cout<<"Vector()"<<endl;
}
template<class T>
//拷贝构造函数
Vector<T>::Vector(const Vector<T>& v)
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
template<class T>
void Vector<T>::Swap(Vector<T>& v)
{
    swap(_start,v._start);
    swap(_finish,v._finish);
    swap(_endofstarge,v._endofstarge);
}

//赋值运算符重载（现代写法）
template<class T>
Vector<T>& Vector<T>::operator=(Vector<T> v)
{
    // cout<<"Vector<T>& operator="<<endl;
    this->Swap(v);
    return *this;
}
//析构函数
template<class T>
Vector<T>::~Vector()
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
template<class T>
void Vector<T>::PushBack(const T& data)
{
    //计算数组的实际大小
    size_t _size = _finish - _start;
    Insert(_size,data);
}
//尾删一个元素
template<class T>
void Vector<T>::PopBack()
{
    //计算数组的实际大小
    size_t _size = _finish - _start;
    Erase(_size - 1);
}

//扩容函数
template<class T>
void Vector<T>::Expand(size_t n)
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
template<class T>
void Vector<T>::Insert(size_t pos,const T& data)
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
template<class T>
void Vector<T>::Erase(size_t pos)
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
template<class T>
T& Vector<T>::Front() const
{
    assert(_start < _finish);
    return *_start;
}
//取数组尾元素
template<class T>
T& Vector<T>::Back() const
{
    assert(_start < _finish);
    return *(_finish - 1);
}

//计算数组的实际大小
template<class T>
size_t Vector<T>::Size() const
{
    return _finish - _start;
}
//计算数组的容量
template<class T>
size_t Vector<T>::Capacity() const
{
    return _endofstarge - _start;
}
//判断数组是否为空
template<class T>
bool Vector<T>::Empty() const
{
    return _start == _finish;
}
//保留
template<class T>
void Vector<T>::Reserve(size_t n)
{
    Expand(n);
    _finish = _start + n;
}
//重新设置数组的大小
//缺省参数只能在声明时给出
template<class T>
void Vector<T>::Resize(size_t n,const T& flag)
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
template<class T>
T& Vector<T>::operator[](size_t n) const
{
    assert(_start < _finish && n < Size());
    //cout<<_start[n]<<endl;
    return _start[n];
}

template<class T>
void Vector<T>::Display()
{
    T* index = _start;
    while(index < _finish)
    {
        cout<<(*index)<<" ";
        index++;
    }
    cout<<endl;
}


