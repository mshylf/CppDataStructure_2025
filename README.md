# 使用C++及模板技术实现各种数据结构类型
GitHub仓库地址：https://github.com/mshylf/CppDataStructure_2025

国内镜像仓库地址：https://gitcode.com/2404_89567743/CppDataStructure_2025

本项目使用visual studio 2022创建C++项目实现各种数据结构类型，为个人学习记录使用，若发现错误烦请及时指正。

## 已更新：
- 顺序表
- 单链表
- 双链表
- 顺序栈
- 链栈
- 循环队列

## 文件结构及功能描述

```plaintext
CppDataStructure_2025
├── main.cpp
├── .gitattributes
├── .gitignore
├── CppDataStructure_2025.sln
├── CppDataStructure_2025.vcxproj
├── CppDataStructure_2025.vcxproj.filters
├── src
│   ├── LinkList
│   │   ├── LinkList.hpp
│   │   └── doubleLinkList.hpp
│   ├── SqList
│   │   └── SqList.hpp
│   ├── test
│   │  ├── test.h
│   │  └── test.cpp
│   ├── stack
│   │   ├── stack.hpp
│   │   └── LStack.hpp
│   ├── Queue
│       └── CQueue.hpp
```

| 文件 | 功能描述 |
|:-:|:-:|
| main.cpp | 主函数 |
| .gitattributes | .gitattributes允许指定由 git 使用的文件和路径的属性 |
| .gitignore | 在git中忽略文件和文件夹 |
| CppDataStructure_2025.sln | 解决方案文件 |
| CppDataStructure_2025.vcxproj | 项目文件，记录项目相关的属性配置 |
| CppDataStructure_2025.vcxproj.filters | 项目文件过滤器 |
|src|代码实现文件夹|

|src文件子目录|文件名|功能描述|
|:-:|:-:|:-:|
|LinkList|LinkList.hpp|单链表实现|
||doubleLinkList.hpp|双链表实现|
|SqList|SqList.hpp|顺序表实现|
|test|test.h|测试文件头文件|
||test.cpp|测试文件实现代码|
|stack|stack.hpp|顺序栈实现|
||LStack.hpp|链栈实现|
|Queue|CQueue.hpp|循环队列实现|
