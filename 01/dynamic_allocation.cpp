# include <iostream>
using namespace std;

int main()
{
    int* pA;
    pA = new int; // 同样可以用带可变的参数的数组，然后让用户决定参数大小以便生成正常大小的数组， Eg: pA = new int[num]
    *pA=50;
    cout << *pA <<endl;
    delete pA;
}