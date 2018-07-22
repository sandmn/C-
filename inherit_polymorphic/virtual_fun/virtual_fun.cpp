#include<iostream>
using namespace std;

//虚函数：在类的成员函数前加virtual就构成了虚函数
//虚函数重写：在子类中定义一个与父类的虚函数完全相同的函数，就构成了重写（函数名，参数列表，返回值相同）（协变除外）
class Person
{
    public:
        //构造函数
        Person(const string name = "yanxuechun")
            :_name(name)
            {
            }
        //拷贝构造函数
        Person(const Person& p)
            :_name(p._name)
        {
        }
        //赋值运算符重载
        Person& operator=(const Person& p)
        {
            if(this != &p)
            {
                _name = p._name;
            }
            return *this;
        }
        //析构函数
        ~Person()
        {
            cout<<"~Person()"<<endl;
        }
        //公有成员函数
        virtual void Display()
        {
            cout<<"全价票"<<endl;
        }
    private:
            string _name;
};

class Student : public Person
{
    public:
        //构造函数
        Student(const string& name = "hujiangqi",int num = 1)
            :Person(name)//调用父类的构造函数初始化父类对象
             ,_num(num)//子类自己来初始化自己的对象
    {
    }
        //拷贝构造函数
        Student(const Student& s)
            :Person(s)//切片，调用父类的拷贝构造函数初始化父类对象
             ,_num(s._num)
    {
    }
        //赋值运算符重载
        Student& operator=(const Student& s)
        {
            if(this != &s)
            {
                //调用父类的赋值运算符重载函数对父类成员进行赋值
                Person::operator=(s);
                //切片。因为子类的operator=会隐藏父类的operator=函数，
                //所以如果不显示的指定类作用域，此处调用的是子类的operator=函数，此时，就会陷入无限递归，直至栈溢出。
                _num = s._num;
                ////或者可以通过以下方式进行赋值
                //_name = s._name;
                //_num = s._num;
            }
        }
        //析构函数
        ~Student()
        {
            //编译器会将子类的析构函数名和父类的析构函数名处理为相同的名字，所以此处子类会对子类的析构函数形成重载
            //此时在析构子类对象时，会先析构子类对象，然后自动调用父类析构函数析构父类对象
            cout<<"~Student()"<<endl;
        }
        //公有成员函数
        virtual void Display()
        {
            cout<<"买半价票"<<endl;
        }
    private:
            int _num;//学号
};

int main()
{
    //1. 父类子类均未定义虚函数时
    ////不是指针或者引用，调用的不是虚函数，普通调用，按类型查找
    //对象调用函数，根据类型判断
    //Person p1;
   // p1.Display();//全价票
    //Student s1;
   // s1.Display();//半价票
   // s1.Person::Display();//全价票
   // p1 = s1;
   // p1.Display();//全价票

    ////是指针，调用的不是虚函数，普通调用，按类型查找
    //指针调用的不是虚函数，不构成多态，根据类型判断
    //Person* p2 = &p1;
    //p2->Display();//全价票
    //p2 = &s1;//切片
    //p2->Display();//全价票
    //Student* s2 = &s1;
    //s2->Display();//半价票
    //s2 = (Student*)&p1;
    //s2->Person::Display();//全价票
    ////s2->Display();//中断异常
    ////此处，可以将父类指针赋值给子类指针，但是要经过强转
    ////当父类指针指向的是父类对象时，子类指针在对子类对象特有的成员进行操作时，会引发中断异常
    ////当父类指针指向的是父类对象时，子类指针在对父类对象的成员进行操作时，会正常执，不会引发异常


    ////是引用，调用的不是虚函数，普通调用，按类型查找
    //引用，没有调用虚函数，按照类型查找
    //Person& p3 = p1;
    //p3.Display();//全价票
    //Person& p4 = s1;//切片
    //p4.Display();//全价票
    //Student& s3 = (Student&)p1;
    ////s3.Display();//引发中断异常,父类引用的是父类对象,子类调用子类特有的成员函数
    //s3.Person::Display();//全价票，子类调用父类的成员函数
    //Student& s4 = s1;
    //s4.Display();//半价票
    //Person& p5 = s1;//切片，父类引用指向子类对象
    //Student& s5 = (Student&)p5;//强制转换，子类引用指向父类对象
    //s5.Display();//半价票
    ////将父类引用强制转换赋值给子类引用，父类引用指向的是子类对象
    ////当子类引用调用子类特有的成员时，可以调用成功
    //s5.Person::Display();//半价票


    //2.子类声明为虚函数，父类没有声明为虚函数
    //不是指针或者引用，调用的不是虚函数，普通调用，按类型查找
    //Person p1;
    //p1.Display();//全价票
    ////不是指针或者引用，调用的是虚函数，普通调用，按类型查找
    //Student s1;
    //s1.Display();//半价票
    ////不是指针或者引用，调用的不是虚函数，普通调用，按类型查找
    //s1.Person::Display();//全价票
    ////不是指针或者引用，调用的不是虚函数，普通调用，按类型查找
    //p1 = s1;//切片
    //p1.Display();//全价票

    //是指针，调用的不是虚函数，普通调用，按类型查找
    //Person* p2 = &p1;
    //p2->Display();//全价
    //p2 = &s1;//切片
    //p2->Display();//全价:因为父类成员函数中没有定义为虚函数，所以不构成虚函数重写，所以，不构成多态，所以按照类型进行调用
    //Student* s2 = &s1;
    //s2->Display();//半价
    //s2 = (Student*)&p1;
    ////s2->Display();//引发中断异常
    //s2->Person::Display();//全价票

    //是引用，调用的不是虚函数，普通调用，按类型查找
    //Person& p3 = p1;
    //p3.Display();//全价票
    //Person& p4 = s1;//切片
    //p4.Display();//全价票：父类子类均未定义虚函数时，不构成虚函数重写，不构成多态，所以按照类型进行调用
    //Student& s3 = (Student&)p1;
    ////s3.Display();//中断异常
    //s3.Person::Display();//全价票
    //Student& s4 = s1;
    //s4.Display();//半价票



    //父类中定义了虚函数
    //Person p1;
    //p1.Display();//全价票：对象调用函数，不构成多态，按照类型查找
    //Student s1;
    //s1.Display();//半价票：对象调用函数，不构成多态，按照类型查找
    //s1.Person::Display();//全价票：对象调用函数，不构成多态，按照类型查找
    //p1 = s1;//切片
    //p1.Display();//全价票：对象调用函数，不构成多态，按照类型查找

    //Person* p2 = &p1;
    //p2->Display();//全价票：父类指针调用虚函数，构成多态，按照对象查找
    //p2 = &s1;//切片
    //p2->Display();//半价票：父类指针调用虚函数，构成多态，按照对象查找
    //Student* s2 = &s1;
    //s2->Display();//半价票：子类指针调用虚函数，不构成多态，按照类型查找
    //s2 = (Student*)&p1;
    //s2->Display();//全价票(有问题)
    //s2->Person::Display();//全价票:子类指针调用虚函数，不构成多态，按照类型查找

    //是引用，调用的不是虚函数，普通调用，按类型查找
    //Person& p3 = p1;
    //p3.Display();//全价票：构成多态，按照对象查找
    //Person& p4 = s1;
    //p4.Display();//半价票：构成多态，按照对象查找
    //Student& s3 = (Student&)p1;
    //s3.Display();//全价票
    //Student& s4 = s1;
    //s4.Display();//半价票

    return 0;
}

