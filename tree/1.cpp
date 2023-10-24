#include <iostream>
using namespace std;

void SearchChange (node* root,int x,int newdata);
void insert(node* &root,int x);

struct node //定义一个链表带上两个指针
{
    int data; // 这里选择用一个int来存储key值
    node* lchild=NULL;
    node* rchild=NULL;
};

/**
 * 生成一个新的节点
 * @param v 节点的权值
*/
node* newNode(int v)
{
    node* Node=new node;
    Node->data=v;
}

/**
 * 通过递归批量修改某种key。
 * @param root 二叉树树根指针
 * @param x 原值
 * @param newdata 新值
*/
void SearchChange (node* root,int x,int newdata) 
{
    if(root==NULL)
    {
        return; 			// 空树,代表抵达递归边界
    }
    if(root->data==x)		// 找到数据域为x的结点，把它修改成newdata
    { 
        root->data = newdata;
    }
    SearchChange(root->lchild,x,newdata); // 往左子树搜索 x（递归式）
    SearchChange(root->rchild,x,newdata);	// 往右子树搜索 x（递归式）
}

// insert 函数将在二叉树中插入一个数据域为 x 的新结点
//注意根结点指针 root 要使用引用，否则插入不会成功
void insert(node* &root,int x)
{
    if(root==NULL)		//空树，说明查找失败，也即插入位置（递归边界）
    { 
        root=newNode(x);
        return;
    }
    if(root->lchild==NULL) // 由二叉树的性质，x 应该插在左子树
    {
        insert(root->lchild,x);		//往左子树搜索（递归式）
    }
	else
	{
        insert(root->rchild,x);		//往右子树搜索（递归式）
    }
}
//以下是通过数组建立二叉树的方法。
node* Create(int data[],int n)
{
    node* root = NULL; //新建空根结点root 
    for(int i=0;i<n;i++)
    {
        insert(root,data[i]); //将data[0]~data[n-1]插入二叉树中
    }
    return root; //返回根结点
}

