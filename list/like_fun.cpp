#include<iostream>
#include<vector>
#include<list>
#include<functional>
#include<algorithm>
using namespace std;

template<class T>
struct Greater
{
    bool operator()(const T& l,const T& r)
    {
        return l > r;
    }
};

template<class T>
struct Less
{
    bool operator()(const T& l,const T& r)
    {
        return l < r;
    }
};

void Print(list<int>& l)
{
    list<int>::iterator it = l.begin();
    while(it != l.end())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}

int main()
{
    //Greater<int> g;
    ////利用模板类中对()进行运算符重载来实现仿函数
    ////像函数，但实际不是函数，而是根据类的对象调用类的成员函数
    //cout<<g(1,2)<<endl;
    //Less<float> l;
    //cout<<l(3.2,9.3)<<endl;

    //list<int> l;
    //l.push_back(4);
    //l.push_back(3);
    //l.push_back(5);
    //l.push_back(1);
    //l.push_back(7);
    //l.push_back(4);
    ////首先由greater类生成一个匿名对象
    ////然后在sort的实现中根据这个匿名对象调用该类型的成员变量进行比较
    //l.sort(greater<int>());
    //Print(l);
    //l.sort(less<int>());
    //Print(l);

    greater<int> g;
    cout<<g(1,2)<<endl;

    less<float> l;
    cout<<l(1.2,1.4)<<endl;

    int arr[] = {2,4,2,1,5};
    //sort(arr,arr + 5);
    sort(arr,arr + 5,greater<int>());
    int i = 0;
    for(i = 0;i < 5;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    vector<int> v;
    v.push_back(5);
    v.push_back(3);
    v.push_back(6);
    v.push_back(2);
    v.push_back(3);

    sort(v.begin(),v.end());
    for(i = 0;i < 5;i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;

    char ch[] = "532642";
    sort(ch,ch+6);
    cout<<ch<<endl;
    return 0;

}
