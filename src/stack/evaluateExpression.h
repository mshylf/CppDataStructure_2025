#pragma once
#include<iostream>
#include"stack.hpp"
#include<unordered_map>

//后缀表达式求值，输入中数字之后需使用符号隔离，如"4#7#2#3#*-*26#5#8#+/+"
int evaluatePostfix(char str[]);

//中缀表达式转后缀表达式，并返回后缀表达式
std::string infixToPostfix(char str[]);

//比较运算符的优先级，若theta1>=theta2返回1，否则返回0
bool compareThe(char theta1,char theta2);
