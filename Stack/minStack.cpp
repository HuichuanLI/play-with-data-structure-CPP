//
// Created by lhc456 on 2023/5/7.
//
#include<iostream>

using namespace std;
const int N = 100100;

struct mystack {
    int a[N];                           //存放栈元素，int型
    int t = 0;                          //栈顶位置
    void push(int x) { a[++t] = x; }    //送入栈
    int top() { return a[t]; }    //返回栈顶元素
    void pop() { t--; }    //弹出栈顶
    int empty() { return t == 0 ? 1 : 0; } //返回1表示空
} st;

int h[N], ans[N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
    for (int i = n; i >= 1; i--) {
        while (!st.empty() && h[st.top()] <= h[i])
            st.pop();                //栈顶奶牛没我高，弹出它，直到栈顶奶牛更高
        if (st.empty()) ans[i] = 0;  //栈空，没有仰望对象
        else ans[i] = st.top();   //栈顶奶牛更高，是仰望对象
        st.push(i);
    }
    for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
    return 0;
}