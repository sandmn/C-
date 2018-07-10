#include<iostream>
#include<stdlib.h>
using namespace std;


//构造函数一般用于为对象中的成员分配内存，析构函数一般用于将对象成员申请的内存进行释放
//而对于基本类型来说，在构造函数中没有申请内存，在析构函数中没有释放内存
//所以，调不调用构造和析构函数均可以，因此malloc和new对于基本类型来说没有区别
//因为基本类型不需要去动态申请内存，所以说new存在的意义是去动态申请空间的
//free存在的意义就是释放空间的
//
//
//所以动态申请基本类型时，也就不需要调用构造函数进行初始化，因此有无初始化这个过程都没有关系，
//所以，对于基本类型来说，malloc和new没有区别
//在释放动态申请的基本类型的内存时，没有调用析构函数进行清理，因此有无析构函数清理的过程都没有关系
//所以，对于基本类型来说，delete和free没有区别。
class Array
{
    public:
        //自定义构造函数
        Array(size_t size = 100)
            :_size(size)
             ,_a(0)
        {
            cout<<"Array(size_t size)"<<endl;
            if(_size)
            {
                _a = new int[size];
            }
        }
        //自定义析构函数
        ~Array()
        {
            cout<<"~Array()"<<endl;
            if(_a)
            {
                delete[] _a;
                _a = NULL;
            }
        }
        //自定义公有函数访问私有成员变量
        void Display()
        {
            cout<<_size<<endl;
        }
    private:
        int _size;
        int* _a;
};

//定位new表达式，用于对动态申请的内存进行初始化，格式为：
//new(指针) Type;(调用无参的构造函数)
//new(指针) Type(参数列表);(调用有参的构造函数)

int main()
{
    //利用malloc+定位new()来模拟new，实现动态开辟内存和初始化
    //利用显式的析构函数和free来模拟delete
    //Array* p1 = (Array*)malloc(sizeof(Array));
    //new(p1) Array;
    //p1->Display();
    //p1->~Array();
    //free(p1);

    //利用malloc+定位new()来模拟new[],实现数组的动态内存开辟和初始化
    //利用显式的析构函数和free来模拟delete
    Array* p2 = (Array*)malloc(10*sizeof(Array));
    int i = 0;
    for(;i < 10;i++)
    {
        new(p2+i) Array(29);
    }
    for(i = 0;i < 10;i++)
    {
        p2->Display();
    }

    for(i = 0;i < 10;i++)
    {
        (p2+i)->~Array();
    }
    free(p2);
    return 0;
}



////查看new和malloc调用构造函数和析构函数的过程
//int main()
//{
//    Array* p1 = new Array;
//    p1->Display();
//
//    Array* p2 = (Array*)malloc(sizeof(Array));
//    p2->Display();
//   
//    Array* p3 = new Array[3];
//    p3->Display();
//   
//    Array* p4 = new Array(20);
//    p4->Display();
//
//    delete p1;
//    free(p2);
//    delete[] p3;
//    delete p4;
//    return 0;
//}



//int main()
//{
//    ////内存申请和释放函数匹配问题
//    //int* p1 = new int;
//    //int* p2 = new int(8);
//    //int* p3 = new int[3];
//    //int* p4 = (int*)malloc(sizeof(int));
//
//    ////因为p1是动态申请的基本类型，所以不会调用析构函数，所以不会多分配4字节的内存
//    ////因此在调用delete[]进行释放时，不会调用析构函数进行清理，
//    ////首先会调用operator delete[],再调用operator delete,最后再调用free对申请的空间进行清理
//    //delete[] p1;
//
//    ////p2是动态申请的基本类型，所以不会调用析构函数
//    ////delete首先调用operator delete，再调用free进行释放
//    ////delete p2;
//
//    ////free直接释放动态申请的内存空间
//    //free(p2);
//
//    ////因为p3是动态申请的基本类型，所以不会调用析构函数，所以不会多分配4字节的内存
//    ////所以可以直接调用delete进行内存的释放
//    //delete p3;
//
//    ////同理，delete也可以对malloc动态申请的内存进行释放
//    //delete p4;
//
//
//
//    //malloc动态申请内存空间
//    //int* a1 = (int*)malloc(sizeof(int));
//    //int* a3 = (int*)malloc(5*sizeof(int));
//    //cout<<*a1<<endl;
//    //int i = 0;
//    //for(;i < 5;i++)
//    //{
//    //    cout<<a3[i]<<endl;
//    //}
//
//    //new动态申请内存空间
//    //int* a1 = new int;
//    //int* a2 = new int(19);
//    //int* a3 = new int[5];
//
//    //cout<<*a1<<endl;
//    //cout<<*a2<<endl;
//    //int i = 0;
//    //for(;i < 5;i++)
//    //{
//    //    cout<<a3[i]<<endl;
//    //}
//
//    //delete a1;
//    //delete a2;
//    //dlete[] a3;
//    return 0;
//}
