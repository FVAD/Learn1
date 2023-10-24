# include <iostream>
using namespace std;

//这个文件的学习目的是建立一个双向链表并实现常用的几个操作。

struct node
{
    int data;
    node* next=NULL;
    node* previous = NULL;
};


int count_x(node* p, int x);
void print_table(node* p);
void insert_table(node* head,int position,int key);
void delete_key(node* head,int key);


/**
 * 这个函数应该不需要修改，因为遍历可以仅仅是单向的。
 * @param p 链表指针
 * @param x 定位元素
 * @return 计数器的值
*/
int count_x(node* p, int x)
{
    node* o = p->next;
    int count=0;
    while (o->next!=NULL)
    {
        //遍历链表，寻找对应的key;
        if (o->data == x)
        {
            count++;
        }
        o = o->next;
    }
    return count;
}

/**
 * 这个函数应该需要修改，虽然遍历可以仅仅是单向的（或者用并行？双向遍历到中间），但是要修改另外一个指针
 * @param p 链表指针
 * @param x 定位元素
 * @return 计数器的值
*/
void delete_key(node* head, int key)
{
    node* pD=head->next;	//pD从第一个结点开始枚举
    node* pre=head;	
    node* pU=head->previous; // pU作为多出来的指针仅仅用于修改删除项的previous和改变下一个previous的指向
    while(pD!=NULL)
    {
		if(pD->data==key)
        { 
            //数据域恰好为 key，说明要删除该结点
            pre->next=pD->next; // 应该直接赋值即可（？
            pU = pD->previous; //此时pD指向目标元素, pU指向目标元素的前一个元素
            delete pD; //不释放pU是因为pU指向的元素不应该被删除
            pD=pre->next;
            pD->previous = pU;
        }
        else
        {
            //数据域不是 key ，把 pre 和 p 都后移一位
            pre=pD;
            pD=pD->next;
        }
    }
}

/**
 * @param head 传入的链表头 
 * @param position 插入的位置
 * @param key 传入参数的key值
 * @return NONE
*/
void insert_table(node* head,int position,int key)
{
    node* pA = head;
    node* pB = new node;
    for (int i = 0; i < position-1; i++)
    {
        pA = pA->next;
    }
    // 改变新值地址的指向和前一个值地址的指向
    pB->data = key;
    pB->next = pA->next;
    pA->next = pB; 
    //如果顺序调转会导致插入值之后的链表断开，导致后面的元素无法被访问。
}

/**
 * @param array[] 数组
 * @param n 数组长度
 * @return head结构体指针
*/
node* create(int array[], int n)
{

    node *p, *pre, *head; //pre存储之前的节点
    head = new node; // 因为没有立刻赋值，这里使用动态分配内存的办法新建一个node对象;
    pre = head;

    for (size_t i = 0; i < n; i++)
    {
        p = new node; // 在头节点之后新建节点
        p->data = array[i];
        // p->next = NULL
        pre->next = p;
        p->previous = pre; // 赋值给另外一个方向的指针
        pre = p; // 均是对地址的修改，因此不必考虑形式参数等等其他的影响。
    }
    return head;
}
/**
 * @param 链表指针
 * @return None
*/
void print_table(node* p)
{
    while (p != NULL) // 打印链表的剩下的值
    {
        cout << p->data << " ";
        p = p->next;
        cout << endl;
    }
    
}

int main()
{
    // 输入数组
    int n;
    cout << "输入链表长度" << endl;
    cin >> n;
    cout << "依次输入链表各项的值" << endl;
    int* a;
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >>  a[i];
        cout << endl;
    }

    node* L = create(a, n);  // L是这个链表的head
    node* o = L->next; //next则指向下一个指针
    while (o != NULL) // 打印链表的剩下的值
    {
        cout << o->data << endl;
        o = o->next;
    }
    
    delete a;
}

// 那么如何建立一个head有数据的单向链表？这里是我个人的修改。
/**
 * @param 数组，数组长度
 * @return head结构体指针
*/
node* create1(int array[], int n)

{
    
    node *p, *pre, *head; //pre为存储之前的节点
    head = new node; // 因为没有立刻赋值，这里使用动态分配内存的办法新建一个node对象;
    pre = head;
    head->data = array[0]; // 直接对head的data进行赋值。此时main函数的node* o = L
    for (size_t i = 1; i < n; i++)
    {
        p = new node; // 在头节点之后新建节点
        p->data = array[i];
        // p->next = NULL
        pre->next = p;
        pre = p; // 均是对地址的修改，因此不必考虑形式参数等等其他的影响。
    }
    return head;
}
