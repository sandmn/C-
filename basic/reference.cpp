#include<iostream>
using namespace std;


void Swap(int& i,int& r)
{
    int temp = i;
    i = r;
    r = temp;
}

void Test()
{
    //指针可以指向空
    int* p = 0;
    //引用必须指向有效的变量
    int& a = *p;
    int b = 2;
    Swap(a,b);
}
int main()
{
    Test();
    return 0;
}


////sizeof引用的大小为其所指向的变量的大小
////如果是不同类型之间的引用，则sizeof引用的大小为其所指向临时变量的大小
////const常引用不能进行自增自减操作
//int main()
//{
//    
//    const int& a = 2.3;
//    //a++;
//    cout<<sizeof(a)<<endl;
//    const double&b = 3;
//    cout<<sizeof(b)<<endl;
//    
//    int c = 5;
//    int& d = c;
//    d++;
//    cout<<d<<endl;
//    return 0;
//}


//////通过汇编看函数栈帧调用
//int Add(int a,int b)
//{
//    return a + b;
//}
//void Test()
//{
//    int ret = Add(1,2);
//}
//int main()
//{
//    Test();
//    return 0;
//}




////传引用做返回值，引用做返回值
//
////传值返回，出了作用域，变量不在
////int fun(int a,int b)
////{
////    return a+b;
////}
//
//////引用做返回值，出了作用域，变量还在
////int& fun(int a,int b)
////{
////    static int ret = a + b;
////    return ret;
////}
//
////引用做返回值，出了作用域，变量不在，结果未定义
//int& fun(int a,int b)
//{
//    int ret = a + b;
//    return ret;
//}
//
//int main()
//{
//    //将引用变量赋值给普通变量
//    int ret = 10;
//    int& ret1 = ret;
//    int ret2 = ret;
//    cout<<ret<<endl;
//    cout<<ret1<<endl;
//    cout<<ret2<<endl;
//
//    ret = 20;
//    cout<<ret<<endl;
//    cout<<ret1<<endl;
//    cout<<ret2<<endl;

//    int a = 1;
//    int b = 2;
//    int ret = fun(a,b);
//    cout<<ret<<endl;
//    fun(10,20);
//    cout<<ret<<endl;
//    //int& ret = fun(a,b);
//    //cout<<ret<<endl;
//}





//当不希望函数内改变参数的值时，可以使用常引用传参

////利用大数据测试值传递和引用传递的效率
//Struct data
//{
//    array[1000];
//};
//
//Void DealData(struct data d)
//{
//    d.array[0] = 0;
//    d.array[1] = 1;
//    d.array[2] = 2;
//}
//
//Int main()
//{
//    struct data d;
//    int i = 0;
//    int begin = 
//
//}

//值传递，引用传递，指针传递比较
//////值传递
////void Swap(int a,int b)
////{
////    int temp = a;
////    a = b;
////    b = temp;
////}
//
////引用传递
//void Swap(int& a,int& b)
//{
//    int temp = a;
//    a = b;
//    b = temp;
//}
//
//////指针传递
////void Swap(int* a,int* b)
////{
////    int temp = *a;
////    *a = *b;
////    *b = temp;
////}
////引用做参数
//int main()
//{
//    int a = 1;
//    int b = 2;
//    
//    cout<<"a:"<<a<<endl;
//    cout<<"b:"<<b<<endl;
//
//    Swap(a,b);
//    //Swap(&a,&b);
//
//    cout<<"a:"<<a<<endl;
//    cout<<"b:"<<b<<endl;
//
//    return 0;
//}


////const引用
//int main()
//{
//    //同类型间引用
//    int a1 = 10;
//    int& a2 = a1;
//    a2 = 11;
//    cout<<a1<<endl;
//
//    //权限缩小
//    const int& a3 = a2;
//    cout<<a3<<endl;
//    //a3 = 12;//const定义的常量不能进行赋值
//
//    //同类型进行引用
//    const int a4 = 20;
//    const int& a5 = a4;
//    cout<<a5<<endl;
//
//    //权限放大，引用失败
//    //int& a6 = a5;
//    //a6 = 21;
//    //cout<<a5<<endl;
//
//    //对常量进行引用
//    const int& a7 = 9;//常量只有常属性，只有常引用才可引用常量
//    cout<<a7<<endl;
//
//    //不同类型的变量间进行引用，实际是对临时变量进行引用
//    double a8 = 2.4489897;
//    //int& a9 = a8;
//    //cout<<a9<<endl;
//    //a10在引用时，a8首先生成临时变量，其中存放为2，a10实际引用的是a8的临时变量
//    //因为临时变量具有常属性，所以要用常引用对临时变量进行引用
//    const int& a10 = a8;
//    cout<<a10<<endl;
//    const float& a11 = a8;//此时的临时变量中存放的是2.44
//    cout<<a11<<endl;
//
//    //不同类型之间的引用，只能用const对临时变量进行引用
//    float a12 = 3.869867;
//    const int& a13 = a12;
//    const double& a14 = a12;
//    cout<<a13<<endl;
//    cout<<a14<<endl;
//
//    int a15 = 10;
//    //float& a16 = a15;
//    const float& a17 = a15;
//    cout<<a17<<endl;
//
//      //不同类型的常量间进行引用
//      //相当与对临时变量进行引用
//      const float& a18 = 2;
//      const double& a19 = 3;
//      const int& a20 = 7.34;
//      cout << a18 << endl;
//      cout << a19 << endl;
//      cout << a20 << endl;
//
//    return 0;
//}
////

//int main()
//{
//    //引用是给变量起一个别名
//    //引用在定义时必须进行初始化
//    //一个变量可以起多个别名
//    //一个引用初始化后，不能在对其他的变量进行引用
//    int a = 10;
//    int& b = a;
//    cout<<&a<<endl;
//    cout<<&b<<endl;
//
//    b = 20;
//    cout<<a<<endl;
//    cout<<b<<endl;
//
//    int& c = b;
//    cout<<c<<endl;
//
//    int d = 4;
//    int& b = d;
//    cout<<b<<endl;
//    return 0;
//}
