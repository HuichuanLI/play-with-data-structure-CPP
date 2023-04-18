//
// Created by lhc456 on 2023/4/19.
//
//---------------------------------------------
//链式队列中每个节点的定义
#include <iostream>

#pragma warning (disable: 4996)
using namespace std;

template<typename T> //T代表数据元素的类型
struct QueueNode {
    T data;       //数据域，存放数据元素
    QueueNode<T> *next;  //指针域，指向下一个同类型（和本节点类型相同）节点
};

//链式队列的定义
template<typename T> //T代表数组中元素的类型
class LinkQueue {
public:
    LinkQueue();                          //构造函数
    ~LinkQueue();                         //析构函数

public:
    bool EnQueue(const T &e);            //入队列（增加数据）
    bool DeQueue(T &e);                  //出队列（删除数据）
    bool GetHead(T &e);   //读取队头元素，但该元素并没有出队列而是依旧在队列中

    void DispList();                     //输出链式队列中的所有元素
    int ListLength();                  //获取链式队列的长度（实际拥有的元素数量）
    bool IsEmpty();                      //判断链式队列是否为空

private:
    QueueNode<T> *m_front;              //头指针（指向头结点），这一端允许出队（删除）
    QueueNode<T> *m_rear;                //专门引入尾指针以方便入队（插入）操作
    int m_length;                        //记录长度，方便获取长度
};

//通过构造函数对链式队列进行初始化
template<typename T>
LinkQueue<T>::LinkQueue() {
    m_front = new QueueNode<T>; //先创建一个头结点
    m_front->next = nullptr;
    m_rear = m_front;
    m_length = 0;

    //若不带头节点的链式队列初始化代码应该如下，供参考
    /*m_front = nullptr;
    m_rear = nullptr;*/
}

//通过析构函数对链式队列进行资源释放
template<typename T>
LinkQueue<T>::~LinkQueue() {
    QueueNode<T> *pnode = m_front->next;
    QueueNode<T> *ptmp;
    while (pnode != nullptr) //该循环负责释放数据节点
    {
        ptmp = pnode;
        pnode = pnode->next;
        delete ptmp;
    }
    delete m_front;             //释放头结点
    m_front = m_rear = nullptr; //非必须
    m_length = 0;               //非必须
}

//入队列（增加数据），也就是从队尾增加数据
template<typename T>
bool LinkQueue<T>::EnQueue(const T &e) {
    QueueNode<T> *node = new QueueNode<T>;
    node->data = e;
    node->next = nullptr;

    m_rear->next = node; //新节点插入到m_rear后面
    m_rear = node;       //更新队列尾指针

    m_length++;
    return true;
}

//出队列（删除数据），也就是删除队头数据
template<typename T>
bool LinkQueue<T>::DeQueue(T &e) {
    if (IsEmpty() == true) {
        cout << "当前链式队列为空，不能进行出队操作!" << endl;
        return false;
    }

    QueueNode<T> *p_willdel = m_front->next;
    e = p_willdel->data;

    m_front->next = p_willdel->next;
    if (m_rear == p_willdel) //队列中只有一个元素节点（被删除后，整个队列就为空了）
        m_rear = m_front;  //设置队列为空(尾指针指向头指针)

    delete p_willdel;
    m_length--;
    return true;
}

//读取队头元素，但该元素并没有出队列而是依旧在队列中
template<typename T>
bool LinkQueue<T>::GetHead(T &e) {
    if (IsEmpty() == true) {
        cout << "当前链式队列为空，不能读取队头元素!" << endl;
        return false;
    }

    e = m_front->next->data;
    return true;
}

//输出链式队列中的所有元素，时间复杂度为O(n)
template<class T>
void LinkQueue<T>::DispList() {
    QueueNode<T> *p = m_front->next;
    while (p != nullptr) {
        cout << p->data << " ";  //每个数据之间以空格分隔
        p = p->next;
    }
    cout << endl; //换行
}

//获取链式队列的长度（实际拥有的元素数量），时间复杂度为O(1)
template<class T>
int LinkQueue<T>::ListLength() {
    return m_length;
}

//判断链式队列是否为空，时间复杂度为O(1)
template<class T>
bool LinkQueue<T>::IsEmpty() {
    //当然，换一种判断方式也行：if(m_front->next == nullptr) return true;
    if (m_front == m_rear) {
        return true;
    }
    return false;
}

int main() {
    //---------------------------
    LinkQueue<int> lnobj;
    lnobj.EnQueue(150);

    int eval2 = 0;
    lnobj.DeQueue(eval2);
    lnobj.EnQueue(200);
    lnobj.EnQueue(700);
    lnobj.DispList();
}