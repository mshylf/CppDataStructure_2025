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
    myString(const myString& otherStr);
    // 拷贝赋值运算符
    myString& operator=(const myString& otherStr);
    // 析构函数
    ~myString();
    // 串联接，将其他串接到当前串中
    void strConcat(const char *chars);
    // 运算符重载
    myString& operator+=(const char* chars);
    // 获取当前字符串副本
    // 由于拷贝构造需要在const对象上调用该函数，因此将其定义为const成员函数
    char *getDate() const;
    // 判空操作
    bool strEmpty();
    // 获取长度
    int getLength();
    // 清空操作
    void clearStr();
    //求子串(给定位置长度)
    char *subString(int pos,int len);
    
private:
    int MAXSIZE;
    char *date;
    int length;
};

inline myString::myString() : MAXSIZE(100), length(0)
{
    this->date = new (std::nothrow) char[this->MAXSIZE];
    if (!date)
    {
        throw std::runtime_error("内存申请失败");
    }
    this->date[0] = '\0'; // 使用 '\0' 表示字符串结束符
}

inline myString::myString(const myString &otherStr)
{
    // 私有成员（private）的访问权限是 类级别 而非 对象级别
    // 同一个类的所有成员函数可以访问 任何同类对象 的私有成员
    this->MAXSIZE = otherStr.MAXSIZE;
    this->length = 0;
    this->date = new char[this->MAXSIZE];
    char * tempStr = otherStr.getDate();
    this->strConcat(tempStr);
    delete[] tempStr;
}

inline myString &myString::operator=(const myString &otherStr)
{
    //这里不需要重载!=，因为在此比较的是指针
    if (this != &otherStr) {
        delete[] this->date;
        this->MAXSIZE = otherStr.MAXSIZE;
        this->length = 0;
        this->date = new char[this->MAXSIZE];
        char * tempStr = otherStr.getDate();
        this->strConcat(tempStr);
        delete[] tempStr;
    }
    return *this;
}

inline myString::~myString()
{
    delete[] this->date;
}

inline void myString::strConcat(const char *chars)
{
    int i = 0;
    while (chars[i] != '\0')
    {
        // 重新分配内存
        if (this->length + 1 >= this->MAXSIZE)
        {
            this->MAXSIZE += 100;
            char *temp = new (std::nothrow) char[this->MAXSIZE];
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

inline myString &myString::operator+=(const char *chars)
{
    this->strConcat(chars);
    return *this;
}

inline char *myString::getDate() const
{
    char *new_date = new char[this->length + 1];
    for (int i = 0; i < this->length; i++)
    {
        new_date[i] = this->date[i];
    }
    new_date[this->length] = '\0';
    return new_date;
}

inline bool myString::strEmpty()
{
    return !this->length;
}

inline int myString::getLength()
{
    return this->length;
}

inline void myString::clearStr()
{
    this->length = 0;
    this->MAXSIZE = 100;
    delete[] this->date;
    this->date = new (std::nothrow) char[this->MAXSIZE];
    if (!date)
    {
        throw std::runtime_error("内存申请失败");
    }
}

inline char* myString::subString(int pos, int len)
{
    // 边界检查
    if (pos < 1 || pos > this->length)
    {
        throw std::out_of_range("起始位置无效");
    }
    if (len < 0 || pos + len - 1 > this->length)
    {
        throw std::out_of_range("子串长度无效");
    }

    // 分配足够的内存，包括 '\0'
    char* tempStr = new char[len + 1];
    int j = 0;
    for (int i = pos - 1; i < pos - 1 + len; i++)
    {
        tempStr[j] = this->date[i];
        j++;
    }
    tempStr[j] = '\0'; // 添加字符串结束符
    return tempStr;
}
