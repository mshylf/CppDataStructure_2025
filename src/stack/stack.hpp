#pragma once
#include <iostream>

//栈的顺序存储结构代码实现（扩容）
template<class T>
class Stack
{
public:
    //当top的值为-1时，栈为空
    //无参构造
    Stack();
    //析构函数
    ~Stack();
    //将元素x入栈
    void push(T x);
    //出栈操作，并将栈顶元素返回
    T pop();
    //由栈底向栈顶遍历
    void forEach();
    //判断栈是否为空
    bool isEmpty();
    //读出栈顶元素，但并不删除栈顶元素
    T getTop();

private:
    //栈顶指针
    int top;
    //存放数据元素
    T* data;
    //栈的最大容量，若栈满则重新分配
    int MAXSIZE;
};

//无参构造 
template<class T>
inline Stack<T>::Stack()
{
    this->MAXSIZE = 10;
    this->data = new T[MAXSIZE];
    this->top = -1;
}

//析构函数
template<class T>
inline Stack<T>::~Stack()
{
    delete[] this->data;
}

//将元素x入栈
template<class T>
inline void Stack<T>::push(T x)
{
    // 判断是否需要扩展容量
    if (top == MAXSIZE - 1)
    {
        // 扩展容量
        T* temp = new T[MAXSIZE * 2];
        for (int i = 0; i <= this->top; i++)
        {
            temp[i] = this->data[i];
        }
        delete[] this->data;
        this->data = temp;
        MAXSIZE *= 2; // 更新 MAXSIZE
    }
    this->data[++top] = x;
}

//出栈操作，并将栈顶元素返回
template<class T>
inline T Stack<T>::pop()
{
    if (top == -1)
    {
        std::cout << "栈中无元素" << std::endl;
        return T();
    }
    else if (top < -1)
    {
        std::cout << "您的输入越界" << std::endl;
        return T();
    }
    T temp = this->data[top];
    top--;
    return temp;
}

//由栈底向栈顶遍历
template<class T>
inline void Stack<T>::forEach()
{
    if (top == -1)
    {
        std::cout << "栈中无元素" << std::endl;
        return;
    }
    else if (top < -1)
    {
        std::cout << "您的输入越界" << std::endl;
        return;
    }
    for (int i = 0; i <= this->top; i++)
    {
        std::cout << this->data[i] << std::endl;
    }
}

//判断栈是否为空
template<class T>
inline bool Stack<T>::isEmpty()
{
    if (top == -1)
    {
        return true;
    }
    else if (top < -1)
    {
        throw "越界";
    }
    return false;
}

//读栈顶元素
template <class T>
T Stack<T>::getTop()
{
    if (top == -1)
    {
        std::cout << "栈中无元素" << std::endl;
        return T();
    }
    else if (top < -1)
    {
        std::cout << "您的输入越界" << std::endl;
        return T();
    }
    return this->data[top];
}
