#include <iostream>
#include <cstring>
#include <cassert>
#include <stdexcept>
#include "myString.h"
#include <vector>
using namespace std;

// 前向声明所有测试函数
void test_special_cases();
void test_constructors_extended();
void test_assignment_operators_extended();
void test_string_operations_extended();
void test_substring_edge_cases();
void test_comparison_operators_extended();
void test_memory_operations();

// 增强版验证函数
void verifyString(const myString& s, const char* expected, int line) {
    char* data = s.getDate();
    bool valid = (strcmp(data, expected) == 0);
    cout << "[" << (valid ? "✓" : "✗") << "] Line " << line 
         << " Expected: \"" << expected << "\", Got: \"" << data << "\"\n";
    assert(valid);
    delete[] data;
}

#define VERIFY(s, expected) verifyString(s, expected, __LINE__)

// 增强异常测试宏
#define TEST_EXCEPTION(expr, etype, msg) \
do { \
    try { \
        expr; \
        cerr << "[" << __LINE__ << "] Expected exception not thrown: " << msg << "\n"; \
        assert(false); \
    } \
    catch (const etype& e) { \
        cout << "[" << __LINE__ << "] ✓ Caught expected exception: " << e.what() << "\n"; \
    } \
    catch (...) { \
        cerr << "[" << __LINE__ << "] ✗ Wrong exception type thrown\n"; \
        assert(false); \
    } \
} while(0)

//=== 增强测试用例 ===//

void test_special_cases() {
    cout << "\n[ Special Cases Testing ]\n";
    
    // 空字符串测试
    myString empty;
    VERIFY(empty, "");
    assert(empty.getLength() == 0);
    assert(empty.strEmpty());

    // 单字符测试
    myString single;
    single += "A";
    VERIFY(single, "A");
    assert(single.getLength() == 1);
}

void test_constructors_extended() {
    cout << "\n[ Extended Constructor Tests ]\n";
    
    // 移动后对象状态验证
    myString src;
    src += "Source";
    myString moved(std::move(src));
    VERIFY(moved, "Source");
    assert(src.getLength() == 0);
    assert(src.strEmpty());

    // 自我移动测试
    myString self;
    self = std::move(self); // 应该无影响
    self += "Self";
    VERIFY(self, "Self");
}

void test_assignment_operators_extended() {
    cout << "\n[ Extended Assignment Tests ]\n";
    
    myString s1, s2;
    s1 += "Original";
    
    // 链式赋值测试
    myString s3;
    s3 = s2 = s1;
    VERIFY(s3, "Original");
    VERIFY(s2, "Original");

    // 自我赋值测试
    s1 = s1;
    VERIFY(s1, "Original");
}

void test_string_operations_extended() {
    cout << "\n[ Extended String Operations ]\n";
    
    // 多次拼接测试
    myString s;
    for(int i=0; i<10; i++) {
        s += to_string(i).c_str();
    }
    VERIFY(s, "0123456789");
    assert(s.getLength() == 10);

    // 清空后重用测试
    s.clearStr();
    VERIFY(s, "");
    s += "Reused";
    VERIFY(s, "Reused");

    // 混合操作测试
    myString complex;
    complex += "Start";
    complex += "";
    complex += "Middle";
    complex.clearStr();
    complex += "End";
    VERIFY(complex, "End");
}

void test_substring_edge_cases() {
    cout << "\n[ Substring Edge Cases ]\n";
    
    myString s;
    s += "ABCDE";
    
    // 合法边界测试
    char* sub1 = s.subString(1, 5);
    assert(strcmp(sub1, "ABCDE") == 0);
    delete[] sub1;
    
    char* sub2 = s.subString(3, 0);
    assert(strcmp(sub2, "") == 0);
    delete[] sub2;

    // 异常测试增强
    TEST_EXCEPTION(s.subString(-1, 2), std::out_of_range, "Negative position");
    TEST_EXCEPTION(s.subString(3, -5), std::out_of_range, "Negative length");
    TEST_EXCEPTION(s.subString(4, 10), std::out_of_range, "Overlength");
}

void test_comparison_operators_extended() {
    cout << "\n[ Extended Comparison Tests ]\n";
    
    myString a, b, c;
    a += "Apple";
    b += "Apple";
    c += "apple";
    
    assert(a == b);
    assert(!(a == c));
    
    // 不同长度比较
    myString shortStr;
    shortStr += "App";
    assert(!(a == shortStr));
}

void test_memory_operations() {
    cout << "\n[ Memory Operation Tests ]\n";
    
    // 大内存测试
    myString big;
    string large(10000, 'X');
    big += large.c_str();
    VERIFY(big, large.c_str());
    assert(big.getLength() == 10000);

    // 内存重用测试
    big.clearStr();
    big += "Small";
    VERIFY(big, "Small");
    assert(big.getLength() == 5);
}
// 在testString.cpp中添加以下内容

//=== KMP Next数组测试 ===//

// 数组比对辅助函数
void AssertNextArray(int* actual, const int* expected, int length) {
    for (int i = 0; i < length; ++i) {
        if (actual[i] != expected[i]) {
            cerr << "✗ Mismatch at index " << i 
                 << " Expected: " << expected[i]
                 << " Actual: " << actual[i] << endl;
            assert(false);
        }
    }
    cout << "✓ Next array matched\n";
}

void test_kmp_next() {
    cout << "\n[ KMP Next Array Tests ]\n";
    myString obj;

    // 测试用例组
    {
        cout << "-- Test Case 1: Repeated Pattern --\n";
        const char* input = "AAAAA";
        int expected[] = {-1, 0, 1, 2, 3};
        int* result = obj.strFind_KMP_next_01(input);
        AssertNextArray(result, expected, 5);
        delete[] result;
    }

    {
        cout << "-- Test Case 2: No Common Prefix --\n";
        const char* input = "ABCDE";
        int expected[] = {-1, 0, 0, 0, 0};
        int* result = obj.strFind_KMP_next_01(input);
        AssertNextArray(result, expected, 5);
        delete[] result;
    }

    {
        cout << "-- Test Case 3: Partial Overlap --\n";
        const char* input = "ABABA";
        int expected[] = {-1, 0, 0, 1, 2};
        int* result = obj.strFind_KMP_next_01(input);
        AssertNextArray(result, expected, 5);
        delete[] result;
    }

    {
        cout << "-- Test Case 4: Standard KMP Case --\n";
        const char* input = "ABCDABD";
        int expected[] = {-1, 0, 0, 0, 0, 1, 2};
        int* result = obj.strFind_KMP_next_01(input);
        AssertNextArray(result, expected, 7);
        delete[] result;
    }

    {
        cout << "-- Test Case 5: Previous Problem Case --\n";
        const char* input = "abaabc";
        int expected[] = {-1, 0, 0, 1, 1, 2};
        int* result = obj.strFind_KMP_next_01(input);
        AssertNextArray(result, expected, 6);
        delete[] result;
    }

    {
        cout << "-- Test Case 6: Edge Case (Single Char) --\n";
        const char* input = "A";
        int expected[] = {-1};
        int* result = obj.strFind_KMP_next_01(input);
        AssertNextArray(result, expected, 1);
        delete[] result;
    }

    {
        cout << "-- Test Case 7: Empty String --\n";
        const char* input = "";
        int* result = obj.strFind_KMP_next_01(input);
        assert(result == nullptr);
    }
}

//=== KMP搜索算法测试 ===//

void AssertKMPResult(myString& s, const char* pattern, int expected) {
    int result = s.strFind_KMP_01(pattern);
    cout << "Search '" << pattern << "' in '" << s.getDate() 
         << "' => Position: " << result 
         << " | Expected: " << expected << " ["
         << (result == expected ? "✓" : "✗") << "]\n";
    assert(result == expected);
}

void test_kmp_search() {
    cout << "\n[ KMP Search Algorithm Tests ]\n";
    myString s;

    // 基础测试组
    {
        cout << "-- Basic Pattern Matching --\n";
        s += "ABABABABCABAB";
        AssertKMPResult(s, "ABABC", 4);   // 中间匹配
        AssertKMPResult(s, "ABAB", 0);    // 开头重复匹配
        AssertKMPResult(s, "CABAB", 8);   // 尾部匹配
    }

    // 边界情况测试
    {
        cout << "\n-- Edge Cases --\n";
        myString edge;
        edge += "ABCDE";
        
        // 全串匹配
        AssertKMPResult(edge, "ABCDE", 0);
        // 单个字符匹配
        AssertKMPResult(edge, "C", 2);
        // 无匹配情况
        AssertKMPResult(edge, "XYZ", -1);
    }

    // 特殊模式测试
    {
        cout << "\n-- Special Patterns --\n";
        myString sp;
        sp += "AAAAAAA";
        
        AssertKMPResult(sp, "AAA", 0);    // 重复模式匹配
        AssertKMPResult(sp, "AAAAAA", 0); // 长重复模式
        AssertKMPResult(sp, "AAB", -1);   // 部分匹配失败
    }

    // 混合内容测试
    {
        cout << "\n-- Mixed Content --\n";
        myString mix;
        mix += "AB123CDAB234AB";
        
        AssertKMPResult(mix, "AB", 0);    // 多位置匹配取首个
        AssertKMPResult(mix, "AB234", 7); // 数字模式匹配
        AssertKMPResult(mix, "CDAB", 5);  // 混合字符匹配
    }

    // 异常情况测试
    {
        cout << "\n-- Exception Handling --\n";
        myString normal;
        normal += "NormalString";
        
        // 空模式测试
        TEST_EXCEPTION(
            normal.strFind_KMP_01(""), 
            std::invalid_argument, 
            "Null pattern"
        );
    }
}

//=== 增强版Next数组测试 ===//
void testEnhancedNextArray() {
    cout << "\n[ Enhanced Next Array Tests ]\n";
    myString s;

    // 测试用例结构体
    struct TestCase {
        const char* pattern;
        vector<int> expected;
        const char* description;
    };

    // 测试用例集合（修改后预期数组）
    vector<TestCase> testCases = {
        {"ababcabaa", {-1,0,0,1,2,0,1,2,3}, "Partial repeat with backtracking"},
        {"ABCDABD",   {-1,0,0,0,0,1,2},     "Standard KMP example"},
        {"AAAAAA",    {-1,0,1,2,3,4},       "All identical characters"},
        {"A",         {-1},                 "Single character"},
        {"ABABA",     {-1,0,0,1,2},         "Overlapping prefix pattern"},
        {"ABCABC",    {-1,0,0,0,1,2},       "Multiple partial matches"},
        {"ABAABAB",   {-1,0,0,1,1,2,3},     "Complex backtracking scenario"},
        {"abababa",   {-1,0,0,1,2,3,4},     "Progressive pattern growth"},
        {"",          {},                   "Empty pattern (should return nullptr)"}
    };

    for (const auto& tc : testCases) {
        cout << "\n-- Testing: " << tc.description << " (" << tc.pattern << ") --\n";
        
        int* actual = s.strFind_KMP_next_02(tc.pattern);
        
        // 处理空模式特殊情况
        if (strlen(tc.pattern) == 0) {
            if (actual != nullptr) {
                cerr << "✗ Expected nullptr for empty pattern\n";
                assert(false);
            }
            continue;
        }

        // 数组长度验证
        if (actual == nullptr) {
            cerr << "✗ Unexpected nullptr for non-empty pattern\n";
            assert(false);
        }

        // 逐元素对比
        bool allMatch = true;
        for (size_t i = 0; i < tc.expected.size(); ++i) {
            if (actual[i] != tc.expected[i]) {
                cerr << "  ✗ Mismatch at index " << i 
                     << "\n    Expected: " << tc.expected[i]
                     << "\n    Actual:   " << actual[i] << endl;
                allMatch = false;
            }
        }
        
        if (allMatch) {
            cout << "✓ All elements matched\n";
        } else {
            // 打印完整数组对比
            cout << "Expected: [";
            for (auto val : tc.expected) cout << val << " ";
            cout << "]\nActual:   [";
            for (size_t i = 0; i < tc.expected.size(); ++i) cout << actual[i] << " ";
            cout << "]\n";
            assert(false);
        }

        delete[] actual;
    }
}

int main() {

    // 新增测试组
    test_special_cases();
    test_constructors_extended();
    test_assignment_operators_extended();
    test_string_operations_extended();
    test_substring_edge_cases();
    test_comparison_operators_extended();
    test_memory_operations();
    test_kmp_next(); // 新增KMP测试
    test_kmp_next();    // 原有next数组测试
    test_kmp_search();  // 新增搜索测试
    testEnhancedNextArray();

    cout << "\n=== All enhanced tests passed! ===\n";
    return 0;
}