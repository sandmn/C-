#include<iostream>
#include<string.h>
using namespace std;
//类型萃取

////内置类型结构体
//struct __TrueType
//{
//    bool Get()
//    {
//        return true;
//    }
//};
////非内置类型结构体
//struct __FalseType
//{
//    bool Get()
//    {
//        return false;
//    }
//};
//template <typename T>
//struct TypeTraits
//{
//    typedef __FalseType __IsPODType;
//};
////内置类型的特化
//template <>
//struct TypeTraits< int>
//{
//    typedef __TrueType __IsPODType;
//};
//
//template<typename T>
//void Copy(T*tmp, T*_pdata,int _sz)
//{
//    if (TypeTraits<T>::__IsPODType().Get())
//    {
//        cout<<"memcpy"<<endl;
//        memcpy(tmp, _pdata, sizeof(T)*_sz);
//    }
//    else
//    {
//        cout<<"for"<<endl;
//        int i = 0;
//        for (i = 0;i < _sz;i++)
//        {
//            tmp[i] = _pdata[i];
//        }
//    }
//}
//                                        
//int main()
//{
//    char c1[125];
//    char* c2 = "hello";
//    Copy(c1,c2,6);
//    cout<<c1<<endl;
//    return 0;
//}


//定义两个类型用来标识自定义类型和基本类型

//基本类型
struct _TrueType
{
    bool Get()
    {
        return true;
    }
};

//自定义类型
struct _FalseType
{
    bool Get()
    {
        return false;
    }
};

//类型萃取（类型替换）

//将自定义类型定义为模板参数
template<class T>
class TypeTraits
{
    public:
        typedef _FalseType _IsPodType;   
};

//特化基本类型
template<>
class TypeTraits<int>
{
    public:
        typedef _TrueType _IsPodType;
};

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
            cout<<"Vector(const Vector<T>& v)"<<endl;
            size_t _capacity = v._endofstarge - v._start;
            size_t _size = v._finish - v._start;
            _start = new T[_capacity];

            //类型萃取
            //基本类型+自定义类型（浅拷贝）
            //TypeTraits<T>表示一个类型
            //TypeTraits<T>::_IsPodType:表示取该类型中的一个成员_IsPodType
            //TypeTraits<T>::_IsPodType():表示生成_IsPodType类型的一个匿名对象
            //TypeTraits<T>::_IsPodType().Get()：表示根据匿名对象调用该类型中的一个成员函数
            if(TypeTraits<T>::_IsPodType().Get())
            {
                cout<<"memcpy"<<endl;
                memcpy(_start,v._start,sizeof(T)*_capacity);
            }
            else
            {
                cout<<"for"<<endl;
                //自定义类型（深拷贝）
                int index = 0;
                for(;index < _size;index++)
                {
                    _start[index] = v._start[index];
                }
                _finish = _start + _size;
                _endofstarge = _start + _capacity;
            }
        }
    private:
        T* _start;
        T* _finish;
        T* _endofstarge;

};

int main()
{
    Vector<int> v1;
    Vector<int> v2(v1);
    Vector<string> v3;
    Vector<string> v4(v3);
    return 0;
}
