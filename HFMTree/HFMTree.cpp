//
// Created by lhc456 on 2023/4/16.

#include <iostream>
#include <cassert>

#pragma warning (disable: 4996)
using namespace std;

//哈夫曼树的节点
struct HFMTreeNode {
    int weight; //权值
    int parent; //父亲（数组下标值）
    int lchild; //左孩子（数组下标值）
    int rchild; //右孩子（数组下标值）
};

//哈夫曼树：用一个数组来保存哈夫曼树
class HFMTree {
public:
    HFMTree(int nodecount, int *pweight)  //构造函数
    //参数nodecount代表要创建的哈夫曼树的叶子节点的数量
    //pWeight代表叶子节点的权重数组
    {
        m_length = nodecount;
        int iMaxNodeCount = 2 * m_length - 1;
        m_data = new HFMTreeNode[iMaxNodeCount];  //哈夫曼树的节点总数是2n-1（n代表哈夫曼树的叶子节点数量）

        for (int i = 0; i < iMaxNodeCount; ++i) {
            m_data[i].parent = -1;  //-1标记未被使用
            m_data[i].lchild = -1;
            m_data[i].rchild = -1;
        }
        for (int i = 0; i < m_length; ++i) {
            m_data[i].weight = pweight[i];
        }
    }

    ~HFMTree() //析构函数
    {
        delete[] m_data;
    }

public:
    //真正的开始创建哈夫曼树
    void CreateHFMTree() {
        int idx1 = 0;
        int idx2 = 0;

        int iMaxNodeCount = 2 * m_length - 1; //2n-1是整个哈夫曼树的节点数量
        int initlength = m_length;
        for (int i = initlength; i < iMaxNodeCount; ++i) {
            SelectTwoMinValue(idx1, idx2);
            m_data[i].weight = m_data[idx1].weight + m_data[idx2].weight; //新节点的权值等于左右孩子
            m_data[i].lchild = idx1;
            m_data[i].rchild = idx2;

            m_data[idx1].parent = i;
            m_data[idx2].parent = i;

            m_length++; //SelectTwoMinValue()函数要用到该值
        } //end for i
        return;
    }

    //前序遍历二叉树(根左右)
    void preOrder(int idx) {
        if (idx != -1) {
            cout << m_data[idx].weight << " ";
            preOrder(m_data[idx].lchild);
            preOrder(m_data[idx].rchild);
        }
    }

    //获取树中节点数量
    int GetLength() {
        return m_length;
    }

    //生成哈夫曼编码
    bool CreateHFMCode(int idx) //参数idx是用于保存哈夫曼树的数组某个节点的下标
    {
        //调用这个函数时，m_length应该已经等于整个哈夫曼树的节点数量，那么哈夫曼树的叶子节点数量应该这样求
        int leafNodeCount = (m_length + 1) / 2;

        if (idx < 0 || idx >= leafNodeCount) {
            //只允许对叶子节点求其哈夫曼编码
            return false;
        }
        string result = ""; //保存最终生成的哈夫曼编码
        int curridx = idx;
        int tmpparent = m_data[curridx].parent;
        while (tmpparent != -1) //沿着叶子向上回溯
        {
            if (m_data[tmpparent].lchild == curridx) {
                //前插0
                result = "0" + result;
            } else {
                //前插1
                result = "1" + result;
            }
            curridx = tmpparent;
            tmpparent = m_data[curridx].parent;
        } //end while
        cout << "下标为【" << idx << "】，权值为" << m_data[idx].weight << "的节点的哈夫曼编码是" << result << endl;
        return true;
    }


private:
    //选择两个根权重最小的节点，通过引用返回这个节点所在的下标
    void SelectTwoMinValue(int &rtnIdx1, int &rtnIdx2) {
        int minval1 = INT_MAX;
        int minval2 = INT_MAX;

        //找最小值
        for (int i = 0; i < m_length; ++i) {
            if (m_data[i].parent == -1) //父标记未被使用
            {
                if (minval1 > m_data[i].weight) {
                    minval1 = m_data[i].weight; //记录最小值
                    rtnIdx1 = i; //记录下标
                }
            }
        } //end for i

        //找第二个最小的值
        for (int i = 0; i < m_length; ++i) {
            if (m_data[i].parent == -1 && i != rtnIdx1) //注意&&后的条件，目的是把第一个找到的最小权值的节点排除
            {
                if (minval2 > m_data[i].weight) {
                    minval2 = m_data[i].weight; //记录最小值
                    rtnIdx2 = i; //记录下标
                }
            }
        } //end for i
        return;
    }

private:
    HFMTreeNode *m_data;
    int m_length;  //记录当前树有多少个节点【数组中多少个节点被使用了】
};

//--------------------------------
int main() {

    //int weighLst[] = { 1,2,2,4,8 }; //权值列表（数组），数组中的数据顺序无所谓
    //HFMTree hfmtobj(
    //	sizeof(weighLst) / sizeof(weighLst[0]),   //权值列表中元素个数
    //	weighLst                            //权值列表首地址
    //);

    //hfmtobj.CreateHFMTree(); //创建哈夫曼树
    //hfmtobj.preOrder(hfmtobj.GetLength() - 1); //遍历哈夫曼树，参数其实就是根节点的下标（数组最后一个有效位置的下标）

    int weighLst[] = {12, 15, 9, 24, 8, 32};
    HFMTree hfmtobj(
            sizeof(weighLst) / sizeof(weighLst[0]),   //权值列表中元素个数
            weighLst                                  //权值列表首地址
    );

    hfmtobj.CreateHFMTree(); //创建哈夫曼树
    hfmtobj.preOrder(hfmtobj.GetLength() - 1); //遍历哈夫曼树，参数其实就是根节点的下标（数组最后一个有效位置的下标）

    //求哈夫曼编码
    cout << "--------------" << endl;
    for (int i = 0; i < sizeof(weighLst) / sizeof(weighLst[0]); ++i)
        hfmtobj.CreateHFMCode(i);

    return 0;
}



