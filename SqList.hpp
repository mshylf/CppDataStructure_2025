#pragma once
#include<iostream>
#define MaxSize 2

template<class T>
class SqList
{
public:
	//�޲ι���һ����˳���
	SqList();
	//�вι���һ������Ϊn�Ŀ�˳���
	SqList(T a[], int n);
	//���������ͷ�˳����ڴ�
	~SqList();
	//����data�ܴ�С
	int SizeofData();
	//��˳���ĳ���	
	int GetLength();
	//���ҵ�i��Ԫ��(���㿪ʼ)�����ظ�Ԫ��	
	bool GetItem(int i, T& e);
	//����ֵΪx��Ԫ�ز�������λ��	
	int locate(T x);
	//�ڵ�i��λ�ò���ֵΪx��Ԫ��
	void insert(int i, T X);
	//ɾ����i��λ�õ�Ԫ��,������ͨ��&e��������
	bool remove(int i, T& e);
	//����˳���
	void forEach();
	//�ж�˳����Ƿ�Ϊ��
	bool empty();
private:
	T* data;
	//������ݵ�����
	int length;
	//��¼˳����д洢��Ԫ�ظ���
};

template<typename T>
//�޲ι��콨��һ���յ�˳���
SqList<T>::SqList() :length(0)
{
	this->data = new T[MaxSize];
}

template<typename T>
//�вι��콨��һ������Ϊn������Ϊa[]������
SqList<T>::SqList(T a[], int n) :length(0)
{
	//��n>MaxSize,��˳�������ΪMaxSize*(n/MaxSize+1)
	//�������СΪMaxSize
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
//����data�ܴ�С
int SqList<T>::SizeofData()
{

	return sizeof(T) * this->length;
}

template<typename T>
//���������ͷ�˳����ڴ�
SqList<T>::~SqList()
{
	delete[] this->data;
	this->data = nullptr;
}

template<typename T>
//���س���
int SqList<T>::GetLength()
{
	return this->length;
}

template<typename T>
//��λ���ң����ص�iλ��Ԫ��
//ʹ�����ý�Ԫ�ش���,����ֵʹ��������ؽϺ�
//�����ֵΪԪ��,�򲻺��ж��Ƿ�Խ��(Խ�粻�ܷ���ģ��,ֻ���׳��쳣)
bool SqList<T>::GetItem(int i, T& e)
{
	if (i >= this->length || i < 0)
	{
		std::cout << "�����ʵ�λ��Խ��" << std::endl;
		return false;
	}
	e = this->data[i];
	return true;
}

template<typename T>
//����ֵΪx��Ԫ�ز�������λ��
int SqList<T>::locate(T x)
{
	for (int i = 0; i < this->length; i++)
	{
		if (this->data[i] == x)
		{
			return i;
		}
	}
	std::cout << "�����ڸ�Ԫ��" << std::endl;
	return -1;
}

template<typename T>
//�ڵ�i��λ�ò���ֵΪx��Ԫ��
void SqList<T>::insert(int i, T x)
{
	//�ж�˳����С�Ƿ���ȷ,��С��������MaxSize�ĳ���
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
		std::cout << "������Խ���iֵ" << std::endl;
		return;
	}
	//������λ�õĺ��Ԫ�غ���
	for (int k = length; k > i; k--)
	{
		data[k] = data[k - 1];
	}
	data[i] = x;
	this->length++;
}

template<typename T>
//ɾ����i��λ�õ�Ԫ��,������ͨ��&e��������
bool SqList<T>::remove(int i, T& e)
{
	if (i < 0 || i >= this->length)
	{
		std::cout << "��������Խ��" << std::endl;
		e = NULL;
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
//����˳���
inline void SqList<T>::forEach()
{
	std::cout << "Ԫ�ر�������:" << std::endl;
	for (int i = 0; i < this->length; i++)
	{
		std::cout << this->data[i] << std::endl;
	}
}

template<typename T>
//�ж��Ƿ�Ϊ��
inline bool SqList<T>::empty()
{
	if (this->length)
		return false;
	else
		return true;
}
