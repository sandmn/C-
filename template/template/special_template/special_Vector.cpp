#include<iostream>
#include<string.h>
#include<assert.h>
#include<string>
using namespace std;


//偏特化：1. 特殊部分参数
//        2. 对参数作出要求，而不指定具体类型
template<class T>
class Test
{
    public:
        Test()
        {
            cout<<"无特化"<<endl;
        }
    private:
        T a;
};

template<class T>
class Test<T*>
{
    public:
        Test()
        {
            cout<<"半特化"<<endl;
        }
    private:
        T* a;
};

template<class T>
class Test<T&>
{
    public:
        Test()
        {
            cout<<"半特化（引用）"<<endl;
        }
    private:
        int a;
};

//T& Test<const T&>::a = 10;
int main()
{
    const int& a = 10;
    cout<<a<<endl;
    Test<int> t1;
    Test<int&> t3;
    Test<int*> t2;
    return 0;
}


////注意：将无特化的模板放在前面，特化和半特化的模板放在后面
////模板类的使用
//template<class T1,class T2>
//class Vector
//{
//    public:
//        //构造函数
//        Vector()
//            :_start(NULL)
//             ,_finish(NULL)
//             ,_endofstarge(NULL)
//    {
//        cout<<"无特化"<<endl;
//    }
//    private:
//        T1* _start;
//        T1* _finish;
//        T1* _endofstarge;
//};
////类模板的全特化
//template<>
//class Vector<int,int>
//{
//    public:
//        //构造函数
//        Vector()
//        :_start(NULL)
//            ,_finish(NULL)
//            ,_endofstarge(NULL)
//            {
//                cout<<"全特化"<<endl;
//            }
//    private:
//        int* _start;
//        int* _finish;
//        int* _endofstarge;
//};
//
//template<class T>
//class Vector<int,T>
//{
//    public:
//        //构造函数
//        Vector()
//        :_start(NULL)
//            ,_finish(NULL)
//            ,_endofstarge(NULL)
//            {
//                cout<<"半特化"<<endl;
//            }
//    private:
//        T* _start;
//        T* _finish;
//        T* _endofstarge;
//
//};
//
//int main()
//{
//    //验证存放int的数组
//    Vector<int,int> v1;
//    Vector<int,string> v3;
//    Vector<string,string> v2;
//    return 0;
//}




