#include<iostream>
using namespace std;

//非类型的模板函数参数(有问题)
template<class T,int N>
void Print(const T& n)
{
    cout<<(n+N)<<endl;
}


//使用非类型的类模板参数
template<class T,size_t MAX = 10>
class Test
{
    public:
        void Set(const T& s)
        {
            data[0] = s;
         //   cout<<data[0]<<endl;
        }
        void Put()
        {
            cout<<data[0]<<endl;
        }
    private:
        T data[MAX];
};


int main()
{
    Test<string,5> t1;
    t1.Set("yanxuechun");
    t1.Put();
 
    Print(10,5);
    return 0;
}
