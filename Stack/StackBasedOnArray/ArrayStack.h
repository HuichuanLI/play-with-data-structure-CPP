//
// Created by lhc456 on 2023/5/1.
//

#ifndef PLAY_WITH_ALGO_ARRAYSTACK_H
#define PLAY_WITH_ALGO_ARRAYSTACK_H

template<class T>
class ArrayStack {
public:
    ArrayStack();

    ArrayStack(int count);

    ~ArrayStack();

    void push(T data);     //入栈
    T pop();      //出栈，并删除栈顶元素
    T peek();     //返回栈顶元素，不删除栈顶元素，栈顶指针不变
    int stackSize();

    int stackMaxSize();

private:
    int flag;       //栈顶标签，指向栈顶
    int count;     //栈的容量
    T *array;       //指针
};

#endif //PLAY_WITH_ALGO_ARRAYSTACK_H
