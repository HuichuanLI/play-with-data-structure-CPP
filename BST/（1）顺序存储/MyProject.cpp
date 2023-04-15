
#include <iostream>

#pragma warning (disable: 4996)
using namespace std;

#define MaxSize 100       //数组的尺寸

enum ECCHILDSIGN  //节点标记
{
    E_Root,       //树根
    E_ChildLeft,  //左孩子
    E_ChildRight  //右孩子
};

//树中每个节点的定义
template<typename T>//T代表数据元素的类型
struct BinaryTreeNode {
    T data;   //数据域，存放数据元素
    bool isValid;//该节点是否有效以应对非完全二叉树（只有保存了实际节点数据的节点才是有效的）
};

//二叉树的定义
template<typename T>
class BinaryTree {
public:
    BinaryTree()      //构造函数
    {
        for (int i = 0; i <= MaxSize; ++i) //注意数组的大小是MaxSize+1，所以这里i的终止值没问题
        {
            SqBiTree[i].isValid = false; //开始时节点无效，没保存任何数据
        }
    }

    ~BinaryTree() {};     //析构函数

public:
    //创建一个树节点
    int CreateNode(int parindex, ECCHILDSIGN pointSign, const T &e);

    //获取父节点的下标
    int getParentIdx(int sonindex) {
        if (ifValidRangeIdx(sonindex) == false) //位置不合理
            return -1;

        if (SqBiTree[sonindex].isValid == false) //不是个合理的节点，不要尝试找父节点
            return -1;

        return int(sonindex / 2);  //i的父节点是（i / 2）向下取整
    }

    //获取某个节点所在的高度：
    //根据二叉树性质五：具有n（n > 0）个节点的完全二叉树的高度为⌈log(⁡n + 1)⌉或者⌊log(⁡n)⌋ + 1。这里的对数都是以2为底
    int getPointLevel(int index) {
        if (ifValidRangeIdx(index) == false) //位置不合理
            return -1;

        if (SqBiTree[index].isValid == false)//不是个合理的节点，不要尝试找父节点
            return -1;

        //采用公式⌊log(n)⌋ + 1
        int level = int(log(index) / log(2) + 1);//c++中的log（n）函数求的是以e(2.71828)为底的对数值，如果要求以数字m为底的对数值，则需要log(n)/log(m)

        return level;
    }

    //获取二叉树的深度
    int getLevel() {
        if (SqBiTree[1].isValid == false) //没根？
            return 0;

        int i;
        for (i = MaxSize; i >= 1; --i) {
            if (SqBiTree[i].isValid == true) //找到最后一个有效节点
                break;
        } //end for
        return getPointLevel(i);
    }

    //判断是否是个完全二叉树
    bool ifCompleteBT() {
        if (SqBiTree[1].isValid == false) //没根？这是二叉树吗？
            return false;

        int i;
        for (i = MaxSize; i >= 1; --i) {
            if (SqBiTree[i].isValid == true) //找到最后一个有效节点
                break;
        } //end for

        for (int k = 1; k <= i; ++k) {
            if (SqBiTree[k].isValid == false) //所有节点必须都要有效
                return false;
        }
        return true;
    }

    //前序遍历二叉树，其他的遍历方式在二叉树的链式存储中再详细书写代码和讲解
    void preOrder() {
        if (SqBiTree[1].isValid == false) //没根？这是二叉树吗？
            return;

        preOrder(1); //根节点的数组下标是1，所以这里把根的下标传递过去
    }

    void preOrder(int index) {
        if (ifValidRangeIdx(index) == false) //位置不合理
            return;

        if (SqBiTree[index].isValid == false) //不是个合理的节点
            return;

        //根左右顺序
        cout << (char) SqBiTree[index].data << ""; //输出节点的数据域的值，为方便观察，用char以显示字母
        preOrder(2 * index);  //递归方式前序遍历左子树
        preOrder(2 * index + 1); //递归方式前序遍历右子树
    }

private:
    bool ifValidRangeIdx(int index) //是否是一个有效的数组下标值
    {
        //位置必须合理
        if (index < 1 || index > MaxSize)  //[0]下标留着不用。因定义数组时定义的是MaxSize + 1，所以数组最大下标是MaxSize。
            return false;
        return true;
    }

private:
    BinaryTreeNode<T> SqBiTree[MaxSize + 1]; //存储二叉树节点的数组，为写程序方便，下标为[0]的数组元素不使用，因此这里+1
};

//创建一个树节点
template<class T>
//参数1：父节点所在数组下标，参数2：标记所创建的是树根、左孩子、右孩子，参数3：插入的树节点的元素值
//返回值，返回存储位置对应的数组下标，返回-1表示非法下标（执行失败）
int BinaryTree<T>::CreateNode(int parindex, ECCHILDSIGN pointSign, const T &e) {
    if (pointSign != E_Root) //非根节点，则一定是子节点，要求parindex一定要是个合理值
    {
        if (ifValidRangeIdx(parindex) == false) //位置不合理
            return -1;
        if (SqBiTree[parindex].isValid == false) //父节点不可以无效
            return -1;
    }

    int index = -1;
    if (pointSign == E_Root) //根
    {
        index = 1;//根节点固定存储在下标为1的位置。
    } else if (pointSign == E_ChildLeft) //左孩子
    {
        //创建的是左孩子节点，节点i的左孩子节点的下标是2i
        index = 2 * parindex;
        if (ifValidRangeIdx(index) == false)
            return -1; //非法下标
    } else //右孩子
    {
        //节点i的右孩子节点的下标是2i+1
        index = 2 * parindex + 1;
        if (ifValidRangeIdx(index) == false)
            return -1; //非法下标
    }

    SqBiTree[index].data = e;
    SqBiTree[index].isValid = true; //标记该下标中有有效数据
    return index;
}

int main() {

    BinaryTree<int> mytree;
    //创建一棵二叉树
    int indexRoot = mytree.CreateNode(-1, E_Root, 'A'); //创建树根节点A
    int indexNodeB = mytree.CreateNode(indexRoot, E_ChildLeft, 'B');  //创建树根的左子节点B
    int indexNodeC = mytree.CreateNode(indexRoot, E_ChildRight, 'C'); //创建树根的右子节点C

    int indexNodeD = mytree.CreateNode(indexNodeB, E_ChildLeft, 'D'); //创建节点B的左子节点D
    int indexNodeE = mytree.CreateNode(indexNodeC, E_ChildRight, 'E'); //创建节点C的右子节点E

    int iParentIndexE = mytree.getParentIdx(indexNodeE);   //获取某个节点的父节点的下标
    cout << "节点E的父节点的下标是：" << iParentIndexE << endl;

    int iLevel = mytree.getPointLevel(indexNodeD);  //获取某个节点所在的高度
    cout << "节点D所在的高度是：" << iLevel << endl;
    iLevel = mytree.getPointLevel(indexNodeE);
    cout << "节点E所在的高度是：" << iLevel << endl;
    cout << "二叉树的深度是：" << mytree.getLevel() << endl;
    cout << "二叉树是个完全二叉树吗？" << mytree.ifCompleteBT() << endl;

    cout << "------------" << endl;
    cout << "前序遍历序列为：";
    mytree.preOrder();   //前序遍历


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



