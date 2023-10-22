# include <stdio.h>
# include <stdlib.h>
// 先划分， 再合并
// 划分的目的是得到有序的最小单位
// 因此合并时只需要以其中一个为参照将另一个与参照依次比较即可
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
void merge(int arr[], int temarr[], int left,int mid,int right)
{
    //标记左半未被标记的元素
    int l_p = left;
    //标记右半未被标记的元素
    int r_p = mid + 1;

    int pos = left;
    //合并
    while (l_p <= mid && r_p <= right)
    {
        if (arr[l_p] < arr[r_p])
        {
            temarr[pos++]=arr[l_p++];
        }
        else
        {
            temarr[pos++]=arr[r_p++];
        }
        
        
    }
    

    //左半
    while (l_p<=mid)
    {
        temarr[pos++]=arr[l_p++];
    }
    
    //右半
    while (r_p<=right)
    {
        temarr[pos++]=arr[r_p++];
    }

    // 最终合并(篡改原来的数组)
    while (left <= right)
    {
        arr[left]=temarr[left];
        left++;
    }
    
}

void msort(int arr[], int temarr[], int left, int right)
{
    // 排除只有一个元素的有序区域
    if (left < right)
    {
        int mid = (left+right)/2;
        // 划分左半区域
        msort(arr, temarr, left, mid);
        // 划分右半部分
        msort(arr, temarr, mid+1, right);
        // 合并
        merge(arr, temarr, left, mid, right); 
    }
    
}
void merge_sort(int arr[], int n)
{
    // 辅助数组
    int* temarr = (int*)malloc(n * sizeof(int));
    if (temarr) // True
    {
        msort(arr, temarr, 0, n-1);
        free(temarr);
    }
    else
    {
        printf("ERROR");
    }
    
    
}


int main(){
    int a[] = {19,100,9,97,17,1,8};
    print_array(a, 7);
    merge_sort(a, 7);
    print_array(a, 7);  
}
