#pragma once
#include <iostream>

template<class T>
class LNode
{
public:
	T data;
	LNode<T>* NEXT;
};

template<class T>
class LinkList
{
public:
	//无参构造，建立一个带头结点空单链表
	LinkList();
	//有参构造，建立长度为n的单链表
	//mode==0为头插法，mode==1为尾插法
	LinkList(T a[], int n, bool mode);
	//析构函数
	~LinkList();
	//遍历单链表
	void forEachList();
private:
	LNode<T>* head = nullptr;
};

//无参构造，建立一个空单链表(空头结点)
template<typename T>
LinkList<T>::LinkList()
{
	this->head = new LNode<T>;
	this->head->NEXT = nullptr;
	this->head->data = NULL;
}


//有参构造，建立长度为n的单链表
//mode==0为头插法，mode==1为尾插法
template<class T>
LinkList<T>::LinkList(T a[], int n, bool mode)
{
	if (n <= 0)
	{
		std::exit(1);
	}

	this->head = new LNode<T>;
	this->head->NEXT = nullptr;

	LNode<T>* p;
	p = this->head;

	if (mode == false)
		//头插法
	{
		q = new LNode<T>;
		q->data = a[i];
		q->NEXT = this->head->NEXT;
		this->head->NEXT = q;
	}
	else
		//尾插法
	{
		for (int i = 0; i < n; i++)
		{
			q = new LNode<T>;
			q->data = a[i];
			q->NEXT = nullptr;
			p->NEXT = q;
			p = p->NEXT;
		}
	}
}

//析构函数
template<typename T>
inline LinkList<T>::~LinkList()
{
	LNode<T>* p;
	p = this->head;
	while (p)
	{
		LNode<T>* q;
		q = p;
		p = p->NEXT;
		delete q;
	}
}

//遍历单链表
template<class T>
inline void LinkList<T>::forEachList()
{
	LNode<T>* p = this->head;
	while (p)
	{
		std::cout << p->data << std::endl;
		p = p->NEXT;
	}
}
