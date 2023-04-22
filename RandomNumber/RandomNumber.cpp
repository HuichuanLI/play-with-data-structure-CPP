#include "RandomNumber.h"
#include <ctime>

#define m 65536L
#define b 1194211693L
#define c 12345L
using namespace std;

//函数RandomNumber用来产生种子
RandomNumber::RandomNumber(unsigned long s) {
    time_t timer;
    if (s == 0)
        d = time(NULL);  //由系统时间产生种子
    else
        d = s;  //由用户提供种子
}

//函数random用来产生0：n-1之间的随机整数
unsigned short RandomNumber::random(unsigned long n) {
    d = b * d + c;  //用线性同余式计算新的种子d
    return (unsigned short) ((d >> 16) % n);  //把d的高16位映射到0~(n-1)范围内
}

//函数fRandom用来产生[0,1)之间的随机实数
double RandomNumber::fRandom(void) {
    return random(m) / double(m);
}  
