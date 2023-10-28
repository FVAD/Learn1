#include <iostream>
#include <vector> // 这里采用Vector套vector构造二维数组
using namespace std;
void double_push(vector<Node> Adj, int a, int b, int power);


struct Node
{
    int v,w;
    Node(int _v,int _w):v(_v),w(_w) {} //构造函数
};

// 双边加法
void double_push(vector<Node>* Adj, int a, int b, int power)
{
    Adj[a].push_back(Node (b, power));
    Adj[b].push_back(Node (a, power));
}

int main()
{
    int n=5;
    // cin >> n; // 用默认值建立vector容器
    vector<Node> Adj[n];
    Adj[1].push_back(Node (3, 4)); // 单边加法
    double_push(Adj, 1, 4, 2); // 双边加法
}

// 也许是这样写的？
