#include<iostream>
#include "RandomNumber.h"
#include<cmath>

using namespace std;

template<class Type>
bool majority(Type T[], int n) // 判定主元素的蒙特卡罗算法
{
    RandomNumber rnd;
    int i = rnd.random(n) + 1; //产生1~n之间的随机下标
    Type x = T[i];  // 随机选择数组元素
    int k = 0;
    for (int j = 1; j <= n; j++)
        if (T[j] == x)
            k++;
    return (k > n / 2);  //当 k>n/2 时，T含有主元素
}

template<class Type>
bool majorityMC(Type T[], int n, double kesi) { // 重复次调用算法majority
    double p = 0.5;
    int k = (int) ceil(log(kesi) / log(1 - p));
    for (int i = 1; i <= k; i++)
        if (majority(T, n))
            return true;
    return false;
}

int main(int argc, char **argv) {
    int n = 10;
    int T[n] = {1, 1, 1, 1, 5, 1, 1, 1, 6, 7};
    double kesi = 0.0001;
    bool res = majorityMC(T, n, kesi);
    cout << "res=" << res << endl;
    return 0;
}
