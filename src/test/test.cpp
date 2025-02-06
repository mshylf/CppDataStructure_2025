#include"../../src/SqList/SqList.hpp"
#include"../../src/LinkList/LinkList.hpp"
#include"test.h"
using namespace std;

//顺序表测试函数
int SqListTest()
{
	// 为有参构造准备条件
	int arr[] = { 4, 5, 6, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);

	// 有参构造顺序表
	SqList<int> SQ1(arr, n);

	// 测试插入函数
	SQ1.insert(0, 1);
	SQ1.insert(1, 2);
	SQ1.insert(2, 3);

	// 总大小
	cout << "元素个数为:" << SQ1.GetLength() << endl;
	cout << "顺序表大小为:" << SQ1.SizeofData() << "字节" << endl;
	std::cout << "共有" << SQ1.GetLength() / MaxSize << "个MaxSize块," << "每个MaxSize块长度为" << MaxSize << std::endl
		<< endl;

	// 测试GetItem(int i, T &e)函数
	// 超出范围测试
	for (int i = -1; i < SQ1.GetLength() + 1; i++)
	{
		int tempE = 0;
		if (SQ1.GetItem(i, tempE))
		{
			cout << "第" << i << "个位置上为" << tempE << "元素" << endl;
		}
	}
	cout << endl;

	// 测试locate(int i)函数
	// 不存在元素测试
	for (int i = 0; i < SQ1.GetLength() + 1; i++)
	{
		int j = SQ1.locate(i);
		if (j != -1)
		{
			cout << "元素" << i << "在第" << j << "个位置" << endl;
		}
	}
	cout << endl;

	// 测试remove及foreach函数
	int temp, i = 6;
	if (SQ1.remove(i, temp))
	{
		cout << "移除了第" << i << "个位置的元素" << temp << endl;
	}
	SQ1.forEach();

	return 0;
}

//单链表测试函数
int LinkListTest()
{
	//无参构造测试
	LinkList<int> temp1;
	//insert(int i, T x)测试
	temp1.insert(1, 1);
	temp1.insert(1, 0);
	temp1.insert(3, 2);
	cout << "无参函数与插入函数检测：" << endl;
	temp1.forEachList();
	cout << endl;

	//有参函数构造
	int arr[] = { 4, 5, 6, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	//头插法
	LinkList<int> temp_0(arr, n, 0);
	//尾插法
	LinkList<int> temp_1(arr, n, 1);

	cout << "有参构造头插法" << endl;
	temp_0.forEachList();
	cout << endl;
	cout << "有参构造尾插法" << endl;
	temp_1.forEachList();
	cout << endl;
	cout << "测试按位查找头插法第2个输出：" << temp_0.getItem(2) << endl;
	cout << "测试按位查找尾插法第2个输出：" << temp_1.getItem(2) << endl;
	cout << "按位查找越界测试:" << temp_1.getItem(8) << endl;
	cout << endl;
	cout << "测试按值查找头插法第2个输出：" << temp_0.locate(4) << endl;
	cout << "测试按值查找尾插法第2个输出：" << temp_1.locate(4) << endl;
	cout << "按值查找越界测试: " << temp_1.locate(0) << endl;
	cout << endl;

	//insertNextNode(T e, T x)在第一个数据为e的结点后插入值为x的元素测试
	temp1.insertNextNode(0, 0);
	temp1.insertNextNode(2, 4);
	temp1.forEachList();
	//失败情况测试
	temp1.insertNextNode(3, 2);
	cout << endl;

	//insertNextNode(T e, T x)在第一个数据为e的结点前插入值为x的元素测试
	temp1.insertPriorNode(0, 0);
	temp1.insertPriorNode(4, 3);
	temp1.forEachList();
	//失败情况测试
	temp1.insertNextNode(5, 2);
	cout << endl;

	//测试删除函数
	cout << "删除了" << temp1.remove(1) << "元素" << endl;
	cout << "删除了" << temp1.remove(6) << "元素" << endl;
	temp1.forEachList();
	temp1.remove(7);
	return 0;
}
