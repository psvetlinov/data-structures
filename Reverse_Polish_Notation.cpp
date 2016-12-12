#include <iostream>
#include <string>
#include <stack>
using namespace std;

int checkPriority(char s)
{
	switch (s)
	{
	case '+':return 1;break;
	case '-':return 1;break;
	case '*': return 2;break;
	case '/': return 2;break;
	case '^':return 3;break;
	default:return -1;
	}
}

const char* reverseRec(char* str)
{
	char* reverse=new char[strlen(str)+1];
	stack<char> stack;
	int i = 0;
	int j = 0;
	int sizeStr = strlen(str);
	while (i < sizeStr)
	{
		if (str[i] >= '0' && str[i] <= '9') reverse[j++] = str[i];
		else if (str[i] == '(') stack.push(str[i]);
		else if (str[i] == ')')
		{
			while (stack.top() != '(')
			{
				reverse[j++] = stack.top();
				stack.pop();
			}
			stack.pop();
		}
		else
		{
			while (!stack.empty() && checkPriority(stack.top()) >= checkPriority(str[i]))
			{
				reverse[j++] = stack.top();
				stack.pop();
			}
			stack.push(str[i]);
		}
		i++;
	}
	while (!stack.empty())
	{
		reverse[j++] = stack.top();
		stack.pop();
	}
	reverse[j] = '\0';
	return reverse;
}

int RevPolRecordValue(const char* str)
{
	stack<int> st;
	int i = 0;
	int first, second;
	while (i < strlen(str))
	{
		if (str[i] >= '0' && str[i] <= '9') st.push(str[i] - '0');
		else {
			second = st.top();
			st.pop();
			first = st.top();
			st.pop();
			switch (str[i])
			{
			case'+':st.push(first + second);break;
			case '-':st.push(first - second);break;
			case '*':st.push(first * second);break;
			case '/':st.push(first / second);break;
			case '^':st.push(pow(first, second));break;
			}
		}
		i++;
	}
	return st.top();
}

//simple tests
int main()
{
	cout<<reverseRec("(6+3*2)")<<endl;
	cout<<RevPolRecordValue(reverseRec("(6+3*2)"))<<endl;
	system("pause");
	return 0;
}
