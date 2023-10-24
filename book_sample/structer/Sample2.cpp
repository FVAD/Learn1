#include <iostream>
using namespace std;

//声明结构体类型 Car
struct Car{
   int num;
   double gas;
};

int main()
{
   Car car1;

   cout << "请输入车牌号。\n";
   cin >> car1.num;
   cout << "请输入汽油量。\n";
   cin >> car1.gas;
   cout << "车牌号是" << car1.num << "汽油量是" << car1.gas << "。\n";

   return 0;
}
