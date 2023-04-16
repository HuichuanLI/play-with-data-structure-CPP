//
// Created by lhc456 on 2023/4/16.
//
#include <iostream>

#pragma warning (disable: 4996)
using namespace std;

//树中每个节点的定义
template<typename T> //T代表数据元素的类型
struct BinaryTreeNode {
    T data;
    BinaryTreeNode *leftChild,   //左子节点指针
    *rightChild;  //右子节点指针
};


//二叉查找树的定义
template<typename T>
class BinarySearchTree {
public:
    BinarySearchTree()  //构造函数
    {
        root = nullptr;
    }

    ~BinarySearchTree() //析构函数
    {
        ReleaseNode(root);
    }

    //二叉树中序遍历代码（排序），方便测试时显示节点数据
    void inOrder() {
        inOrder(root);
    }

    void inOrder(BinaryTreeNode<T> *tNode) {
        if (tNode != nullptr) {
            //左根右顺序
            inOrder(tNode->leftChild);
            cout << tNode->data << " ";
            inOrder(tNode->rightChild);
        }
    }

    //插入元素
    void InsertElem(const T &e)  //不可以指定插入位置，程序内部会自动确定插入位置
    {
        InsertElem(root, e);
    }

    void InsertElem(BinaryTreeNode<T> *&tNode, const T &e) //注意第一个参数类型
    {
        if (tNode == nullptr) //空树
        {
            tNode = new BinaryTreeNode<T>;
            tNode->data = e;
            tNode->leftChild = nullptr;
            tNode->rightChild = nullptr;
            return;
        }

        if (e > tNode->data) {
            InsertElem(tNode->rightChild, e);
        } else if (e < tNode->data) {
            InsertElem(tNode->leftChild, e);
        } else {
            //要插入的数据与当前树中某节点数据相同，则不允许插入
            //什么也不做
        }
        return;
    }

    //查找某个节点
    BinaryTreeNode<T> *SearchElem(const T &e) {
        return SearchElem(root, e);
    }

    BinaryTreeNode<T> *SearchElem(BinaryTreeNode<T> *tNode, const T &e) {
        if (tNode == nullptr)
            return nullptr;

        /*
        if (tNode->data == e)
            return tNode;

        if (e < tNode->data)
            return SearchElem(tNode->leftChild,e); //在左子树上做查找
        else
            return SearchElem(tNode->rightChild,e); //在右子树上左查找
        */
        BinaryTreeNode<T> *tmpnode = tNode;
        while (tmpnode) {
            if (tmpnode->data == e)
                return tmpnode;
            if (tmpnode->data > e)
                tmpnode = tmpnode->leftChild;
            else
                tmpnode = tmpnode->rightChild;
        }
        return nullptr;
    }

    //删除某个节点
    void DeleteElem(const T &e) {
        return DeleteElem(root, e);
    }
    //void DeleteElem(BinaryTreeNode<T>*& tNode, const T& e)  //注意第一个参数类型
    //{
    //	if (tNode == nullptr)
    //		return;

    //	if (e > tNode->data)
    //	{
    //		DeleteElem(tNode->rightChild, e);
    //	}
    //	else if (e < tNode->data)
    //	{
    //		DeleteElem(tNode->leftChild, e);
    //	}
    //	else
    //	{
    //		//找到了节点，执行删除操作：
    //		if (tNode->leftChild == nullptr && tNode->rightChild == nullptr) //要删除的节点左子树和右子树都为空（叶节点）
    //		{
    //			//即将被删除节点的左孩子和右孩子都为空
    //			BinaryTreeNode<T>* tmpnode = tNode;
    //			tNode = nullptr; //这实际上就是让指向该节点的父节点指向空
    //			delete tmpnode;
    //		}
    //		else if (tNode->leftChild == nullptr) //其实这个else if代码可以和上个if代码合并，这里为了看的更清晰就不合并了
    //		{
    //			//即将被删除节点的左孩子为空（但右孩子不为空）
    //			BinaryTreeNode<T>* tmpnode = tNode;
    //			tNode = tNode->rightChild;
    //			delete tmpnode;
    //		}
    //		else if (tNode->rightChild == nullptr)
    //		{
    //			//即将被删除节点的右孩子为空（但左孩子不为空）
    //			BinaryTreeNode<T>* tmpnode = tNode;
    //			tNode = tNode->leftChild;
    //			delete tmpnode;
    //		}
    //		else
    //		{
    //			// 即将被删除节点的左右孩子都不为空
    //			//(1)找到这个要删除节点的左子树的最右下节点
    //			BinaryTreeNode<T>* tmpparentnode = tNode;  //tmpparentnode代表要删除节点的父节点
    //			BinaryTreeNode<T>* tmpnode = tNode->leftChild; //保存要删除节点左子树的最右下节点
    //			while (tmpnode->rightChild)
    //			{
    //				tmpparentnode = tmpnode;
    //				tmpnode = tmpnode->rightChild;
    //			} //end while
    //			tNode->data = tmpnode->data;

    //			//此时，tmpnode指向要删除节点左子树的最右下节点（也就是真正要删除的节点），tmpparentnode指向真正要删除的节点的父节点。
    //			//(2)删除tmpnode所指向的节点（该节点是真正要删除的节点）
    //			if (tmpparentnode == tNode)
    //			{
    //				//此条件成立，表示上面while循环一次都没执行，也就是意味着要删除节点左子树没有右孩子（但可能有左孩子）
    //				tNode->leftChild = tmpnode->leftChild;    //让要删除节点的左孩子  指向  真正要删除节点的左孩子的左孩子
    //			}
    //			else
    //			{
    //				//此条件成立，表示上面while循环至少执行一次，这意味着要删除节点的左子树有1到多个右孩子，但这个右孩子不可能再有右孩子【因为tmpnode指向的是最后一个右孩子】（最多只能有左孩子）
    //				tmpparentnode->rightChild = tmpnode->leftChild; //tmpnode不可能有右孩子，最多只可能有左孩子
    //			}
    //			//(3)把最右下节点删除
    //			delete tmpnode;
    //		} //end if
    //	}
    //}

    void DeleteElem(BinaryTreeNode<T> *&tNode, const T &e)  //注意第一个参数类型
    {
        if (tNode == nullptr)
            return;

        if (e > tNode->data) {
            DeleteElem(tNode->rightChild, e);
        } else if (e < tNode->data) {
            DeleteElem(tNode->leftChild, e);
        } else {
            //找到了节点，执行删除操作：
            if (tNode->leftChild != nullptr && tNode->rightChild != nullptr) {
                BinaryTreeNode<T> *tmpnode = tNode->leftChild; //保存要删除节点左子树的最右下节点
                while (tmpnode->rightChild) {
                    tmpnode = tmpnode->rightChild;
                } //end while
                tNode->data = tmpnode->data;
                DeleteElem(tNode->leftChild, tmpnode->data); //递归调用，因为上述是要删除节点左子树（下的最右节点），所以这里第一个参数是leftChild
            } else {
                BinaryTreeNode<T> *tmpnode = tNode;
                if (tNode->leftChild == nullptr)
                    tNode = tNode->rightChild;
                else
                    tNode = tNode->leftChild;
                delete tmpnode;
            }
        }
    }

    //查找值最大节点
    BinaryTreeNode<T> *SearchMaxValuePoint() {
        return SearchMaxValuePoint(root);
    }

    BinaryTreeNode<T> *SearchMaxValuePoint(BinaryTreeNode<T> *tNode) {
        if (tNode == nullptr) //空树
            return nullptr;

        //从根节点开始往右侧找即可
        BinaryTreeNode<T> *tmpnode = tNode;
        while (tmpnode->rightChild != nullptr)
            tmpnode = tmpnode->rightChild;
        return tmpnode;
    }

    //查找值最小节点
    BinaryTreeNode<T> *SearchMinValuePoint() {
        return SearchMinValuePoint(root);
    }

    BinaryTreeNode<T> *SearchMinValuePoint(BinaryTreeNode<T> *tNode) {
        if (tNode == nullptr) //空树
            return nullptr;

        //从根节点开始往左侧找即可
        BinaryTreeNode<T> *tmpnode = tNode;
        while (tmpnode->leftChild != nullptr)
            tmpnode = tmpnode->leftChild;
        return tmpnode;
    }

    //找按中序遍历的二叉查找树中当前节点的前趋节点
    BinaryTreeNode<T> *GetPriorPoint_IO(BinaryTreeNode<T> *findnode) {
        if (findnode == nullptr)
            return nullptr;
        /*
        //以下代码后来考虑了一下，没必要存在
        //(1)所以如果当前结点有左孩子, 那么找左子树中值最大的节点
        if (findnode->leftChild != nullptr)
            return SearchMaxValuePoint(findnode->leftChild);
        */

        BinaryTreeNode<T> *prevnode = nullptr;
        BinaryTreeNode<T> *currnode = root;  //当前节点，从根开始找
        while (currnode != nullptr) {
            if (currnode->data < findnode->data) //当前节点小
            {
                //(1)从一系列比当前要找的值小的节点中找一个值最大的当前趋节点
                //当前节点值比要找的  节点值小，所以当前节点认为有可能是前趋
                if (prevnode == nullptr) {
                    //如果前趋节点还为空，那不防把当前节点认为就是前趋
                    prevnode = currnode;
                } else //prevnode不为空
                {

                    //既然是找前趋，那自然是找到比要找的值小的 一系列节点中 值最大的
                    if (prevnode->data < currnode->data) {
                        prevnode = currnode; //前趋自然是找一堆 比当前值小的 值中 最大的一个。
                    }
                }
                //(2)继续逼近要找的节点，一直到找到要找的节点，找到要找的节点后，要找的节点的左节点仍旧可能是前趋
                currnode = currnode->rightChild;  //当前节点小，所以往当前节点的右子树转
            } else if (currnode->data > findnode->data) //当前节点值比要找的值大，所以当前节点肯定不会是要找的值的前趋
            {
                //当前节点大，所以往当前节点的左子树转
                currnode = currnode->leftChild;
            } else //(currnode->data == findnode->data) ，这个else其实可以和上个else合并，但为了清晰，就不合并了
            {
                //当前节点值  就是要找的节点值，那么 前趋也可能在当前节点的左子树中，所以往左子树转继续找看有没有更合适的前趋
                currnode = currnode->leftChild;
            }
        } //end while

        return prevnode;
    }

    //找按中序遍历的二叉查找树中当前节点的后继节点
    BinaryTreeNode<T> *GetNextPoint_IO(BinaryTreeNode<T> *findnode) {
        if (findnode == nullptr)
            return nullptr;

        BinaryTreeNode<T> *nextnode = nullptr;
        BinaryTreeNode<T> *currnode = root;  //当前节点，从根开始找
        while (currnode != nullptr) {
            if (currnode->data > findnode->data) //当前节点大
            {
                //(1)从一系列比当前要找的值大的节点中找一个值最小的当后继节点
                //当前节点值比要找的  节点值大，所以当前节点认为有可能是后继
                if (nextnode == nullptr) {
                    //如果后继节点还为空，那不防把当前节点认为就是后继
                    nextnode = currnode;
                } else //nextnode不为空
                {
                    //既然是找后继，那自然是找到比要找的值大的 一系列节点中 值最小的
                    if (nextnode->data > currnode->data) {
                        nextnode = currnode; //后继自然是找一堆 比当前值大的 值中 最小的一个。
                    }
                }
                //(2)继续逼近要找的节点，一直到找到要找的节点，找到要找的节点后，要找的节点的右节点仍旧可能是后继
                currnode = currnode->leftChild;  //当前节点大，所以往当前节点的左子树转
            } else if (currnode->data < findnode->data) //当前节点值比要找的值小，所以当前节点肯定不会是要找的值的后继
            {
                //当前节点小，所以往当前节点的右子树转
                currnode = currnode->rightChild;
            } else //(currnode->data == findnode->data)
            {
                //当前节点值  就是要找的节点值，那么 后继也可能在当前节点的右子树中，所以往右子树转继续找看有没有更合适的后继
                currnode = currnode->rightChild;
            }
        } //end while
        return nextnode;
    }

private:
    void ReleaseNode(BinaryTreeNode<T> *pnode) {
        if (pnode != nullptr) {
            ReleaseNode(pnode->leftChild);
            ReleaseNode(pnode->rightChild);
        }
        delete pnode;
    }

private:
    BinaryTreeNode<T> *root; //树根指针
};
