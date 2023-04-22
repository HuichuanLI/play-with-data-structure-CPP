//
// Created by lhc456 on 2023/4/22.
//
#include <iostream>
#include<cmath>
#include "RandomNumber.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//计算PI的值
double Darts_pi(int n) {
    static RandomNumber darts; //定义一个RandomNumber类的对象darts
    int k = 0, i;
    double x, y;
    for (i = 1; i <= n; i++) {
        x = darts.fRandom(); //调用类的函数fRandom产生一个[0,1)之间的实数，赋给x
        y = darts.fRandom(); //调用类的函数fRandom产生一个[0,1)之间的实数，赋给y
        if ((x * x + y * y) <= 1)
            k++;
    }
    return 4 * k / double(n);
}

int main(int argc, char **argv) {
    cout << "请输入随机实验次数n:";
    int n;
    cin >> n;
    double s = Darts_pi(n);
    cout << "估算的pi值为：" << s << endl;
    return 0;
}
