#include<iostream>
using namespace std;




////空指针传参
//class A
//{
//    public:
//        virtual void f1()
//        {
//
//        }
//        void f2()
//        {
//            cout<<"haha"<<endl;
//        }
//        void f3()
//        {
//            cout<<_a<<endl;
//        }
//    protected:
//        int _a;
//};
//
//int main()
//{
//    A* p = NULL;
//    //将空指针传参给this指针（空指针也是指针，不会编译报错）
//    //因为通过指针来调用虚函数，所以进行多态调用，
//    //此时需要在对象模型中知道虚表指针，所以要对对象进行解引用
//    //此时，对空指针进行解引用时，就会因为访问非法内存而异常终止
//    //p->f1();
//    //同样传参空指针，而不会编译报错
//    //但是调用的不是虚函数，所以进行普通调用
//    //此时，直接call到函数的入口地址处，而不需要对对对象解引用
//    //在该函数的执行中，也没有对对象的解引用，所以不会出现异常
//    p->f2();
//    //与上述情况基本相同，但是，在函数的执执行过程中
//    //因为要访问成员变量_a,所以要进入对象模型中，所以要对对象进行解引用
//    //此时，对空指针进行解引用就会出现异常
//    //p->f3();
//    return 0;
//}


////打印多继承的虚函数表
//class Base1
//{
//    public:
//        virtual void func1()
//        {
//            cout<<"Base1:func1()"<<endl;
//        }
//        virtual void func2()
//        {
//            cout<<"Base1:func2()"<<endl;
//        }
//    protected:
//        int a;
//};
//
//class Base2
//{
//    public:
//        virtual void func1()
//        {
//            cout<<"Base2:func1()"<<endl;
//        }
//        virtual void func2()
//        {
//            cout<<"Base2:func2()"<<endl;
//        }
//    protected:
//        int b;
//};
//
//class Device : public Base1,public Base2
//{
//    public:
//        virtual void func1()
//        {
//            cout<<"Device:func1()"<<endl;
//        }
//        virtual void func3()
//        {
//            cout<<"Device:func3()"<<endl;
//        }
//    protected:
//        int c;
//};
//
//
//typedef void (*FUNC)();
//
////打印虚函数表
//void PrintVtable(int* VTable)
//{
//    cout<<"虚函数表>"<<VTable<<endl;
//    int* index = VTable;
//    while(*index)
//    {
//        FUNC func = (FUNC)(*index);
//        cout<<(*index)<<"->";
//        func();
//        index++;
//    }
//    cout<<endl;
//}
//
//int main()
//{
//    Base1 b1;
//    Base2 b2;
//    Device d1;
//
//
//    //打印Base1的虚函数表
//    int* VTable1 = (int*)(*(int*)&b1);
//    PrintVtable(VTable1);
//    //打印Base2的虚函数表
//    int* VTable2 = (int*)(*(int*)&b2);
//    PrintVtable(VTable2);
//    //打印Device的虚函数表
//    int* DTable1 = (int*)(*(int*)&d1);
//    PrintVtable(DTable1);
//    int* DTable2 = (int*)(*(int*)((Base1)&d1 + 1));
//    PrintVtable(DTable2);
//
//    return 0;
//}

//打印单继承的虚函数表（有问题）
//class Base
//{
//    public:
//        virtual void func1()
//        {
//            cout<<"Base:func1()"<<endl;
//        }
//        virtual void func2()
//        {
//            cout<<"Base:func2()"<<endl;
//        }
//    protected:
//        int _a;
//};
//
//class Device : public Base
//{
//    public:
//        virtual void func1()
//        {
//            cout<<"Device:func1()"<<endl;
//        }
//        virtual void func3()
//        {
//            cout<<"Device:func3()"<<endl;
//        }
//        virtual void func4()
//        {
//            cout<<"Device:func4()"<<endl;
//        }
//    protected:
//        int _b;
//};
//
//typedef void (*FUN)();
//
////打印虚函数表
//void PrintVtable(int* VTable)
//{
//    cout<<"虚函数表:"<<VTable<<endl;
//    int* index = VTable;
//    while(*index != 0)
//    {
//        FUN func = (FUN)(*index);
//        cout<<(*index)<<"->";
//        func();
//        index++;
//    }
//}
//
//int main()
//{
//    Base b1;
//    Device d1;
//
//    int* VTable1 = (int*)(*(int*)&b1);
//    int* VTable2 = (int*)(*(int*)&d1);
//
//    PrintVtable(VTable1);
//    PrintVtable(VTable2);
//
//    return 0;
//}


