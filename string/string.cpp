#include<iostream>
#include<string.h>
using namespace std;

//实现C++标准库的string类的相关操作
class String
{
    public:
        //自定义构造函数
        String(const char* str)
            :_str(new char[strlen(str) + 1])//自定义初始化列表，根据str给_str动态开辟空间
        {
            //将str中的内容拷贝到_str中
            strcpy(_str,str);
        }
        //自定义拷贝构造函数
        String(const String& s)
            :_str(new char[strlen(s._str) + 1])//根据s中的char*类型的字符串为_str动态开辟空间
        {
            //将s中的char*类型的字符串内容拷贝给_str
            strcpy(_str,s._str);
        }

        //自定义赋值运算符重载
        //为了进行连续赋值，将赋值操作的返回值设置为String类型
        //因为赋值操作，右侧的字符串内容不变，所以可以将其设定为const类型的引用
        String& operator=(const String& s)
        {
            //判断是否是对自己进行赋值
            if(this != &s)
            {
                //首先动态申请一片源串大小的空间
                char* tmp = new char[strlen(s._str) + 1];
                //将源串中的内容拷贝到新开辟的内存空间中
                strcpy(tmp,s._str);
                //将目标字符串中的char*类型的内存进行释放
                delete[] _str;
                //最后再将新开辟的内存拷贝给目标串
                _str = tmp;
            }
            //最后返回this指针指向的字符串
            return *this;
        }
        //自定义析构函数
        ~String()
        {
            //对String中的字符串内容进行释放
            delete[] _str;
            _str = NULL;
        }
        //返回C风格的字符串
        char* c_str()
        {
            return _str;
        }

    private:
        //定义私有成员char*类型的指针
        char* _str;
};


int main()
{
    //定义一个String类
    String s1("hello");//调用构造函数
    cout<<s1.c_str()<<endl;
    String s2 = s1;//调用拷贝构造函数
    cout<<s2.c_str()<<endl;

    String s3("hello world!");
    cout<<s3.c_str()<<endl;

    s1 = s3;
    cout<<s1.c_str()<<endl;

    return 0;
}
