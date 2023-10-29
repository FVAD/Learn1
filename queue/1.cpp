#include <iostream>
#include <vector>

using namespace std;

// 使用单向链表实现队列
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){}
};

class LinkedListQueue
{
private:
    ListNode *front, *rear;
    int queSize;
public:
    LinkedListQueue()
    {
        front = nullptr;
        rear = nullptr;
        queSize = 0;
    }
    ~LinkedListQueue()
    {
        // 遍历链表删除节点，释放内存
        freeMemoryLinkedList(front);
    }

    /* Size */
    int size()
    {
        return queSize;
    }

    /* Free Mem */
    void freeMemoryLinkedList(ListNode *front)
    {
        ListNode *Tmp = front;
        while (front->next!=nullptr)
        {
            Tmp = front->next;
            delete front;
            front = Tmp;
        }
        
    }
    /* Empth? */
    bool isEmpty()
    {
        return queSize == 0;
    }

    /* push */
    void push(int num)
    {
        // rear 后加入
        ListNode *node = new ListNode(num);
        // 如为空队列则同时获得 front 和 rear
        if (front == nullptr)
        {
            front = node;
            rear = node;
        }
        // 否则在rear后加入
        else
        {
            rear->next = node;
            rear = node;
        }
        queSize++;
    }

    /* Pop */
    void pop()
    {
        int num = peak(); // 主要是为了测“是否为空”
        ListNode *tmp = front;
        front = front->next;
        // free memory
        delete tmp;
        queSize--;
    }

    /* Peak Element */
    int peak()
    {
        if (size() == 0)
        {
            throw out_of_range("队列为空");
        }
        return front->val;
        
    }

    /* vector 化 */
    vector<int> toVector()
    {
        ListNode *node = front;
        vector<int> res(size());
        for (int i = 0; i < res.size(); i++)
        {
            res[i] = node->val;
            node = node->next;
        }
        return res;
    }
};