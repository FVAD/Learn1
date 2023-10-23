#include <iostream>
using namespace std;
void func();
int* func1();
int a=10;

void func()
{
    int b = 0;
    static int c = 0; // static声明后可以在局部变量处保持数据的存储，但是这样最终的数据不能在其他区域内调用
    b++;
    c++; 
    cout << c <<"-\n";
}
int* func1(){
    int d=88;
    int* pD= &d;
    return pD;
}
int main()
{
    cout << a << endl;
    int a = 11;
    cout << a << endl;
    cout << ::a << endl; // ::后带变量名便是使用全局变量。（在全局变量和局部变量名字重叠的时候）
    for (int i = 0; i < 3; i++)
    {
        func();
    }
    cout << "d" << *func1() << endl;
    int * pC = func1(); //理论上这段代码是得到一个没有意义的指针，不知道为什么会在这里出错（正常运行）。
    cout << *pC;
    //cout<< "b"<< b << endl;
    // cout<< "c" << c << endl;
    // 区域外仍然无法调用c
}
