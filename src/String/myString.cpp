#include "myString.h"
myString::myString() : MAXSIZE(100), length(0)
{
    this->data = new (std::nothrow) char[this->MAXSIZE];
    if (!data)
    {
        throw std::runtime_error("内存申请失败");
    }
    this->data[0] = '\0'; // 使用 '\0' 表示字符串结束符
}

myString::myString(const myString &otherStr)
{
    // 私有成员（private）的访问权限是 类级别 而非 对象级别
    // 同一个类的所有成员函数可以访问 任何同类对象 的私有成员
    this->MAXSIZE = otherStr.MAXSIZE;
    this->length = 0;
    this->data = new char[this->MAXSIZE];
    char *tempStr = otherStr.getDate();
    this->strConcat(tempStr);
    delete[] tempStr;
}

// 返回对象的引用可以支持链式赋值
myString &myString::operator=(const myString &otherStr)
{
    // 这里不需要重载!=，因为在此比较的是指针
    if (this != &otherStr)
    {
        delete[] this->data;
        this->MAXSIZE = otherStr.MAXSIZE;
        this->length = 0;
        this->data = new char[this->MAXSIZE];
        char *tempStr = otherStr.getDate();
        this->strConcat(tempStr);
        delete[] tempStr;
    }
    return *this;
}

// 右值引用（Rvalue Reference）是 C++11 引入的特性，用 && 符号表示。
// 它专门用于绑定临时对象（右值），允许高效地"转移"资源而非复制。
myString::myString(myString &&otherStr) noexcept : MAXSIZE(otherStr.MAXSIZE), length(otherStr.length), data(otherStr.data)
{
    // 清空对象资源的所有权，防止双重释放（释放掉当前的data内存）
    otherStr.data = nullptr;
    otherStr.length = 0;
    otherStr.MAXSIZE = 0;
}

myString &myString::operator=(myString &&otherStr) noexcept
{
    if (this != &otherStr)
    {
        // 释放当前对象资源
        delete[] data;

        // 转移资源所有权
        this->data = otherStr.data; // 接管指针
        this->MAXSIZE = otherStr.MAXSIZE;
        this->length = otherStr.length;

        // 4. 置空原对象
        otherStr.data = nullptr; // 防止原对象析构时释放内存
        otherStr.MAXSIZE = 0;
        otherStr.length = 0;
    }
    return *this; // 5. 返回当前对象引用
}

myString::~myString()
{
    delete[] this->data;
}

void myString::strConcat(const char *chars)
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
                temp[j] = this->data[j];
            }
            delete[] this->data;
            this->data = temp;
        }
        // 从 1 开始
        this->data[this->length] = chars[i];
        this->length++;
        i++;
    }
    // 添加字符串末尾的空字符
    this->data[this->length] = '\0';
}

myString &myString::operator+=(const char *chars)
{
    this->strConcat(chars);
    return *this;
}

char *myString::getDate() const
{
    char *new_date = new char[this->length + 1];
    for (int i = 0; i < this->length; i++)
    {
        new_date[i] = this->data[i];
    }
    new_date[this->length] = '\0';
    return new_date;
}

bool myString::strEmpty() const
{
    return !this->length;
}

int myString::getLength() const
{
    return this->length;
}

void myString::clearStr()
{
    this->length = 0;
    this->MAXSIZE = 100;
    delete[] this->data;
    this->data = new (std::nothrow) char[this->MAXSIZE];
    if (!data)
    {
        throw std::runtime_error("内存申请失败");
    }
}

char *myString::subString(int pos, int len)
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
    char *tempStr = new char[len + 1];
    int j = 0;
    for (int i = pos - 1; i < pos - 1 + len; i++)
    {
        tempStr[j] = this->data[i];
        j++;
    }
    tempStr[j] = '\0'; // 添加字符串结束符
    return tempStr;
}

bool myString::strCompare(const myString &otherStr) const
{
    if (this->length != otherStr.length)
        return false;
    for (int i = 0; i < this->length; i++)
    {
        if (this->data[i] != otherStr.data[i])
            return false;
    }
    return true;
}

// 使用友元可以支持隐式转换
bool operator==(const myString &a, const myString &b)
{
    return a.strCompare(b);
}

int myString::strFind_normal(const char *chars)
{
    if (!chars || chars[0] == '\0' || !this->data)
    {
        return 0; // 约定空串匹配位置0
    }
    int chars_length = 0;
    while (chars[chars_length] != 0)
    {
        chars_length++;
    }
    if (chars_length > this->length)
    {
        return 0;
    }
    for (int i = 0; i < this->length - chars_length + 1; i++)
    {
        int k = i;
        for (int j = 0; j < chars_length; j++, k++)
        {
            if (this->data[i] != chars[j])
                break;
        }
        if (k - i == chars_length)
        {
            return i + 1;
        }
    }
    return 0;
}

int *myString::strFind_KMP_next_01(const char *chars)
{
    int chars_length = 0, i = 0;
    while (chars[chars_length] != '\0')
        chars_length++;

    int *next = new int[chars_length];

    if (chars_length == 0 || chars[0] == '\0')
        return nullptr;
    if (chars_length == 1)
    {
        next[0] = -1;
        return next;
    }

    next[0] = -1;
    next[1] = 0;
    for (int i = 2; i < chars_length; i++)
    {
        int k = 1, j = 0;
        while (k < i)
        {
            if (chars[k] != chars[j])
            {
                if (j)
                    j = next[j];
                else
                    k++;
            }
            else if (chars[k] == chars[j])
            {
                k++;
                j++;
            }
        }
        // if k==i
        next[i] = j;
    }
    return next;
}

int myString::strFind_KMP_01(const char *chars)
{
    int index = -1;
    int *next = this->strFind_KMP_next_01(chars);
    if (chars == nullptr || next == nullptr)
    {
        throw std::invalid_argument("Null pattern");
    }
    int chars_length = 0;
    while (chars[chars_length] != '\0')
        chars_length++;

    int j = 0, i = 0;
    while (i < this->length && j < chars_length)
    {
        if (j == -1 || chars[j] == this->data[i])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == chars_length)
    {
        index = i - chars_length;
    }

    delete[] next;
    return index;
}