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
	//在第i个位置插入值为x的元素（按位插入）
	void insert(int i, T x);
	//在第一个数据为e的结点后插入值为x的元素
	void insertNextNode(T e, T x);
	//在第一个数据为e的结点前插入值为x的元素
	void insertPriorNode(T e, T x);
	//注意按值插入两者区别，在前插函数中使用了不同的插入逻辑

	//删除单链表的第i个元素并返回
	T remove(int j);
	//删除函数同样有按值删除结点前后的函数，与按值插入思想相似，不再赘述
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
	LNode<T>* p = head->NEXT;
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
	//找到第i-1个元素
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

//在第一个数据为e的结点后插入值为x的元素
template<class T>
inline void LinkList<T>::insertNextNode(T e, T x)
{
	LNode<T>* p = this->head;
	//找到第i个元素（数据为e）并在其后插入即可
	for (int i = 0; i < this->length; i++)
	{
		p = p->NEXT;
		if (p->data == e)
		{
			LNode<T>* q = new LNode<T>;
			q->data = x;
			q->NEXT = p->NEXT;
			p->NEXT = q;

			this->length++;
			return;
		}
		//输出错误信息
		if (i == this->length - 1)
		{
			std::cout << "没有您要查询的元素" << std::endl;
		}
	}
}

//在第一个数据为e的结点前插入值为x的元素
template<class T>
inline void LinkList<T>::insertPriorNode(T e, T x)
{
	LNode<T>* p = this->head;
	//假设原单链表中第i，i+1结点对应的数据分别为e,s ；待插入结点数据为x
	//则该函数在找到第i个元素（数据为e）后需要在其前面插入结点，又需要找到第i-1个结点向其后插入新结点，需要重新进行一次循环
	//我们可以找到一种方法将第二次查找的时间复杂度从O(n)降为O(1)
	//既：1、寻找到第i个元素后正常将新结点插入在其后，此时第i，i+1，i+2结点对应的数据分别为e，x，s
	// 2、仅需将第i，i+1结点的数据进行交换即可得到我们期望的效果：x，e，s
	for (int i = 0; i < this->length; i++)
	{
		p = p->NEXT;
		if (p->data == e)
		{
			LNode<T>* q = new LNode<T>;
			q->data = x;
			q->NEXT = p->NEXT;
			p->NEXT = q;

			q->data = p->data;
			p->data = x;
			this->length++;
			return;
		}
		//输出错误信息
		if (i == this->length - 1)
		{
			std::cout << "没有您要查询的元素" << std::endl;
		}
	}
}

//删除单链表的第i个元素并返回
template<class T>
inline T LinkList<T>::remove(int j)
{
	if (j > this->length || j < 0)
	{
		std::cout << "您的删除越界了";
		return T();
	}
	LNode<T>* p = this->head;
	//找到第j-1个元素（数据为e）并删除第j个元素
	for (int i = 1; i < j; i++)
	{
		p = p->NEXT;
	}
	LNode<T>* q = p->NEXT;
	T temp = q->data;
	p->NEXT = p->NEXT->NEXT;
	delete q;
	this->length--;

	return temp;
}

