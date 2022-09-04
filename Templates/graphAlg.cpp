#include<iostream>
#include<queue>
using namespace std;

// 图的抽象类
template<class TypeOfVer, class TypeOfEdge>
class graph {
public:
    virtual void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) = 0; // 纯虚函数
    virtual void remove(TypeOfVer x, TypeOfVer y) = 0;
    virtual bool exist(TypeOfVer x, TypeOfVer y) const = 0;
    virtual ~graph() {};
};

template<class TypeOfVer, class TypeOfEdge>
class adjMatrixGraph : public graph<TypeOfVer, TypeOfEdge> {
public:
    adjMatrixGraph(int vSize, const TypeOfVer d[], const TypeOfEdge noEdgeFlag) {
        int i, j;
        Vers = vSize;
        Edges = 0;
        noEdge = noEdgeFlag;

        ver = new TypeOfVer[vSize];
        for (i = 0; i < vSize; ++i) ver[i] = d[i];

        edge = new TypeOfEdge * [vSize];
        for (i = 0; i < vSize; ++i) {
            edge[i] = new TypeOfEdge[vSize];
            for (j = 0; j < vSize; ++j) edge[i][j] = noEdge;
            edge[i][i] = 0;
        }
    }
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
        int u = find(x), v = find(y);
        edge[u][v] = w;
        ++Edges;
    }
    void remove(TypeOfVer x, TypeOfVer y) {
        int u = find(x), v = find(y);
        edge[u][v] = noEdge;
        --Edges;
    }
    bool exist(TypeOfVer x, TypeOfVer y) const {
        int u = find(x), v = find(y);
        if (edge[u][v] == noEdge) return false;
        return true;
    }
    ~adjMatrixGraph() {
        delete[] ver;
        for (int i = 0; i < Vers; ++i) delete[] edge[i];
        delete[] edge;
    }

    void floyd() const;
private:
    TypeOfEdge** edge;
    TypeOfVer* ver;
    TypeOfEdge noEdge;
    int Vers, Edges;
    int find(TypeOfVer v) const {
        for (int i = 0; i < Vers; ++i)
            if (ver[i] == v) return i;
        return -1;
    }
};

template<class TypeOfVer, class TypeOfEdge>
void adjMatrixGraph<TypeOfVer, TypeOfEdge>::floyd() const
{
    // O(|V|^3)
    TypeOfEdge** d = new TypeOfEdge * [Vers];
    int** prev = new int* [Vers];
    int i, j, k;

    // d_k[i][j]=min(d_{k-1}[i][j], d_{k-1}[i][k]+d_{k-1}[k][j])
    // 将每个节点作为每条路径上的一个中间节点，看看从起始点到中间节点，
    // 再从中间节点到终止节点间的距离是不是比已知的距离短。

    for (i = 0; i < Vers; ++i) {
        d[i] = new TypeOfEdge[Vers];
        prev[i] = new int[Vers];
        for (j = 0; j < Vers; ++j) {
            d[i][j] = edge[i][j];
            prev[i][j] = (edge[i][j] != noEdge) ? i : -1;
        }
    }

    for (k = 0; k < Vers; ++k) {
        for(i=0;i<Vers;++i)
            for (j=0;j<Vers;++j)
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    prev[i][j] = prev[k][j];
                }
    }

    cout << "***** Shortest Distance *****" << endl;
    for (i = 0; i < Vers; ++i) {
        for (j = 0; j < Vers; ++j)
            cout << d[i][j] << '\t';
        cout << endl;
    }

    cout << "***** Prev Matrix *****" << endl;
    for (i = 0; i < Vers; ++i) {
        for (j = 0; j < Vers; ++j)
            cout << prev[i][j] << '\t';
        cout << endl;
    }

    for (int i = 0; i < Vers; ++i)
        delete[] prev[i], d[i];
    delete[] prev, d;
}

/*
template<class T>
class A {
public:
    virtual int func() = 0;
protected:
    int a;      // This is not allowed
};

template<class T>
class B : public A<T> {
public:
    int func() {
        a = 0;
        return a;
    }
};
*/

class DisjointSet {
private:
    int size;
    int* parent;
public:
    DisjointSet(int n) {
        size = n;
        parent = new int[size];
        for (int i = 0; i < size; ++i)
            parent[i] = -1;
    }
    ~DisjointSet() { delete[] parent; }
    void Union(int root1, int root2) {
        if (root1 == root2) return;
        // 将规模较小的树作为规模大的树的子树
        // 规模使用负数记录
        if (parent[root1] > parent[root2]) {    // root1 规模小
            parent[root2] += parent[root1];     // 记录规模
            parent[root1] = root2;              // root1 归为 root2 下
        }
        else {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
    }
    int Find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = Find(parent[x]);     // 路径压缩
    }
};

template<class TypeOfVer, class TypeOfEdge>
class adjListGraph : public graph<TypeOfVer, TypeOfEdge> {
public:
    adjListGraph(int vSize, const TypeOfVer d[]) {
        Vers = vSize;
        Edges = 0;

        verList = new verNode[vSize];
        for (int i = 0; i < Vers; ++i) verList[i].ver = d[i];
    }

    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w) {
        int u = find(x), v = find(y);
        verList[u].head = new edgeNode(v, w, verList[u].head);
        ++Edges;
    }

    void remove(TypeOfVer x, TypeOfVer y) {
        int u = find(x), v = find(y);
        edgeNode* p = verList[u].head, * q;

        if (p == NULL) return;

        if (p->end == v) {      // 第一个就应该被删除
            verList[u].head = p->next;
            delete p;
            --Edges;
            return;
        }

        while (p->next != NULL && p->next->end != v) p = p->next;   // 查找被删除的边

        if (p->next != NULL) {
            q = p->next;
            p->next = q->next;
            delete p;
            --Edges;
        }

    }

    bool exist(TypeOfVer x, TypeOfVer y) const {
        int u = find(x), v = find(y);
        edgeNode* p = verList[u].head;

        while (p != NULL && p->end != v) p = p->next;
        if (p == NULL) return false;
        return true;
    }

    void dfs() const;
    void bfs() const;
    void topSort(int *&top) const;
    void criticalPath() const;
    void kruskal() const;
    void prim(TypeOfEdge noEdge) const;
    void dijkstra(TypeOfVer start, TypeOfEdge noEdge) const;

    ~adjListGraph() {
        int i;
        edgeNode* p;

        for (i = 0; i < Vers; ++i) {
            while ((p = verList[i].head) != NULL) {
                verList[i].head = p->next;
                delete p;
            }
        }

        delete[] verList;
    }
private:
    struct edgeNode {
        int end;            // 终点编号
        TypeOfEdge weight;
        edgeNode* next;

        edgeNode(int e, TypeOfEdge w, edgeNode *n = NULL): end(e), weight(w), next(n) {}
    };

    struct verNode {
        TypeOfVer ver;
        edgeNode* head;     // 对应单链表的头指针

        verNode(edgeNode *h = NULL): head(h) {}
    };

    verNode* verList;
    int Vers, Edges;
    int find(TypeOfVer v) const {
        for (int i = 0; i < Vers; ++i)
            if (verList[i].ver == v) return i;
        return -1;
    }

    void dfs(int start, bool visited[]) const;
    void printPath(int start, int finish, int* prev) const;
};

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const
{
    // O(|V|+|E|)

    bool* visited = new bool[Vers];
    
    for (int i = 0; i < Vers; ++i) visited[i] = false;

    cout << "******* dfs ********" << endl;

    for (int i = 0; i < Vers; ++i) {
        if (visited[i]) continue;
        dfs(i, visited);
        cout << endl;
    }

    delete[] visited;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
{
    edgeNode* p = verList[start].head;

    cout << verList[start].ver << '\t';
    visited[start] = true;

    while (p != NULL) {
        if (!visited[p->end]) dfs(p->end, visited);
        p = p->next;
    }
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const
{
    // O(|V|+|E|)

    bool* visited = new bool[Vers];
    int currentNode;
    queue<int> q;
    edgeNode* p;

    for (int i = 0; i < Vers; ++i) visited[i] = false;

    cout << "******* bfs ********" << endl;

    for (int i = 0; i < Vers; ++i) {
        if (visited[i]) continue;
        q.push(i);
        while (!q.empty()) {
            currentNode = q.front(); q.pop();
            if (visited[currentNode]) continue;
            cout << verList[currentNode].ver << '\t';
            visited[currentNode] = true;
            p = verList[currentNode].head;
            while (p != NULL) {
                if (!visited[p->end]) q.push(p->end);
                p = p->next;
            }
        }
        cout << endl;
    }

    delete[] visited;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::topSort(int *&top) const
{
    // 通过检查入度是否为0来判断是否可以访问。
    // O(|V|+|E|)

    queue<int> q;
    edgeNode* p;
    int current;
    int* inDegree = new int[Vers];

    for (int i = 0; i < Vers; ++i) {
        inDegree[i] = 0;
        for (p = verList[i].head; p != NULL; p = p->next)
            ++inDegree[p->end];
    }

    for (int i = 0; i < Vers; ++i)
        if (inDegree[i] == 0) q.push(i);

    //cout << "****** topSort *******" << endl;
    int cnt = 0;
    while (!q.empty()) {
        current = q.front(); q.pop();
        //cout << verList[current].ver << '\t';
        top[cnt++] = current;
        for (p = verList[current].head; p != NULL; p = p->next)
            if (--inDegree[p->end] == 0)
                q.push(p->end);
    }

    //cout << endl;
    delete[] inDegree;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::criticalPath() const
{
    int* top = new int[Vers];
    topSort(top);

    TypeOfEdge* ee = new TypeOfEdge[Vers], * le = new TypeOfEdge[Vers];
    edgeNode* p;
    int i;

    // 最早发生时间
    // max(ee[j]+weight(j,k))
    for (i = 0; i < Vers; ++i) ee[i] = 0;
    for (i = 0; i < Vers; ++i)
        for (p = verList[i].head; p != NULL; p = p->next)
            if (ee[p->end] < ee[top[i]] + p->weight)
                ee[p->end] = ee[top[i]] + p->weight;

    // 最迟发生时间
    // min(ve[j]-weight(k,j))
    for (i = 0; i < Vers; ++i) le[i] = ee[Vers - 1];
    for (i = Vers - 1; i >= 0; --i)
        for (p = verList[top[i]].head; p != NULL; p = p->next)
            if (le[p->end] - p->weight < le[top[i]])
                le[top[i]] = le[p->end] - p->weight;

    // 相等的为关键路径上的点
    // >= + <= => =
    for (i = 0; i < Vers; ++i)
        if (le[top[i]] == ee[top[i]])
            cout << '(' << verList[top[i]].ver << ", " << ee[top[i]] << ')';
    cout << endl;

    delete[] top, ee, le;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::kruskal() const
{
    struct edge {
        int beg, end;
        TypeOfEdge w;
        bool operator<(const edge& rp) const { return w < rp.w; }
    };

    int edgesAccepted = 0, u, v;
    edgeNode* p;
    edge e;
    DisjointSet ds(Vers);
    priority_queue<edge> pq;

    for (int i = 0; i < Vers; ++i)
        for (p=verList[i].head;p!=NULL;p=p->next)
            if (i < p->end) {
                e.beg = i;
                e.end = p->end;
                e.w = p->weight;
                pq.push(e);
            }

    while (edgesAccepted < Vers - 1) {  // 直到边数为顶点数-1
        e = pq.top(); pq.pop();
        u = ds.Find(e.beg);
        v = ds.Find(e.end);
        if (u != v) {                   // 不属于同一个子图
            ++edgesAccepted;
            ds.Union(u, v);
            cout << '(' << verList[e.beg].ver << ',' << verList[e.end].ver << ")\t";
        }
    }
    cout << endl;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::prim(TypeOfEdge noEdge) const
{
    bool* flag = new bool[Vers];
    TypeOfEdge* lowCost = new TypeOfEdge[Vers];
    int* startNode = new int[Vers];

    edgeNode* p;
    TypeOfEdge min;
    int start, i, j;

    for (i = 0; i < Vers; ++i) {
        flag[i] = false;
        lowCost[i] = noEdge;
    }

    start = 0;
    for (i = 1; i < Vers; ++i) {
        // 对于 start 的每一条边 (start,v)，如果 v 不在生成树中，并且边的边值 w 小于 lowCost[v]
        for (p = verList[start].head; p != NULL; p = p->next)
            if (!flag[p->end] && lowCost[p->end] > p->weight) {
                lowCost[p->end] = p->weight;
                startNode[p->end] = start;
            }

        flag[start] = true;
        // 从 lowCost 中寻找最小的元素，将下标存入start
        min = noEdge;
        for (j = 0; j < Vers; ++j)
            if (lowCost[j] < min) {
                min = lowCost[j];
                start = j;
            }
        cout << '(' << verList[startNode[start]].ver << ',' << verList[start].ver << ")\t";
        lowCost[start] = noEdge;
    }
    cout << endl;

    delete[] flag, lowCost, startNode;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::printPath(int start, int finish, int prev[]) const
{
    if (start == finish) {
        cout << verList[start].ver;
        return;
    }
    printPath(start, prev[finish], prev);
    cout << "->" << verList[finish].ver;
}

template<class TypeOfVer, class TypeOfEdge>
void adjListGraph<TypeOfVer, TypeOfEdge>::dijkstra(TypeOfVer start, TypeOfEdge noEdge) const
{
    // O(|V|^2)
    TypeOfEdge* distance = new TypeOfEdge[Vers];
    bool* known = new bool[Vers];
    int* prev = new int[Vers];
    int i, j, sNo, u;
    TypeOfEdge min;
    edgeNode* p;

    for (i = 0; i < Vers; ++i) {
        distance[i] = noEdge;
        known[i] = false;
    }

    // 对起始节点的初始化
    sNo = find(start);
    distance[sNo] = 0;
    prev[sNo] = sNo;

    for (i = 1; i < Vers; ++i) {
        min = noEdge;
        // 寻找具有最短距离的节点
        for (j = 0; j < Vers; ++j)
            if (!known[j] && distance[j] < min) {
                min = distance[j];
                u = j;
            }
        // 标记为已被访问
        known[u] = true;
        // 更新距离
        for (p = verList[u].head; p != NULL; p = p->next)
            if (!known[p->end] && distance[p->end] > min + p->weight) {
                distance[p->end] = min + p->weight;
                prev[p->end] = u;
            }
    }

    // 打印路径
    for (i = 0; i < Vers; ++i) {
        cout << start << "-->" << verList[i].ver << ": ";
        printPath(sNo, i, prev);
        cout << "\t\tL: " << distance[i] << endl;
    }

    delete[] distance, known, prev;
}

int main() {
    adjMatrixGraph<char, int> mg(3, "abc", INT32_MAX);
    mg.insert('a', 'b', 8);
    mg.insert('a', 'c', 5);
    mg.insert('c', 'b', 2);
    mg.insert('b', 'a', 3);
    mg.insert('c', 'a', 6);
    mg.floyd();

    adjListGraph<char, int> g(6, "abcdef");
    g.insert('a', 'b', 1);
    g.insert('a', 'c', 3);
    g.insert('a', 'd', 5);
    g.insert('b', 'c', 1);
    g.insert('c', 'd', 1);
    g.insert('b', 'e', 2);
    g.insert('d', 'e', 1);
    g.insert('c', 'f', 2);
    g.insert('e', 'f', 2);
    g.insert('d', 'f', 2);

    g.dfs();
    g.bfs();
    int* top = new int[7];
    g.topSort(top);
    delete[] top;
    g.criticalPath();
    g.kruskal();
    g.prim(INT32_MAX);
    g.dijkstra('a', INT32_MAX);

    return 0;
}
