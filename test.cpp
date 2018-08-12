#include<iostream>
#include<string>
#include<stack>
using namespace std;

int main()
{
    cout<<"hello world\n"<<endl;
    return 0;
}

//struct Point
//{
//    int row;
//    int col;
//
//};
//
//void Maze(int** A,int n,int m,Point entry,Point cur_point,Point pre,int P,stack<int>* cur,stack<int>* mmin,int* mypower)
//{
//    if(A == NULL)
//    {
//        return;
//    }
//    //首先判断某位置能否落脚
//    if(!CanStay(A,n,m))
//    {
//        return;
//    }
//    //如果能落脚，将该位置的坐标入栈，并标记
//    Point p = {cur_point.row,cur_point.col};
//    Mark(A,cur_point);
//    //判断是否到达出口
//    if(Exit(A,cur_point) == 1)
//    {
//        //判断是否到达出口
//        if(*mypower < P)
//        {
//            return;
//        }
//    }
//    Point up = cur_point;
//    up.row--;
//    Maze(A,n,m,entry,up,cur_point,P,&cur,&mmin,&mypower);
//    Point right = cur_point;
//    right.col++;
//    Maze(A,n,m,entry,right,cur_point,P,&cur,&mmin,&mypower);
//    Point down = cur_point;
//    down.row++;
//    Maze(A,n,m,entry,right,cur_point,P,&cur,&mmin,&mypower);
//    Point left = cur_point;
//    Maze(A,n,m,entry,left,cur_point,P,&cur,&mmin,&mypower);
//
//}
//
//
//int main()
//{
//    int n,m,P;
//    cin>>n>>m>>P;
//    int A[11][11];
//    int i = 0;
//    for(i = 0;i < n;i++)
//    {
//        int j = 0;
//        for(j = 0;j < m;j++)
//        {
//            cin>>A[i][j];
//        }
//    }
//    //定义一个栈保存走过的路径
//    stack<Point> cur;
//    stack<Point> mmin;
//    Point entry = {0,0};
//    Point cur_point = {0,0};
//    Point pre = {0,0};
//    int mypower = 0;
//    Maze(A,n,m,entry,cur_point,pre,P,&cur,&mmin,&mypower);
//    return 0;
//}
//
//
////int main()
////{
////    int n;
////    int sum;
////    cin>>n>>sum;
////    int* A = new int[n + 1];
////    int i = 0;
////    for(i = 1;i <= n;i++)
////    {
////        cin>>A[i];
////
////    }
////
////    //num的横纵坐标为i和j，表示遍历到第I个数时和为j的方案个数为num[i][j]
////    int num[1000][1000] = {0};
////    //因为遍历到第i个数和为j的方案个数为：
////    //如果A[i] <= j,则前i-1个数中何为j的方案个数加上前i-1个数中和为j-A[i]的方案个数
////    //即num[i][j] = num[i - 1][j] + num[i - 1][j - A[i]]
////    //如果A[i] > j,则num[i][j] = num[i - 1][j]
////    num[0][0] = 1;
////    for(i = 1;i <= n;i++)
////    {
////        int j = 0;
////        for(j = 0;j <= sum;j++)
////        {
////            if(A[i] <= j)
////            {
////                num[i][j] = num[i - 1][j] + num[i - 1][j - A[i]];
////            }
////            else
////            {
//                num[i][j] = num[i - 1][j];
//            }
//
//        }
//    }
//    cout<<num[n][sum];
//    return 0;
//}


////练习第一题:
//string Delete_Str(string src_str,string sub_str)
//{
//    string ret;
//    int index = 0;
//    for(index = 0;index < src_str.size();index++)
//    {
//        int i = 0;
//        for(i = 0;i < sub_str.size();i++)
//        {
//            if(src_str[index] == sub_str[i])
//            {
//                //ret.pushback(src_str[index]);
//                break;
//            }
//        }
//        if(i == sub_str.size())
//        {
//            ret.push_back(src_str[index]);
//        }
//    }
//    return ret;
//}
//int main()
//{
//    string src_str;
//    string sub_str;
//    getline(cin,src_str);
//    getline(cin,sub_str);
//    string ret = Delete_Str(src_str,sub_str);
//    cout<<ret<<endl;
//    return 0;
//}
