#include<iostream>
#include<vector>
#include<list>

using namespace std;
//迭代器失效问题

////打印链表
//template<class T>
//void Print_list(list<T>& l)
//{
//    //在函数模板中使用迭代器的问题：
//    //定义迭代器的前面声明为class或typedef,用于区别该迭代器是一个类型名还是一个list的成员
//    class list<T>::iterator it = l.begin();
//    while(it != l.end())
//    {
//        cout<<*it<<" ";
//        it++;
//    }
//    cout<<endl;
//}
//
////打印vector
//template<class T>
//void Print_vector(vector<T>& v)
//{
//    class vector<T>::iterator it = v.begin();
//    while(it != v.end())
//    {
//        cout<<*it<<" ";
//        it++;
//    }
//    cout<<endl;
//}

//打印容器中的内容
//以容器作为模板参数
template<class Container>
void PrintContainer(const Container& con)
{
    class Container::const_iterator it = con.begin();
    while(it != con.end())
    {
        cout<<*it<<" ";
        it++;
    }
    cout<<endl;
}


int main()
{
    list<int> l;
    int index = 0;
    for(; index < 8;index++)
    {
        l.push_back(index);
    }
    //链表的erase会使迭代器失效，造成野指针问题
    list<int>::iterator it1 = l.begin();
    while(it1 != l.end())
    {
        if(*it1 % 2 == 0)
        {
            it1 = l.erase(it1);
        }
        else
        {
            it1++;
        }
    }
    PrintContainer(l);
   // Print_list<int>(l);
    //链表的insert不会使迭代器失效
    it1 = l.begin();
    l.insert(it1,10);
    l.insert(it1,20);
    PrintContainer(l);
    //Print_list(l);//此处虽然没有传递T的类型，但是模板函数或根据参数进行类型推演，从而获取T的类型



    //vector的迭代器失效问题
    vector<int> v;
    for(index = 0;index < 8;index+=2)
    {
        v.push_back(index);
    }
    vector<int>::iterator it2 = v.begin();
    //vector中使用erase会出现为失效问题，造成逻辑错误
    //while(it2 != v.end())
    //{
    //    if(*it2 % 2 == 0)
    //    {
    //        it2 = v.erase(it2);
    //    }
    //    else
    //    {
    //        it2++;
    //    }
    //}
    //Print_vector(v);
    
    //vector中使用insert出现迭代器失效问题
    v.push_back(10);
    it2 = v.begin();
    size_t cap = v.capacity();
    cout<<cap<<endl;
    v.insert(++it2,50);
    PrintContainer(v);
    //Print_vector(v);


    return 0;
}
