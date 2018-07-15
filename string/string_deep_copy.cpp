#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
using namespace std;


//实现string类的增删查改
class String
{
    public:
        //构造函数（设置缺省参数）
        String(const char* str = "")
            :_size(strlen(str))
            ,_capacity(_size)
            {
                _str = new char[_size + 1];
                strcpy(_str,str);
            }
        //自定义交换String类对象的函数
        //s1.Swap(s2)
       void Swap(String& s)
        {
            swap(_str,s._str);
            swap(_size,s._size);
            swap(_capacity,s._capacity);
        }
       // //如果是标准库中定义的交换函数,要定义一个对象，开销太大
       // 因为String类对象的创建要涉及深拷贝
       //
       // swap(String* s1,String* s2)
       // {
       //     String tmp;
       //     tmp = *s1;
       //     *s1 = *s2;
       //     *s2 = tmp;
       // }

        //拷贝构造函数（传统写法）
  //      String(const String& s)
  //          :_str(new char[strlen(s._str) + 1])
  //           ,_size(strlen(s._str))
  //           ,_capacity(strlen(s._str))
  //  {
  //      strcpy(_str,s._str);
  //  }

        //拷贝构造函数(现代写法)
        String(const String& s)
            :_str(NULL)
        {
            String tmp(s._str);
            Swap(tmp);
            //this->Swap(tmp);
            //s.Swap(*this);
        }


        ////赋值运算符重载（传统写法）
        //String& operator=(const String& s)
        //{
        //    if(this != &s)
        //    {
        //        char* tmp = new char[strlen(s._str) + 1];
        //        strcpy(tmp,s._str);
        //        delete[] _str;
        //        _str = tmp;
        //        _size = s._size;
        //        _capacity = s._capacity;
        //    }
        //    return *this;
        //}

        ////赋值运算符重载（现代写法1）
        //String& operator=(const String& s)
        //{
        //    if(this != &s)
        //    {
        //        String tmp(s._str);
        //        Swap(tmp);
        //    }
        //    return *this;
        //}

        //赋值运算符重载（现代写法2）
        String& operator=(String s)
        {
            Swap(s);
            //this->Swap(s);
            return *this;
        }

        //扩容函数：n为实际需要的内存大小
        void Expand(size_t n)
        {
            if(n > _capacity)
            {
                char* tmp = new char[n + 1];
                strcpy(tmp,_str);
                delete[] _str;
                _str = tmp;
                _capacity = n;
            }
        }

        //保留
        //在已知需要增容多大的内存时，提前开好空间，以防频繁的开空间造成性能问题
        void Reserve(size_t n)
        {
            Expand(n);
        }

        //重新设置字符串的实际大小，并初始化
        void ReSize(size_t n,char ch = '\0')
        {
            //如果所要求的大小n小于原来的实际大小，则将原来的实际大小改为n
            if(n < _size)
            {
                _str[n] = '\0';
                _size = n;
            }
            //如果原来的实际大小：
            else
            {
                //如果n小于_capacity,再将从_size到n的字符均初始化为字符ch
                //如果n大于_capacity，则进行扩容，将之后的字符均初始化为ch
                if(n > _capacity)
                {
                    Expand(n);
                }
                //此时的n必小于等于_capacity,将从_size开始的到n的字符全部初始化为字符ch
                int i = _size;
                for(;i < n;i++)
                {
                    _str[i] = ch;
                }
                _str[n] = '\0';
                _size += n;
            }
        }

        //实现增删查改
        //增：
        ////尾插一个字符（方法1）
        //void PushBack(char ch)
        //{
        //    //如果源字符串中的实际长度正好等于字符串的容量，此时就需要扩容
        //    //如果扩容，就扩大到原来的2倍
        //    if(_size == _capacity)
        //    {
        //        Expand(_capacity*2);
        //    }
        //    //在_size处添加字符
        //    //注意：更新_size的值
        //    _str[_size++] = ch;
        //    _str[_size] = '\0';
        //}
        //尾插一个字符（方法2）
        void PusHBack(char ch)
        {
            //尾插一个字符相当于在字符串的最后一个位置插入一个字符
            //此时直接调用Insert函数即可实现
            Insert(_size,ch);
        }

        ////尾插一个字符串（方法1）
        //void Append(const char* str)
        //{
        //    //如果实际需要的总字符串长度大于实际的字符串长度，则进行扩容
        //    if(_size + strlen(str) > _capacity)
        //    {
        //        //此时如果扩张到原来的2倍，可能不够，所以本次字符串实际需要多少，就扩张多少
        //        Expand(_size + strlen(str));
        //    }
        //    //然后将新字符串进行追加
        //    strcat(_str + _size,str);
        //    //然后更新字符串的实际长度值
        //    _size += strlen(str);
        //}
        ////尾插一个字符串（方法2）
        void Append(const char* str)
        {
            //相当于在最后一个位置插入一个字符串
            Insert(_size,str);
        }

        //任意位置插入一个字符
        void Insert(size_t pos,char ch)
        {
            //字符插入的位置不能超过字符串的长度
            assert(pos <= _size);
            //如果字符串实际长度已经达到字符串的容量，则进行扩容
            if(_size == _capacity)
            {
                Expand(_capacity*2);
            }
            //在容量已经满足的情况下添加字符
            //从源字符串的'\0'位置开始，向后移动，移动到pos位置处（包含pos位置）
            //此时end不能为size_t类型，如果Pos为0时，end就会减到-1
            //当减到-1时，因为end是无符号整型，此时就会非常大，所以，就会一直大于0，而陷入死循环
            //所以要将end改为int类型
            //size_t end = _size;
            int end = _size;
            //当end为-1时，与pos(pos = 0)进行比较，因为pos是无符号整型
            //此时，两种不同类型的数据进行比较时，就会自动进行类型提升，
            //将小范围的类型改变为大范围的类型，即int就会自动改变为无符号整型
            //又会变成很大的数与0进行比较，所以要将pos强转为int，这样就可以进行比较了
            for(;end >= (int)pos;end--)
            {
                _str[end + 1] = _str[end];
            }
            //字符后移成功之后，再在pos位置上添加新的字符
            _str[pos] = ch;
            //记得更新_size的值
            _size++;
        }

        //任意位置插入一个字符串
        void Insert(size_t pos,const char* str)
        {
            assert(pos <= _size);
            int len = strlen(str);//计算新添加字符串的长度
            //首先判断源字符串的容量是否足够，不够则进行扩容
            if(_size + len > _capacity)
            {
                //需要多少扩容多少即可
                Expand(_size + len);
            }
            //在容量已经足够的情况下添加字符串
            //此时需要将指定位置之后的所有字符均往后移新添加字符串的长度
            //待所有的字符后移完成之后再将新的字符串添加进源字符串
            //与上述相同，如果pos为0时，就会产生死循环，数组越界问题
            //所以要将end的类型设置为int，并且在比较时要将pos强转为int类型进行比较
            //从'\0'开始往后移动
            int end = _size;
            for(;end >= (int)pos;end--)
            {
                _str[end + len] = _str[end];
            }
            //字符后移成功之后，将新的字符串添加进源字符串
            //可以利用字符拷贝函数将新字符串中的有效字符拷贝到指定位置，但是不能拷贝'\0'
            strncpy(_str + pos,str,len);
            //注意，插入完成之后要更新字符串的实际字符值
            _size += len;
        }

        //"+="运算符重载:
        //"+="C风格的字符串:s1 += "hello"
        void operator+=(const char* str)
        {
            //相当于在最后一个位置插入一个字符串
            //首先计算调用字符串的长度
            //int size = strlen(this._str);
            Insert(_size,str);
            //插入完成之后更新实际字符串的长度值
            //_size += strlen(str);
            //return *this;
        }
        //String& operator+=(const char* str)
        //{
        //    //相当于在最后一个位置插入一个字符串
        //    //首先计算调用字符串的长度
        //    //int size = strlen(this._str);
        //    Insert(_size,str);
        //    //插入完成之后更新实际字符串的长度值
        //    //_size += strlen(str);
        //    return *this;
        //}
        //"+="String类的字符串
        String& operator+=(const String& s)
        {
            //相当于在最后一个位置插入一个字符串
            //首先计算调用字符串的长度
            //int size = strlen(this._str);
            Insert(_size,s._str);//*this += s._str;
            //插入完成之后更新实际字符串的长度值
           // _size += strlen(s._str);
            return *this;
        }
        //"+"运算符重载
        String operator+(const char* str)
        {
            //因为源字符串的内容和长度都不能改变
            //所以要新定义一个字符串取保存修改之后的字符串
            String ret(*this);
            ret += str;//调用上述的"+="运算符重载函数
            return ret;
        }
        String operator+(const String& s)
        {
            String ret(*this);
            ret += s;
            return ret;
        }

        //删：
        //尾删一个字符
        void PopBack()
        {
            assert(_size > 0);
            //将字符串最后一个实际字符变为\0
            _str[--_size] = '\0';
            //直接将字符串的实际大小减1即可
            //--_size;
        }
        //在任意位置删除一个长度为len的字符串
        void Erase(size_t pos,size_t len)
        {
            assert(pos < _size);
            //如果小于等于要删除的字符串，则从删除的位置开始将后续的字符全部删除
            if(_size - pos <= len)
            {
                _str[pos] = '\0';
                _size = pos;
            }
            //如果从删除的位置到结尾的字符串个数大于要删除的长度，
            //则直接删除指定的长度，然后将后续的字符串前移即可
            else
            {
                strcpy(_str + pos,_str + pos + len);
                _size = _size - len;
            }
           // _size = strlen(_str);
        }

        //查：
        //查看字符串的实际长度
        size_t Size()
        {
            return _size;
        }
        //查看字符串的容量
        size_t Capacity()
        {
            return _capacity;
        }
        //查看字符串是否为空
        bool Empty()
        {
            return _size == 0;
            //if(_size == 0)
            //{
            //    return true;
            //}
            //else
            //{
            //    return false;
            //}
        }
        //查看某个位置的字符
        char& operator[](size_t pos)
        {
            //assert(pos < _size);
            return _str[pos];
        }
        //查看某个字符所在的位置下标
        size_t Find(const char& ch) const
        {
            size_t index = 0;
            for(;index < _size;index++)
            {
                if(_str[index] == ch)
                {
                    return index;
                }
            }
            return -1;
        }
        //查看某个子字符串所在的位置下标
        size_t Find(const char* str) const
        {
            if(_str == NULL || str == NULL)
            {
                return -1;
            }
            char* src = _str;
            while(*src != '\0')
            {
                char* src_tmp = src;
                const char* dst = str;
                while(*src_tmp == *dst && *dst != '\0')
                {
                    src_tmp++;
                    dst++;
                }
                if(*dst == '\0')
                {
                    return src - _str;
                }
                if(*src_tmp != *dst)
                {
                    src++;
                }
            }
            return -1;
        }

        //"<"运算符重载
        //s1 < s2
        bool operator<(const String& s) const
        {
            char* str1 = _str;
            char* str2 = s._str;
            while(*str1 != '\0' && *str2 != '\0')
            {
                if(*str1 < *str2)
                {
                    return true;
                }
                else if(*str1 == *str2)
                {
                    str1++;
                    str2++;
                }
                else
                {
                    return false;
                }
            }
            if(*str1 == '\0' && *str2 != '\0')
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //"=="运算符重载
        bool operator==(const String& s) const 
        {
            const char* str1 = _str;
            const char* str2 = s._str;
            while(*str1 != '\0' && *str2 != '\0')
            {
                if(*str1 == *str2)
                {
                    str1++;
                    str2++;
                }
                else
                {
                    return false;
                }
            }
            if(*str1 == '\0' && *str2 == '\0')
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        //"<="运算符重载
        bool operator<=(const String& s) const
        {
            return (*this < s) || (*this == s);
        }
        //">"运算符重载
        bool operator>(const String& s) const
        {
            return !(*this <= s);
        }
        //">="运算符重载
        bool operator>=(const String& s) const
        {
            return !(*this < s);
        }
        //"!="运算符重载
        bool operator!=(const String& s) const
        {
            return !(*this == s);
        }

        //析构函数
        ~String()
        {
            if(_str)
            {
                delete[] _str;
                _str = NULL;
                _size = 0;
                _capacity = 0;
            }
        }
        char* c_str()
        {
            return _str;
        }
    private:
        char* _str;//_str用于保存字符串
        int _size;//_size用于指示字符串实际的字符个数
        int _capacity;//_capacity表示字符串的容量
    public:
        static int npos;
};
int String::npos = 1;

int main()
{
    //调用构造函数创建一个String类型的字符串
    String s1("hello");
    cout<<s1.c_str()<<endl;
    //调用拷贝构造函数新创建一个字符串
    String s2(s1);
    cout<<s2.c_str()<<endl;
    String s3 = s1;
    //s3.Display();

    s1 += " world";
    cout<<s1.c_str()<<endl;
    String s4;
    s4 = s1 + " world";
    cout<<s4.c_str()<<endl;

    
    ////在字符串s1字后追加一个字符
    //s1.PushBack('q');
    //cout<<s1.c_str()<<endl;
    //在字符串s2之后追加一个字符串
    //s2.Append(" world");
    //cout<<s2.c_str()<<endl;

    //测试Insert在任意位置插入一个字符
    //s1.Insert(0,'a');
    //cout<<s1.c_str()<<endl;
    //s1.Insert(6,'b');
    //cout<<s1.c_str()<<endl;
    //s1.Insert(10,'w');
    //cout<<s1.c_str()<<endl;
    
    //测试在任意位置插入一个字符串
    //s1.Insert(0,"world ");
    //cout<<s1.c_str()<<endl;
    //s1.Insert(5," world");
    //cout<<s1.c_str()<<endl;
    //s1.Insert(2," world");
    //cout<<s1.c_str()<<endl;
    //s1.Insert(10,"hello");
    //cout<<s1.c_str()<<endl;

    ////测试"+="C风格字符串
    //s1 += " world";
    //cout<<s1.c_str()<<endl;
    ////测试"+="String风格字符串
    //String s3 = " world";
    //s2 += s3;
    //cout<<s2.c_str()<<endl;

    ////测试"+"C风格字符串
    //String ret1 = s1 + " world";
    //cout<<ret1.c_str()<<endl;
    ////测试"+"String风格字符串
    //String ret2 = s2 + ret1;
    //cout<<ret2.c_str()<<endl;

    ////测试尾删一个字符
    //s1.PopBack();
    //cout<<s1.c_str()<<endl;

    //在指定位置删除指定长度的字符串
    //s1.Erase(0,1);
    //cout<<s1.c_str()<<endl;
    //s2.Erase(0,5);
    //cout<<s2.c_str()<<endl;
    //s3.Erase(0,7);
    //cout<<s3.c_str()<<endl;
    //s1.Erase(0,0);
    //cout<<s1.c_str()<<endl;
    //
    //s1.Erase(2,2);
    //cout<<s1.c_str()<<endl;
    //s2.Erase(2,3);
    //cout<<s2.c_str()<<endl;
    //s3.Erase(2,5);
    //cout<<s3.c_str()<<endl;
    //s1.Erase(2,0);
    //cout<<s1.c_str()<<endl;
    //
    //s1.Erase(5,2);
    //cout<<s1.c_str()<<endl;
    //s1.Erase(5,5);
    //cout<<s1.c_str()<<endl;
    //s1.Erase(5,10);
    //cout<<s1.c_str()<<endl;
    //s1.Erase(5,0);
    //cout<<s1.c_str()<<endl;
    
    ////测试Size,Capacity,Empty函数
    //cout<<s1.Size()<<endl;
    //s1.PushBack('a');
    //cout<<s1.Capacity()<<endl;
    //cout<<s1.Empty()<<endl;
    //s2.Erase(0,10);
    //cout<<s2.Size()<<endl;
    //cout<<s2.Capacity()<<endl;
    //cout<<s2.Empty()<<endl;

    ////测试"[]"运算符
    //cout<<s1[0]<<endl;
    //cout<<s1[3]<<endl;
    //cout<<s1[4]<<endl;
    //cout<<s1[5]<<endl;
    //cout<<s1[9]<<endl;

    ////查看某个字符所在的位置下标
    //cout<<s1.Find('h')<<endl;
    //cout<<s1.Find('l')<<endl;
    //cout<<s1.Find('o')<<endl;
    //cout<<s1.Find('a')<<endl;

    ////查看某个子字符串所在的位置下标
    //cout<<s1.Find("he")<<endl;
    //cout<<s1.Find("ll")<<endl;
    //cout<<s1.Find("o")<<endl;
    //cout<<s1.Find("gdf")<<endl;
    //cout<<s1.Find("hdg")<<endl;

    ////测试各种运算符重载
    //s2 = "world";
    //s3 = "hellohsbj";
    //String s4 = "hello";
    //String s5 = "adhkf";
    //cout<<(s1<s2)<<endl;
    //cout<<(s1<s3)<<endl;
    //cout<<(s1<s4)<<endl;
    //cout<<(s1<s5)<<endl;
    //cout<<(s1==s2)<<endl;
    //cout<<(s1==s3)<<endl;
    //cout<<(s1==s4)<<endl;
    //cout<<(s1==s5)<<endl;
    //cout<<(s1>s2)<<endl;
    //cout<<(s1>s3)<<endl;
    //cout<<(s1>s4)<<endl;
    //cout<<(s1>s5)<<endl;
    //cout<<(s1<=s4)<<endl;
    //cout<<(s1>=s4)<<endl;
    //cout<<(s1!=s4)<<endl;

    ////测试ReSize
    //s1.ReSize(3,'q');
    //cout<<s1.c_str()<<endl;
    //s2.PushBack('p');
    //s2.ReSize(8,'a');
    //cout<<s2.c_str()<<endl;
    //s3.ReSize(10,'o');
    //cout<<s3.c_str()<<endl;

    ////测试Reserve
    //int start1 = clock();
    //char buf[128];
    //int n = 20000;
    //int i = 0;
    //String s4;
    //for(i = 0;i < n;i++)
    //{
    //    //将整数以10进制的形式转化为字符串格式
    //    //该函数是在Windows下扩展的，Linux下不能使用
    //    itoa(i,buf,10);
    //    s4 += buf;
    //}
    //int end1 = clock();

    //int start2 = clock();
    //String s5;
    //s2.Reserve(s1.Capacity());
    //for(i = 0;i < n;i++)
    //{
    //    itoa(i,buf,10);
    //    s5 += buf;
    //}
    //int end2 = clock();

    //cout<<end1-start1<<endl;
    //cout<<end2-start2<<endl;
    
    return 0;
}


////实现C++标准库中的string类的基本操作(现代写法)
//class String
//{
//    public:
//        //自定义构造函数
//        String(const char* str)
//            :_str(new char[strlen(str) + 1])
//        {
//            cout<<"String(char*)"<<endl;
//            strcpy(_str,str);
//        }
//
//        //自定义拷贝构造函数（传统）
//       // String(const String& s)
//       //     :_str(new char[strlen(s._str) + 1])
//       // {
//       //     strcpy(_str,s._str);
//       // }
//
//        //自定义拷贝构造函数(现代)
//        String(const String& s)
//            :_str(NULL)
//        {
//            cout<<"String(String)"<<endl;
//            String tmp = s._str;
//            //String tmp(s._str);
//            swap(_str,tmp._str);
//        }
//
//        //赋值运算符重载（传统写法）
//        String& operator=(const String& s)
//        {
//            if(this != &s)
//            {
//                char* tmp = new char[strlen(s._str) + 1];
//                strcpy(tmp,s._str);
//                delete[] _str;
//                _str = tmp;
//            }
//            return *this;
//        }
//
//        ////赋值运算符重载（现代写法1）
//        //String& operator=(const String& s)
//        //{
//        //    if(this != &s)
//        //    {
//        //        //调用构造函数
//        //        //String tmp(s._str);
//        //        //或者调用拷贝构造函数
//        //        String tmp(s);
//        //        swap(_str,tmp._str);
//        //    }
//        //    return *this;
//        //}
//        ////赋值运算符重载（现代写法2）
//        //String& operator=(String s)
//        //{
//        //    swap(_str,s._str);
//        //    return *this;
//        //}
//        //析构函数
//        ~String()
//        {
//            if(_str)
//            {
//                delete[] _str;
//                _str = NULL;
//            }
//        }
//        //输出C风格的字符串
//        char* c_str()
//        {
//            return _str;
//        }
//    private:
//        char* _str;
//};
//
//int main()
//{
//    String s1("hello");//调用构造函数
//    cout<<s1.c_str()<<endl;
//
//    String s2(s1);//调用拷贝构造函数（现代写法）
//    cout<<s2.c_str()<<endl;
//
//    String s3 = "yanxuechun";//调用构造函数
//    s1 = s2 = s3;//调用赋值运算符重载（现代写法1）
//   // s1 = s2 = s3;//调用赋值运算符重载（现代写法2）
//    cout<<s1.c_str()<<endl;
//    cout<<s2.c_str()<<endl;
//    cout<<s3.c_str()<<endl;
//
//    return 0;
//}


////实现C++标准库的string类的相关操作
////构造，拷贝构造，赋值运算符重载，析构，返回C风格的字符串的传统写法
//class String
//{
//    public:
//        //自定义构造函数
//        String(const char* str)
//            :_str(new char[strlen(str) + 1])//自定义初始化列表，根据str给_str动态开辟空间
//        {
//            cout<<"String(str)"<<endl;
//            //将str中的内容拷贝到_str中
//            strcpy(_str,str);
//        }
//        //自定义拷贝构造函数
//        String(const String& s)
//            :_str(new char[strlen(s._str) + 1])//根据s中的char*类型的字符串为_str动态开辟空间
//        {
//            cout<<"String(String)"<<endl;
//            //将s中的char*类型的字符串内容拷贝给_str
//            strcpy(_str,s._str);
//        }
//
//        //自定义赋值运算符重载
//        //为了进行连续赋值，将赋值操作的返回值设置为String类型
//        //因为赋值操作，右侧的字符串内容不变，所以可以将其设定为const类型的引用
//        String& operator=(const String& s)
//        {
//            cout<<"operator="<<endl;
//            //判断是否是对自己进行赋值
//            if(this != &s)
//            {
//                //首先动态申请一片源串大小的空间
//                char* tmp = new char[strlen(s._str) + 1];
//                //将源串中的内容拷贝到新开辟的内存空间中
//                strcpy(tmp,s._str);
//                //将目标字符串中的char*类型的内存进行释放
//                delete[] _str;
//                //最后再将新开辟的内存拷贝给目标串
//                _str = tmp;
//            }
//            //最后返回this指针指向的字符串
//            return *this;
//        }
//        //自定义析构函数
//        ~String()
//        {
//            cout<<"~String"<<endl;
//            //对String中的字符串内容进行释放
//            delete[] _str;
//            _str = NULL;
//        }
//        //返回C风格的字符串
//        char* c_str()
//        {
//            return _str;
//        }
//
//    private:
//        //定义私有成员char*类型的指针
//        char* _str;
//};
//
//
//int main()
//{
//    //定义一个String类
//    String s1("hello");//调用构造函数
//    cout<<s1.c_str()<<endl;
//
//    String s4 = "hello";//调用构造函数
//    cout<<s4.c_str()<<endl;
//
//    char* str1 = "hello";
//    char str2[] = "hello";
//    cout<<sizeof(s1)<<endl;
//    cout<<sizeof(str1)<<endl;
//    cout<<sizeof(str2)<<endl;
//
//    String s2 = s1;//调用拷贝构造函数
//    cout<<s2.c_str()<<endl;
//
//    String s3("hello world!");
//    cout<<s3.c_str()<<endl;
//
//    s2 = s1 = s3;//调用赋值运算符重载
//    cout<<s1.c_str()<<endl;
//    cout<<s2.c_str()<<endl;
//
//    return 0;
//}
