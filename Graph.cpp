#include <iostream>
#include <queue>
using namespace std;
template <class T>
struct Node {
	T inf;
	Node<T>* next;
	Node(T _inf, Node<T>* _next) :inf(_inf), next(_next) {}
};
template <class T>
class LList {
	Node<T>* start;
	Node<T>* current;
	Node<T>* end;
	void copyList(const LList<T>&other) {
		start = current = end = NULL;
		Node<T>*p = other.start;
		while (p) {
			toEnd(p->inf);
			p = p->next;
		}
	}
	void deleteList() {
		Node<T>*p;
		while (start) {
			p = start;
			start = start->next;
			delete p;
		}
		end = NULL;
	}
public:
	LList() {
		start = end = NULL;
	}
	~LList() {
		deleteList();
	}
	LList(const LList<T>&other) {
		copyList(other);
	}
	LList<T>&operator=(const LList<T>&other) {
		if (this != &other) {
			deleteList();
			copyList(other);
		}
		return *this;
	}
	void toEnd(const T&x) {
		Node<T>* p = end;
		end = new Node < T >(x, NULL);
		if (p) p->next = end;
		else start = end;
	}
	void iterStart(Node<T>*p) {
		if (p) current = p;
		else current = start;
	}
	Node<T>* iter() {
		Node<T>*p = current;
		if (current) current = current->next;
		return p;
	}
	bool empty() const {
		return start == NULL;
	}
	void print() const {
		Node<T>*p = start;
		while (p) {
			cout << p->inf << " ";
			p = p->next;
		}
		cout << endl;
	}
	int length() const {
		int size = 0;
		Node<T>*p = start;
		while (p) {
			size++;
			p = p->next;
		}
		return size;
	}
	void deleteAfter(Node<T>* p, T& x)
	{
		if (p->link)
		{
			Node<T>* q = p->link;
			x = q->inf;
			p->link = q->link;
			if (q == end) end = p;
			delete q;
		}
		else
		{
			cout << "There is not an element after p.\n";
			exit(1);
		}
	}
	void deleteElem(Node<T>* p, T& x)
	{
		if (p == start)
		{
			x = p->inf;
			if (start == end)
			{
				start = end = NULL;
			}
			else start = start->link;
			delete p;
		}
		else
		{
			Node<T>* q = start;
			while (q->link != p) q = q->link;
			deleteAfter(q, x);
		}
	}
};


template <class T>
class Graph
{
	LList<LList<T>> graph;
public:
	void addVertex(T& vertex)
	{
		LList<T> newVertex;
		newVertex.toEnd(vertex);
		graph.toEnd(newVertex);
	}
	void deleteEdge(T& vert1, T& vert2)
	{
		graph.iterStart();
		Node<LList<T>>* p;
		Node<T>* q;
		do
		{
			p = graph.iter();
			p->inf.iterStart();
			q = p->inf.iter();
		} while (q->inf != vert1);
		q = q->next;
		while (q->inf != vert2)
		{
			q = q->next;
		}
		T elem;
		p->inf.deleteElem(q, elem);
	}
	void deleteVertex(T& vertex)
	{
		graph.iterStart();
		Node<LList<T>>* p = graph.iter();
		Node<LList<T>>* r;
		while (p)
		{
			p->inf.iterStart();
			Node<T>* q = p->inf.iter();
			if (isEdge(q->inf, vertex))
			{
				deleteEdge(q->inf, vertex);
			}
			p = p->next;
		}
		graph.iterStart();
		Node<T>* q;
		do
		{
			r = graph.iter();
			r->inf.iterStart();
			q = r->inf.iter();
		} while (q->inf != vertex);
		LList<T> elem;
		graph.deleteElem(r, elem);
	}
	bool isVertex(T& vert1)
	{
		graph.iterStart();
		Node<LList<T>>*p = graph.iter();
		while (p) {
			p->inf.iterStart();
			Node<T>*q = p->inf.iter();
			if (q->inf == vert1)
			{
				return true;
			}
			else
			{
				p = p->next;
			}
		}
		return false;
	}
	bool isEdge(T& vert1, T& vert2)
	{
		Node<T>* p = point(vert1);
		p = p->next;
		while (p && p->inf != vert2)
		{
			p = p->next;
		}
		return p != NULL;
	}
	Node<T>* point(T& a)
	{
		graph.iterStart();
		Node<LList<T>>* p;
		Node<T>* q;
		do
		{
			p = graph.iter();
			p->inf.iterStart();
			q = p->inf.iter();
		} while (q->inf != a);
		return q;
	}
	void addEdge(T vert1, T vert2)
	{
		if (!isVertex(vert1) && !isVertex(vert2))
		{
			addVertex(vert1);
			addVertex(vert2);
		}
		Node<T>* p;
		Node<T>* q = point(vert1);
		//p = new Node<T>;
		p->inf = vert2;
		p->next = q->next;
		q->next = p;
	}
	bool empty() const
	{
		return graph.empty();
	}
	LList<T> vertexes()
	{
		LList<T> l;
		graph.iterStart();
		Node<LList<T>>* p = graph.iter();
		while (p)
		{
			p->inf.iterStart();
			Node<T>* q = p->inf.iter();
			l.toEnd(q->inf);
			p = p->next;
		}
		return l;
	}
	void print()
	{
		graph.iterStart();
		Node<LList<T>>* p = graph.iter();
		while (p)
		{
			p->inf.print();
			p = p->next;
		}
		cout << endl;
	}
	void bfs(T vertex)
	{
		LList<T> visited;
		queue<T> q;
		q.push(vertex);
		visited.toEnd(vertex);
		while (!q.empty())
		{
			cout << q.front() << " ";
			Node<T>* start = point(q.front());
			start = start->next;
			while (start)
			{
				if (!member(visited, start->inf))
				{
					q.push(start->inf);
					visited.toEnd(start->inf);
				}
			}
			q.pop();
		}

	}

};
template<typename T>
bool member(LList<T>& l, T& elem)
{
	l.iterStart();
	Node<T>* p = l.iter();
	while (p)
	{
		if (p->inf == elem)
		{
			return true;
		}
		p = p->next;
	}
	return false;
}


int main()
{
	Graph<int> g;
	g.addRib(1, 2);
	g.addRib(1, 3);
	g.addRib(1, 4);
	g.addRib(2, 3);
	g.addRib(2, 5);
	g.bfs(1);
	system("pause");
	return 0;
}
