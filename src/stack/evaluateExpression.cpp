#include "evaluateExpression.h" 


//后缀表达式求值，输入中操作数之后需使用符号隔离，如"4#7#2#3#*-*26#5#8#+/+"
int evaluatePostfix(char str[])
{
	//算法思想：
	//从左向右扫描字符串，遇到操作数则入栈，遇到算符则运算栈中最近两条数据并入栈

	Stack<int> S;

	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			//处理运算符
			int rightNum = S.pop();
			int leftNum = S.pop();
			int temp = 0;
			//将左右数数出栈，不能交换出栈顺序
			switch (str[i])
			{
			case '+':
			{
				temp = leftNum + rightNum;
				S.push(temp);
				break;
			}
			case '-':
			{
				temp = leftNum - rightNum;
				S.push(temp);
				break;
			}
			case '*':
			{
				temp = leftNum * rightNum;
				S.push(temp);
				break;
			}
			case '/':
			{
				if (!rightNum)
				{
					std::cout << "除数不能为0" << std::endl;
					throw "除数不能为0";
				}
				temp = leftNum / rightNum;
				S.push(temp);
				break;
			}
			default:
				break;
			}
			i++;
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			//处理操作数
			int d = 0;
			//设置进位
			while (str[i] >= '0' && str[i] <= '9')
			{
				d = d * 10 + (str[i] - '0');
				i++;
			}

			//操作数入栈
			S.push(d);
		}
		else
			i++;
	}

	return S.pop();
}

//中缀表达式转后缀表达式，并返回后缀表达式
std::string infixToPostfix(char str[])
{

	std::string str2;
	Stack<char> s;
	int i = 0;
	while (str[i] != '\0')
	{
		//处理操作符
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')')
		{
			//当前为')'时，依次出栈并输出至'('，最后出栈'('
			if (str[i] == ')')
			{
				while (s.getTop() != '(')
				{
					str2 += s.pop();
				}
				s.pop();
			}
			//当栈空或当前运算符优先级>栈顶元素优先级时，入栈
			else if (s.isEmpty() || !compareThe(str[i], s.getTop()))
			{
				s.push(str[i]);
			}
			//当前运算符优先级<=栈顶元素时，依次出栈并输出
			//直至栈空或当前元素优先级>栈顶元素或栈顶元素为'(',然后入栈
			else
			{
				while (!s.isEmpty() && compareThe(str[i], s.getTop()) && s.getTop() != '(')
				{
					str2 += s.pop();
				}
				s.push(str[i]);
			}
			i++;
		}
		else if (str[i] >= '0' && str[i] <= '9')
		{
			//处理操作数,直接输出，格式为‘1#21#’
			while (str[i] >= '0' && str[i] <= '9')
			{
				str2 += str[i];
				i++;
			}
			str2 += '#';
		}
		else
			i++;
	}

	//当所有元素扫描完成之后，将栈中的元素依次出栈并输出
	while (!s.isEmpty())
	{
		str2 += s.pop();
	}

	return str2;

	//算法原理
	// 1.从左向右扫描，左优先的后缀表达式操作数顺序与中缀表达式相同，故扫描到操作数将其输出即可
	// 2.利用栈实现对运算符（+,-,*,/）的管理，每个运算符的生效顺序不同，先生效的运算符先弹出
	// 3.若左边的运算符优先级<当前运算符或栈为空,则将当前运算符入栈，等待与其右边运算符比较
	// 4.当扫描到当前运算符时，若左边的运算符优先级>=当前运算符，
	//则左边的运算符先生效，故将其弹出，直到栈为空或者栈顶运算符优先级小于当前为止
	// 5.对'()'的处理：
	//  5.1 当扫描到'('时，应优先处理括号内内容，故直接将其入栈
	//  5.2 括号内扫描规则与上述2,3,4相同
	//  5.3 直到遇到')'时，将栈中运算符出栈，直到将'('弹出为止，最后删除'('
	//  5.4 在实际代码中可将'（'视为优先级最高的处理，简化代码
	// 6.扫描结束后，若栈中仍有运算符则将运算符全部出栈即可
}

//比较运算符的优先级，若theta1<=theta2返回1，否则返回0
bool compareThe(char theta1, char theta2)
{
	std::unordered_map<char, int> priority
	{
		{'+',1},{'-',1},{'*',2},{'/',2},{'(',3}
	};
	return priority[theta1] <= priority[theta2];
}
