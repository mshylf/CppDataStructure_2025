#include <iostream>
#include <cstring> // 修复 strcmp 未声明的问题
#include "myString.hpp"
using namespace std;

// 测试函数
void testStrAssign(const char* testStr, const char* expectedOutput, int testNumber)
{
    try
    {
        myString str;
        str.strAssign(const_cast<char*>(testStr)); // 调用 strAssign
        cout << "Test " << testNumber << ": " << str.getDate() << endl;

        // 验证结果
        if (strcmp(str.getDate(), expectedOutput) == 0)
        {
            cout << "Result: Passed" << endl;
        }
        else
        {
            cout << "Result: Failed (Expected: " << expectedOutput << ", Got: " << str.getDate() << ")" << endl;
        }
    }
    catch (const exception& e)
    {
        cout << "Test " << testNumber << ": Exception occurred - " << e.what() << endl;
    }
}

int main_()
{
    // 测试用例 1：普通字符串
    testStrAssign("Hello, World!", "Hello, World!", 1);

    // 测试用例 2：空字符串
    testStrAssign("", "", 2);

    // 测试用例 3：超过初始容量的字符串
    testStrAssign("This is a very long string that exceeds the initial capacity of the myString class.",
                  "This is a very long string that exceeds the initial capacity of the myString class.", 3);

    // 测试用例 4：单字符字符串
    testStrAssign("A", "A", 4);

    // 测试用例 5：特殊字符
    testStrAssign("!@#$%^&*()", "!@#$%^&*()", 5);

    // 测试用例 6：包含空格的字符串
    testStrAssign("   Leading and trailing spaces   ", "   Leading and trailing spaces   ", 6);

    // 测试用例 7：非常长的字符串（超过初始容量多次）
    const char* longStr1 = "This is a very long string that will exceed the initial capacity of 101 characters. "
                           "It is designed to test the dynamic memory allocation of the myString class.";
    testStrAssign(longStr1, longStr1, 7);

    // 测试用例 8：更长的字符串（多次扩展内存）
    const char* longStr2 = "This is an even longer string that will require multiple memory reallocations. "
                           "It is designed to push the limits of the myString class and ensure that it can handle "
                           "very large strings without any issues. This string is intentionally made very long to "
                           "test the robustness of the memory allocation logic.";
    testStrAssign(longStr2, longStr2, 8);

    // 测试用例 9：极长字符串（极限测试）
    string extremeStr(10000, 'X'); // 创建一个包含 10000 个 'X' 的字符串
    testStrAssign(extremeStr.c_str(), extremeStr.c_str(), 9);

    return 0;
}
