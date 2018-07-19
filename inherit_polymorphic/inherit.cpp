#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;


////子类中的六大默认成员函数：如果不显示写出，则系统会默认合成这六个成员函数
////注意：在子类中也会继承父类的六个默认成员函数
//class Person
//{
//    public:
//        //构造函数
//        Person(const string& name = "yanxuechun")
//            :_name(name)
//            {
//                cout<<"Person()"<<endl;
//            }
//        //拷贝构造函数
//        Person(const Person& p)
//            :_name(p._name)
//        {
//            cout<<"Person(const Person& p)"<<endl;
//        }
//        //赋值运算符重载
//        Person& operator=(const Person& p)
//        {
//            cout<<"operator="<<endl;
//            if(this != &p)
//            {
//                _name = p._name;
//            }
//            return *this;
//        }
//        //析构函数
//        ~Person()
//        {
//            cout<<"~Person()"<<endl;
//        }
//    protected:
//        string _name;
//};
//class Student : public Person
//{
//    public:
//        //构造函数
//        Student(const string& name = "hujiangqi",int num = 1)
//            :Person(name)//注意：此处不能写为：_name(name)
//            ,_num(num)
//    {
//        cout<<"Student()"<<endl;
//    }
//        //拷贝构造函数
//        Student(const Student& s)
//            :Person(s._name)//切片：将子类对象赋值给父类对象
//            ,_num(s._num)
//    {
//        cout<<"Student(const Student&)"<<endl;
//    }
//        //赋值运算符重载
//        Student& operator=(const Student& s)
//        {
//            cout<<"operator=(const Student&)"<<endl;
//            if(this != &s)
//            {
//                //方式一：调用父类的赋值运算符重载函数对父类成员进行赋值
//                Person::operator=(s);
//                //调用子类的赋值运算符重载函数对子类成员进行赋值
//                _num = s._num;
//                //方式二：手工赋值
//               // _name = s._name;
//               // _num = s._num;
//            }
//            return *this;
//        }
//        //析构函数：先析构子类，在析构父类
//        //子类会隐藏父类的析构函数
//        //析构子类时，会先析构子类，然后自动调用父类的析构函数析构父类
//        ~Student()
//        {
//            cout<<"~Student()"<<endl;
//        }
//    private:
//        int _num;
//};
//
//int main()
//{
//    //构造函数
//    Student s1;
//    //拷贝构造函数
//    Student s2(s1);
//    //赋值运算符重载
//    s2 = s1;
//    return 0;
//}



////重定义和隐藏:在父类和子类中：
//成员变量名相同，构成隐藏
//成员函数名相同，参数任意，也构成隐藏或重定义
//注意与重载的区别:重载是在不同作用域范围内，函数名相同，参数列表不同，返回值任意
//class Person
//{
//    public:
//        //构造函数
//        Person(const string& name = "yanxuechun",const int num = 1)
//            :_name(name)
//             ,_num(num)
//    {
//        cout<<"Person"<<endl;
//    }
//        //拷贝构造函数
//        Person(const Person& p)
//            :_name(p._name)
//             ,_num(p._num)
//    {
//        cout<<"Person(const Person& )"<<endl;
//    }
//        //赋值运算符重载
//        Person& operator=(const Person& p)
//        {
//            cout<<"operator="<<endl;
//            if(this != &p)
//            {
//                _name = p._name;
//                _num = p._num;
//            }
//            return *this;
//        }
//        //析构函数
//        ~Person()
//        {
//            cout<<"~Person"<<endl;
//        }
//        void Display()
//        {
//            cout<<"_name:"<<_name<<endl;
//            cout<<"_id:"<<_num<<endl;
//        }
//    protected:
//        string _name;//姓名
//        int _num;//身份证号
//};
//class Student : public Person
//{
//    public:
//        Student(const string name = "yanxuechun",int id = 0,int num = 1)
//            :Person(name,id)//从父类继承的成员由父类的调用父类的构造函数进行初始化
//             ,_num(num)
//    {
//        cout<<"Student"<<endl;
//    }
//        //在子类中访问父类中被隐藏的成员时，要要加上域作用限定符
//        void Display()
//        {
//            cout<<"_name:"<<_name<<endl;
//            cout<<"_id:"<<Person::_num<<endl;
//            cout<<"_num:"<<_num<<endl;
//        }
//    private:
//        int _num;//学生的学号
//};
//int main()
//{
//    Student s("hujiangqii",1,2);
//    s.Display();
//    s.Person::Display();
//    return 0;
//}



////继承和转换：赋值兼容规则
//class Person
//{
//    public:
//        //构造函数
//        //C风格字符串在赋值给string字符串时，会先生成string类型的临时变量
//        //name实际是string类型的临时变量的引用,临时变量具有常属性，所以必须加const
//        //此时传参时，即可以传递string类的对象，也可以传递C风格的字符串
//        Person(const string& name = "yanxuechun")
//            :_name(name)//此处调用string类的拷贝构造函数
//        {
//        }
//        //如果参数为C风格字符串的指针，则传参时只能传递C风格的字符串
//        //而不能是string类的对象
//        //Person(const char* _str = "yanxuechun")
//        //    :_name(_str)//此处调用string类的构造函数
//        //{}
//        
//        //拷贝构造函数
//        Person(const Person& p)
//            :_name(p._name)//此处调用string类的拷贝构造函数
//        {
//        }
//        //赋值运算符重载
//        Person& operator=(const Person& p)
//        {
//            if(this != &p)
//            {
//                _name = p._name;//此处调用string类的赋值运算符重载函数
//                return *this;
//            }
//        }
//        //析构函数
//        ~Person()
//        {
//        }
//        //公有成员函数
//        void Display()
//        {
//            cout<<_name<<endl;
//        }
//    private:
//        string _name;//父类有一个string类型的成员变量
//};
////公有继承
//class Student : public Person
//{
//    public:
//        //对父类的Display函数进行覆盖
//        void Display()
//        {
//            cout<<_num<<endl;
//        }
//        int _num;
//};
//int main()
//{
//    Person p;
//    Student s;
//
//    //子类对象可以赋值给父类对象
//    //p = s;
//    //p.Display();
//    //s.Display();
//    //s.Person::Display();
//
//    ////父类对象的指针或者引用可以指向子类对象
//    //Person* p1 = &s;
//    //p1->Display();//根据类型进行调用
//    //Person& p2 = s;
//    //p2.Display();//根据类型进行函数调用
//
//    ////父类对象不能赋值给子类对象
//    //s = p;
//
//    ////子类对象的指针或者引用不可以指向父类对象
//    //Student* s1 = &p;
//    //Student& s2 = p;
//
////有问题
//
////    //子类对象的指针或者引用可以指向父类对象（通过强制类型转换）
////    Student* s1 = (Student*)&p;
////    s1->Display();//通过类型调用函数
////    Student& s2 = (Student&)p;
////    s2.Display();//通过类型调用函数
////
////    //子类指针或引用指向父类时：即将父类的指针或者引用赋值给子类指针或引用
////    //1. 如果父类指针或引用指向父类，则子类指针对其特有的成员进行操作时，会中断引发异常
////    s1->_num = 10;
////    cout<<s1->_num<<endl;
////    s2._num = 20;
////    cout<<s2._num<<endl;
//
//    ////2. 如果父类指针或引用指向子类，则子类指针对其特有的成员进行操作时，不会引发异常
//    //Person* p1 = &s;
//    //Person& p2 = s;
//    //Student* s3 = (Student*)p1;
//    //Student& s4 = (Student&)p2;
//    //s3->_num = 1;
//    ////s4._num = 2;
//    //cout<<s3->_num<<endl;
//
//   // string s("yanxuechun");
//   // Person p("yanxuechun");
//}





////验证成员的访问限定符与继承关系
//class Person
//{
//    public:
//        void Display()
//        {
//            cout<<"haha"<<endl;
//        }
//        int _n1;
//    protected:
//        int _n2;
//    private:
//        int _n3;
//};
////公有继承：除私有成员不可见（存在但不能访问）外，其余成员的属性不变
////          父类中的公有成员在子类中还是公有成员(公有成员在类内外均可访问)
////          父类中的受保护成员在子类中还是受保护成员（受保护成员只在子类/本类中可访问，类外不能访问）
//class Student1:public Person
//{
//    public:
//        void Display()
//        {
//            _n1 = 10;
//            _n2 = 20;
//           // _n3 = 30;
//            _s = 40;
//            cout<<_n1<<endl;
//            cout<<_n2<<endl;
//           // cout<<_n3<<endl;
//            cout<<_s<<endl;
//        }
//    int _s;
//};
////保护继承:除父类的私有成员外父类的其余成员均变为受保护成员（类和子类中可以访问，类外不可以访问）
//class Student2:protected Person
//{
//    public:
//        void Display()
//        {
//            _n1 = 10;
//            _n2 = 20;
//            //_n3 = 30;
//            cout<<_n1<<endl;
//            cout<<_n2<<endl;
//            //cout<<_n3<<endl;
//        }
//};
////私有继承:除父类中的私有成员外，其余成员在子类中均为私有成员，只在本类中可以访问，在子类中和类外均不能访问
//class Student3 : private Person
//{
//    public:
//        void Display()
//        {
//            _n1 = 10;
//            _n2 = 20;
//            //_n3 = 30;
//            cout<<_n1<<endl;
//            cout<<_n2<<endl;
//            //cout<<_n3<<endl;
//        }
//
//};
//int main()
//{
//    //Person p;
//    //cout<<sizeof(p)<<endl;
//    
//    //Student1 s1;
//    //cout<<sizeof(s1)<<endl;
//    //s1.Display();
//    //s1._n1 = 1;
//    ////s1._n2 = 2;
//    ////s1._n3 = 3;
//    //cout<<s1._n1<<endl;
//    ////cout<<s1._n2<<endl;
//    ////cout<<s1._n3<<endl;
//
//    //Student2 s2;
//    //cout<<sizeof(s2)<<endl;
//   // s2.Display();
//   // s2._n1 = 1;
//   // s2._n2 = 2;
//   //// s2._n3 = 3;
//   // cout<<_s2._n1<<endl;
//   // cout<<_s2._n2<<endl;
//   //// cout<<_s2._n3<<endl;
//
//    Student3 s3;
//    cout<<sizeof(s3)<<endl;
//    s3.Display();
//    //s3._n1 = 1;
//    //s3._n2 = 2;
//   //// s2._n3 = 3;
//    //cout<<_s3._n1<<endl;
//    //cout<<_s3._n2<<endl;
//   //// cout<<_s2._n3<<endl;
//    return 0;
//}



//class Person
//{
//    public:
//        //对于默认的构造函数，此时就类似于：
//        //Person()
//        //:_name();//此处会调用string的缺省构造函数
//        //{
//        //
//        //}
//        //构造函数
//        //如果调用构造函数时，没有传递参数，此时在参数中就会使用默认参数来调用string类的构造函数构造参数name
//        //如果传参时，传递时C风格的字符串，此时参数就会根据传参的字符串来调用string类的构造函数来构造参数name
//        //如果传参时，传递的是string风格的字符串，此时就会调用string类的拷贝构造函数来构造参数name
//        Person(const string& name = "yanxuechun")
//            :_name(name)//此处调用string类的拷贝构造函数
//            {
//                cout<<"Person"<<endl;
//                _name = name;//此处调用string类的赋值运算符重载函数
//            }
//        //拷贝构造函数
//        Person(const Person& p)
//            :_name(p._name)
//        {
//            cout<<"Person(const Person& p)"<<endl;
//        }
//        //赋值运算符重载
//        Person& operator=(const Person& p)
//        {
//            if(this != &p)
//            {
//                _name = p._name;//此处调用string类的赋值运算符重载
//            }
//        }
//        //析构函数
//        ~Person()
//        {
//            cout<<"~Person()"<<endl;
//        }//此处会调用string类的析构函数
//
//        void Display()
//        {
//            cout<<_name<<endl;//此处调用string类的"<<"重载函数
//        }
//    protected:
//        string _name;
//};
//
//class Student:public Person
//{
//    protected:
//        int _num;
//};
//
//
//int main()
//{
//    Person p;
//    p.Display();
//    Person p1("hujiangqi");
//    p1.Display();
//    return 0;
//}
