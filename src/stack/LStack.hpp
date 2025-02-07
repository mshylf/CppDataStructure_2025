#pragma once
#include <iostream>

//链栈实现

//定义链栈结点
template<class T>
class LSNode
{
public:
	T data;
	LSNode<T>* next;
};

//定义链栈类，使用不带头结点的单链表实现
template<class T>
class LStack
{
public:
	//无参构造
	LStack();
	//析构函数
	~LStack();
	//入栈
	void push(T x);
	//出栈
	T pop();
	//遍历栈（栈顶->栈底）
	void forEach();
	//获取栈顶元素
	T getTop();
	//判断栈空
	bool isEmpty();

private:
	LSNode<T>* top;
};

//无参构造
template<class T>
inline LStack<T>::LStack()
{
	//使用不带头结点的单链表
	//在入栈时若判断为空指针则直接指向新建结点
	this->top = nullptr;
}

//析构函数
template<class T>
inline LStack<T>::~LStack()
{
	while (this->top)
	{
		LSNode<T>* p = this->top;
		this->top = this->top->next;
		delete p;
	}
}

//入栈
template<class T>
inline void LStack<T>::push(T x)
{
	if (this->top)
	{
		LSNode<T>* temp = new LSNode<T>;
		temp->data = x;
		temp->next = this->top;
		top = temp;
	}
	else
	{
		this->top = new LSNode<T>;
		this->top->data = x;
		this->top->next = nullptr;
	}

}

//出栈
template<class T>
inline T LStack<T>::pop()
{
	if (!this->top)
	{
		std::cout << "栈为空" << std::endl;
		return T();
	}
	else
	{
		LSNode<T>* p = this->top;
		this->top = p->next;
		T temp = p->data;
		delete p;
		return temp;
	}
}

//遍历栈
template<class T>
inline void LStack<T>::forEach()
{
	if (!this->top)
	{
		std::cout << "栈为空" << std::endl;
		return;
	}
	LSNode<T>* p = this->top;
	while (p)
	{
		std::cout << p->data << std::endl;
		p = p->next;
	}
}

//获取栈顶元素
template<class T>
inline T LStack<T>::getTop()
{
	return this->top->data;
}

//判断栈空
template<class T>
inline bool LStack<T>::isEmpty()
{
	if (this->top)
	{
		return false;
	}
	else
	{
		return true;
	}
}
