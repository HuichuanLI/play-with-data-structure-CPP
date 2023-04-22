//
// Created by lhc456 on 2023/4/22.
//
#include <iostream>
#include <cmath>
#include "RandomNumber.h"

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//试除法，素数测试的确定性算法
bool Prime(unsigned int n) {
    int m = floor(sqrt(double(n)));
    for (int i = 2; i <= m; i++)
        if (n % i == 0)
            return false;
    return true;
}

//wilson定理测试是否为素数,只能用于小于24的正整数的素数测试，大于24，24！将会溢出
long long fan(unsigned int n) {
    if (n == 0)
        return 1;
    else
        return n * fan(n - 1);
}

bool WilsonP(unsigned int n) {
    if (fan(n - 1) % n == n - 1)
        return true;
    return false;
}

//改进wilson定理实现，解决n!过大导致的溢出问题，利用(n-1)!%n=((n-1)*((n-2)!%n))%n
bool WilsonP1(unsigned int n) {
    long long mul = 1;
    for (int i = 1; i < n; i++)
        mul = (mul * i) % n;
    if (mul == n - 1)
        return true;
    return false;
}

//素数测试的随机化算法，无意义，得到的解可信度低于0.5
bool Prime1(unsigned int n) {
    RandomNumber rnd;
    int m = floor(sqrt(double(n)));
    unsigned int i = rnd.random(m - 2) + 2;//产生2~m-1之间的随机数
    return (n % i != 0);
}

//费尔马小定理
bool fermat_prime(int n) {
    int a, power = n - 1, d = 1;
    RandomNumber rnd;
    a = rnd.random(n - 2) + 2;
    while (power > 1) {
        if (power % 2 == 1) {
            d = d * a;
            d = d % n;
        }
        power = power / 2;
        a = a * a % n;
    }
    if (a * d % n == 1)
        return true;
    else
        return false;
}

//二次探测定理
bool Secondary_detection(int n) {
    bool result = true;
    for (int i = 2; i < n - 1; i++)
        if ((i * i) % n == 1) {
            result = false;
            break;
        }
    return result;
}

//费尔马小定理+二次探测定理
void power1(unsigned long a, unsigned long p, unsigned long n, unsigned long &result, bool &composite) {
    unsigned long x;
    if (p == 0)
        result = 1;
    else {
        power1(a, p / 2, n, x, composite); //递归计算
        result = (x * x) % n; //二次探测
        if ((result == 1) && (x != 1) && (x != n - 1))
            composite = true;
        if ((p % 2) == 1)  //p是奇数
            result = (result * a) % n;
    }
}

bool Miller_Rabin(unsigned long n) {
    RandomNumber rnd;
    unsigned long a, result;
    bool composite = false;
    a = rnd.random(n - 3) + 2;//产生2~n-2之间的随机数
    power1(a, n - 1, n, result, composite);
    if (composite || (result != 1))
        return false;
    else
        return true;
}

bool Miller_Rabin(unsigned long n, unsigned int k) {
    RandomNumber rnd;
    unsigned long a, result;
    bool composite = false;
    for (int i = 1; i <= k; i++) {
        a = rnd.random(n - 3) + 2;
        power1(a, n - 1, n, result, composite);
        if (composite || (result != 1))
            return false;
    }
    return true;
}

int main(int argc, char **argv) {
    cout << "请输入任意正整数n:" << endl;
    int n;
    cin >> n;
    cout << "试除法结果：n是否为素数？" << Prime(n) << endl;
    cout << "Wilson定理结果：n是否为素数？" << WilsonP(n) << endl;
    cout << "Wilson定理改进实现：n是否为素数？" << WilsonP1(n) << endl;
    cout << "随机化算法结果：n是否为素数？" << Prime1(n) << endl;
    cout << "费尔马小定理：n是否为素数？" << fermat_prime(n) << endl;
    cout << "二次探测定理：n是否为素数？" << Secondary_detection(n) << endl;
    cout << "费尔马小定理+二次探测定理：n是否为素数？" << Miller_Rabin(n) << endl;
    cout << "费尔马小定理+二次探测定理：n是否为素数？" << Miller_Rabin(n, 5) << endl;
    return 0;
}
