#include <iostream>
using namespace std;

template <typename T>
struct Box
{
	int data;
	Box<T>* next;
};

template <typename T>
class Queue
{
	Box<T>* first;
	Box<T>* last;
	bool isEmpty;
	void copy(const Queue<T>& other)
	{
		first = nullptr;
		last = nullptr;
		Box<T>* temp = other.first;
		while (temp)
		{
			push(temp->data);
			temp = temp->next;
		}
	}
	void del()
	{
		T elem;
		while (pop(elem))
		{
		}
	}
public:
	Queue()
	{
		first = nullptr;
		last = nullptr;
		isEmpty = true;
	}
	bool empty()
	{
		return isEmpty;
	}
	bool full()
	{
		return !empty() && first == last;
	}

	void push(T elem)
	{
		if (empty())
		{
			Box<T>* temp = new Box<T>;
			temp->data = elem;
			first = last = temp;
		}
		else
		{
			Box<T>* temp = new Box<T>;
			temp->data = elem;
			last->next = temp;
			last = temp;
		}
	}
	bool pop(T& elem)
	{
		if (empty())
			return false;
		Box<T>* temp = first;
		first = first->next;
		delete temp;
		return true;
	}

	Queue(const Queue<T>& other)
	{
		copy(other);
	}

	~Queue()
	{
		del();
	}
	Queue<T>& operator=(const Queue<T>& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
};
