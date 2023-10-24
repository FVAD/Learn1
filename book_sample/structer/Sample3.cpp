#include <iostream>
using namespace std;

//声明结构体类型 Car
struct Car{
   int num;
   double gas;
};

int main()
{
   Car car1 = {1234, 25.5};
   Car car2 = {4567, 52.2};

   cout << "car1 的车牌号是" << car1.num << "汽油量是" << car1.gas << "。\n";
   cout << "car2 的车牌号是" << car2.num << "汽油量是" << car2.gas << "。\n";

   car2 = car1;

   cout << "将 car1 的值赋值到 car2。\n";

   cout << "car2 的车牌号是" << car2.num << "汽油量是" << car2.gas << "。\n";

   return 0;
}
