#include <iostream>
using namespace std;

//声明结构体类型 Car
struct Car{
   int num;
   double gas;
};

//show 函数的声明
void show(Car& c);

int main()
{
   Car car1 = {0, 0.0};

   cout << "请输入车牌号。\n";
   cin >> car1.num;

   cout << "请输入汽油量。\n";
   cin >> car1.gas;

   show(car1);

   return 0;
}

//show 函数的定义
void show(Car& c)
{
   cout << "车牌号是" << c.num << "汽油量是" << c.gas << "。\n";
}
