
//名字空间和域作用解析符的使用

#include<iostream>
#include<stdio.h>
using namespace std;

//int a = 30;
namespace my
{
    int a = 10;
    namespace it
    {
        int a = 50;
    }
}
namespace your
{
    int a = 20;
}

//int a = 30;
//using namespace your;
using namespace my;
int a = 30;
//cout<<a<<endl;
int main()
{
    int a = 40;
    //std::cout<<a<<std::endl;
    //std::cout<<::a<<std::endl;
    //std::cout<<my::a<<std::endl;
    //std::cout<<your::a<<std::endl;

    cout<<a<<endl;
    cout<<::a<<endl;
    cout<<my::it::a<<endl;
    cout<<your::a<<endl;
    return 0;
}



//int a = 10;
//int main()
//{
//    int a = 20;
//    //printf和cout的输出均遵循就近原则
//    //::左边为空，表示访问的是全局域
//    printf("%d\n",::a);
//    cout<<::a<<endl;
//    return 0;
//}

//int main()
//{
//    std::cout<<"hello world!"<<std::endl;
//    return 0;
//}
