#pragma once
#include"../../src/SqList/SqList.hpp"
#include"../../src/LinkList/LinkList.hpp"
#include"../../src/LinkList/doubleLinkList.hpp"
#include"../../src/stack/stack.hpp"
#include"../../src/stack/LStack.hpp"
#include"../../src/Queue/CQueue.hpp"
#include"../../src/stack/bracketCheck.h"

//顺序表测试函数
int SqListTest();
//单链表测试函数
int LinkListTest();
//双链表测试函数
int doubleLinkListTest();
//栈测试函数
int stackTest();
//链栈测试函数
int LStackTest();
//循环队列测试函数
int CQueueTest();
//测试括号检测函数
int bracketCheckTest();

//打印字符串
void printStr(char str[], int length);
