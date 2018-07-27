#include<iostream>
#include<vector>
using namespace std;

//打印vector中的元素：1. for循环+"[]"重载
//                    2. 迭代器

//1. 打印数组的元素值
//size() + for + []
template<class T>
void Print1(const vector<T>& v)
{
    int index = 0;
    for(index = 0;index < v.size();index++)
    {
        cout<<v[index]<<" ";
    }
    cout<<endl;
}

//迭代器不能使用模板
////迭代器打印vector元素
//template<class T>
//void Print2(const vector<T> v)
//{
//    vector<T>::const_iterator it = v.begin();
//    while(it != v.end())
//    {
//        cout<<*it<<" ";
//        it++;
//    }
//    cout<<endl;
//}
//
////2. 修改数组的元素值
////根据"[]"修改vector中的元素数值
//template<class T>
//void Motify1(vector<T>& v)
//{
//    int index = 0;
//    for(index = 0;index < v.size();index++)
//    {
//        v[index] += 1;
//    }
//}
//
////根据迭代器打印vector中的元素值
//template<class T>
//void Motify2(vector<T>& v)
//{
//    vector<T>::iterator it = v.begin();
//    //将数组各元素在原基础上加1
//    while(it != v.end())
//    {
//        *it += 1;
//        it++;
//    }
//}
//
////3. 逆序打印数组
// 根据size()+for+[]来实现
template<class T>
void Reverse_Print1(const vector<T>& v)
{
    int index = v.size() - 1;
    for(;index >= 0;index--)
    {
        cout<<v[index]<<" ";
    }
    cout<<endl;
}
////根据const的逆置迭代器打印
//template<class T>
//void Reverse_Print2(const vector<T>& v)
//{
//    vector<T>::const_reverse_iterator rit = v.rbegin();
//    while(rit != v.rend())
//    {
//        cout<<*rit<<" ";
//        rit++;
//    }
//    cout<<endl;
//}
//
////4.逆向修改vector中的元素值
//template<class T>
//void Reverse_Modify(vector<T>& v)
//{
//    vector<T>::reverse_iterator it = v.rbegin();
//    while(it != v.rend())
//    {
//        *it -= 1;
//        it++;
//    }
//
//}

int main()
{
    vector<int> v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    Print1(v1);
    Reverse_Print1(v1);
    //Print2(v1);

    vector<string> s1(3,"hello");
    s1.push_back("yanxuechun");
    Print1(s1);
    Reverse_Print1(s1);

    vector<int> v2(10);
    Print1(v2);

    //利用迭代器赋值：只能在同类型的数据之间进行赋值
    v2.assign(v1.begin(),v1.end());
    Print1(v2);

    //只能在同类型的数据之间进行赋值
    //s1.assign(v1.begin(),v1.end());
    //Print1(s1);

   // Print2(v1);

   // Motify1(v1);
   // Print1(v1);
   // Motify2(v1);
   // Print2(v1);

   // Reverse_Print1(v1);
   // Reverse_Print2(v1);

   // Reverse_Modify(v1);
   // Reverse_Print2(v1);

    //vector<string> s1(10,"hello");
    //s1.push_back("yanxuechun");
    //Print2(s1);
    //Reverse_Print2(s1);
    return 0;
}

