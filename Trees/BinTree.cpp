#include <iostream>
#include <assert.h>
#include <string>
#include <queue>
#include <fstream>
using namespace std;

template <typename T>
using mapFn = T(*)(const T&);
template<typename ResT, typename ElemT>
using reduceFn = ResT(*)(ResT, ElemT);

template <typename T>
struct Node
{
	T inf;
	Node<T>* left;
	Node<T>* right;
	Node()
	{
		left = NULL;
		right = NULL;
	}
	Node(Node<T>* _l, Node<T>* _r, T _i) : left(_l), right(_r), inf(_i) {}
};

template <typename T>
class BinTree
{
	Node<T>* root;
	void copyHelp(Node<T>*& _root, Node<T>*& otherRoot)
	{
		if (otherRoot == NULL)
		{
			_root = NULL;
		}
		_root = new Node<T>;
		_root->inf = otherRoot->inf;
		copyHelp(_root->left, otherRoot->left);
		copyHelp(_root->right, otherRoot->right);
	}
	void copy(const BinTree<T>& other)
	{
		copyHelp(root, other.root);
	}
	void deleteHelp(Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return;
		}
		else
		{
			deleteHelp(_root->left);
			deleteHelp(_root->right);
			delete _root;
			_root = NULL;
		}
	}
	void del()
	{
		deleteHelp(root);
	}
	void addHelp(T elem, Node<T>*& _root)
	{
		if (_root == NULL)
		{
			_root = new Node<T>;
			_root->inf = elem;
		}
		else
		{
			if (_root->inf > elem)
			{
				addHelp(elem, _root->left);
			}
			if (_root->inf < elem)
			{
				addHelp(elem, _root->right);
			}
			if (_root->inf == elem)
			{
				cout << "Element exists!" << endl;
			}
		}
	}
	void addHelpOrdinary(Node<T>*& pos) const
	{
		T x; char c;
		cout << "root: "; cin >> x;
		pos = new Node<T>;
		assert(pos != NULL);
		pos->inf = x;
		pos->left = NULL;
		pos->right = NULL;
		cout << "Left Tree of: " << x << " y/n? ";
		cin >> c;
		if (c == 'y') addHelpOrdinary(pos->left);
		cout << "Right Tree of: " << x << " y/n? ";
		cin >> c;
		if (c == 'y') addHelpOrdinary(pos->right);
	}
	void printHelp(Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return;
		}
		printHelp(_root->left);
		cout << _root->inf << " ";
		printHelp(_root->right);
	}
	bool memberHelp(T elem, Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return false;
		}
		if (_root->inf == elem)
		{
			return true;
		}
		else
		{
			return memberHelp(elem, _root->left) || memberHelp(elem, _root->right);
		}
	}
	T minelem(Node<T>* _root) const
	{
		assert(_root != NULL);
		Node<T>* crr = _root;
		while (crr->left != NULL)
		{
			crr = crr->left;
		}
		return crr->inf;
	}
	T maxelem(Node<T>* _root) const
	{
		assert(_root != NULL);
		Node<T>* crr = _root;
		while (crr->right != NULL)
		{
			crr = crr->right;
		}
		return crr->inf;
	}
	void removeHelp(T elem, Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return;
		}
		if (_root->inf == elem && _root->left == NULL && _root->right == NULL)
		{
			delete _root;
			_root = NULL;
			return;
		}
		if (_root->inf > elem)
		{
			removeHelp(elem, _root->left);
		}
		if (_root->inf < elem)
		{
			removeHelp(elem, _root->right);
		}
		if (_root->left == NULL)
		{
			Node<T>* temp = _root;
			_root = _root->right;
			delete temp;
			return;
		}
		if (_root->right == NULL)
		{
			Node<T>* temp = _root;
			_root = _root->left;
			delete temp;
			return;
		}
		T minElem = minelem(_root->right);
		_root->inf = minElem;
		removeHelp(minElem, _root->right);
	}
	void bfsHelp(Node<T>*& _root)
	{
		queue<Node<T>*> q;
		assert(_root != NULL);
		if (_root)
		{
			q.push(_root);
		}
		while (!q.empty())
		{
			Node<T>* temp = q.front();
			cout << temp->inf << " ";
			q.pop();
			if (temp->left)
			{
				q.push(temp->left);
			}
			if (temp->right)
			{
				q.push(temp->right);
			}
		}
		cout << endl;
	}
	bool mirrorHelp(Node<T>* leftroot, Node<T>* rightroot)
	{
		if (leftroot == NULL && rightroot == NULL) return true;
		if (leftroot == NULL && rightroot != NULL || leftroot != NULL && rightroot == NULL) return false;
		return mirrorHelp(leftroot->right, rightroot->left) && mirrorHelp(leftroot->left, rightroot->right);
	}
	void levelPrintHelp(Node<T>*& _root, int level, queue<T>& q)
	{
		if (_root)
		{
			if (level == 0)
			{
				q.push(_root->inf);
			}
			else
			{
				level--;
				levelPrintHelp(_root->left, level, q);
				levelPrintHelp(_root->right, level, q);
			}
		}
	}
	bool isomorphHelp(Node<T>*& root1, Node<T>*& root2)
	{
		if (root1 == NULL && root2 == NULL) return true;
		if (root1 == NULL && root2 != NULL || root1 != NULL && root2 == NULL) return false;
		return isomorphHelp(root1->left, root2->left) && isomorphHelp(root1->right, root2->right);
	}
	//simple actions with trees(helpers):
	int countHelp(Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return 0;
		}
		return 1 + countHelp(_root->left) + countHelp(_root->right);
	}
	int countEvensHelp(Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return 0;
		}
		int count = countEvensHelp(_root->left) + countEvensHelp(_root->right);
		if (_root->inf % 2 == 0)
		{
			return count + 1;
		}
		else
		{
			return count;
		}
	}
	int max(int a, int b)
	{
		if (a > b)
		{
			return a;
		}
		else return b;
	}
	int heightHelp(Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return 0;
		}
		else
		{
			return 1 + max(heightHelp(_root->left), heightHelp(_root->right));
		}

	}
	int sumOfElemsHelp(Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return 0;
		}
		else
		{
			return _root->inf + sumOfElemsHelp(_root->left) + sumOfElemsHelp(_root->right);
		}
	}
	int countLeavesHelp(Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return 0;
		}
		if (_root->left == NULL && _root->right == NULL)
		{
			return 1;
		}
		else
		{
			return countLeavesHelp(_root->left) + countLeavesHelp(_root->right);
		}
	}
	int maxLeafHelp(Node<T>*& _root)
	{
		if (_root->left == NULL && _root->right==NULL)
		{
			return _root->inf;
		}
		if (_root->left == NULL && _root->right != NULL)
		{
			return maxLeafHelp(_root->right);
		}
		if (_root->left != NULL && _root->right == NULL)
		{
			return maxLeafHelp(_root->left);
		}
		if (_root->left != NULL && _root->right != NULL)
		{
			int left = maxLeafHelp(_root->left);
			int right = maxLeafHelp(_root->right);
			return max(left, right);
		}
	}
	int searchCountHelp(bool(*pred)(const T&), Node<T>* _root)
	{
		if (_root == NULL)
		{
			return 0;
		}
		if ((pred)(_root->inf))
		{
			return 1 + searchCountHelp(pred, _root->left) + searchCountHelp(pred, _root->right);
		}
		else
		{
			return searchCountHelp(pred, _root->left) + searchCountHelp(pred, _root->right);
		}
	}
	void isBOTHelp(Node<T>*& _root, vector<T> v)
	{
		if (_root == NULL)
		{
			return;
		}
		isBOTHelp(_root->left, v);
		v.push_back(_root->inf);
		isBOTHelp(_root->right);
	}
	//prep.
	void checkTreeHelp(Node<string>*& _root, string& str, int level)
	{
		if (_root)
		{
			if (level == 0)
			{
				str+=_root->inf;
			}
			else
			{
				level--;
				checkTreeHelp(_root->left, str, level);
				checkTreeHelp(_root->right, str, level);
			}
		}
}
	void serializeHelp(Node<T>*& _root, ostream& out)
	{
		if (_root == NULL)
		{
			out << "nullptr";
			return;
		}
		out << _root->inf << " ";
		serializeHelp(_root->left, out);
		serializeHelp(_root->right, out);
	}
	void mapHelp(Node<T>*& _root, mapFn<T> f)
	{
		if (_root == NULL)
		{
			return;
		}
		_root->inf = f(_root->inf);
		mapHelp(_root->left, f);
		mapHelp(_root->right, f);
	}
	
	//task2
	void changeHelp(Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return;
		}

		if (_root->left!=NULL && _root->right == NULL)
		{
			Node<T>* temp = _root->left;
			_root->right = temp;
			_root->left = NULL;
			temp = NULL;
		}
		else if (_root->left == NULL && _root->right != NULL)
		{
			_root->left = new Node<T>;
			Node<T>* temp = _root->right;
			_root->left = temp;
			_root->right = NULL;
			temp = NULL;
		}
		else if(_root->left != NULL && _root->right != NULL)
		{
			Node<T>* temp = _root->left;
			_root->left = _root->right;
			_root->right = temp;
		}
		changeHelp(_root->left);
		changeHelp(_root->right);

	}
	void minusOne(Node<T>*& _root)
	{
		if (_root == NULL)
		{
			return;
		}
		else
		{
			_root->inf = _root->inf*(-1);
			minusOne(_root->left);
			minusOne(_root->right);
		}
	}
	//task3
	void sumNodesHelp(Node<T>*& _root, int& sum)
	{
		if (_root == NULL) return;
		else {
			sumNodesHelp(_root->right, sum);
			sum *= 10;
			sum += _root->inf;
			sumNodesHelp(_root->left, sum);
		}
	}

public:
	BinTree()
	{
		root = NULL;
	}
	BinTree(const BinTree<T>& other)
	{
		copy(other);
	}
	~BinTree()
	{
		del();
	}
	BinTree& operator=(const BinTree<T>& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	void add(T elem)
	{
		addHelp(elem, root);
	}
	void print()
	{
		printHelp(root);
	}
	void member(T elem)
	{
		cout << "Member test: " << memberHelp(elem, root) << endl;
	}
	T minelem() const
	{
		return minelem(root);
	}
	T maxelem() const
	{
		return maxelem(root);
	}
	void remove(T elem)
	{
		removeHelp(elem, root);
	}
	void bfs()
	{
		cout << "BFS print: ";
		bfsHelp(root);
	}
	bool mirror()
	{
		if (root == NULL) return false;
		return mirrorHelp(root->left, root->right);
	}
	void printLevel(int level, queue<T>& q)
	{
		levelPrintHelp(root, level, q);
	}
	bool isomorph(BinTree<T> t)
	{
		isomorphHelp(root, t->root);
	}
	//simple actions with trees:
	void count()
	{
		cout << "Number of elements in tree: " << countHelp(root) << endl;
	}
	void countEvens()
	{
		cout<<"Number of even elements in tree: "<< countEvensHelp(root)<<endl;
	}
	void height()
	{
		cout << "Height of tree: " << heightHelp(root) << endl;
	}
	void sumOfElems()
	{
		cout << "Sum of elements in tree: " << sumOfElemsHelp(root) << endl;
	}
	void countLeaves()
	{
		cout << "Number of leaves in tree: " << countLeavesHelp(root) << endl;
	}
	void maxLeaf()
	{
		cout << "Max leaf in tree: " << maxLeafHelp(root) << endl;
	}
	void searchCount(bool(*pred)(const T&))
	{
		cout << "Search count test: " << searchCountHelp(pred, root) << endl;
	}
	bool isBOT()
	{
		vector<T> v;
		isBOTHelp(root, v);
		for (int i = 0;i < v.size();i++)
		{
			T elem1 = v.back();
			v.pop_back();
			T elem2 = v.back();
		}
		if (elem1 > elem2)
		{
			return true;
		}
		return false;
	}

	//preparation_12.12.2016
	bool checkTree(int lvl)
	{
		string str;
		checkTreeHelp(root, str, lvl);
		return (str.compare(root->inf)==0);
	}
	void addOrdinary()
	{
		addHelpOrdinary(root);
	}
	void serialize(ostream& out)
	{
		serializeHelp(root, out);
		cout << endl;
	}
	void map(mapFn<T> f)
	{
		mapHelp(root, f);
	}	

	//task2
	void exchange()
	{
		changeHelp(root);
		minusOne(root);
	}
	
	//task3
	int sumNodes()
	{
		int sum = 0;
		sumNodesHelp(root,sum);
		return sum;
	}
};
template<typename T>
int length(Node<T>*& _root)
{
	if (_root == NULL)
	{
		return 0;
	}
	else return 1 + length(_root->left) + length(_root->right);
}
bool testSearch(const int& a)
{
	if (a > 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//test reduce:
template<typename ResT, typename ElemT>
ResT reduce(ElemT arr[], int size, reduceFn<ResT, ElemT> f, ResT init)
{
	ResT result = init;
	for (int i = 0;i < size;i++)
	{
		result = f(result, arr[i]);
	}
	return result;
}
int sum(int acc, int x)
{
	return acc + x;
}

//hw task5
int crown(int n, int p)
{
	queue<int> q;
	q.push(n);
	int c = q.front();
	while (p > 0)
	{
		c = q.front();
		q.pop();
		p--;
		q.push(c + 1);
		q.push(c * 2);
	}
	return q.front();
}

int main()
{
	//simple tests:
	/*BinTree<string> t1;
	t1.addOrdinary();
	cout<<t1.checkTree(1)<<endl;
	cout << t1.checkTree(2) << endl;*/
	BinTree<int> t;
	//queue<int> q;
	t.add(11);
	t.add(9);
	t.add(15);
	t.add(12);
	t.add(8);
	t.add(10);
	//t.print();
	t.bfs();
	/*t.count();
	t.countEvens();
	t.countLeaves();
	t.height();
	t.maxLeaf();
	t.searchCount(testSearch);
	t.sumOfElems();
	t.member(8);
	t.remove(9);
	cout << "after remove:" << endl;
	t.print();
	t.printLevel(2, q);
	while (!q.empty()) {
		cout << q.front() << " ";
		q.pop();
	}
	cout << boolalpha << t.mirror() << endl;
	int arr[] = { 1,2,3,4 };
	cout <<"reduce test:"<< reduce<int, int>(arr, 4, sum, 0) << endl;*/

	//hw tests:
	/*t.exchange();
	cout << "After exchange: ";
	t.bfs();
	t.addOrdinary();
	cout << t.sumNodes() << endl;
	for (int i = 0;i < 5;i++)
	{
		cout << crown(5, i)<<endl;
	}*/

	system("pause");
	return 0;
}
