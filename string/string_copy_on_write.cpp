#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

class String
{
    public:
        //构造函数
        //在构造函数中申请一片字符串大小的空间和引用计数大小的空间
        String(const char* str = "")
            :_size(strlen(str))
            ,_capacity(_size)
            ,_pcount(new int(1))
        {
            _str = new char[_size];
            strcpy(_str,str);
        }
        //拷贝构造函数
        //将左边的指针指向右边字符串的指针
        //然后是右边字符串的引用计数值加1，使左边引用计数指针等于右边引用计数指针
        String(const String& s)
            :_str(s._str)
             ,_size(s._size)
             ,_capacity(s._capacity)
        {
            ++*(s._pcount);
            _pcount = s._pcount;
            //strcpy(_str,str);
        }
        //赋值运算符重载
        String& operator=(String& s)
        {
            //先考虑是否是自己给自己赋值，如果是，则不用再进行后续操作了
            if(this != &s)
            {
                //先使左边的字符串额引用计数值减1
                --(*_pcount);
                //1.如果减完之后的值为0，说明没有其他字符串与之共享空间
                //再使左边字符串的指针等于右边字符串的指针，并且使右边字符串的引用计数加1之后赋值为左边字符串的引用计数
                if((*_pcount) == 0)
                {
                    //则直接将字符串空间和引用计数空间释放
                    delete[] _str;
                    delete _pcount;
                }
                //2.如果减完之后的值不为0，则说明有其他字符串在与之共享空间
                //此时，不用释放空间，
                //只需使左边字符串的指针等于右边字符串的指针，并且使右边字符串的引用计数加1之后赋值给左边字符串的引用计数
                _str = s._str;
                ++(*(s._pcount));
                _pcount = s._pcount;
                _size = s._size;
                _capacity = s._capacity;
            }
        }
        //析构函数
        ~String()
        {
            //先使引用计数减1
            --*(_pcount);
            //如果减完之后的引用计数为0了，则直接释放字符串和引用计数的空间
            if(*(_pcount) == 0)
            {
                delete[] _str;
                delete _pcount;
            }
            //否则，不用释放空间
            //最后将其余两个成员赋值为0即可
            _size = 0;
            _capacity = 0;
        }

        void CopyOnWrite()
        {
            //如果此时的引用计数为1，则不用另外开辟空间，直接进行修改就可以
            //如果此时的引用计数大于1，则需要另外开辟空间进行写时拷贝
            if(*_pcount > 1)
            {
                //首先开辟一段与原来大小相同的空间
                char* tmp_str = new char[_capacity + 1];
                //将原来的内容复制到新开辟的空间上
                strcpy(tmp_str,_str);
                //在开辟一段引用计数大小的空间，并初始化为1
                int* tmp_pcount = new int(1);
                //将原来的引用计数值减1
                --(*_pcount);
                //将字符串和引用计数的指针指向新开辟的空间
                _str = tmp_str;
                _pcount = tmp_pcount;
            }
        }

        //读时不拷贝
        //因为要进行读，所以this指针指向的对象不能改变，所以可以用const进行声明
        //因为字符串再返回前后均存在，所以可以返回字符的引用
        //因为返回的字符的值不能改变，所以将其设置为const类型的
        //const char& operator[](size_t n) const
        //{
        //    cout<<"read"<<endl;
        //    assert(n < _size);
        //    return *(_str + n);
        //}
        //"[]"运算符重载:写时拷贝，读时也拷贝
        //返回值为常引用，即返回值不能改变
        //因为要进行写实拷贝，即对象的成员要改变，则this指针指向的对象不能设置为const
        //因为字符串在函数调用结束后还存在，所以可以直接返回引用，因为对于返回的字符还有可能进行改变，所以不能返回const类型
        char& operator[](size_t n)
        {
            cout<<"write"<<endl;
            assert(n < _size);
            CopyOnWrite();
            return *(_str + n);
        }


        void Expand(size_t n)
        {
            //如果n大于_capacity时才需要进行扩容
            if(n > _capacity)
            {
                //扩充n+1大小的容量
                char* tmp = new char[n + 1];
                //将_str中的内容拷贝到tmp中
                strcpy(tmp,_str);
                //然后释放原有的内存
                delete[] _str;
                //将tmp赋值给_str
                _str = tmp;
                //最后对_capacity的值进行修改
                _capacity = n;
            }
        }
        void Reserve(size_t n);
        void Resize(size_t n,char ch = '\0');

        //增删查改
        //增：
        void PushBack(const char ch)
        {
            //因为要多字符串进行写入，所以要进行写时拷贝
            CopyOnWrite();
            //如果当前字符串的实际大小已达到容量，则在进行插入时就需要扩容
            if(_size == _capacity)
            {
                Expand(_capacity*2);
            }
            //在容量已足够的情况下，直接进行插入元素
            _str[_size++] = ch;
            _str[_size] = '\0';
        }
        void Append(const char* str)
        {
            //因为要对字符串进行追加，所以要进行写时拷贝
            CopyOnWrite();
            //如果当前字符串的实际大小已达到容量，此时需要扩容
            size_t len = strlen(str);
            if(_size + len > _capacity)
            {
                Expand(_size + len);
            }
            //在容量已足够的情况下，对字符串进行追加
            strcat(_str + _size,str);
            _size += len;
        }
        void Insert(size_t pos,char ch)
        {
            //首先判断插入的位置是否合法
            assert(pos <= _size);
            //先进行写时拷贝
            CopyOnWrite();
            //判断容量是否足够
            if(_size == _capacity)
            {
                Expand(2*_capacity);
            }
            //在容量已足够的情况下，对字符串进行追加
            //将字符后移
            int end = _size;
            for(;end >= (int)pos;end--)
            {
                _str[end + 1] = _str[end];
            }
            //后移成功后，在进行插入字符
            _str[pos] = ch;
            _size++;
        }
        void Insert(size_t pos,const char* str);

        void PopBack();
        void Erase(size_t pos,size_t len);

        //运算符重载
        //"+="运算符重载:s1 += "hello"
        String& operator+=(const char* str);
        String& operator+=(const String& s);
        String operator+(const char* str);
        String operator+(const String& s);
        bool operator<(const String& s);
        bool operator==(const String& s);
        
        size_t Size();
        size_t Capacity();
        size_t Empty();

        size_t Find(const char ch);
        size_t Find(const char* str);
        

        //输出C风格的字符串
        char* c_str()
        {
            return _str;
        }

    private:
        char* _str;
        int* _pcount;
        size_t _size;
        size_t _capacity;
};

int main()
{
    //调用构造函数
    String s1("hello");
    cout<<s1.c_str()<<endl;
    //调用拷贝构造函数
    String s2(s1);
    cout<<s2.c_str()<<endl;
    //调用赋值运算符重载
    String s3(" world");
    //cout<<s3.c_str()<<endl;
    s3 = s1;
    cout<<s3.c_str()<<endl;

    ////测试"[]"运算符重载
    //cout<<s3[0]<<endl;
    //cout<<s3[3]<<endl;
    //cout<<s3[4]<<endl;
    ////cout<<s3[5]<<endl;
    ////cout<<s3[7]<<endl;
    //s3[0] = 'a';
    //cout<<s3[0]<<endl;

    ////测试PushBack
    //s1.PushBack('d');
    //s1.PushBack('a');
    //s1.Append(" world");
    //s2.PushBack('f');
    //s2.Append(" yanxuechu");
    //s3.PushBack('h');
    //s3.Append(" hujiangqi");
    //cout<<s1.c_str()<<endl;
    //cout<<s2.c_str()<<endl;
    //cout<<s3.c_str()<<endl;

    //测试Append
    //s1.Append(" world");
    //s2.Append(" yanxuechu");
    //s3.Append(" hujiangqi");
    //cout<<s1.c_str()<<endl;
    //cout<<s2.c_str()<<endl;
    //cout<<s3.c_str()<<endl;

    //测试Insert
    s1.Insert(0,'a');
    s1.Insert(3,'b');
    s1.Insert(7,'c');
    //s1.Insert(10,'d');
    s2.Insert(0,'w');
    s2.Insert(2,'x');
    s2.Insert(7,'y');
    //s2.Insert(11,'z');
    s3.Insert(0,'o');
    s3.Insert(1,'p');
    s3.Insert(7,'q');
    //s3.Insert(12,'r');
    cout<<s1.c_str()<<endl;
    cout<<s2.c_str()<<endl;
    cout<<s3.c_str()<<endl;





    return 0;
}
