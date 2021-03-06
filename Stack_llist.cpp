#include <iostream>
#include <string>
using namespace std;

template<typename T>
struct Box
{
	Box<T>* next;
	T num;
};

template<typename T>
class Stack
{
	Box<T>* top;
	void copy(const Stack& other)
	{
		Box<T>* start = other.top;
		if (!other.empty()) {
			top = new Box<T>;
			Box<T>* temp = top;//pointer to top of new Stack
			top->num = start->num;//copying
			Box<T>* box;
			while (start->next != NULL)
			{
				start = start->next;//moving in otherStack
				box = new Box<T>;
				box->num = start->num;
				temp->next = box;
				temp = temp->next;
			}
		}
	}
	void del()
	{
		while(!empty())
		{
			pop();
		}
	}
public:
	Stack()
	{
		top = nullptr;
	}
	void push(T elem)
	{
		Box<T> temp = new Box<T>;
		temp.num = elem;
		temp.next = top;
		top = &temp;
	}
	void pop()
	{
		Box<T>* temp;
		temp = top;
		top = top->next;
		delete temp;
	}
	bool empty()
	{
		if (top == nullptr)
			return true;
		return false;
	}
	Stack(const Stack<T>& other)
	{
		copy(other);
	}
	~Stack()
	{
		del();
	}
	Stack<T>& operator=(const Stack<T>& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
};