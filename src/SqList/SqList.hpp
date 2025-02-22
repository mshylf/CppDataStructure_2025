#pragma once
#include <iostream>
constexpr auto MaxSize = 10;

template<class T>
class SqList
{
public:

	//无参构造一个空顺序表
	SqList();
	//有参构造一个长度为n的空顺序表
	SqList(T a[], int n);
	//析构函数释放顺序表内存
	~SqList();
	//返回data总大小
	int SizeofData();
	//求顺序表的长度	
	int GetLength();
	//查找第i个元素(从零开始)并返回该元素	
	bool GetItem(int i, T& e);
	//查找值为x的元素并返回其位置	
	int locate(T x);
	//在第i个位置插入值为x的元素
	void insert(int i, T X);
	//删除第i个位置的元素,并将其通过&e带出函数
	bool remove(int i, T& e);
	//遍历顺序表
	void forEach();
	//判断顺序表是否为空
	bool empty();
private:
	T* data;
	//存放数据的数组
	int length;
	//记录顺序表中存储的元素个数
};

template<typename T>
//无参构造建立一个空的顺序表
SqList<T>::SqList() :length(0)
{
	this->data = new T[MaxSize];
}

template<typename T>
//有参构造建立一个长度为n，内容为a[]的数组
SqList<T>::SqList(T a[], int n) :length(0)
{
	//若n>MaxSize,则将顺序表扩大为MaxSize*(n/MaxSize+1)
	//否则其大小为MaxSize
	if (n > MaxSize)
	{
		int i = n / MaxSize;
		this->data = new T[MaxSize * (i + 1)];
	}
	else
	{
		this->data = new T[MaxSize];
	}
	for (int i = 0; i < n; i++)
	{
		data[i] = a[i];
		length++;
	}
}

template<typename T>
//返回data总大小
int SqList<T>::SizeofData()
{

	return sizeof(T) * this->length;
}

template<typename T>
//析构函数释放顺序表内存
SqList<T>::~SqList()
{
	delete[] this->data;
	this->data = nullptr;
}

template<typename T>
//返回长度
int SqList<T>::GetLength()
{
	return this->length;
}

template<typename T>
//按位查找，返回第i位的元素
//使用引用将元素带出,返回值使用情况返回较好
//若返回值为元素,则不好判断是否越界(越界不能返回模板,只能抛出异常)
bool SqList<T>::GetItem(int i, T& e)
{
	if (i >= this->length || i < 0)
	{
		std::cout << "您访问的位置越界" << std::endl;
		return false;
	}
	e = this->data[i];
	return true;
}

template<typename T>
//查找值为x的元素并返回其位置
int SqList<T>::locate(T x)
{
	for (int i = 0; i < this->length; i++)
	{
		if (this->data[i] == x)
		{
			return i;
		}
	}
	std::cout << "不存在该元素" << std::endl;
	return -1;
}

template<typename T>
//在第i个位置插入值为x的元素
void SqList<T>::insert(int i, T x)
{
	//判断顺序表大小是否正确,若小了则多分配MaxSize的长度
	int j = this->SizeofData() / sizeof(T) / MaxSize;
	if (this->length + 1 > j * MaxSize)
	{
		T* tempData = new T[MaxSize * (j + 1)];
		for (int k = 0; k < this->length; k++)
		{
			tempData[k] = this->data[k];
		}
		delete[] this->data;
		this->data = tempData;
	}
	if (i < 0)
	{
		std::cout << "输入了越界的i值" << std::endl;
		return;
	}
	//将插入位置的后的元素后移
	for (int k = length; k > i; k--)
	{
		data[k] = data[k - 1];
	}
	data[i] = x;
	this->length++;
}

template<typename T>
//删除第i个位置的元素,并将其通过&e带出函数
bool SqList<T>::remove(int i, T& e)
{
	if (i < 0 || i >= this->length)
	{
		std::cout << "您的输入越界" << std::endl;
		e = T();
		return false;
	}
	e = this->data[i];
	for (int j = i; j < length - 1; j++)
	{
		this->data[j] = this->data[j + 1];
	}
	this->length = this->length - 1;
	return true;
}

template<typename T>
//遍历顺序表
inline void SqList<T>::forEach()
{
	std::cout << "元素遍历如下:" << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->data[i] << std::endl;
	}
}

template<typename T>
//判断是否为空
inline bool SqList<T>::empty()
{
	if (this->length)
		return false;
	else
		return true;
}
