#include <iostream>
using namespace std;
void print_array(int a[], int m);
void insert_sort(int a[], int m);


void print_array(int a[], int m){
    for (int i = 0; i < m; i++)
    {
        cout << a[i] <<" ";
    }
    cout << endl;
}

void insert_sort(int a[], int m){ //最好的情况要比较n-1次，最坏的情况要比较(0+n-1)*n/2 --时间复杂度是O(n^2) -> O(n) 空间复杂度O(1)
    print_array(a, m); //这种方法排序稳定（相同的值的量的相对位置是一定的）
    for (int i = 0; i < m; i++)
    {
        int key = a[i]; //暂存器
        int j = i - 1;
        while (j >= 0 && a[j] > key)
        {
            a[j+1]=a[j];
            j--; //将所有的比key大的值依次右移
        }
        a[j+1]=key; //最终j+1会是空白的，即上一次向右移动
        
    }
    print_array(a, m);
}

int main(){
    int a[] = {2,3,4,2,3,1,5,1,3,5,2,4,1,3};
    insert_sort(a, 14);  
}
