#pragma once
#include <iostream>
#include <stdexcept>

class myString
{
public:
    // 构造函数
    myString();
    // 拷贝构造函数
    // 避免无限递归，使用引用传入，若使用值传入会无限调用拷贝构造函数
    // 值传递时，otherStr会调用自生的拷贝构造函数来生成副本
    // 这时在被调用的拷贝构造函数中又会要求传入副本从而引起递归
    // 还需注意深浅拷贝问题
    myString(const myString &otherStr);
    // 拷贝赋值运算符
    myString &operator=(const myString &otherStr);
    // 移动构造函数，当前字符串直接接管对象字符串在堆区的内存
    // 参数中传入&&表示右值引用，并与拷贝构造函数形成区分
    myString(myString &&otherStr);
    // 移动赋值运算符
    myString &operator=(myString &&otherStr);
    // 析构函数
    ~myString();
    // 串联接，将其他串接到当前串之后
    void strConcat(const char *chars);
    // +=运算符重载
    myString &operator+=(const char *chars);
    // 获取当前字符串副本（堆区中，记得释放堆区内存）
    // 由于拷贝构造需要在const对象上调用该函数，因此将其定义为const成员函数
    char *getDate() const;
    // 判空操作
    bool strEmpty() const;
    // 获取长度
    int getLength() const;
    // 清空操作
    void clearStr();
    // 求子串(给定位置长度)
    char *subString(int pos, int len);
    // 比较串,相同返回1，否则返回0
    // 使用常量引用可以避免再调用拷贝构造函数创建一个副本而导致不必要的开销
    bool strCompare(const myString &otherStr) const;
    // 重载==运算符
    friend bool operator==(const myString& a, const myString& b);
    // 朴素模式匹配算法
    int strFind_normal(const char * chars);
    // 求kmp算法中next算法
    int *strFind_KMP_next_01(const char * chars);
    // 简单的KMP算法
    int strFind_KMP_01(const char*chars);

private:
    int MAXSIZE;
    char *data;
    int length;
};
