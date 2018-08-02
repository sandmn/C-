#include<iostream>
#include<list>
#include <algorithm>
using namespace std;

//STL中list的使用
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
    list<int> l;
    int i = 0;

    //push_back,push_front的使用
    for(i = 0;i < 5;i++)
    {
        l.push_back(i);
    }
    for(i = 5;i < 10;i++)
    {
        l.push_front(i);
    }
    Print(l);

    //pop_front,pop_back的使用
    l.pop_front();
    l.pop_back();//8 7 6 5 0 1 2 3
    Print(l);
    
    list<int>::iterator it1 = l.begin();

    ////迭代器的使用
    //list<int>::reverse_iterator it2 = l.rbegin();
    //while(it2 != l.rend())
    //{
    //    cout<<*it2<<" ";
    //    it2++;
    //}
    //cout<<endl;

    ////resize的使用
    //l.resize(2);
    //Print(l);
    //l.resize(10);
    //Print(l);


    ////insert的使用
    //l.insert(it1,50);
    //l.insert(it1,5,5);
    //l.insert(it1++,100);//迭代器重载了++运算符，但是没有重载+运算符
    //l.insert(it1,l.begin(),l.end());
    //Print(l);

    ////erase的使用:注意迭代器失效的问题（erase的返回值用于解决迭代器失效的问题）
    //it1 = l.erase(it1);//erase的返回值为待删除元素下一个位置的迭代器
    //it1 = l.erase(it1);
    //Print(l);//6 5 0 1 2 3
    //list<int>::iterator it2 = l.end();
    //it1++;
    //cout<<*it1<<endl;
    //it2--;
    //it2--;
    //++it2;
    //cout<<*it2<<endl;
    //it1 = l.erase(it1,it2);
    //Print(l);
    //cout<<*it1<<endl;

    ////逆置
    //l.reverse();
    //Print(l);

    ////assign的使用
    //list<int> l1;
    //l1.assign(5,10);
    //Print(l1);
    //l1.assign(l.begin(),l.end());
    //Print(l1);

    ////sort的使用
    //l.sort();
    //Print(l);
    //l.sort(g);
    //Print(l);

    //find的使用:在链表的某个数之前插入一个数
    //先根据find找到该元素的位置
    //在利用insert在其之前进行插入
    //it1 = find(l.begin(),l.end(),5);
    //if(it1 != l.end())
    //{
    //    l.insert(it1,100);
    //}
    //Print(l);

    ////将字符串中的单词进行逆置
    //string s = "hello world";
    //string::iterator it3 = s.begin();
    //do
    //{
    //    string::iterator it4 = s.end();
    //    it4 = find(it3,it4,' ');
    //    if(it4 == s.end())
    //    {
    //        reverse(it3,it4);
    //        break;
    //    }
    //    reverse(it3,it4);
    //    it3 = ++it4;
    //}while(1);
    //reverse(s.begin(),s.end());
    //cout<<s<<endl;
    return 0;
}
