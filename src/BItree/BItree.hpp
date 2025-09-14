#pragma once
#include <iostream>

template <class T>
class BINode
{
public:
    T data;
    BINode *lchild;
    BINode *rchild;
    BINode *fchild;
};

template <class T>
class BItree
{
public:
    // 构造函数
    BItree();

private:
    int length;
    BINode *head;
};

template <typename T>
BItree<T>::BItree() : length(0)
{
    head = nullptr;
}