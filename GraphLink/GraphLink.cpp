//
// Created by lhc456 on 2023/4/18.
//
//----------------------
#include <iostream>

#define MaxVertices_size 10 //最大顶点数大小
using namespace std;
//表示边的节点结构
struct EdgeNode {
    int curridx; //边所对应的顶点下标值
    EdgeNode *next; //指向下一条边
};

//表示顶点的节点结构，其后是一个链表，链表中每个节点都代表着和该顶点相连的边
template<typename T> //T代表顶点类型
struct VertexNode {
    T data;    //顶点中的数据
    EdgeNode *point; //指向第一个边节点的指针
};


//邻接表代表的图
template<typename T> //T代表顶点类型
class GraphLink {
public:
    GraphLink() //构造函数
    {
        m_numVertices = 0;
        m_numEdges = 0;
        for (int i = 0; i < MaxVertices_size; ++i) {
            m_VertexArray[i].point = nullptr; //指针可以率先指向nullptr
        }
    }

    ~GraphLink() //析构函数
    {
        for (int i = 0; i < m_numVertices; ++i) {
            EdgeNode *ptmp = m_VertexArray[i].point;
            while (ptmp != nullptr) {
                m_VertexArray[i].point = ptmp->next;
                delete ptmp;
                ptmp = m_VertexArray[i].point;
            } //end while
            m_VertexArray[i].point = nullptr;
        } //end for i
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
        m_VertexArray[m_numVertices].data = tmpv;
        m_VertexArray[m_numVertices].point = nullptr;
        m_numVertices++;
        return true;
    }

    //插入边
    bool InsertEdge(const T &tmpv1, const T &tmpv2) //在tmpv1和tmpv2两个顶点之间插入一条边
    {
        int idx1 = GetVertexIdx(tmpv1);
        int idx2 = GetVertexIdx(tmpv2);
        if (idx1 == -1 || idx2 == -1) //某个顶点不存在，不可以插入边
            return false;

        //判断是否边重复
        EdgeNode *ptmp = m_VertexArray[idx1].point;
        while (ptmp != nullptr) {
            if (ptmp->curridx == idx2)
                return false; //边重复
            ptmp = ptmp->next;
        }

        //可以正常插入，先向下标为idx1对应的顶点的单链表中插入边节点
        ptmp = new EdgeNode;
        ptmp->curridx = idx2;
        ptmp->next = m_VertexArray[idx1].point;  //为简化编码和提升代码执行效率，采用头插法将边节点插入到单链表的最前面
        m_VertexArray[idx1].point = ptmp;

        //对于无向图，tmpv1到tmpv2之间插入边就等于tmpv2到tmpv1之间插入了边，所以接着向下标为idx2对应的顶点的单链表中插入边节点
        ptmp = new EdgeNode;
        ptmp->curridx = idx1;
        ptmp->next = m_VertexArray[idx2].point;  //头插法
        m_VertexArray[idx2].point = ptmp;

        //注意：对于无向图，tmpv1到tmpv2之间插入边就等于tmpv2到tmpv1之间插入了边
        m_numEdges++; //边数量增加1
        return true;
    }

    //删除边
    bool DeleteEdge(const T &tmpv1, const T &tmpv2) //删除两个顶点之间的边
    {
        int idx1 = GetVertexIdx(tmpv1);
        int idx2 = GetVertexIdx(tmpv2);
        if (idx1 == -1 || idx2 == -1)
            return false;

        //在第一个节点中查找边信息
        EdgeNode *prev = nullptr; //指向前趋节点方便做删除边节点的操作
        EdgeNode *ptmp = m_VertexArray[idx1].point;
        while (ptmp != nullptr && ptmp->curridx != idx2) {
            prev = ptmp; //保存前趋节点方便做删除操作
            ptmp = ptmp->next;
        } //end while
        if (ptmp == nullptr) //两个顶点之间没有边，怎么可以删除边呢？
            return false;

        //有边，则可以开始删除边节点
        if (prev == nullptr) {
            //删除的是第一个边节点
            m_VertexArray[idx1].point = ptmp->next; //等价于删除头部的节点
        } else {
            prev->next = ptmp->next;
        }
        delete ptmp;  //释放边节点所占用的内存

        //因为是无向图，所以第二个节点中必然能找到和第一个节点相关的边信息
        prev = nullptr;
        ptmp = m_VertexArray[idx2].point;
        while (ptmp->curridx != idx1) //这里无需判断ptmp != nullptr条件，因为无向图中A到B之间有边，则B到A之间必然有边
        {
            prev = ptmp; //保存前趋节点方便做删除操作
            ptmp = ptmp->next;
        } //end while
        if (prev == nullptr) {
            //删除的是第一个边节点
            m_VertexArray[idx2].point = ptmp->next;
        } else {
            prev->next = ptmp->next;
        }
        delete ptmp;
        m_numEdges--; //边数量减少1
        return true;
    }

    //删除顶点，涉及到顶点对应的边也要删除
    bool DeleteVertex(const T &tmpv) {
        int idx = GetVertexIdx(tmpv);
        if (idx == -1) //顶点不存在
            return false;

        EdgeNode *ptmp = m_VertexArray[idx].point;
        while (ptmp != nullptr) //先释放该顶点后面链接的各个边节点
        {
            //释放边节点也就等价于删除和当前顶点所连接的边,设想一下如下情形
            /*
            0   A：-- > 3-- > 2-- > 1-- > nullptr
            1   B：-- > 5-- > 4-- > 0-- > nullptr
            2   C：-- > 5-- > 0-- > nullptr
            3   D：-- > 5-- > 0-- > nullptr
            4   E：-- > 1-- > nullptr
            5   F：-- > 3-- > 2-- > 1-- > nullptr
            */
            //上面情形中，如果要删除顶点C，那么顶点C关联的下标为5、0的边要删除，但删除前，先要在下标为5、0的顶点所关联的边中删除与顶点C（下标为2）关联的边
            int tmpDestIdx = ptmp->curridx; //以删除顶点C为例。tmpDestIdx = 5
            EdgeNode *ptmpDestPrev = nullptr;   //要开始在下标为5的顶点对应的单链表中找出下标为2的边节点进行删除
            EdgeNode *ptmpDest = m_VertexArray[tmpDestIdx].point;
            while (ptmpDest != nullptr && ptmpDest->curridx != idx) {
                ptmpDestPrev = ptmpDest; //保存前趋节点方便做删除操作
                ptmpDest = ptmpDest->next;
            } //end while ptmpDest

            if (ptmpDest != nullptr) //两个顶点之间有边，就要删除边
            {
                if (ptmpDestPrev == nullptr) {
                    //删除的是第一个边节点
                    m_VertexArray[tmpDestIdx].point = ptmpDest->next;
                } else {
                    ptmpDestPrev->next = ptmpDest->next;
                }
                delete ptmpDest;
            }

            //顶点指向下一个边节点（第一次while循环所执行的是让C节点指向下标为0的边节点）
            m_VertexArray[idx].point = ptmp->next;
            //可以删除顶点C所关联的下标为5的节点了。
            delete (ptmp);
            ptmp = m_VertexArray[idx].point;

            m_numEdges--;//边数减少1
        } //end while ptmp;

        //此时顶点中对应的边信息全部删除了，其他顶点与该被删除顶点相关的边信息也全部删除了。
        //此时，针对顶点C的删除，整个邻接表应该是这样：
        /*
        0   A：-- > 3-- > 1-- > nullptr
        1   B：-- > 5-- > 4-- > 0-- > nullptr
        2   C：-- > nullptr
        3   D：-- > 5-- > 0-- > nullptr
        4   E：-- > 1-- > nullptr
        5   F：-- > 3-- > 1-- > nullptr
        */
        m_numVertices--; //顶点数减少1，后续用到该值，所以先把该值减1
        //因为要删除C顶点，所以要把末尾的F顶点的数据搬到C的位置。
        if (idx != m_numVertices) {
            //要删除的不是最后一个顶点，所以把最后一个顶点的数据搬到要删除的顶点处
            m_VertexArray[idx].data = m_VertexArray[m_numVertices].data;
            m_VertexArray[idx].point = m_VertexArray[m_numVertices].point;

            //上面代码执行完毕后，相当于这种情形了
            /*
            0   A：-- > 3-- > 1-- > nullptr
            1   B：-- > 5-- > 4-- > 0-- > nullptr
            2   F：-------------------------------------->   3-- > 1-- > nullptr
            3   D：-- > 5-- > 0-- > nullptr             /
            4   E：-- > 1-- > nullptr                 /
            5   F：----------------------------------
            */
            //现在相当于把F的下标从5变成了2，那么所有边节点中，涉及到数字5的，都得变成数字2.
            EdgeNode *ptmpnew = m_VertexArray[idx].point;   //--->3--->1-->nullptr
            while (ptmpnew != nullptr) {
                int tidx = ptmpnew->curridx; //3
                EdgeNode *tp = m_VertexArray[tidx].point;  //指向下标3(D节点)对应的边节点的指针，  5-- > 0-- > nullptr
                while (tp != nullptr) {
                    if (tp->curridx == m_numVertices) //在D节点中，找到了下标为5的节点，把该节点的下标值修改为2
                    {
                        tp->curridx = idx;
                        break; //直接跳出while循环即可
                    }
                    tp = tp->next;
                } //end while (tp != nullptr)
                ptmpnew = ptmpnew->next;
            } //end while (ptmpnew != nullptr)

            //上面代码执行完毕后，相当于这种情形了
            /*
            0   A：-- > 3-- > 1-- > nullptr
            1   B：-- > 2-- > 4-- > 0-- > nullptr
            2   F：-- > 3-- > 1-- > nullptr
            3   D：-- > 2-- > 0-- > nullptr
            4   E：-- > 1-- > nullptr
            */
        } //end if (idx != m_numVertices)
        m_VertexArray[m_numVertices].point = nullptr;
        return true;
    }

    //获取某个顶点的第一个邻接顶点的下标，返回-1表示获取失败
    int GetFirstNeighbor(int idx) //idx代表顶点下标
    {
        if (idx == -1)
            return -1; //非法

        EdgeNode *pedge = m_VertexArray[idx].point;
        if (pedge != nullptr) {
            return pedge->curridx;
        }
        return -1;
    }

    //获取某个顶点（下标为idx1）的邻接顶点（下标为idx2）的下一个邻接顶点的下标，返回-1表示获取失败
    int GetNextNeightbor(int idx1, int idx2) {
        if (idx1 == -1 || idx2 == -1)
            return -1;

        EdgeNode *pedge = m_VertexArray[idx1].point;
        while (pedge != nullptr && pedge->curridx != idx2) {
            pedge = pedge->next;
        } //end while
        if (pedge != nullptr && pedge->next != nullptr) {
            //说明找到idx2这个邻接顶点了
            return pedge->next->curridx;
        }
        return -1;
    }

    void DispGraph() //显示图信息
    {
        for (int i = 0; i < m_numVertices; ++i) {
            cout << i << "" << m_VertexArray[i].data << "：-->";   //输出顶点下标和顶点数据
            EdgeNode *ptmp = m_VertexArray[i].point;
            while (ptmp != nullptr) {
                cout << ptmp->curridx << "-->";  //输出顶点相关的边索引（编号）
                ptmp = ptmp->next;
            }
            cout << "nullptr" << endl; //显示指向nullptr并换行
        } //end for
        cout << "图中有顶点" << m_numVertices << "个，边" << m_numEdges << "条!" << endl;
    }

private:
    //获取顶点下标
    int GetVertexIdx(const T &tmpv) {
        for (int i = 0; i < m_numVertices; ++i) {
            if (m_VertexArray[i].data == tmpv)
                return i;
        }
        return -1; //不存在的顶点
    }

private:
    int m_numVertices;    //当前顶点数量
    int m_numEdges;       //边数量
    VertexNode<T> m_VertexArray[MaxVertices_size]; //顶点数组
};


//---------------
//表示弧的节点结构
struct EdgeNode_cross {
    int tailidx; //弧尾顶点下标
    int headidx; //弧头顶点下标
    EdgeNode_cross *headlink;//弧头相同的下一个弧
    EdgeNode_cross *taillink; //弧尾相同的下一个弧
    //int weight; //权值，可以根据需要决定是否需要此字段
};

//表示顶点的节点结构
template<typename T>
struct VertexNode_cross {
    T data;    //顶点中的数据
    EdgeNode_cross *firstin; //该顶点作为弧头的第一条弧（入度指针）
    EdgeNode_cross *firstout; //该顶点作为弧尾的第一条弧（出度指针）
};

int main() {
    //--------------
    GraphLink<char> gm2;
    //向图中插入顶点
    gm2.InsertVertex('A');
    gm2.InsertVertex('B');
    gm2.InsertVertex('C');
    gm2.InsertVertex('D');
    gm2.InsertVertex('E');
    gm2.InsertVertex('F');
    //向图中插入边
    gm2.InsertEdge('A', 'B');
    gm2.InsertEdge('A', 'C');
    gm2.InsertEdge('A', 'D');
    gm2.InsertEdge('B', 'E');
    gm2.InsertEdge('B', 'F');
    gm2.InsertEdge('C', 'F');
    gm2.InsertEdge('D', 'F');
    gm2.DispGraph();
    gm2.DeleteEdge('A', 'D');
    gm2.DeleteEdge('E', 'B');
    gm2.DeleteEdge('E', 'C'); //删除一个不存在的边
    cout << "-----------------" << endl;
    gm2.DispGraph();
    gm2.DeleteVertex('C');
    cout << "-----------------" << endl;
    gm2.DispGraph();
}