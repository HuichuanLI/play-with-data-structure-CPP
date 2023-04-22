//
// Created by lhc456 on 2023/4/22.
//
#include <iostream>
#include <cmath>
#include "RandomNumber.h"

using namespace std;

//计算定积分,f(x)=|sin(x)|
double f(double x) {
    return abs(sin(x));
}

double Darts_Definite_integral(int n) {
    static RandomNumber dart; //定义一个RandomNumber类的对象dart
    int k = 0, i;
    double x, y;
    for (i = 1; i <= n; i++) {
        x = dart.fRandom(); //调用类的函数fRandom产生一个[0,1)之间的实数，赋给x
        y = dart.fRandom(); //调用类的函数fRandom产生一个[0,1)之间的实数，赋给y
        if (y <= f(x))
            k++;
    }
    return k / double(n);
}

int main(int argc, char **argv) {
    cout << "请输入随机实验次数n:";
    int n;
    cin >> n;
    double s = Darts_Definite_integral(n);
    cout << "f(x)的定积分为：" << s << endl;
    return 0;
}
