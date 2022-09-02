// 是否存在EL路径

#include<iostream>
using namespace std;

#define MAXV 100

typedef struct {
    int numVertices, numEdges;
    char VerticesList[MAXV];
    int Edge[MAXV][MAXV];
} MGraph;

int IsExistEL(MGraph G) {
    // G 中度为奇数的顶点数为不大于2的偶数时（0或2）
    int degreeOdd = 0;
    for (int i = 0; i < G.numVertices; ++i) {
        int degree = 0;
        for (int j = 0; j < G.numVertices; ++j)
            degree += G.Edge[i][j];
        if (degree % 2 == 1 && ++degreeOdd > 2)
            return 0;
    }
    if (degreeOdd == 1) return 0;
    return 1;
}

int main() {
    MGraph G;
    G.numVertices = 5;
    G.numEdges = 7;
    G.Edge[0][1] = G.Edge[1][0] = 1;
    G.Edge[0][4] = G.Edge[4][0] = 1;
    G.Edge[1][4] = G.Edge[4][1] = 1;
    G.Edge[1][3] = G.Edge[3][1] = 1;
    G.Edge[3][4] = G.Edge[4][3] = 1;
    G.Edge[2][3] = G.Edge[3][2] = 1;
    G.Edge[0][2] = G.Edge[2][0] = 1;
    cout << IsExistEL(G) << endl;
    return 0;
}