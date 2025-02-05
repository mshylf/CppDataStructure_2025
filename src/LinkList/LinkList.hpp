#pragma once
#include <iostream>
#define OUTSIZE 99999

//普通结点
template<class T>
class LNode {
public:
    T data;
    LNode<T>* NEXT;
};

//单链表（头结点） 
template<class T>
class LinkList {
private:
    //length统计链表中元素个数
    int length = 0;
    LNode<T>* head = nullptr;
public:
    
    // 无参构造，建立一个带头结点空单链表
    LinkList();
    // 有参构造，建立长度为n的单链表
    // mode==0为头插法，mode==1为尾插法
    LinkList(T a[], int n, int mode);
    // 析构函数
    ~LinkList();
    // 遍历单链表
    void forEachList();
    //求单链表的长度
    int getLength();
    //按位查找(从1开始)
    T getItem(int i);
    //按值查找
    int locate(T x);
    //在第i个位置插入值为x的元素
    void insert(int i, T x);
    //删除单链表的第i个元素并返回

};

template<class T>
LinkList<T>::LinkList()
{
    this->head = new LNode<T>;
    this->head->NEXT = nullptr;
    this->head->data = T();
}

// 有参构造，建立长度为n的单链表
// mode==0为头插法，mode==1为尾插法
template<class T>
LinkList<T>::LinkList(T a[], int n, int mode) {
    if (n <= 0) {
        std::exit(1);
    }

    this->head = new LNode<T>;
    this->head->NEXT = nullptr;

    LNode<T>* p;
    p = this->head;

    if (mode == 0) {
        // 头插法
        for (int i = 0; i < n; i++) {
            LNode<T>* q = new LNode<T>;
            q->data = a[i];
            q->NEXT = this->head->NEXT;
            this->head->NEXT = q;
            this->length++;
        }
    }
    else {
        // 尾插法
        for (int i = 0; i < n; i++) {
            LNode<T>* q = new LNode<T>;
            q->data = a[i];
            q->NEXT = nullptr;
            p->NEXT = q;
            p = p->NEXT;
            this->length++;
        }
    }
}

// 析构函数
template<typename T>
LinkList<T>::~LinkList() {
    LNode<T>* p;
    p = this->head;
    while (p) {
        LNode<T>* q;
        q = p;
        p = p->NEXT;
        delete q;
    }
}

// 遍历单链表
template<class T>
void LinkList<T>::forEachList() {
    LNode<T>* p = this->head->NEXT;
    while (p) {
        std::cout << p->data << std::endl;
        p = p->NEXT;
    }
}

// 求单链表的长度
template<class T>
int LinkList<T>::getLength()
{
    return this->length;
}

// 按位查找（从1开始）
template<class T>
T LinkList<T>::getItem(int i)
{
    if (i > this->getLength() || i < 0)
    {
        std::cout << "您的查找越界了";
        return OUTSIZE;
    }
    LNode<T>* p = this->head;
    for (int j = 0; j < i; j++)
    {
        p = p->NEXT;
    }

    return p->data;
}

//按值查找
template<class T>
int LinkList<T>::locate(T x)
{
    int index = 0;
    LNode<T> * p = head->NEXT;
    while (p)
    {
        index++;
        if (p->data == x)
        {
            return index;
        }
        p = p->NEXT;
    }
    return OUTSIZE;
}

//在第i个位置插入x
template<class T>
inline void LinkList<T>::insert(int i, T x)
{
    if (i > this->length + 1 || i <= 0)
    {
        return;
    }
    LNode<T>* p = this->head;
    for (int j = 1; j < i; j++)
    {
        p = p->NEXT;
    }
    
    LNode<T>* q = new LNode<T>;
    q->data = x;
    q->NEXT = p->NEXT;
    
    p->NEXT = q;

    this->length++;
}


