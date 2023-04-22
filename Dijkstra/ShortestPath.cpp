//
// Created by lhc456 on 2023/4/20.
//
// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include  <assert.h>
#include <stack>

using namespace std;
#pragma warning(disable : 4996)

//------------------------------
namespace _nmsp1 {
#define MaxVertices_size 100 //最大顶点数大小
#define INT_MAX_MY       2147483647 //整型能够保存的最大数值，用以表示两个顶点之间不存在边

    ////边结构
    //struct Edge
    //{
    //	int idx_startVert;  //边所对应的开始顶点下标索引
    //	int idx_endVert;    //边所对应的结束顶点下标索引
    //	int weight;         //边的权值
    //};

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

            //pm_Edges[idx1][idx2] = pm_Edges[idx2][idx1] = weight; //无向图
            pm_Edges[idx1][idx2] = weight; //有向图
            m_numEdges++; //边数量增加1
            return true;
        }

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

        //迪杰斯特拉（Dijkstra）算法 求最短路径
        bool ShortestPath_Dijkstra(const T &tmpv) //tmpv:源顶点（起始/源顶点/开始顶点）
        {
            int idx = GetVertexIdx(tmpv);
            if (idx == -1) //顶点不存在
                return false;

            bool *pS = new bool[m_numVertices]; //创建集合S用于保存已经处理过的顶点信息（标记各顶点是否已经找到最短路径）
            int *pdist = new int[m_numVertices];//存放当前起始点到其他各个顶点的距离（最短路径/权值之和），开始时只需要把邻接矩阵中该点所在行的数据存入其中，比如如果从顶点A开始，那么存入的数据是“0   22   ∞    6   ∞   ∞”

            int *ppath = new int[m_numVertices]; //记录每个顶点在最短路径上的前趋节点。其内容需要根据pdist中内容来得出：
            //pdist中对应下标位置是∞,则ppath对应位置是-1
            //pdist中对应下标位置有权值，则ppath对应位置是起始点的下标

//初始化
            for (int i = 0; i < m_numVertices; ++i) {
                pS[i] = false;  //表示所有顶点都没有加入到集合S中
                pdist[i] = pm_Edges[idx][i]; //保存起始顶点到其他顶点的权值
                if (i == idx || pdist[i] == INT_MAX_MY) {
                    ppath[i] = -1;
                } else {
                    ppath[i] = idx;
                }
            }
            pS[idx] = true; //表示下标为idx的顶点加入到了集合S中，也就是先把起始点加入到集合S中。
            //执行完上述初始化后：pS = {true,false,false,false,false,false} ,   pdist = {0,22,∞,6,∞,∞} ,  ppath = {-1,0，-1,0,-1,-1};

            int minpathweight = INT_MAX_MY; //保存最小路径权值
            int minidx = -1;

            for (int i = 0; i < m_numVertices -
                                1; ++i) //因为每次循环都会向集合S加入一个顶点，S中原来 已经有一个顶点了，所以只需要再循环m_numVertices-1次，把所有顶点加入到S中，迪杰斯特拉就执行完毕
            {
                //现在：从起始顶点到其他所有顶点的路径中，选择一条最短路径保存在minpath中
                minpathweight = INT_MAX_MY;
                for (int j = 0; j < m_numVertices; ++j) //本循环找pdist中权值最小的
                {
                    if (
                            pS[j] == false &&    //不在S集合中的顶点
                            pdist[j] < minpathweight) {
                        minpathweight = pdist[j]; //记录最小路径权值
                        minidx = j; //下标记录下来
                    }
                }//end j

                //找到了最短路径，该路径对应的终点（顶点）下标保存在minidx中，将其放入到S集合中。
                pS[minidx] = true;      //根据演示图内容，第一次minidx = 3;代表顶点D

                //m的第一次循环分析如下：
                //现在要看一看再加入了顶点D之后 开始顶点【经过顶点D】到其他顶点是不是有更短的路径【也就是看如何更新pdist】，已知
                //（1）顶点D到其他顶点的权值是：{∞，10，20，0，∞，∞}
                //（2）                  此时pdist = {0,22,∞,6,∞,∞}, ppath = {-1, 0， -1, 0, -1, -1};
                //（3）下面的dest循环执行后，pdist = {0,16,26,6,∞,∞}, ppath = {-1, 3， 3,  0, -1, -1};
                for (int dest = 0; dest < m_numVertices; ++dest) {
                    if (
                            pS[dest] == false &&    //到达的目标顶点是不可以包含在集合S中的
                            (pm_Edges[minidx][dest] != 0 &&
                             pm_Edges[minidx][dest] != INT_MAX_MY)   //顶点D到其他顶点（B、C）都有路径而且B、C这两个顶点目前不包含在S中
                            ) {
                        //A到D的权值  + D到其他点的权值
                        if (minpathweight + pm_Edges[minidx][dest] <
                            pdist[dest]) //A到D的权值+ D到B的权值如果要是比原来的A到B的权值小，则更新A到B的权值为最小的
                        {
                            pdist[dest] = minpathweight + pm_Edges[minidx][dest];
                            ppath[dest] = minidx;
                        }
                    }
                } //end for dest
            } //end i

            //显示最短路径信息
            cout << "从源顶点" << pm_VecticesList[idx] << "到其他各顶点的最短路径信息如下(不显示的表示没路径)：" << endl;
            //源顶点下标是idx
            for (int destveridx = 0; destveridx < m_numVertices; ++destveridx) {
                if (idx == destveridx)
                    continue;

                //源顶点和目标顶点不同，则显示源顶点到目标顶点的最短路径
                int weight = pdist[destveridx];  //源顶点到目标顶点的最短路径长度
                if (weight == INT_MAX_MY) //两个顶点之间没有路径
                    continue;

                cout << pm_VecticesList[idx] << "--->" << pm_VecticesList[destveridx] << "：" << "最短路径长度("
                     << weight << ")，最短路径：";

                //借用个标准库中的堆栈保存数据
                std::stack<int> tempstack; //#include <stack>
                tempstack.push(destveridx); //最终顶点下标先扔到堆栈

                int tmpidx = ppath[destveridx];
                while (tmpidx != idx) //不等于源顶点时循环
                {
                    tempstack.push(tmpidx);
                    tmpidx = ppath[tmpidx];
                } //end while

                tempstack.push(idx); //源顶点扔到堆栈

                while (!tempstack.empty()) {
                    cout << pm_VecticesList[tempstack.top()]; //显示栈顶元素
                    tempstack.pop(); //删除栈顶元素
                    if (tempstack.size() != 0)
                        cout << "→";
                } //end while

                cout << endl; //换行
            } //end for destveridx

            delete[] pdist;
            delete[] ppath;
            delete[] pS;
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

    _nmsp1::GraphMatrix<char> gm;
    gm.InsertVertex('A');
    gm.InsertVertex('B');
    gm.InsertVertex('C');
    gm.InsertVertex('D');
    gm.InsertVertex('E');
    gm.InsertVertex('F');
    //向图中插入边
    gm.InsertEdge('A', 'B', 22); //22代表边的权值
    gm.InsertEdge('A', 'D', 6);
    gm.InsertEdge('B', 'E', 100);
    gm.InsertEdge('C', 'B', 50);
    gm.InsertEdge('C', 'E', 40);
    gm.InsertEdge('C', 'F', 10);
    gm.InsertEdge('D', 'B', 10);
    gm.InsertEdge('D', 'C', 20);
    gm.InsertEdge('F', 'D', 65);
    gm.InsertEdge('F', 'E', 35);

    //显示图形
    gm.DispGraph();

    gm.ShortestPath_Dijkstra('A');
    //gm.ShortestPath_Dijkstra('F');
    return 0;
}
