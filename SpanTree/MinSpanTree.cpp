//
// Created by lhc456 on 2023/4/20.
//
// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <cassert>

#pragma warning (disable: 4996)
using namespace std;


//------------------------------
namespace _nmsp1 {
#define MaxVertices_size 100 //最大顶点数大小
#define INT_MAX_MY       2147483647 //整型能够保存的最大数值，用以表示两个顶点之间不存在边

    template<typename T>  //T代表顶点类型
    class GraphMatrix     //邻接矩阵代表的图
    {
    public:
        GraphMatrix() //构造函数，空间复杂度O(n)+O(n^2)=O(n^2)
        {
            m_numVertices = 0;
            m_numEdges = 0;

            pm_VecticesList = new T[MaxVertices_size];

            pm_Edges = new int *[MaxVertices_size];
            for (int i = 0; i < MaxVertices_size; ++i) {
                pm_Edges[i] = new int[MaxVertices_size];
            } //end for

            for (int i = 0; i < MaxVertices_size; ++i) {
                for (int j = 0; j < MaxVertices_size; ++j) {
                    if (i == j) {
                        //顶点自己到自己对应的边的权值应该用0标记
                        pm_Edges[i][j] = 0;

                    } else {
                        pm_Edges[i][j] = INT_MAX_MY; //开始时矩阵中不记录边信息，即边与边之间的权值信息给成最大值INT_MAX_MY
                    }
                }
            }
        }

        ~GraphMatrix() //析构函数
        {
            delete[] pm_VecticesList;

            for (int i = 0; i < MaxVertices_size; ++i) {
                delete[] pm_Edges[i];
            } //end for
            delete[] pm_Edges;
        }

    public:
        //插入顶点
        bool InsertVertex(const T &tmpv) {
            if (m_numVertices >= MaxVertices_size) //顶点空间已满
            {
                cout << "顶点空间已满" << endl;
                return false;
            }

            if (GetVertexIdx(tmpv) != -1) //该顶点已经存在
            {
                cout << "顶点 " << tmpv << " 已经存在!" << endl;
                return false;
            }

            pm_VecticesList[m_numVertices] = tmpv;
            m_numVertices++;
            return true;
        }

        //插入边
        bool
        InsertEdge(const T &tmpv1, const T &tmpv2, int weight) //在tmpv1和tmpv2两个顶点之间插入一条边，注意权值也要插入进来。weight代表边与边之间的权值
        {
            int idx1 = GetVertexIdx(tmpv1);
            int idx2 = GetVertexIdx(tmpv2);
            if (idx1 == -1 || idx2 == -1)//某个顶点不存在，不可以插入边
                return false;

            if (pm_Edges[idx1][idx2] != INT_MAX_MY)//边重复
                return false;

            pm_Edges[idx1][idx2] = pm_Edges[idx2][idx1] = weight; //无向图是个对称矩阵。tmpv1到tmpv2之间插入边就等于tmpv2到tmpv1之间插入了边
            m_numEdges++; //边数量增加1
            return true;
        }

        ////删除边
        //bool DeleteEdge(const T& tmpv1, const T& tmpv2) //删除两个顶点之间的边
        //{
        //	int idx1 = GetVertexIdx(tmpv1);
        //	int idx2 = GetVertexIdx(tmpv2);
        //	if (idx1 == -1 || idx2 == -1)
        //		return false;

        //	if (pm_Edges[idx1][idx2] == 0)//没边不能删除
        //		return false;

        //	pm_Edges[idx1][idx2] = pm_Edges[idx2][idx1] = 0;
        //	m_numEdges--; //边数量减少1
        //	return true;
        //}

        ////删除顶点，涉及到顶点对应的边也要删除
        //bool DeleteVertex(const T& tmpv)
        //{
        //	int idx = GetVertexIdx(tmpv);
        //	if (idx == -1) //顶点不存在
        //		return false;

        //	int deledges = 0; //要删除的边数统计（顶点被删除，相关的边则肯定也不存在了）
        //	//统计矩阵中该顶点对应的边数
        //	for (int i = 0; i < m_numVertices; ++i)
        //	{
        //		if (pm_Edges[idx][i] != 0)
        //		{
        //			deledges++;
        //		}
        //	}

        //	//该顶点在矩阵中所在行和列都要删除
        //	//(1)下面的行先覆盖上面的行
        //	for (int i = idx; i < (m_numVertices - 1); ++i) //行数
        //	{
        //		for (int j = 0; j < m_numVertices; ++j) //列数
        //		{
        //			pm_Edges[i][j] = pm_Edges[i + 1][j];
        //		}
        //	}
        //	//(2)右面的列再覆盖左面的列
        //	for (int i = 0; i < (m_numVertices - 1); ++i) //行数，因为上面的处理，行数已经少了1了
        //	{
        //		for (int j = idx; j < (m_numVertices - 1); ++j) //列数
        //		{
        //			pm_Edges[i][j] = pm_Edges[i][j + 1];
        //		}
        //	}

        //	//从顶点列表里把顶点删除，注意观察的顺序还是要保持的，比如观察顺序是A,B,C,D,E,F，如果删除了C，则观察顺序应该保持为A,B,D,E,F
        //	for (int i = idx; i < (m_numVertices - 1); ++i)
        //	{
        //		pm_VecticesList[i] = pm_VecticesList[i + 1];
        //	}

        //	m_numVertices--; //顶点数减少
        //	m_numEdges -= deledges;//边数减少
        //	return true;
        //}

        void DispGraph() //显示图信息，其实就是显示矩阵信息
        {
            cout << "   ";  //为了凑一些对齐关系，所以先输出三个空格
            //输出图中的顶点，其实就是矩阵的最顶上一行的顶点名信息
            for (int i = 0; i < m_numVertices; ++i) {
                printf("%5c", pm_VecticesList[i]);  //5：不够5位的右对齐
            }
            cout << endl; //换行
            //输出对应的邻接矩阵
            for (int i = 0; i < m_numVertices; ++i) //注意循环结束条件是真实的顶点个数
            {
                //输出矩阵左侧的顶点名
                cout << pm_VecticesList[i] << "  ";
                for (int j = 0; j < m_numVertices; ++j) {
                    if (pm_Edges[i][j] == INT_MAX_MY) {
                        printf("%5s", "∞");  //两个顶点之间没有边
                    } else {
                        printf("%5d", pm_Edges[i][j]);
                    }
                } //end for j
                cout << endl; //换行
            } //end for i
            cout << endl; //换行
        }

        //判断某个idx值是否位于最小生成树顶点下标数组中
        bool IfInMstVertIdxArray(int curridx, int *p_inMstVertIdxArray, int in_MstVertCount) {
            for (int i = 0; i < in_MstVertCount; ++i) {
                if (p_inMstVertIdxArray[i] == curridx) //这个idx位于最小生成树顶点下标数组中
                    return true;

            } //end for
            return false; //这个idx不在最小生成树顶点下标数组中
        }

        //用 普里姆（Prim）算法创建最小生成树
        bool CreateMinSpanTree_Prim(const T &tmpv)  //tmpv作为创建最小生成树时的起始顶点
        {
            int idx = GetVertexIdx(tmpv);
            if (idx == -1) //顶点不存在
                return false;

            int in_MstVertCount = 1;  //已经增加到生成树中的顶点数量，刚开始肯定是要把起始顶点放进去所以这里给1
            int *p_inMstVertIdxArray = new int[m_numVertices]; //已经增加到生成树【最小生成树】中的顶点的下标会保存到该数组中

            p_inMstVertIdxArray[0] = idx; //起始顶点下标
            int minWeight = INT_MAX_MY;  //用来记录当前的最小权值，先给成最大值
            int minTmpStartVertIdx = -1; //临时存放一个开始顶点的下标值（一个边的开始顶点）
            int minTmpEndVertIdx = -1;   //临时存放一个目标顶点的下标值（一个边的末端顶点）

            while (true) {
                if (in_MstVertCount == m_numVertices) //生成树中的顶点数量等于了整个图的顶点数量，最小生成树创建完毕
                    break;

                minWeight = INT_MAX_MY; //权值先给成最大值

                for (int iv = 0; iv < in_MstVertCount; ++iv) //遍历所有生成树中已有的顶点，从其中找到以该顶点开始的边中权值最小的边所对应的目标顶点
                {
                    int tmpidx = p_inMstVertIdxArray[iv]; //拿到该位置的信息【顶点索引】
                    for (int i = 0; i < m_numVertices; ++i) //遍历所有顶点以找到所有以tmpidx顶点为起点的边
                    {
                        if (pm_Edges[tmpidx][i] != 0 && pm_Edges[tmpidx][i] !=
                                                        INT_MAX_MY) //当前顶点与目标顶点不是同一个顶点（否则权值==0）并且与目标顶点之间有连线（否则权值 == INT_MAX_MY)
                        {
                            //在以iv顶点为起点的所有边中找权值最小的边
                            //权值最小的边所目标顶点不在最小生成树顶点下标数组中，说明是个新顶点
                            if (pm_Edges[tmpidx][i] < minWeight &&
                                IfInMstVertIdxArray(i, p_inMstVertIdxArray, in_MstVertCount) == false) {
                                minWeight = pm_Edges[tmpidx][i];
                                minTmpStartVertIdx = tmpidx; //记录边对应的开始顶点下标
                                minTmpEndVertIdx = i;    //记录边对应的目标顶点下标
                            }
                        }
                    } //end for i
                }//end for iv

                //走到这里，肯定找到了个新顶点，输出最小生成树的边信息
                cout << pm_VecticesList[minTmpStartVertIdx] << "--->" << pm_VecticesList[minTmpEndVertIdx] << " : 权值="
                     << minWeight << endl;
                p_inMstVertIdxArray[in_MstVertCount] = minTmpEndVertIdx;  //将新顶点增加到最小生成树的下标数组中
                in_MstVertCount++;
            } //end while

            //内存释放
            delete[] p_inMstVertIdxArray;
            return true;
        }

        //用 普里姆（Prim）算法创建最小生成树 的第二种方法
        bool CreateMinSpanTree_Prim2(const T &tmpv)  //tmpv作为创建最小生成树时的起始顶点
        {
            int idx = GetVertexIdx(tmpv);
            if (idx == -1) //顶点不存在
                return false;

            int lowcost[MaxVertices_size];    //保存权值的数组，采用new动态分配也可以
            int veridx[MaxVertices_size];      //保存顶点下标的数组，采用new动态分配也可以
            for (int i = 0; i < m_numVertices; ++i) {
                lowcost[i] = pm_Edges[idx][i];   //保存开始顶点的权值信息
                veridx[i] = idx;                 //保持开始顶点的下标信息
            } //end for

            int minTmpStartVertIdx = -1;
            int minTmpEndVertIdx = -1;
            for (int i = 0; i < m_numVertices - 1; ++i) //循环“顶点数-1”次即可创建出最小生成树
            {
                //在lowcost数组中找权值最小的顶点
                int minWeight = INT_MAX_MY;
                for (int w = 0; w < m_numVertices; ++w) //遍历lowcost数组，找到其中权值最小的
                {
                    if (lowcost[w] != 0 && minWeight > lowcost[w]) {
                        minWeight = lowcost[w];
                        minTmpEndVertIdx = w;
                    }
                } //end for w
                minTmpStartVertIdx = veridx[minTmpEndVertIdx];
                cout << pm_VecticesList[minTmpStartVertIdx] << "--->" << pm_VecticesList[minTmpEndVertIdx] << " : 权值="
                     << minWeight << endl; //显示边和权值信息
                lowcost[minTmpEndVertIdx] = 0; //权值设置为0表示该顶点被放入了最小生成树中

                //通过最新寻找到的顶点来修改lowcost数组和veridx数组中的内容
                for (int v = 0; v < m_numVertices; ++v) {
                    if (lowcost[v] > pm_Edges[minTmpEndVertIdx][v]) {
                        lowcost[v] = pm_Edges[minTmpEndVertIdx][v];
                        veridx[v] = minTmpEndVertIdx;
                    }
                } //end for v

            }//end for i
            return true;
        }

    private:
        //获取顶点下标
        int GetVertexIdx(const T &tmpv) {
            for (int i = 0; i < m_numVertices; ++i) {
                if (pm_VecticesList[i] == tmpv)
                    return i;
            }
            return -1; //不存在的顶点
        }

    private:
        int m_numVertices;   //当前顶点数量
        int m_numEdges;      //边数量
        T *pm_VecticesList;  //顶点列表
        int **pm_Edges;      //边信息，二维数组
    };

}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);//程序退出时检测内存泄漏并显示到“输出”窗口

    _nmsp1::GraphMatrix<char> gm;

    //向图中插入顶点
    gm.InsertVertex('A');
    gm.InsertVertex('B');
    gm.InsertVertex('C');
    gm.InsertVertex('D');
    gm.InsertVertex('E');
    gm.InsertVertex('F');
    //向图中插入边
    gm.InsertEdge('A', 'B', 100); //100代表边的权值
    gm.InsertEdge('A', 'C', 15);
    gm.InsertEdge('A', 'D', 20);
    gm.InsertEdge('B', 'C', 40);
    gm.InsertEdge('B', 'E', 65);
    gm.InsertEdge('C', 'D', 25);
    gm.InsertEdge('C', 'E', 70);
    gm.InsertEdge('C', 'F', 80);
    gm.InsertEdge('D', 'F', 30);
    gm.InsertEdge('E', 'F', 40);
    gm.DispGraph();

    ////删除图中的边
    //gm.DeleteEdge('A', 'D');
    //gm.DispGraph();
    ////删除图中的顶点
    //gm.DeleteVertex('C');
    //gm.DispGraph();

    gm.CreateMinSpanTree_Prim('A');
    cout << "---------------------" << endl;
    gm.CreateMinSpanTree_Prim2('E');

    return 0;
}
