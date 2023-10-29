#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

struct Vertex
{
public:
    int key;
    string val;
    Vertex(int key, string val)
    {
        this->key = key;
        this->val = val;
    }
};

class GraphAdjList
{
private:
    /* data */
public:
    // key: 顶点, value：邻接顶点
    unordered_map<Vertex *, vector<Vertex *>> adjList;
    // 建立了两者的映射（unordered_map的原理实际上是哈希表）

    /* 删除指定节点 */
    void remove(vector<Vertex *> &vec, Vertex *vet)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i] == vet)
            {
                vec.erase(vec.begin() + i);
                break;
            }
        }
    }

    /* INIT */
    GraphAdjList(const vector<vector<Vertex *>> &edges)
    {
        for (const vector<Vertex *> &edge : edges)
        {
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0], edge[1]);
        }
    }

    /* 顶点数量 */
    int size()
    {
        return adjList.size();
    }

    /* 添加一条边 */
    void addEdge(Vertex *vet1, Vertex *vet2)
    {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
        {
            // 这是C++下抛出异常的语句结构
            throw invalid_argument("不存在顶点");
        }
        // 建立联系（双向） adjList[vet1] 就是顶点 vet1 对应的邻接顶点的集合
        adjList[vet1].push_back(vet2);
        adjList[vet2].push_back(vet1);
    }

    /* 删除一条边 */
    void removeEdge(Vertex *vet1, Vertex *vet2)
    {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
        {
            throw invalid_argument("不存在顶点");
        }
        remove(adjList[vet1], vet2);
        remove(adjList[vet2], vet1);
    }

    /* 添加顶点 */
    void addVertex(Vertex *vet)
    {
        if (adjList.count(vet))
        // Number of elements with specified key. This function only makes sense for %unordered_multimap;
        // for %unordered_map the result will either be 0 (not present) or 1 (present).
        {
            // cout << "顶点已经存在" << endl;
            return;
        }
        adjList[vet] = vector<Vertex *>();
    }

    /* 删除顶点 */
    void removeVertex(Vertex *vet)
    {
        if (!adjList.count(vet))
        {
            throw invalid_argument("不存在顶点");
            // 删除映射过去的vector容器
            adjList.erase(vet);
            for (auto &adj : adjList)
            {
                remove(adj.second, vet); // 这段代码没看懂
            }
        }
    }
    /* 打印Vector 容器 */
    void printVector(const vector<Vertex *> &vet)
    {
        for (auto &ve : vet)
        {
            cout << "Key: " << ve->key << ", Val: " << ve->val << ";";
        }
    }

    /* 打印邻接表 */
    void print()
    {
        cout << "邻接表 =" << endl;
        for (auto &adj : adjList)
        {
            const auto &key = adj.first;
            const auto &vec = adj.second;
            cout << key->val << ": ";
            printVector(vec);
            cout << endl;
        }
    }
};

/**
 * 广度优先遍历是一种由近及远的遍历方式，从某个节点出发，始终优先访问距离最近的顶点，并一层层向外扩张。
 * 如从左上角顶点出发，先遍历该顶点的所有邻接顶点，然后遍历下一个顶点的所有邻接顶点，以此类推，直至所有顶点访问完毕。
 */
vector<Vertex *> graphBFS(GraphAdjList &graph, Vertex *startVet)
{
    // 顶点遍历序列
    vector<Vertex *> res;
    // 记录已被访问的节点的哈希表（只记录节点，可用 set 而不用 map）
    unordered_set<Vertex *> visited = {startVet};
    // 建立队列
    queue<Vertex *> que;
    que.push(startVet);
    // 从顶点 vet 开始，循环直到访问完全部的顶点
    while (!que.empty())
    {
        Vertex *vet = que.front();
        que.pop();          //队首出列
        res.push_back(vet); //遍历序列记录顶点
        // 开始遍历
        for (auto adjVet : graph.adjList[vet])
        {
            if (visited.count(adjVet))
            {
                continue;
            }
            que.push(adjVet);
            visited.emplace(adjVet);
        }
        
    }
    // 返回遍历序列(此时这里res其实就是目标输出格式)
    return res;

}

// 深度优先遍历：思路是“走到尽头再返回”，实现原理是 visited 和 res 保持一致；
/* 深度优先遍历 DFS 辅助函数 */
void dfs(GraphAdjList &graph, unordered_set<Vertex *> &visited, vector<Vertex *> &res, Vertex *vet) {
    res.push_back(vet);   // 记录访问顶点
    visited.emplace(vet); // 标记该顶点已被访问
    // 遍历该顶点的所有邻接顶点
    for (Vertex *adjVet : graph.adjList[vet]) {
        if (visited.count(adjVet))
            continue; // 跳过已被访问过的顶点
        // 递归访问邻接顶点
        dfs(graph, visited, res, adjVet);
    }
}

/* 深度优先遍历 DFS */
// 使用邻接表来表示图，以便获取指定顶点的所有邻接顶点
vector<Vertex *> graphDFS(GraphAdjList &graph, Vertex *startVet) {
    // 顶点遍历序列
    vector<Vertex *> res;
    // 哈希表，用于记录已被访问过的顶点
    unordered_set<Vertex *> visited;
    dfs(graph, visited, res, startVet);
    return res;
}

// TEST
int main()
{
    // 创建一些顶点
    Vertex v1(1, "A");
    Vertex v2(2, "B");
    Vertex v3(3, "C");
    Vertex v4(4, "D");
    Vertex v5(5, "E");

    // 创建边的列表
    vector<vector<Vertex *>> edges = {
        {&v1, &v2},
        {&v2, &v3},
        {&v3, &v4},
        {&v4, &v1}};

    // 创建一个图对象
    GraphAdjList graph(edges);

    // 打印邻接表
    graph.print();

    // 添加和删除边、顶点等操作可以在这里进行测试
    graph.addEdge(&v1, &v3);
    graph.removeEdge(&v2, &v3);
    graph.addVertex(&v5);
    graph.addEdge(&v2, &v5);

    graph.print();
    cout << "----------BFS---------" << endl;
    vector<Vertex *> a= graphBFS(graph, &v1);
    graph.printVector(a);
    cout << endl;
    cout << "----------END---------" << endl;
    cout << "----------DFS---------" << endl;
    vector<Vertex *> b= graphDFS(graph, &v1);
    graph.printVector(b);
    cout << endl;
    cout << "----------END---------" << endl;
    return 0;
}
