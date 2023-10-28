#include <iostream>
#include <queue>
using namespace std;

// 这里假设顶点加起来有10个
/**
 * 顶点
*/
struct Vertex
{
    //编号
    int vid;
    // value
    string val;
    int isVisited;
    Vertex()
    {
        this->isVisited=0;
    }
    Vertex(int vid, string val)
    {
        this->val=val;
        this->vid=vid;
        this->isVisited=false;
    }
};

/**
 * AOV网类型
*/
class AOVGraph
{
private:
    // 存储所有顶点
    Vertex* allVertex[10];
    // 顶点之间的关系::使用邻接矩阵，这里将它的值直接用于计数，故edge的值只有两种
    int edges[10][10];
    int num; // 维护顶点编号
public:
    AOVGraph();
    /**
     * 查询顶点是否存在
    */
    Vertex* findVertex(string val);
    Vertex* findVertex(int vid); // 参数重构
    /**
     * 创建顶点
     * @return 顶点的指针
    */
    Vertex* addVertex(string val);
    /**
     * 添加顶点之间的关系
    */
    void addEdge(Vertex* from, Vertex* to, int weight=1);
    /**
     * 拓扑排序实现
    */
    void topSort();
   /**
    * 遍历输出
   */
    void show(){
        cout << "输出各个点之间的关系：" << endl;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                cout << this->edges[i][j] << "\t";
            }
            cout << endl;
        }
        
    }
};

AOVGraph::AOVGraph()
{
    this->num=0;
    for (int i = 0; i < 10; i++)
    {
        this->allVertex[i]=NULL;
        for (int j = 0; j < 10; j++)
        {
            // 邻接矩阵的任何两点的关系初始化为0
            this->edges[i][j]=0;
        }
        
    }
    
}

/**
 * 查找匹配顶点
 * @param val 节点的值
 * @return 节点的指针
*/
Vertex* AOVGraph::findVertex(string val)
{
    for (int i = 0; i < this->num; i++)
    {
        if (this->allVertex[i]==NULL)
        {
            continue;
        }
        if (this->allVertex[i]->val.compare(val)==0) // val的值匹配
        {
            return this->allVertex[i];
        }
        
    }
    return NULL;
}
/**
 * 查找匹配顶点
 * @param vid 节点的编号
 * @return 节点的指针
*/
Vertex* AOVGraph::findVertex(int vid)
{
    for (int i = 0; i < this->num; i++)
    {
        if (this->allVertex[i]==NULL)
        {
            continue;
        }
        if (this->allVertex[i]->vid==vid) // 编号vid的值匹配
        {
            return this->allVertex[i];
        }
        
    }
    return NULL;
}

/**
 * 创建新的顶点，编号为最后一位（即与元素的个数相同）
 * @param val 新顶点的值
 * @return 新的顶点的指针
*/
Vertex* AOVGraph::addVertex(string val)
{
    // try to find
    Vertex* ver=this->findVertex(val);
    if (ver!=NULL)
    {
        return ver;
    }
    ver=new Vertex(this->num, val);
    this->allVertex[this->num]=ver;
    this->num++;
    return ver;
}

/**
 * 添加顶点之间的关系（使用邻接矩阵）
*/
void AOVGraph::addEdge(Vertex* from, Vertex* to, int weight)
{
    this->edges[from->vid][to->vid]=weight; //weight的值应该就只有0、1两种（虽然它叫weight）
}

/**
 * 拓扑排序
 * 思路是寻找入点为0的点放在第一位，然后在图中去除它，然后重新寻找，然后往后压
*/
void AOVGraph::topSort()
{
    // queue
    queue<Vertex*> myQueue;
    int vid= 0;
    Vertex* ver=NULL;
    int i = 0;
    while (i<this->num)
    {   
        // 从邻接矩阵的一列开始扫描，然后在邻接矩阵中查找入度为0的第一个顶点
        for (int col = 0; col < this->num; col++)
        {
            int find = 1;
            ver=this->findVertex(col);
            // 检测是否已经被访问过 为什么要检测？
            if (ver != NULL && ver->isVisited==true)
            {
                continue;
            }
            for (int row = 0; row < this->num; row++)
            {
                if (this->edges[row][col]==1)
                {
                    find=0;
                    break;
                }
                
            }
            if (find == 1)
            {
                vid = col;
                myQueue.push(ver);
                ver->isVisited = true;
                // del 以此为入度的边
                for (int col = 0; col < this->num; col++)
                {
                    if (this->edges[vid][col]==1)
                    {
                        this->edges[vid][col]=0;
                    }

                }
                break;
            }
            
        }
        i++;
    }
    // 检测有向无环图的性质
    if (myQueue.size()==this->num)
    {
        cout << "无环" << endl;
    }
    else
    {
        cout << "图中有环" << endl;
    }
    while (!myQueue.empty())
    {
        Vertex* ver=myQueue.front(); //建立一个从头开始的指针不断地输出队列中的信息
        cout << ver->val << "\t";
        myQueue.pop();
    }
    cout << endl;
}

// TEST
int main(int argc, char** argv) {
	AOVGraph* aovGraph=new AOVGraph();
	Vertex* from=aovGraph->addVertex("面向对象"); //0
	Vertex* to=	aovGraph->addVertex("多线程"); //1
	aovGraph->addEdge(from,to,1);

	to=	aovGraph->addVertex("IO流"); //2
	aovGraph->addEdge(from,to,1);

	to=	aovGraph->addVertex("网络编程"); //3
	aovGraph->addEdge(from,to,1);

	Vertex* temp=to;
	to=	aovGraph->addVertex("JDBC"); //4
	aovGraph->addEdge(temp,to,1);

	from=aovGraph->addVertex("数据库"); //5
	aovGraph->addEdge(from,to,1);
	aovGraph->show();

	aovGraph->topSort();
	aovGraph->show();
	return 0;
    // 这样的代码运行后会导致原有的会被完全删除，理论上可以通过复制一个实例的方式变得可以复用。
}

// 拓扑排序一般是指将入度从小到大的方式排序输出