//
// Created by lhc456 on 2023/4/18.
//
// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <cassert>

#pragma warning (disable: 4996)
using namespace std;

namespace _NM1 {
    //双亲表示法
    template<typename T>//T代表数据元素的类型
    struct TreeNode {
        T data;     //数据域
        int parent;  //指针域，父节点在数组中的下标
    };

#define MaxTreeSize 200 //树中能够保存的最大节点个数

    //树的定义
    template<typename T>
    class Tree {
    public:
        Tree() //构造函数
        {
            for (int i = 0; i < MaxTreeSize; ++i) {
                m_data[i].parent = -1;  //-1表示目前还没有父亲，类似于空指针的作用
            }
            m_length = 0;
        }

    private:
        TreeNode<T> m_data[MaxTreeSize];  //节点数组
        int m_length; //树中包含的节点数量
    };
}

//-----------------
namespace _NM2 {
    //孩子表示法方案一作为树存储结构时，树的节点结构定义
    template<typename T, int treedeg>//T代表数据元素的类型,treedeg代表树的度
    struct TreeNode {
        T data;     //数据域
        TreeNode *child[treedeg];  //指针数组，其中的每个指针指向一个孩子节点
    };
}
//-----------------
namespace _NM3 {
    //孩子表示法 方案二作为树存储结构时，树的节点结构定义
    template<typename T>//T代表数据元素的类型
    struct TreeNode {
        T data;     //数据域
        int degree; //度域，存放该节点的度
        TreeNode **child; //指针的指针

    public:
        TreeNode(int tmpdegree) //构造函数
        {
            degree = tmpdegree;
            child = new TreeNode *[degree]; //相当于定义了degree个指向TreeNode对象的指针
            for (int i = 0; i < degree; ++i)
                child[i] = nullptr;
        }

        ~TreeNode()  //析构函数
        {
            delete[]child;
        }
    };
}

//-----------------
namespace _NM4 {
    //孩子节点结构：一个保存孩子下标的结构
    struct ChildNode {
        int child;//孩子下标
        ChildNode *next; //指向下个相同的结构
    };

    ////表头（父亲）节点结构
    //template <typename T>//T代表数据元素的类型
    //struct TreeNode
    //{
    //	T data; //数据域
    //	ChildNode* firstchild; //通过该指针可以找到该节点的第一个孩子
    //};
    //
    //表头（父亲）节点结构
    template<typename T>//T代表数据元素的类型
    struct TreeNode {
        T data; //数据域
        int parent; //父节点所在Tree结构中的m_data数组下标
        ChildNode *firstchild; //通过该指针可以找到该节点的第一个孩子
    };


#define MaxTreeSize 200 //树中能够保存的最大节点个数

    template<typename T> //T代表数据元素的类型
    class Tree {
    private:
        TreeNode<T> m_data[MaxTreeSize];  //节点数组
        int m_length; //树中包含的节点数量
    };
}

//-----------------
namespace _NM5 {
    //孩子兄弟表示法作为树存储结构时，树的节点结构定义
    template<typename T> //T代表数据元素的类型
    struct TreeNode {
        T data;     //数据域
        TreeNode *firstchild;//指针域，指向第一个孩子节点
        TreeNode *rightbro; //指针域，指向右兄弟节点
    };
}

int main() {


    return 0;
}

