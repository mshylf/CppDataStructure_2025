#include "bracketCheck.h"

bool bracketCheck(char str[], int length)
{
	Stack<char> S;

	for (int i = 0; i < length; i++)
	{
		//扫描到左括号入栈
		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
		{
			S.push(str[i]);
		}
		//扫描到右括号对比
		else if (str[i] == ')' || str[i] == '}' || str[i] == ']')
		{
			//若栈空，匹配失败
			if (S.isEmpty())
				return false;

			char leftTemp = S.pop();
			if (leftTemp == '(')
			{
				if (str[i] != ')')
					return false;
			}
			else if (leftTemp == '{')
			{
				if (str[i] != '}')
					return false;
			}
			else if (leftTemp == '[')
			{
				if (str[i] != ']')
					return false;
			}
		}
	}

	//最后判断若栈中仍有元素，则匹配失败
	if (S.isEmpty())
		return true;
	else
		return false;
}
