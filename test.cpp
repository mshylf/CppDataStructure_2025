#include"SqList.hpp"
#include"test.h"
using namespace std;

int SqListTest()
{
	cout << "你好" << endl;
	// 为有参构造准备条件
	int arr[] = {4, 5, 6, 7};
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
