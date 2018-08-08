#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

//top_k问题
//方法一：首先对数组进行排序，在使用resize取前k个元素

//打印vector
template<class Container>
void Print(const Container& con)
{
    class Container::const_iterator it = con.begin();
    while(it != con.end())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;

}


//方法二：
//使用优先级队列取前k个最大的数
//如果取前k个最大的数，则创建小堆，每次剔除一个最小的数，遍历完待排序区间之后，所有最小的数剔除完毕，就剩下k个最大的数
//如果取前k个最小的数，则创建大堆，每次剔除一个最大的数，遍历完待排序区间之后，所有最大的数剔除完毕，就剩下k个最小的数
int main()
{
    vector<int> v;
    v.push_back(9);
    v.push_back(30);
    v.push_back(27);
    v.push_back(2);
    v.push_back(7);
    v.push_back(42);

    int k = 4;

    //取前k个最小的数
    //定义一个基于大堆的优先级队列
    priority_queue<int> gq;
    int i = 0;
    //首先在优先级队列中放置k个元素
    for(;i < k;i++)
    {
        gq.push(v[i]);
    }
    //然后对待排序区间的未入队元素进行比较
    //如果未入队元素比堆顶元素小，则出队队首元素，在入队小的元素
    //遍历完整个待排序区间，即获得前k个最小的元素
    while(i < v.size())
    {
        if(v[i] < gq.top())
        {
            gq.pop();
            gq.push(v[i]);
        }
        i++;
    }

    vector<int> lv;
    while(gq.empty() != 1)
    {
        lv.push_back(gq.top());
        gq.pop();
    }
    Print(lv);


    ////取前k个最大的数
    ////定义一个基于小堆的优先级队列
    priority_queue<int,vector<int>,greater<int> > lq;
    i = 0;
    for(i = 0;i < k;i++)
    {
        lq.push(v[i]);
    }
    while(i < v.size())
    {
        if(v[i] > lq.top())
        {
            lq.pop();
            lq.push(v[i]);
        }
        i++;
    }
    vector<int> gv;
    while(lq.empty() != 1)
    {
        gv.push_back(lq.top());
        lq.pop();
    }
    Print(gv);
    return 0;
}


//方法一：
//使用排序函数取前k个最大的数
//int main()
//{
//    vector<int> v;
//    v.push_back(10);
//    v.push_back(19);
//    v.push_back(9);
//    v.push_back(4);
//    v.push_back(20);
//    v.push_back(6);
//    Print(v);
//
//    //对数组进行排序
//    sort(v.begin(),v.end());
//    Print(v);
//
//    //取前k个元素
//    v.resize(4);
//    Print(v);
//
//
//    return 0;
//}
