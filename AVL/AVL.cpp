// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <cassert>

#pragma warning (disable: 4996)
using namespace std;


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
    LinkStack();      //构造函数，参数可以有默认值
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

//--------------------------------------
//平衡二叉树中每个节点的定义
template<typename T> //T代表数据元素的类型
struct AVLNode {
    T data;
    AVLNode *leftChild,   //左子节点指针
    *rightChild;  //右子节点指针
    int balfac;      //平衡因子
};

//平衡二叉树的定义
template<typename T>
class AVLTree {
public:
    AVLTree()  //构造函数
    {
        root = nullptr;
    }

    ~AVLTree() //析构函数
    {
        ReleaseNode(root);
    }

    //插入元素
    void InsertElem(const T &e)  //不可以指定插入位置，程序内部会自动确定插入位置
    {
        InsertElem(root, e);
    }

    void InsertElem(AVLNode<T> *&tNode, const T &e) //注意第一个参数类型
    {
        AVLNode<T> *point = tNode;     //从指向根节点开始
        AVLNode<T> *parent = nullptr;  //保存父亲节点，根节点的父节点肯定先为nullptr

        //借助以往实现的栈（链栈）代码保存插入的节点路径信息（用于后面调节平衡因子、调整平衡）
        LinkStack<AVLNode<T> *> slinkobj;

        //通过一个while循环寻找要插入节点的位置，同时还要把插入路线上所经过的所有节点都保存到栈中，因为这些节点的平衡因子可能需要调整
        while (point != nullptr) {
            if (e == point->data)
                return;   //要插入的数据与当前树中某节点数据相同，则不允许插入，直接返回

            parent = point; //记录父节点，因为后续子节点要往下走，找合适自己的位置
            slinkobj.Push(parent); //入栈（树根在最底下，越往上离要插入的节点越近，最上面元素是要插入的节点的父节点）

            if (e > point->data)
                point = point->rightChild;
            else
                point = point->leftChild;
        } //end while

        //走到这里，point 等于 nullptr，该生成新节点了
        point = new AVLNode<T>;
        point->data = e;
        point->leftChild = nullptr;
        point->rightChild = nullptr;
        point->balfac = 0; //插入时肯定是个叶节点，所以平衡因子肯定等于0

        if (parent == nullptr) {
            //创建的是根节点
            tNode = point;
            return;
        }

        //走到这里表示创建的不是根节点，那么要把孩子链到父亲上
        if (e > parent->data)
            parent->rightChild = point;  //在父节点的右树链入
        else
            parent->leftChild = point;  //在父节点的左树链入

        //下面即将修改平衡因子 以及 调整平衡，前面栈slinkobj里的节点就是可能要更改平衡因子和做平衡调整的节点
        while (slinkobj.Empty() != true) {
            if (slinkobj.Pop(parent) == true) //取栈顶元素到parent中，第一次获取到的是新插入节点的父节点
            {
                //(1)因为插入了孩子，所以 调整父的平衡因子
                if (parent->leftChild == point) //插入的是parent的左子节点
                    parent->balfac++;  //平衡因子+1
                else
                    parent->balfac--;  //平衡因子-1

                //(2)找最小不平衡子树的根节点 并进行平衡性调整
                if (parent->balfac < -1 || parent->balfac > 1) {
                    //有四种旋转方式，采取哪种旋转方式呢？

                    //(1)如果 这棵最小不平衡子树 的根节点 和其孩子节点 的平衡因子都 >0，那就是LL情形，要右旋转来恢复平衡
                    if (parent->balfac > 0 && point->balfac > 0) {
                        RotateRight(parent);
                    }
                        //(2)如果 这棵最小不平衡子树 的根节点 和其孩子节点 的平衡因子都 < 0，那就是RR情形，要左旋转来恢复平衡
                    else if (parent->balfac < 0 && point->balfac < 0) {
                        RotateLeft(parent);
                    }

                        //(3)如果 这棵最小不平衡子树 的根节点 的平衡因子>0  其孩子节点 的平衡因子都 <0，那就是LR情形，要先左旋再右旋来恢复平衡
                    else if (parent->balfac > 0 && point->balfac < 0) {
                        RotateLeftRight(parent);
                    }

                        //(4)如果 这棵最小不平衡子树 的根节点 的平衡因子<0  其孩子节点 的平衡因子都 >0，那就是RL情形，要先右旋再左旋来恢复平衡
                    else //if (parent->balfac < 0 && point->balfac > 0)
                    {
                        RotateRightLeft(parent);
                    }

                    //根相关指针的调整
                    if (slinkobj.Empty() == true) {
                        //本条件成立，表示本次平衡性调整调整到了整个树最上面的根节点，因为平衡性调整会使树根节点发生改变，所以这里要更新根节点的指向
                        root = parent;
                    } else {
                        //本次平衡性调整 并没有调整到 整个树最上面的根节点，但 因为平衡性调整会使树根节点发生改变，所以老根节点的孩子指针应该指向新根节点
                        AVLNode<T> *pParentPoint = nullptr;
                        slinkobj.GetTop(pParentPoint);  //拿到老根的父节点，一定会取得成功，因为栈不为空

                        //判断让老根父节点（pParentPoint）的左孩子指针还是右孩子指针指向新根（parent）
                        if (pParentPoint->data > parent->data)
                            pParentPoint->leftChild = parent;
                        else
                            pParentPoint->rightChild = parent;
                    }
                    break; //最小平衡子树调整完成后，其他不平衡节点自然会恢复平衡，所以不需要再向上调整，这里直接break;
                }

                    //比如某个节点A有个左子树B1，所以其平衡因子为1,现在给其增加一个右子树B2，其平衡因子变为0，
                    //此时不要再继续向上调整节点A的父的平衡因子了，否则会把A父亲的平衡因子调整错误。
                else if (parent->balfac == 0) {
                    //已经平衡，不需要继续 回溯 调整
                    break;
                } else {
                    point = parent;   //让point指向父节点，后序parent的新值要从栈顶获取
                } //end if (parent->balfac < -1 || parent->balfac > 1)

            } //end if
        } //end while

        return;
    }

    //删除某个节点
    void DeleteElem(const T &e) {
        return DeleteElem(root, e);
    }

    void DeleteElem(AVLNode<T> *&tNode, const T &e)  //注意第一个参数类型
    {
        AVLNode<T> *ptmp = tNode; //要删除的节点
        AVLNode<T> *parent = nullptr;  //保存父亲节点，根节点的父节点肯定先为nullptr

        //借助栈保存删除的节点路径信息
        LinkStack<AVLNode<T> *> slinkobj;

        while (ptmp != nullptr) //通过while循环尝试让ptmp指向要被删除的节点
        {
            if (ptmp->data == e)
                break;

            parent = ptmp; //记录父节点
            slinkobj.Push(parent); //入栈

            if (ptmp->data > e)
                ptmp = ptmp->leftChild;
            else
                ptmp = ptmp->rightChild;
        } //end while
        if (ptmp == nullptr)//没有找到要删除的节点
            return;

        //找到了要删除的节点，前面二叉查找树删除节点分几种情况：
        AVLNode<T> *q = nullptr;         //临时指针变量
        if (ptmp->leftChild == nullptr && ptmp->rightChild == nullptr) {
            //如果要删除的节点左子树和右子树都为空（叶节点）
            if (parent != nullptr) {
                if (parent->leftChild == ptmp) //要删除的节点是其父的左孩子
                    parent->leftChild = nullptr;
                else
                    parent->rightChild = nullptr;
            }
        } else if (ptmp->leftChild != nullptr && ptmp->rightChild != nullptr) {
            //如果要删除的节点左子树和右子树都不为空，则把对当前节点的删除转换为对当前节点左子树的最右下节点的删除
            //这里涉及到的问题是要记录最终真删除的节点的路径
            //删除举例：比如删除如下的D节点，最后会转变成删除F节点。ptmp指向的是F节点
            //        *
            //    D              *
            //  *        *         *
            //*   F        *
            //(1)该入栈的节点入栈
            parent = ptmp;  //记录父节点
            slinkobj.Push(parent); //入栈
            //(2)找到这个要删除节点的左子树的最右下节点（也可以找这个要删除节点右子树的最左下节点）,将该节点的值替换到要删除的节点上；
            q = ptmp->leftChild;
            while (q->rightChild != nullptr) {
                parent = q;
                slinkobj.Push(parent); //入栈
                q = q->rightChild;
            }
            ptmp->data = q->data;
            ptmp = q; //让ptmp指向真正删除的节点，也就是把删除一个既有左子树右有右子树的节点转化为删除一个叶子节点。

            //上面找到这个节点肯定没有右子树，因为找的是左子树的最右下节点嘛！
            if (parent != nullptr) {
                if (parent->leftChild == ptmp)
                    parent->leftChild = ptmp->leftChild;
                else
                    parent->rightChild = ptmp->leftChild;
            }
        } else {
            //如果要删除的节点的左子树为空或者右子树为空(两者肯定有一个为空才能走到这个分支)，让q指向不空的孩子节点
            if (ptmp->leftChild != nullptr)
                q = ptmp->leftChild;
            else
                q = ptmp->rightChild;

            if (parent != nullptr) {
                //把被删除的节点的子节点链接到被删除节点的父节点上去
                if (parent->leftChild == ptmp) //要删除的节点是其父的左孩子
                    parent->leftChild = q;
                else
                    parent->rightChild = q;
            }
        }

        //--------------------------------------------------------------
        //parent不为空的情况上面都处理了，这里处理parent为空的情况,parent为空删除的肯定是根节点
        if (parent == nullptr) //有些代码可以合并，但为了方便理解，笔者并没有合并，读者可以自行合并
        {
            if (ptmp->leftChild == nullptr && ptmp->rightChild == nullptr)//这棵树就一个根节点并且删除的就是这个根节点
                tNode = nullptr;
            else if (ptmp->leftChild == nullptr || ptmp->rightChild == nullptr) //要删除这棵树的根节点并且这棵树根的左子树为空或者右子树为空
                tNode = q;
            else {
                //这个else条件应该一直不会成立
                assert(false);//记得#include <cassert>,assert(false);意味着代码不可能执行到这条语句，若执行到了，会报告异常
            }
        }

        //--------------------------------------------------------------
        //处理平衡因子的改变（平衡性调整）
        while (slinkobj.Empty() != true) {
            if (slinkobj.Pop(parent) == true) {
                //如果删除的是叶子节点，并且其父亲只有一个叶子，那么删除后，其父亲就变成叶子了，叶子的平衡因子自然为0
                if (parent->leftChild == nullptr && parent->rightChild == nullptr)
                    parent->balfac = 0;
                else if (parent->leftChild == q) //删除的是左树
                    parent->balfac--; //平衡因子减少1
                else //删除右树
                    parent->balfac++; //平衡因子增加

                if (parent->balfac == -1 || parent->balfac == 1) {
                    //说明parent节点原来的平衡因子为0，也就是原来左右孩子都有，那么删除任意一个孩子，除parent节点平衡因子发生变化外，任何其他的parent的父亲等节点的平衡因子不会发生变化，这里可以直接退出
                    break;
                }
                if (parent->balfac == 0) {
                    //说明parent节点原来的平衡因子为-1或者1，得继续回溯向上尝试调整其他父节点平衡因子
                    q = parent;
                    continue;
                }

                //根据规则来
                if (parent->balfac == -2) {
                    //平衡因子为-2，所以能确定的是，一定有右孩子
                    if (parent->rightChild->balfac == -1) //左旋转
                        RotateLeft(parent);

                    else if (parent->rightChild->balfac == 1) //先右后左旋转
                        RotateRightLeft(parent);

                    else //if (parent->rightChild->balfac == 0) //左旋转，可以和上面合并，读者自己合并代码吧
                    {
                        RotateLeft(parent);
                        parent->balfac = 1;
                        parent->leftChild->balfac = -1;
                    }
                } else {
                    //平衡因子为2，所以能确定的是，一定有左孩子
                    if (parent->leftChild->balfac == -1) //先左后右旋转
                        RotateLeftRight(parent);

                    else if (parent->leftChild->balfac == 1) //右旋转
                        RotateRight(parent);

                    else //if (parent->rightChild->balfac == 0)
                    {
                        RotateRight(parent);
                        parent->balfac = -1;
                        parent->rightChild->balfac = 1;
                    }
                } //end if (parent->balfac == -2)

                //根相关指针的调整
                if (slinkobj.Empty() == true) {
                    //本条件成立，表示本次平衡性调整调整到了整个树最上面的根节点，因为平衡性调整会使树根节点发生改变，所以这里要更新根节点的指向
                    root = parent;
                } else {
                    //本次平衡性调整并没有调整到整个树最上面的根节点，但因为平衡性调整会使树根节点发生改变，所以老根节点的孩子指针应该指向新根节点
                    AVLNode<T> *pParentPoint = nullptr;
                    slinkobj.GetTop(pParentPoint);  //拿到老根的父节点，一定会取得成功，因为栈不为空

                    //判断让老根父节点（pParentPoint）的左孩子指针还是右孩子指针指向新根（parent）
                    if (pParentPoint->data > parent->data)
                        pParentPoint->leftChild = parent;
                    else
                        pParentPoint->rightChild = parent;
                } //end if (slinkobj.Empty() == true)
            } //end if (slinkobj.Pop(parent) == true)
        } //end while
        delete ptmp; //释放掉被删除节点所占用的内存
        return;
    }

private:
    //左旋转（RR插入导致失衡）
    void RotateLeft(AVLNode<T> *&pointer)//注意参数类型
    {
        AVLNode<T> *childLeft = pointer; //pointer是 “最小不平衡子树”的根节点，即 失衡的节点A
        pointer = childLeft->rightChild;  //新根（节点B） = 老根（节点A）的右孩子节点

        childLeft->rightChild = pointer->leftChild;  //如果节点B原来有左孩子，则首先将节点B这个左孩子作为节点A的右孩子。
        pointer->leftChild = childLeft;              //将失衡的节点A 作为节点B 的左孩子

        //需要变动的 平衡因子的处理，其他节点平衡因子不改变，不需要处理
        pointer->balfac = childLeft->balfac = 0;     //节点A和节点B的平衡因子恢复为0
    }

    //右旋转（LL插入导致失衡）
    void RotateRight(AVLNode<T> *&pointer) //注意参数类型
    {
        AVLNode<T> *childRight = pointer; //pointer是 “最小不平衡子树”的根节点，即 失衡的节点A
        pointer = childRight->leftChild;  //新根（节点B） = 老根（节点A）的左孩子节点

        childRight->leftChild = pointer->rightChild;  //如果节点B原来有右孩子，则首先将节点B这个右孩子作为节点A的左孩子。
        pointer->rightChild = childRight;             //将失衡的节点A 作为节点B 的右孩子

        //需要变动的 平衡因子的处理，其他节点平衡因子不改变，不需要处理
        pointer->balfac = childRight->balfac = 0;     //节点A和节点B的平衡因子恢复为0
    }

    //先左后右旋转（LR插入导致失衡）
    void RotateLeftRight(AVLNode<T> *&pointer) {
        //给值，让各个变量指向不同的节点
        AVLNode<T> *childRight = pointer;   //pointer是 “最小不平衡子树”的根节点，即 失衡的节点A
        AVLNode<T> *childLeft = childRight->leftChild;  //节点B = 节点A 的左孩子节点
        pointer = childLeft->rightChild;    //节点C，就是节点B的右孩子，也是最终 先左后右旋转后的新根

        //进行左旋转
        childLeft->rightChild = pointer->leftChild; //如果节点C  原来有左孩子，则将这个左孩子变成节点B的右孩子
        pointer->leftChild = childLeft;   //节点B(childLeft) 变成了其原右孩子(节点C：pointer)的左孩子

        //节点B的平衡因子会改变,这主要取决于节点C原来带的是左孩子还是右孩子（或者说取决于节点C的平衡因子）
        if (pointer->balfac >= 0)  //原来带的是左孩子
            childLeft->balfac = 0; //因为节点C带的左孩子刚好成了节点B的右孩子，节点B原来有个左孩子，所以现在节点B平衡了
        else   //节点C没带左孩子
            childLeft->balfac = 1; //节点B只有一个做好自己，所以节点B平衡因子为1

        //进行上述的左旋转后，新的节点B其实已经是pointer了。而且此时节点C（新根）的平衡因子还保持为老值（1或者-1）
        //再进行右旋转
        childRight->leftChild = pointer->rightChild; //如果节点C原来有右孩子，则将这个右孩子变成节点A的左孩子
        pointer->rightChild = childRight;    //将失衡的节点A向右侧旋转来作为【新】节点B（pointer）的右孩子
        if (pointer->balfac == 1)    //新节点B原来带的是左孩子
            childRight->balfac = -1; //节点A原来有个右孩子，所以节点A平衡因子变成-1
        else
            childRight->balfac = 0;  //新节点B没带孩子或带右孩子，这个右孩子会挂到节点A上当左孩子，所以节点A平衡因子变为0

        //根节点（新节点B）的平衡因子最后调整为0
        pointer->balfac = 0;
    }

    //先右后左旋转（RL插入导致失衡），参考RotateLeftRight()书写
    void RotateRightLeft(AVLNode<T> *&pointer)  //注意参数类型
    {
        AVLNode<T> *childLeft = pointer;  //以课程/书中实际节点来说明：60
        AVLNode<T> *childRight = childLeft->rightChild;  //120
        pointer = childRight->leftChild;    //95

        //进行右旋转
        childRight->leftChild = pointer->rightChild;  //120的左孩子设置为100
        pointer->rightChild = childRight;  //95的右孩子指向120

        //调节120的平衡因子
        if (pointer->balfac <= 0) //如果95的平衡因子是0，-1（95不带孩子或者带右孩子）
            childRight->balfac = 0;  //则120的平衡因子是0
        else   //节点95带左孩子
            childRight->balfac = -1; //则120的平衡因子是-1

        //再进行左旋转
        childLeft->rightChild = pointer->leftChild; //60的右孩子指向（65）
        pointer->leftChild = childLeft; //95的左孩子指向60

        //调节60的平衡因子
        if (pointer->balfac == -1)    //如果95的平衡因子是-1（95带右子树）
            childLeft->balfac = 1;
        else        //节点95不带子树或者带左子树
            childLeft->balfac = 0;

        pointer->balfac = 0;  //95这个节点的平衡因子设置为0
    }

    void ReleaseNode(AVLNode<T> *pnode) {
        if (pnode != nullptr) {
            ReleaseNode(pnode->leftChild);
            ReleaseNode(pnode->rightChild);
        }
        delete pnode;
    }

private:
    AVLNode<T> *root; //树根指针
};
//-----------------------------------------

int main() {

    AVLTree<int> mybtr;
    int array[] = {60, 31, 65, 15, 42, 62, 75, 12, 25, 37, 50, 63, 69, 85, 2, 32, 38, 48, 56, 82, 34};
    int acount = sizeof(array) / sizeof(int);
    for (int i = 0; i < acount; ++i)
        mybtr.InsertElem(array[i]);
    //删除测试
    mybtr.DeleteElem(65);

    return 0;
}


