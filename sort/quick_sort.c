# include <stdio.h>

// 选择最后一个数为基准(pivot)
// 每一次重排可以使基准元素到达正确的位置 ->划分
void print_array(int array[], int n){
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("\n");
    
}
void swap(int* x,int* y){
    int k;
    k = * x;
    * x = * y;
    * y = k;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        // 比pivot小的，全部换到前面去
        if (arr[j] <= pivot)
            swap(&arr[j], &arr[++i]); // i向前进一位后交换
    }
    // 此时，i指向的元素一定大于等于pivot
    swap(&arr[high], &arr[i+1]);
    return i+1;
}

void qsort(int array[], int low, int high)
{
    if (low < high)
    {
        int mid = partition(array, low, high);
        // 此处(mid)的位置已经确定为正确的数据
        // 接下来从左侧和右侧进行排序
        qsort(array, low, mid-1);
        qsort(array, mid+1, high);
    }
    
}
void quick_sort(int array[], int n)
{
    qsort(array, 0, n-1);
}

int main(){
    int a[] = {19,100,9,97,17,1,8};
    print_array(a, 7);
    quick_sort(a, 7);
    print_array(a, 7);  
}
