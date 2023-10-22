#include <stdio.h>
// #include <utils.h>
// 大顶堆： 父节点比左右孩子都大
// 小顶堆： 相反
// 各个节点的下标：i i*2+1(左) i*2+2
// 围护堆的性质发生在父节点的值出现问题之后
// 围护方法： 自底而上
// 用数组存储大顶堆
// 维护的复杂度：O(lgN)


// 维护需要三个参数： 数组， 长度， 待维护节点下标
void swap(int* x,int* y){
    int k;
    k = * x;
    * x = * y;
    * y = k;
}


void heapify(int array[], int n, int i)
{
    int largest = i;
    int l_son = i*2+1;
    int r_son = i*2+2;

    if (l_son < n && array[largest]< array[l_son])
    {
        largest = l_son;
    }
    if (r_son < n && array[largest] < array[r_son])
    {
        largest = r_son;
    }
    if (largest != i)
    {
        swap(&array[largest], &array[i]); //指针修改
        heapify(array, n, largest); // 递归改下面的
    }
    
}
// 建立堆（以大顶堆为例）
// 整体
void heap_sort(int array[], int n)
{
    int i;
    // Build up a heap
    for (i = n/2-1; i >= 0 ; i--)
    {
        heapify(array, n, i);
    }
    for (i = n-1; i > 0; i--)
    {
        swap(&array[i], &array[0]);
        heapify(array, i, 0);
    }
    
    
}

void print_array(int array[], int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d", array[i]);
    }
    printf("\n");
    
}
int main(){
    int a[] = {2,3,4,2,3,1,5,1,3,5,2,4,1,3};
    print_array(a, 14);
    heap_sort(a, 14);
    print_array(a, 14);  
}
