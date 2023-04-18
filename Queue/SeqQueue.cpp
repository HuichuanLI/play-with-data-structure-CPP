//
// Created by lhc456 on 2023/4/16.
//
#include <iostream>

#pragma warning (disable: 4996)
using namespace std;

#define MaxSize 10       //数组的尺寸

template<typename T> //T代表数组中元素的类型
class SeqQueue {
public:
    SeqQueue();                          //构造函数
    ~SeqQueue();                         //析构函数

public:
    bool EnQueue(const T &e);            //入队列（增加数据）
    bool DeQueue(T &e);                  //出队列（删除数据）
    bool GetHead(T &e); //读取队头元素，但该元素并没有出队列而是依旧在队列中
    void ClearQueue();                   //将队列清空

    void DispList();                     //输出顺序队列中的所有元素
    int ListLength();                  //获取顺序队列的长度（实际拥有的元素数量）
    bool IsEmpty();                      //判断顺序队列是否为空
    bool IsFull();                       //判断顺序队列是否已满

private:
    T *m_data;                           //存放顺序队列中的元素
    int m_front;                         //队头指针(数组下标)，允许删除的一端，如果队列不为空，则指向队列头元素
    int m_rear;                          //队尾指针(数组下标)，允许插入的一端 ，如果队列不为空，则指向队尾元素的下一个位置
};

//通过构造函数对顺序队列进行初始化
template<typename T>
SeqQueue<T>::SeqQueue() {
    m_data = new T[MaxSize];  //为一维数组动态分配内存

    //空队列约定m_front和m_rear都为0
    m_front = 0;
    m_rear = 0;
}

//通过析构函数对顺序队列进行资源释放
template<typename T>
SeqQueue<T>::~SeqQueue() {
    delete[] m_data;
}

//入队列（增加数据），也就是从队尾增加数据
template<typename T>
bool SeqQueue<T>::EnQueue(const T &e) {
    if (IsFull() == true) {
        cout << "顺序队列已满，不能再进行入队操作了!" << endl;
        return false;
    }

    m_data[m_rear] = e; //将数据放入队尾
    //m_rear++; //队尾指针向后走，本行和上一行可以合并写成一行代码：m_data[m_rear++] = e;
    m_rear = (m_rear + 1) % MaxSize; //队尾指针加1并取余，这样m_data的下标就控制在了0到(MaxSize-1)之间了
    return true;
}

//出队列（删除数据），也就是删除队头数据
template<typename T>
bool SeqQueue<T>::DeQueue(T &e) {
    if (IsEmpty() == true) {
        cout << "当前顺序队列为空，不能进行出队操作!" << endl;
        return false;
    }

    e = m_data[m_front];  //队头元素值返回到e中。
    //m_front++;//本行和上一行可以合并写成一行代码：e = m_data[m_front++];
    m_front = (m_front + 1) % MaxSize; //队头指针加1并取余
    return true;
}

//读取队头元素，但该元素并没有出队列而是依旧在队列中
template<typename T>
bool SeqQueue<T>::GetHead(T &e) {
    if (IsEmpty() == true) {
        cout << "当前顺序队列为空，不能读取队头元素!" << endl;
        return false;
    }

    e = m_data[m_front];  //队头元素返回到e中。
    return true;
}

//输出顺序队列中的所有元素，时间复杂度为O(n)
template<class T>
void SeqQueue<T>::DispList() {
    //按照从队头到队尾的顺序来显示数据
    //for (int i = m_front; i < m_rear ; ++i)
    for (int i = m_front; i != m_rear;) {
        cout << m_data[i] << " ";  //每个数据之间以空格分隔
        i = (i + 1) % MaxSize;
    }
    cout << endl; //换行
}

//获取顺序队列的长度（实际拥有的元素数量），时间复杂度为O(1)
template<class T>
int SeqQueue<T>::ListLength() {
    //return m_rear - m_front;
    return (m_rear + MaxSize - m_front) % MaxSize;
}

//判断顺序队列是否为空，时间复杂度为O(1)
template<class T>
bool SeqQueue<T>::IsEmpty() {
    if (m_front == m_rear) {
        return true;
    }
    return false;
}

//判断顺序队列是否已满，时间复杂度为O(1)
template<class T>
bool SeqQueue<T>::IsFull() {
    //if(m_rear >= MaxSize) //队尾指针和数组容量做比较
    if ((m_rear + 1) % MaxSize == m_front) {
        return true;
    }
    return false;
}

//将队列清空
template<class T>
void SeqQueue<T>::ClearQueue() {
    m_front = m_rear = 0;
}


int main() {

    SeqQueue<int> seqobj;
    seqobj.EnQueue(150);
    seqobj.EnQueue(200);
    seqobj.EnQueue(300);
    seqobj.EnQueue(400);
    seqobj.DispList();

    cout << "---------" << endl;
    int eval = 0;
    seqobj.DeQueue(eval);
    seqobj.DeQueue(eval);
    seqobj.DispList();

    cout << "---------" << endl;
    seqobj.EnQueue(500);
    seqobj.EnQueue(600);
    seqobj.EnQueue(700);
    seqobj.EnQueue(800);
    seqobj.EnQueue(900);
    seqobj.DispList();



    return 0;
}