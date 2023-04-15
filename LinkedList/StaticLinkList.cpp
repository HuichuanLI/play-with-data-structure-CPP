//
// Created by lhc456 on 2023/4/15.
//
#include <iostream>

#pragma warning (disable: 4996)
using namespace std;

#define MaxSize 201 //静态链表的尺寸，可以根据实际需要设定该值。可用数组下标为0-200
//节点使用情况枚举标记值
enum NODEUSE {
    //这些枚举值都给负值，以免和数组下标（从0开始的正值）冲突
    e_NOUSE = -1,  //未使用（未用）
    e_LAST = -2   //最后一个节点（末尾）
};

//静态链表中每个节点的定义
template<typename T> //T代表数据元素的类型
struct Node {
    T data;  //元素数据域，存放数据元素
    int cur;   //游标，记录下个静态链表节点的数组下标
};

//静态链表的定义
template<typename T>
class StaticLinkList {
public:
    StaticLinkList();                    //构造函数
    ~StaticLinkList() {};                //析构函数

public:
    int findAnIdlePos();                //找到一个空闲位置用于保存数据
    bool ListInsert(int i, const T &e);  //在第i个位置插入指定元素e
    bool ListDelete(int i);              //删除第i个位置的元素

    bool GetElem(int i, T &e);           //获得第i个位置的元素值
    int LocateElem(const T &e);       //按元素值查找其在静态链表中第一次出现的位置

    void DispList();                     //输出静态链表中的所有元素
    int ListLength();                   //获取静态链表的长度
    bool Empty();                        //判断静态链表是否为空

private:
    Node<T> m_data[MaxSize]; //保存节点数据的数组
    int m_length;            //当前长度，也就是当前保存的数据节点数目
};

//通过构造函数对静态链表进行初始化
template<typename T>
StaticLinkList<T>::StaticLinkList() {
    for (int i = 1; i < MaxSize; ++i) //从下标1开始的节点用于保存实际的数据，这些节点的cur有必要设置值，而头节点其实不用给任何初值
    {
        m_data[i].cur = e_NOUSE; //标记这些节点都没使用
    }
    m_length = 0; //还未向其中存入任何数据元素
}

//在m_data中找到一个空闲位置用于保存数据，若没有找到（静态链表满了），则返回-1
template<typename T>
int StaticLinkList<T>::findAnIdlePos() {
    for (int i = 1; i < MaxSize; ++i) //因为下标0是头节点，不能用于保存数据，所以循环变量从1开始
    {
        if (m_data[i].cur == e_NOUSE) //未使用
            return i;
    }
    return -1;
}

//在第iPos个位置（位置编号从1开始）插入指定元素e
template<typename T>
bool StaticLinkList<T>::ListInsert(int iPos, const T &e) {
    if (iPos < 1 || iPos > (m_length + 1)) {
        cout << "元素" << e << "插入的位置" << iPos << "不合法，合法的位置是1到" << m_length + 1 << "之间!" << endl;
        return false;
    }

    int iIdx;
    if ((iIdx = findAnIdlePos()) == -1) //静态链表满了
    {
        cout << "静态链表已满!" << endl;
        return false;
    }

    //既然需要在第iPos个位置插入元素，那么肯定要找到第iPos-1个位置。
    int iDataCount = 1; //统计静态链表中元素数量
    int iIdxPrev;       //保存第iPos-1个位置对应的m_data数组的下标

    if (iPos == 1) //向第一个位置插入元素，要单独处理
    {
        m_data[iIdx].data = e;
        if (m_length == 0) //空表
        {
            m_data[iIdx].cur = e_LAST;
        } else //非空表
        {
            m_data[iIdx].cur = m_data[0].cur;
        }
        m_data[0].cur = iIdx;
    } else {
        int iPosCount = 0; //位置计数
        int tmpcur = m_data[0].cur;

        //前面已经判断过插入位置合法，所以一定可以找到合适的位置，while(true)循环肯定可以正常退出
        while (true) {
            iPosCount++;
            if (iPosCount >= (iPos - 1)) //找到了第iPos-1个位置
            {
                iIdxPrev = tmpcur;
                break;
            }
            tmpcur = m_data[tmpcur].cur;

        } //end while

        int iTmpCurr = m_data[iIdxPrev].cur;
        m_data[iIdxPrev].cur = iIdx;
        m_data[iIdx].data = e;
        m_data[iIdx].cur = iTmpCurr;
    }
    cout << "成功在位置为" << iPos << "处插入元素" << e << "!" << endl;
    m_length++;       //实际表长+1
    return true;
}

//输出静态链表中的所有元素，时间复杂度为O(n)
template<class T>
void StaticLinkList<T>::DispList() {
    if (m_length < 1) {
        //静态链表为空
        return;
    }
    int tmpcur = m_data[0].cur;
    while (true) {
        cout << m_data[tmpcur].data << " ";
        if ((tmpcur = m_data[tmpcur].cur) == e_LAST)
            break;
    } //end while
    cout << endl; //换行
}

//获得第i个位置的元素值，时间复杂度为O(n)
template<class T>
bool StaticLinkList<T>::GetElem(int i, T &e) {
    if (m_length < 1) {
        //静态链表为空
        cout << "当前静态链表为空，不能获取任何数据!" << endl;
        return false;
    }

    if (i < 1 || i > m_length) {
        cout << "获取元素的位置" << i << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
        return false;
    }
    int tmpcur = m_data[0].cur;
    int iPos = 0;
    while (true) {
        iPos++;
        if (iPos == i) {
            e = m_data[tmpcur].data;
            cout << "成功获取位置为" << i << "的元素，该元素的值为" << e << "!" << endl;
            return true;
        }
        tmpcur = m_data[tmpcur].cur;
    }
    return false;
}

//按元素值查找其在静态链表中第一次出现的位置，时间复杂度为O(n)
template<class T>
int StaticLinkList<T>::LocateElem(const T &e) {
    if (m_length < 1) {
        //静态链表为空
        cout << "当前静态链表为空，不能获取任何数据!" << endl;
        return -1;
    }
    int tmpcur = m_data[0].cur;
    int iPos = 0;
    while (true) {
        iPos++;
        if (m_data[tmpcur].data == e && m_data[tmpcur].cur != e_NOUSE) {
            cout << "值为" << e << "的元素在静态链表中第一次出现的位置为" << iPos << "!" << endl;
            return tmpcur;
        }
        if (m_data[tmpcur].cur == e_LAST) {
            //这是没找到
            break;
        }
        tmpcur = m_data[tmpcur].cur;
    }
    cout << "值为" << e << "的元素在静态链表中没有找到!" << endl;
    return -1;  //返回-1表示查找失败
}

//获取静态链表的长度，时间复杂度为O(1)
template<class T>
int StaticLinkList<T>::ListLength() {
    return m_length;
}

//判断静态链表是否为空，时间复杂度为O(1)
template<class T>
bool StaticLinkList<T>::Empty() {
    if (m_length < 1) {
        return true;
    }
    return false;
}

//删除第iPos个位置的元素
template<typename T>
bool StaticLinkList<T>::ListDelete(int iPos) {
    if (m_length < 1) {
        cout << "当前静态链表为空，不能删除任何数据!" << endl;
        return false;
    }
    if (iPos < 1 || iPos > m_length) {
        cout << "删除的位置" << iPos << "不合法，合法的位置是1到" << m_length << "之间!" << endl;
        return false;
    }

    int tmpcur = m_data[0].cur; //第一个数据节点的数组下标
    if (iPos == 1) //删除第一个位置元素，要单独处理
    {
        if (m_length != 1) {
            //这个静态链表里有多个元素，那么
            m_data[0].cur = m_data[tmpcur].cur; //头节点指向第二个数据节点的数组下标
        }
        m_data[tmpcur].cur = e_NOUSE;
        cout << "成功删除位置为" << iPos << "的元素，该元素的值为" << m_data[tmpcur].data << "!" << endl;
    } else {
        int iIdxPrev; //第iPos-1个位置对应的m_data数组的下标
        int iPosCount = 0; //位置计数

        //前面已经判断过删除位置合法，所以一定可以找到合适的位置，while(true)循环肯定可以正常退出
        while (true) {
            iPosCount++;
            if (iPosCount >= (iPos - 1)) //找到了第i-1个位置
            {
                iIdxPrev = tmpcur;
                break;
            }
            tmpcur = m_data[tmpcur].cur;
        } //end while

        int iTmpCurr = m_data[iIdxPrev].cur; //当前要删除的这个节点的数组下标
        m_data[iIdxPrev].cur = m_data[iTmpCurr].cur;//前一个节点的cur指向当前要删除节点的cur
        m_data[iTmpCurr].cur = e_NOUSE; //标记被删除数据节点的数组下标为未用状态
        cout << "成功删除位置为" << iPos << "的元素，该元素的值为" << m_data[iTmpCurr].data << "!" << endl;
    } //end if (iPos == 1)
    m_length--;       //实际表长-1
    return true;
}

int main() {

    StaticLinkList<int> slinkobj;

    slinkobj.ListInsert(1, 12);
    slinkobj.ListInsert(1, 24);
    slinkobj.ListInsert(3, 48);
    slinkobj.ListInsert(2, 100);
    slinkobj.ListInsert(5, 190);
    slinkobj.ListInsert(4, 300);

    slinkobj.DispList();
    slinkobj.LocateElem(190);
    slinkobj.LocateElem(24);
    slinkobj.LocateElem(300);
    cout << "----------------" << endl;
    int eval = 0;
    slinkobj.GetElem(0, eval); //如果GetElem()返回true，则eval中保存着获取到的元素值
    slinkobj.GetElem(1, eval);
    slinkobj.GetElem(3, eval);
    slinkobj.GetElem(6, eval);

    cout << "----------------" << endl;
    slinkobj.ListDelete(1);
    slinkobj.ListDelete(5);
    slinkobj.ListDelete(10);
    slinkobj.DispList();

    cout << "----------------" << endl;
    slinkobj.ListInsert(1, 500);
    slinkobj.ListInsert(3, 600);
    slinkobj.ListInsert(4, 700);
    slinkobj.DispList();

    return 0;
}