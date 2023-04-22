#include "RandomNumber.h"
#include <ctime>

#define m 65536L
#define b 1194211693L
#define c 12345L
using namespace std;

//����RandomNumber������������
RandomNumber::RandomNumber(unsigned long s) {
    time_t timer;
    if (s == 0)
        d = time(NULL);  //��ϵͳʱ���������
    else
        d = s;  //���û��ṩ����
}

//����random��������0��n-1֮����������
unsigned short RandomNumber::random(unsigned long n) {
    d = b * d + c;  //������ͬ��ʽ�����µ�����d
    return (unsigned short) ((d >> 16) % n);  //��d�ĸ�16λӳ�䵽0~(n-1)��Χ��
}

//����fRandom��������[0,1)֮������ʵ��
double RandomNumber::fRandom(void) {
    return random(m) / double(m);
}  
