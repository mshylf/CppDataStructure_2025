#pragma once
#include <iostream>

//顺序存储结构实现循环队列
#define MAXSIZE 3

template<class T>
class CQueue {
public:
	//无参构造
	CQueue();
	//析构函数
	~CQueue();
	//入队
	void enCQueue(T x);
	//出队,并返回出队元素
	T deCQueue();
	//遍历队列
	void forEach();
	//取对头元素
	T getCQueue();

private:
	//队尾指针
	int rare;
	//对头指针
	int fornt;
	//存放数据元素	
	T data[MAXSIZE];
};

//无参构造
template<class T>
inline CQueue<T>::CQueue()
{
	this->rare = this->fornt = 0;
}

template<class T>
inline CQueue<T>::~CQueue() {}

//入队
template<class T>
inline void CQueue<T>::enCQueue(T x)
{
	//判满
	if (this->fornt == (this->rare + 1) % MAXSIZE)
	{
		std::cout << "队列已满" << std::endl;
		return;
	}
	this->data[this->rare] = x;
	this->rare = (++this->rare) % MAXSIZE;
}

//出队,并返回出队元素
template<class T>
inline T CQueue<T>::deCQueue()
{
	if (this->fornt == this->rare)
	{
		std::cout << "队列为空" << std::endl;
		return T();
	}
	T temp = this->data[this->fornt];
	this->fornt = (++this->fornt) % MAXSIZE;
	return temp;
}

//遍历
template<class T>
inline void CQueue<T>::forEach()
{
	if (this->fornt == this->rare)
	{
		std::cout << "队列为空" << std::endl;
		return;
	}
	int i = this->fornt;
	while (i != this->rare)
	{
		std::cout << this->data[i] << std::endl;
		i = (++i) % MAXSIZE;
	}
}

//取对头元素
template<class T>
inline T CQueue<T>::getCQueue()
{
	if (this->fornt == this->rare)
	{
		std::cout << "队列为空" << std::endl;
		return T();
	}
	return this->data[this->fornt];
}
