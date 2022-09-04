
#include<iostream>
using namespace std;

#define MAXVERTEXNUM 100

// 邻接矩阵
template<class TypeOfVertex, class TypeOfEdge>
struct MGraph {
    TypeOfVertex Vertices[MAXVERTEXNUM];
    TypeOfEdge Edges[MAXVERTEXNUM][MAXVERTEXNUM];
    int vertexnum, arcnum;
};

// 邻接表
template<class TypeOfVertex, class TypeOfEdge>
struct ArcNode
{
    int adjvertex;
    ArcNode<TypeOfVertex, TypeOfEdge>* next;
    TypeOfEdge info;
};
template<class TypeOfVertex, class TypeOfEdge>
struct VNode {
    TypeOfVertex data;
    ArcNode<TypeOfVertex, TypeOfEdge>* first;
};
template<class TypeOfVertex, class TypeOfEdge>
struct ALGraph {
    VNode<TypeOfVertex, TypeOfEdge>[MAXVERTEXNUM] vertices;
    int vertexnum, arcnum;
};

// 十字链表
template<class TypeOfEdge>
struct CrossArcNode {
    int tailvertex;         // 位置索引
    int headvertex;
    CrossArcNode<TypeOfEdge>* hlink;        // 指向弧头相同的下一条弧
    CrossArcNode<TypeOfEdge>* tlink;
    TypeOfEdge info;
};
template<class TypeOfVetex, class TypeOfEdge>
struct CrossNode {
    TypeOfVetex data;
    CrossArcNode<TypeOfEdge>* firstin;      // 以该节点为弧头的第一个弧节点
    CrossArcNode<TypeOfEdge>* firstout;
};

// 邻接多重表
template<class TypeOfEdge>
struct MultipleArcNode {
    bool mark;                              // 用于标记这条边是否被搜索过
    int ivertex;                            // 位置
    MultipleArcNode<TypeOfEdge>* ilink;     // 下一条依附于顶点 ivertex 的边
    int jvertex;
    MultipleArcNode<TypeOfEdge>* jlink;
    TypeOfEdge info;
};
template<class TypeOfVertex, class TypeOfEdge>
struct MultipleNode {
    TypeOfVertex data;
    MultipleArcNode<TypeOfEdge>* firstedge;
};

int main() {

    return 0;
}