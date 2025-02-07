#pragma once
#include <iostream>

//双链表普通节点
template<class T>
class DNode
{
public:
	DNode<T>* prior;
	T data;
	DNode<T>* next;
};

//头节点
template<class T>
class dLinkList
{
private:
	int length;
	DNode<T>* head;
public:
	//无参构造
	dLinkList();
	//析构函数
	~dLinkList();
	//第i个位置插入数据e
	void insert(int i, T e);
	//遍历函数
	void forEach();
	//删除结点，并返回被删除元素数据值
	T remove(int i);
};

//无参构造
template<class T>
inline dLinkList<T>::dLinkList()
{
	this->length = 0;
	this->head = new DNode<T>;
	this->head->prior = this->head;
	this->head->next = this->head;
	this->head->data = NULL;
}

//析构函数
template<class T>
inline dLinkList<T>::~dLinkList()
{
	DNode<T>* p = this->head->next;
	while (p != this->head)
	{
		DNode<T>* q = p;
		p = p->next;
		delete q;
	}
	delete this->head;
}
//插入
template<class T>
inline void dLinkList<T>::insert(int i, T e)
{
	if (i<1 || i>this->length + 1)
	{
		std::cout << "您的输入越界了" << std::endl;
		return;
	}
	//找到第i-1个位置进行插入
	DNode<T>* p = this->head;
	for (int j = 1; j < i; j++)
	{
		p = p->next;
	}

	DNode<T>* q = new DNode<T>;
	q->data = e;

	q->next = p->next;
	q->prior = p;
	p->next->prior = q;
	p->next = q;


	this->length++;
}

//遍历函数
template<class T>
inline void dLinkList<T>::forEach()
{
	if (this->head->next == this->head)
	{
		std::cout << "没有元素" << std::endl;
		return;
	}
	DNode<T>* p = this->head->next;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << p->data << std::endl;
		p = p->next;
	}
}

//删除函数
template<class T>
inline T dLinkList<T>::remove(int i)
{
	if (i<1 || i>this->length)
	{
		std::cout << "您的输入越界了" << std::endl;
		return NULL;
	}
	DNode<T>* p = this->head;
	//找到第i个元素并删除
	for (int j = 1; j <= i; j++)
	{
		p = p->next;
	}

	p->prior->next = p->next;
	p->next->prior = p->prior;

	T temp = p->data;
	delete p;
	this->length--;
	return temp;
}
