#pragma once
#include <iostream>
#include <stdexcept>

class myString
{
public:
    // 构造函数
    myString();
    // 析构函数
    ~myString();
    // 赋值操作，将当前串赋值为 chars
    void strAssign(char* chars);
    //复制操作
	void strCopy(myString& str);
    // 获取字符串内容
    const char* getDate() const { return date; }

private:
    int MAXSIZE;
    char* date;
    int length;
};

inline myString::myString() : MAXSIZE(101), length(0)
{
    date = new(std::nothrow) char[this->MAXSIZE];
    if (!date)
    {
        throw std::runtime_error("内存申请失败");
    }
    this->date[0] = '\0'; // 使用 '\0' 表示字符串结束符
}

inline myString::~myString()
{
    delete[] this->date;
}

inline void myString::strAssign(char* chars)
{
    int i = 0;
    while (chars[i] != '\0')
    {
        // 重新分配内存
        if (this->length + 1 >= this->MAXSIZE)
        {
            this->MAXSIZE += 100;
            char* temp = new(std::nothrow) char[this->MAXSIZE];
            if (!temp)
            {
                throw std::runtime_error("内存扩充失败");
            }
            for (int j = 0; j < this->length; j++)
            {
                temp[j] = this->date[j];
            }
            delete[] this->date;
            this->date = temp;
        }
        // 从 1 开始
        this->date[this->length] = chars[i];
        this->length++;
        i++;
    }
    // 添加字符串末尾的空字符
    this->date[this->length] = '\0';
}

inline void myString::strCopy(myString& str)
{
}
