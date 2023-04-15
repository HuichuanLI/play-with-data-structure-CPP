//
// Created by lhc456 on 2023/4/15.
//
#include <iostream>

#pragma warning (disable: 4996)
using namespace std;

#define InitSize 10   //动态数组的初始尺寸
#define IncSize  5    //当动态数组存满数据后每次扩容所能多保存的数据元素数量

template<typename T> //T代表数组中元素的类型
class SeqStack {
public:
    SeqStack(int length = InitSize);     //构造函数，参数可以有默认值
    ~SeqStack();                         //析构函数

public:
    bool Push(const T &e); // 入栈（增加数据）
    bool Pop(T &e);         //出栈（删除数据），也就是删除栈顶数据
    bool GetTop(T &e);  //读取栈顶元素，但该元素并没有出栈而是依旧在栈中

    void DispList();                     //输出顺序栈中的所有元素
    int ListLength();                   //获取顺序栈的长度（实际拥有的元素数量）

    bool IsEmpty();                      //判断顺序栈是否为空
    bool IsFull();                       //判断顺序栈是否已满

private:
    void IncreaseSize();   //当顺序栈存满数据后可以调用此函数为顺序栈扩容

private:
    T *m_data;                          //存放顺序栈中的元素
    int m_maxsize;     //动态数组最大容量
    int m_top;      //栈顶指针(用作数组下标)，指向栈顶元素，该值为-1表示空栈
};

//通过构造函数对顺序栈进行初始化
template<typename T>
SeqStack<T>::SeqStack(int length) {
    m_data = new T[length];  //为一维数组动态分配内存，该值和算法空间复杂度无关，空间复杂度一般指算法额外需要的存储空间。
    m_maxsize = length;      //顺序栈最多可以存储m_maxsize个数据元素
    m_top = -1;              //空栈
}

//通过析构函数对顺序栈进行资源释放
template<typename T>
SeqStack<T>::~SeqStack() {
    delete[] m_data;
}

//入栈（增加数据），通常时间复杂度为O(1)，但一旦需要扩容，时间复杂度就会变成O(n)了
template<typename T>
bool SeqStack<T>::Push(const T &e) {
    if (IsFull() == true) {
        //cout << "顺序栈已满，不能再进行入栈操作了!" << endl;
        //return false;
        IncreaseSize(); //扩容
    }

    m_top++;           //栈顶指针向后走
    m_data[m_top] = e; //本行和上一行可以合并写成一行代码：m_data[++m_top] = e;
    return true;
}

//当顺序栈存满数据后可以调用此函数为顺序栈扩容，时间复杂度为O(n)
template<class T>
void SeqStack<T>::IncreaseSize() {
    T *p = m_data;
    m_data = new T[m_maxsize + IncSize]; //重新为顺序栈分配更大的内存空间
    for (int i = 0; i <= m_top; i++) {
        m_data[i] = p[i];                //将数据复制到新区域
    }
    m_maxsize = m_maxsize + IncSize;     //顺序栈最大长度增加IncSize
    delete[] p;                          //释放原来的内存空间
}

//出栈（删除数据），也就是删除栈顶数据，时间复杂度为O(1)
template<typename T>
bool SeqStack<T>::Pop(T &e) {
    if (IsEmpty() == true) {
        cout << "当前顺序栈为空，不能进行出栈操作!" << endl;
        return false;
    }

    e = m_data[m_top];  //栈顶元素值返回到e中。有的实现版本不会在Pop()成员函数中返回栈顶元素，此时要取得栈顶元素需要用到GetTop()成员函数。
    m_top--;            //本行和上一行可以合并写成一行代码：e = m_data[m_top--];
    return true;
}

//读取栈顶元素，但该元素并没有出栈而是依旧在栈顶中，因此m_top值不会发生改变，时间复杂度为O(1)
template<typename T>
bool SeqStack<T>::GetTop(T &e) {
    if (IsEmpty() == true) {
        cout << "当前顺序栈为空，不能读取栈顶元素!" << endl;
        return false;
    }

    e = m_data[m_top];  //栈顶元素返回到e中。
    return true;
}

//输出顺序栈中的所有元素，时间复杂度为O(n)
template<class T>
void SeqStack<T>::DispList() {
    //按照从栈顶到栈底的顺序来显示数据
    for (int i = m_top; i >= 0; --i) {
        cout << m_data[i] << " ";  //每个数据之间以空格分隔
    }
    cout << endl; //换行
}

//获取顺序栈的长度（实际拥有的元素数量），时间复杂度为O(1)
template<class T>
int SeqStack<T>::ListLength() {
    return m_top + 1;
}

//判断顺序栈是否为空，时间复杂度为O(1)
template<class T>
bool SeqStack<T>::IsEmpty() {
    if (m_top == -1) {
        return true;
    }
    return false;
}

//判断顺序栈是否已满，时间复杂度为O(1)
template<class T>
bool SeqStack<T>::IsFull() {
    if (m_top >= m_maxsize - 1) {
        return true;
    }
    return false;
}

//---------------------------------------
//共享栈
template<typename T> //T代表数组中元素的类型
class ShareStack {
public:
    ShareStack(int length = InitSize)    //构造函数，参数可以有默认值
    {
        m_data = new T[length];  //为一维数组动态分配内存
        m_maxsize = length;      //共享栈最多可以存储m_maxsize个数据元素
        m_top1 = -1;             //顺序栈1的栈顶指针为-1，表示空栈
        m_top2 = length;         //顺序栈2的栈顶指针为length，表示空栈
    }

    ~ShareStack()                        //析构函数
    {
        delete[] m_data;
    }

public:
    bool IsFull()                        //判断共享栈是否已满
    {
        if (m_top1 + 1 == m_top2) {
            return true;
        }
        return false;
    }

    bool Push(int stackNum, const T &e) //入栈（增加数据）,参数stackNum用于标识栈1还是栈2
    {
        if (IsFull() == true) {
            //共享栈满了，你也可以自行增加代码来支持动态增加共享栈的容量，这里简单处理，直接返回false
            cout << "共享栈已满，不能再进行入栈操作了!" << endl;
            return false;
        }
        if (stackNum == 1) {
            //要入的是顺序栈1
            m_top1++;           //栈顶指针向后走
            m_data[m_top1] = e;
        } else {
            //要入的是顺序栈2
            m_top2--;
            m_data[m_top2] = e;
        }
        return true;
    }

    bool Pop(int stackNum, T &e)  //出栈（删除数据），也就是删除栈顶数据
    {
        if (stackNum == 1) {
            //要从顺序栈1出栈
            if (m_top1 == -1) {
                cout << "当前顺序栈1为空，不能进行出栈操作!" << endl;
                return false;
            }
            e = m_data[m_top1];  //栈顶元素值返回到e中
            m_top1--;
        } else {
            //要从顺序栈2出栈
            if (m_top2 == m_maxsize) {
                cout << "当前顺序栈2为空，不能进行出栈操作!" << endl;
                return false;
            }
            e = m_data[m_top2];
            m_top2++;
        }
        return true;
    }

private:
    T *m_data;                          //存放共享栈中的元素
    int m_maxsize;                       //动态数组最大容量
    int m_top1;                          //顺序栈1的栈顶指针
    int m_top2;                          //顺序栈2的栈顶指针
};

//---------------------------
//链式栈中每个节点的定义
template<typename T> //T代表数据元素的类型
struct StackNode {
    T data;  //数据域，存放数据元素
    StackNode<T> *next;  //指针域，指向下一个同类型（和本节点类型相同）节点
};

//链式栈的定义
template<typename T>
class LinkStack {
public:
    LinkStack();      //构造函数
    ~LinkStack();     //析构函数

public:
    bool Push(const T &e); //入栈元素e
    bool Pop(T &e);        //出栈（删除数据），也就是删除栈顶数据
    bool GetTop(T &e);     //读取栈顶元素，但该元素并没有出栈而是依旧在栈中

    void DispList();                     //输出链式栈中的所有元素
    int ListLength();                   //获取链式栈的长度
    bool Empty();                        //判断链式栈是否为空

private:
    StackNode<T> *m_top;   //栈顶指针
    int m_length;//链式栈当前长度
};

//通过构造函数对链式栈进行初始化
template<typename T>
LinkStack<T>::LinkStack() {
    m_top = nullptr;
    m_length = 0;
}

//入栈元素e，时间复杂度为O(1)
template<typename T>
bool LinkStack<T>::Push(const T &e) {
    StackNode<T> *node = new StackNode<T>;
    node->data = e;
    node->next = m_top;
    m_top = node;
    m_length++;
    return true;
}

//出栈（删除数据），也就是删除栈顶数据，时间复杂度为O(1)
template<typename T>
bool LinkStack<T>::Pop(T &e) {
    if (Empty() == true) //链式栈为空
        return false;

    StackNode<T> *p_willdel = m_top;
    m_top = m_top->next;
    m_length--;
    e = p_willdel->data;
    delete p_willdel;
    return true;
}

//读取栈顶元素，但该元素并没有出栈而是依旧在栈中
template<typename T>
bool LinkStack<T>::GetTop(T &e) {
    if (Empty() == true) //链式栈为空
        return false;

    e = m_top->data;
    return true;
}

//输出链式栈中的所有元素，时间复杂度为O(n)
template<class T>
void LinkStack<T>::DispList() {
    if (Empty() == true) //链式栈为空
        return;

    StackNode<T> *p = m_top;
    while (p != nullptr) {
        cout << p->data << " ";  //每个数据之间以空格分隔
        p = p->next;
    }
    cout << endl; //换行
}

//获取链式栈的长度，时间复杂度为O(1)
template<class T>
int LinkStack<T>::ListLength() {
    return m_length;
}

//判断链式栈是否为空，时间复杂度为O(1)
template<class T>
bool LinkStack<T>::Empty() {
    if (m_top == nullptr) //链式栈为空
    {
        return true;
    }
    return false;
}

//通过析构函数对链式栈进行资源释放
template<typename T>
LinkStack<T>::~LinkStack() {
    T tmpnousevalue = {0};
    while (Pop(tmpnousevalue) == true) {}//把栈顶元素删光，while循环也就退出了，此时也就是空栈了
}

int main() {
    
    SeqStack<int> seqobj(10);

    seqobj.Push(150);
    seqobj.Push(200);
    seqobj.Push(300);
    seqobj.Push(400);
    seqobj.DispList();
    int eval = 0;
    seqobj.Pop(eval);
    seqobj.Pop(eval);
    cout << "---------" << endl;
    seqobj.DispList();

    seqobj.Push(8100);

    //--------------------
    ShareStack<int> sharesobj(10);
    sharesobj.Push(1, 150);
    sharesobj.Push(2, 200);
    int eval2;
    sharesobj.Pop(1, eval2);
    sharesobj.Pop(1, eval2);

    //--------------------
    LinkStack<int> slinkobj;
    slinkobj.Push(12);
    slinkobj.Push(24);
    slinkobj.Push(48);
    slinkobj.Push(100);
    slinkobj.DispList();

    int eval3 = 0;
    slinkobj.Pop(eval3);
    slinkobj.DispList();

    return 0;
}

