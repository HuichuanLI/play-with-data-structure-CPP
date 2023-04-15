// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>

#pragma warning (disable: 4996)
using namespace std;

//链式队列相关代码

//链式队列中每个节点的定义
template<typename T> //T代表数据元素的类型
struct QueueNode {
    T data;       //数据域，存放数据元素
    QueueNode<T> *next;  //指针域，指向下一个同类型（和本节点类型相同）节点
};

//链式队列的定义
template<typename T> //T代表数组中元素的类型
class LinkQueue {
public:
    LinkQueue();                          //构造函数，参数可以有默认值
    ~LinkQueue();                         //析构函数

public:
    bool EnQueue(const T &e);            //入队列（增加数据）
    bool DeQueue(T &e);                  //出队列（删除数据）
    bool GetHead(T &e);                  //读取队头元素，但该元素并没有出队列而是依旧在队列中

    void DispList();                     //输出链式队列中的所有元素
    int ListLength();                   //获取链式队列的长度（实际拥有的元素数量）

    bool IsEmpty();                      //判断链式队列是否为空

private:
    QueueNode<T> *m_front;               //头指针（指向头结点），这一端允许出队（删除）
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
    if (m_front == m_rear) //当然，换一种判断方式也行：if(m_front->next == nullptr) return true;
    {
        return true;
    }
    return false;
}


//-------------------
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

//---------------

enum ECCHILDSIGN  //节点标记
{
    E_Root,       //树根
    E_ChildLeft,  //左孩子
    E_ChildRight  //右孩子
};
//树中每个节点的定义
template<typename T> //T代表数据元素的类型
struct BinaryTreeNode {
    T data;        //数据域，存放数据元素
    BinaryTreeNode *leftChild,   //左子节点指针
    *rightChild;  //右子节点指针

    //BinaryTreeNode* parent;      //父节点指针，可以根据需要决定是否引入
};

//为实现二叉树的非递归后序遍历引入的新类模板
template<typename T> //T代表数据元素的类型
struct BTNode_extra {
    BinaryTreeNode<T> *point;
    ECCHILDSIGN pointSign;
};

//二叉树的定义
template<typename T>
class BinaryTree {
public:
    BinaryTree();  //构造函数
    ~BinaryTree(); //析构函数
public:
    //创建一个树节点
    BinaryTreeNode<T> *CreateNode(BinaryTreeNode<T> *parentnode, ECCHILDSIGN pointSign, const T &e);

    //释放树节点
    void ReleaseNode(BinaryTreeNode<T> *pnode);

public:
    //利用扩展二叉树的前序遍历序列来创建一棵二叉树
    void CreateBTreeAccordPT(char *pstr);

private:
    //利用扩展二叉树的前序遍历序列创建二叉树的递归函数
    void CreateBTreeAccordPTRecu(BinaryTreeNode<T> *&tnode, char *&pstr);//参数为引用类型，确保递归调用中对参数的改变会影响到调用者

public:
    //前序遍历二叉树
    void preOrder() {
        preOrder(root);
    }

    void preOrder(BinaryTreeNode<T> *tNode) {
        if (tNode != nullptr) //若二叉树非空
        {
            //根左右顺序
            cout << (char) tNode->data << " "; //输出节点的数据域的值，为方便观察，用char以显示字母
            preOrder(tNode->leftChild);  //递归方式前序遍历左子树
            preOrder(tNode->rightChild); //递归方式前序遍历右子树
        }
    }

    //--------------------------
    //中序遍历二叉树
    void inOrder() {
        inOrder(root);
    }

    void inOrder(BinaryTreeNode<T> *tNode)  //中序遍历二叉树
    {
        if (tNode != nullptr) //若二叉树非空
        {
            //左根右顺序
            inOrder(tNode->leftChild);  //递归方式中序遍历左子树
            cout << (char) tNode->data << " "; //输出节点的数据域的值
            inOrder(tNode->rightChild); //递归方式中序遍历右子树
        }
    }

    //--------------------------
    //后序遍历二叉树
    void postOrder() {
        postOrder(root);
    }

    void postOrder(BinaryTreeNode<T> *tNode)  //后序遍历二叉树
    {
        if (tNode != nullptr) //若二叉树非空
        {
            //左右根顺序
            postOrder(tNode->leftChild);  //递归方式后序遍历左子树
            postOrder(tNode->rightChild); //递归方式后序遍历右子树
            cout << (char) tNode->data << " "; //输出节点的数据域的值
        }
    }

    //--------------------------
    //层序遍历二叉树
    void levelOrder() {
        levelOrder(root);
    }

    void levelOrder(BinaryTreeNode<T> *tNode) {
        if (tNode != nullptr) //若二叉树非空
        {
            BinaryTreeNode<T> *tmpnode;
            LinkQueue<BinaryTreeNode<T> *> lnobj;//注意，队列的元素类型是“节点指针”类型
            lnobj.EnQueue(tNode); //先把根节点指针入队
            while (!lnobj.IsEmpty()) //循环判断队列是否为空
            {
                lnobj.DeQueue(tmpnode); //出队列
                cout << (char) tmpnode->data << " ";
                if (tmpnode->leftChild != nullptr)
                    lnobj.EnQueue(tmpnode->leftChild);  //左孩子入队
                if (tmpnode->rightChild != nullptr)     //右孩子入队
                    lnobj.EnQueue(tmpnode->rightChild);
            } //end while
        }
    }

    //求二叉树节点个数
    int getSize() {
        return getSize(root);
    }

    int getSize(BinaryTreeNode<T> *tNode) //也可以用遍历二叉树的方式求节点个数
    {
        if (tNode == nullptr)
            return 0;

        return getSize(tNode->leftChild) + getSize(tNode->rightChild) + 1; //之所以+1，是因为还有个根节点
    }

    //求二叉树高度（取左右子树中高度更高的）
    int getHeight() {
        return getHeight(root);
    }

    int getHeight(BinaryTreeNode<T> *tNode) {
        if (tNode == nullptr)
            return 0;
        int lheight = getHeight(tNode->leftChild); //左子树高度
        int rheight = getHeight(tNode->rightChild); //右子树高度
        if (lheight > rheight)
            return lheight + 1; //之所以+1，是因为还包括根节点的高度
        return rheight + 1;   //之所以+1，是因为还包括根节点的高度
    }

    BinaryTreeNode<T> *SearchElem(const T &e) {
        return SearchElem(root, e);
    }

    BinaryTreeNode<T> *SearchElem(BinaryTreeNode<T> *tNode, const T &e) {
        if (tNode == nullptr)
            return nullptr;
        if (tNode->data == e)  //从根开始找
            return tNode;
        BinaryTreeNode<T> *p = SearchElem(tNode->leftChild, e); //查找左子树
        if (p != nullptr) //这里的判断不可缺少
            return p;
        return SearchElem(tNode->rightChild, e); //左子树查不到，继续到右子树查找，这里可以直接return
    }

    BinaryTreeNode<T> *GetParent(BinaryTreeNode<T> *tSonNode) {
        return GetParent(root, tSonNode);
    }

    BinaryTreeNode<T> *GetParent(BinaryTreeNode<T> *tParNode, BinaryTreeNode<T> *tSonNode) {
        if (tParNode == nullptr || tSonNode == nullptr)
            return nullptr;

        if (tParNode->leftChild == tSonNode || tParNode->rightChild == tSonNode)
            return tParNode;

        BinaryTreeNode<T> *pl = GetParent(tParNode->leftChild, tSonNode);
        if (pl != nullptr)
            return pl;

        return GetParent(tParNode->rightChild, tSonNode);
    }

    void CopyTree(BinaryTree<T> *targetTree) {
        CopyTree(root, targetTree->root);
    }

    void CopyTree(BinaryTreeNode<T> *tSource, BinaryTreeNode<T> *&tTarget) //注意第二个参数类型为引用
    {
        if (tSource == nullptr) {
            tTarget = nullptr;
        } else {
            tTarget = new BinaryTreeNode<T>;
            tTarget->data = tSource->data;
            CopyTree(tSource->leftChild, tTarget->leftChild);  //对左子树进行拷贝
            CopyTree(tSource->rightChild, tTarget->rightChild);//对右子树进行拷贝
        }
    }

    //非递归方式前序遍历二叉树
    void preOrder_noRecu() {
        preOrder_noRecu(root);
    }

    void preOrder_noRecu(BinaryTreeNode<T> *tRoot) {
        if (tRoot == nullptr)
            return;

        LinkStack<BinaryTreeNode<T> *> slinkobj;
        slinkobj.Push(tRoot); //根节点入栈

        BinaryTreeNode<T> *tmpnode;
        while (!slinkobj.Empty()) //栈不空
        {
            slinkobj.Pop(tmpnode);               //栈顶元素出栈
            cout << (char) tmpnode->data << " ";  //访问栈顶元素

            if (tmpnode->rightChild != nullptr) //注意先判断右树再判断左树
            {
                slinkobj.Push(tmpnode->rightChild); //把右树入栈
            }
            if (tmpnode->leftChild != nullptr) {
                slinkobj.Push(tmpnode->leftChild); //把左树入栈
            }
        } //end while
    }

    //非递归方式中序遍历二叉树
    void inOrder_noRecu() {
        inOrder_noRecu(root);
    }

    void inOrder_noRecu(BinaryTreeNode<T> *tRoot) {
        if (tRoot == nullptr)
            return;

        LinkStack<BinaryTreeNode<T> *> slinkobj;
        slinkobj.Push(tRoot);//根节点入栈

        BinaryTreeNode<T> *tmpnode;
        while (!slinkobj.Empty()) //栈不空
        {
            while (tRoot->leftChild != nullptr) {
                slinkobj.Push(tRoot->leftChild);    //将“当前节点的左节点”入栈
                tRoot = tRoot->leftChild; //将“当前节点的左节点”重新标记为当前节点。
            } //end while

            slinkobj.Pop(tmpnode); //对栈顶元素出栈(同时获取了栈顶元素)
            cout << (char) tmpnode->data << " ";

            //查看右树
            if (tmpnode->rightChild != nullptr) {
                tRoot = tmpnode->rightChild;  //将刚刚从栈顶出栈的元素的右节点标记为当前节点
                slinkobj.Push(tRoot); //右节点入栈
            }
        }//end while
    }

    //非递归后序遍历二叉树
    void postOrder_noRecu() {
        postOrder_noRecu(root);
    }

    void postOrder_noRecu(BinaryTreeNode<T> *tRoot) {
        if (tRoot == nullptr)
            return;

        LinkStack<BTNode_extra<T> > slinkobj;
        BTNode_extra<T> ext_tmpnode;

        do {
            while (tRoot != nullptr) {
                ext_tmpnode.point = tRoot;
                ext_tmpnode.pointSign = E_ChildLeft;  //标记先处理该节点的左孩子
                slinkobj.Push(ext_tmpnode);
                tRoot = tRoot->leftChild;
            }
            while (!slinkobj.Empty()) {
                slinkobj.Pop(ext_tmpnode); //出栈
                if (ext_tmpnode.pointSign == E_ChildLeft) {
                    //把左标记更改为右标记
                    ext_tmpnode.pointSign = E_ChildRight; //标记该节点的右孩子
                    slinkobj.Push(ext_tmpnode);         //重新入栈
                    tRoot = ext_tmpnode.point->rightChild;
                    break;  //终止while循环
                } else //if (ext_tmpnode.pointSign == E_ChildRight) 肯定是右子树标记，所以这个if不需要
                {
                    //根据左右根规则，右节点之后可以访问根节点
                    cout << (char) ext_tmpnode.point->data << " ";
                }
            } //end while
        } while (!slinkobj.Empty());
    }

    //如何根据前序、中序遍历序列来创建一棵二叉树呢？
    //pP_T：前序遍历序列，比如是“ABDCE”，pI_T：中序遍历序列，比如是“DBACE”
    void CreateBTreeAccordPI(char *pP_T, char *pI_T) {
        CreateBTreeAccordPI(root, pP_T, pI_T, strlen(pP_T));
    }

    void
    CreateBTreeAccordPI(BinaryTreeNode<T> *&tnode, char *pP_T, char *pI_T, int n)//参数1为引用类型，确保递归调用中对参数的改变会影响到调用者,n:节点个数
    {
        if (n == 0) {
            tnode = nullptr;
        } else {
            //(1)在中序遍历序列中找根，前序遍历序列中根在最前面
            int tmpindex = 0;   //下标
            while (pP_T[0] != pI_T[tmpindex])
                ++tmpindex;

            tnode = new BinaryTreeNode<T>; //创建根节点
            tnode->data = pI_T[tmpindex];  //第一次tmpindex=2

            //(2)创建左孩子
            CreateBTreeAccordPI(
                    tnode->leftChild,   //创建左孩子
                    pP_T + 1,           //找到前序遍历序列中左树开始节点的位置，这里跳过第一个（根）节点A，得到的是“BDCE”
                    pI_T,               //不需要改动，仍旧是“DBACE”
                    tmpindex            //左孩子有2个节点
            );

            //(3)创建右孩子
            CreateBTreeAccordPI(
                    tnode->rightChild,   //创建右孩子
                    pP_T + tmpindex + 1, //找到前序遍历系列中右树开始节点的位置，不难发现，前序遍历序列和中序遍历序列右树开始节点的位置相同，得到的是“CE”
                    pI_T + tmpindex + 1, //找到中序遍历系列中右树开始节点的位置。得到的是“CE”
                    n - tmpindex - 1   //右孩子节点数
            );
        }
    }

    //如何根据中序、后序遍历序列来创建一棵二叉树呢？
//pI_T：中序遍历序列，比如是“DBACE”，pPOST_T：后序遍历序列，比如是“DBECA”
    void CreateBTreeAccordIPO(char *pI_T, char *pPOST_T) {
        CreateBTreeAccordIPO(root, pI_T, pPOST_T, strlen(pI_T));
    }

    void CreateBTreeAccordIPO(BinaryTreeNode<T> *&tnode, char *pI_T, char *pPOST_T,
                              int n)//参数1为引用类型，确保递归调用中对参数的改变会影响到调用者,n:节点个数
    {
        //可以通过后序遍历找到根节点
        if (n == 0) {
            tnode = nullptr;
        } else {
            //(1)在中序遍历序列中找根，后序遍历序列中根在最后面
            int tmpindex = 0;   //下标
            while (pPOST_T[n - 1] != pI_T[tmpindex])
                ++tmpindex;

            tnode = new BinaryTreeNode<T>; //创建根节点
            tnode->data = pI_T[tmpindex];  //第一次tmpindex=2

            //(2)创建左孩子
            CreateBTreeAccordIPO(
                    tnode->leftChild,    //创建左孩子
                    pI_T, //不需要改动，仍旧是“DBACE”，因为开头的都是左孩子
                    pPOST_T, //不需要改动，仍旧是“DBECA”，因为开头的都是左孩子
                    tmpindex             //左孩子节点数
            );

            //(3)创建右孩子
            CreateBTreeAccordIPO(
                    tnode->rightChild,    //创建右孩子
                    pI_T + tmpindex + 1, //找到中序遍历系列中右树开始节点的位置。得到的是“CE”
                    pPOST_T + tmpindex,   //找到后序遍历系列中右树开始节点的位置。得到的是“ECA”
                    n - tmpindex - 1      //右孩子节点数
            );
        }
    }

private:
    BinaryTreeNode<T> *root; //树根指针
};

//构造函数
template<class T>
BinaryTree<T>::BinaryTree() {
    root = nullptr;
}

//析构函数
template<class T>
BinaryTree<T>::~BinaryTree() {
    ReleaseNode(root);
};

//释放二叉树节点
template<class T>
void BinaryTree<T>::ReleaseNode(BinaryTreeNode<T> *pnode) {
    if (pnode != nullptr) {
        ReleaseNode(pnode->leftChild);
        ReleaseNode(pnode->rightChild);
    }
    delete pnode;
}

//创建一个树节点
template<class T>
//参数1：父节点指针，参数2：标记所创建的是树根、左孩子、右孩子，参数3：插入的树节点的元素值
BinaryTreeNode<T> *BinaryTree<T>::CreateNode(BinaryTreeNode<T> *parentnode, ECCHILDSIGN pointSign, const T &e) {
    //将新节点创建出来
    BinaryTreeNode<T> *tmpnode = new BinaryTreeNode<T>;
    tmpnode->data = e;
    tmpnode->leftChild = nullptr;
    tmpnode->rightChild = nullptr;

    //把新节点放入正确的位置
    if (pointSign == E_Root) {
        //创建的是根节点
        root = tmpnode;
    }
    if (pointSign == E_ChildLeft) {
        //创建的是左孩子节点
        parentnode->leftChild = tmpnode;
    } else if (pointSign == E_ChildRight) {
        //创建的是右孩子节点
        parentnode->rightChild = tmpnode;
    }
    return tmpnode;
}

//利用扩展二叉树的前序遍历序列来创建一棵二叉树
template<class T>
void BinaryTree<T>::CreateBTreeAccordPT(char *pstr) {
    CreateBTreeAccordPTRecu(root, pstr);
}

//利用扩展二叉树的前序遍历序列创建二叉树的递归函数
template<class T>
void BinaryTree<T>::CreateBTreeAccordPTRecu(BinaryTreeNode<T> *&tnode, char *&pstr) {
    if (*pstr == '#') {
        tnode = nullptr;
    } else {
        tnode = new BinaryTreeNode<T>; //创建根节点
        tnode->data = *pstr;
        CreateBTreeAccordPTRecu(tnode->leftChild, ++pstr); //创建左子树
        CreateBTreeAccordPTRecu(tnode->rightChild, ++pstr);//创建右子树
    }
}

int main() {
	
    BinaryTree<int> mytree;
    //创建一棵二叉树
    BinaryTreeNode<int> *rootpoint = mytree.CreateNode(nullptr, E_Root, 'A'); //创建树根节点A
    BinaryTreeNode<int> *subpoint = mytree.CreateNode(rootpoint, E_ChildLeft, 'B'); //创建树根的左子节点B
    subpoint = mytree.CreateNode(subpoint, E_ChildLeft, 'D'); //创建左子节点B下的左子节点D

    subpoint = mytree.CreateNode(rootpoint, E_ChildRight, 'C'); //创建树根的右子节点C
    subpoint = mytree.CreateNode(subpoint, E_ChildRight, 'E');  //创建右子节点C下的右子节点E

    BinaryTree<int> mytree2;
    //mytree2.CreateBTreeAccordPT((char*)"ABD###C#E##");
    //mytree2.CreateBTreeAccordPI((char*)"ABDCE", (char*)"DBACE");
    mytree2.CreateBTreeAccordIPO((char *) "DBACE", (char *) "DBECA");

    //-----------------
    cout << "前序遍历序列为：";
    mytree2.preOrder();   //前序遍历
    cout << endl; //换行

    cout << "中序遍历序列为：";
    mytree2.inOrder();    //中序遍历
    cout << endl; //换行

    cout << "后序遍历序列为：";
    mytree2.postOrder();  //后序遍历

    //----------------
    cout << endl; //换行
    cout << "层序遍历序列为：";
    mytree2.levelOrder();

    //---------------
    cout << endl;
    cout << "二叉树节点个数为：" << mytree2.getSize() << endl;

    //---------------
    cout << "二叉树的高度为：" << mytree2.getHeight() << endl;

    //---------------
    //查找某个节点
    int val = 'B';
    BinaryTreeNode<int> *p = mytree2.SearchElem(val);
    if (p != nullptr)
        cout << "找到了值为" << (char) val << "的节点" << endl;
    else
        cout << "没找到值为" << (char) val << "的节点" << endl;

    //---------------
    //查找某个节点的父节点
    BinaryTreeNode<int> *parp = mytree2.GetParent(p);
    if (parp != nullptr)
        cout << "找到了值为" << (char) val << "的节点的父节点" << (char) parp->data << endl;
    else
        cout << "没找到值为" << (char) val << "的节点的父节点" << endl;

    //--------------
    //测试树的拷贝
    BinaryTree<int> mytree3;
    mytree2.CopyTree(&mytree3);

    //--------------
    cout << "非递归方式前序遍历序列为：";
    mytree2.preOrder_noRecu();
    cout << endl;
    //---------------
    cout << "非递归方式中序遍历序列为：";
    mytree2.inOrder_noRecu();
    cout << endl;
    //---------------
    cout << "非递归方式后序遍历序列为：";
    mytree2.postOrder_noRecu();
    cout << endl;
    //---------------


    return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误nm,
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件



