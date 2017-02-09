#include <iostream>
#include <assert.h>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

template<typename T>
using mapFn = T(*)(const T&);

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
	Node(Node<T>* l, Node<T>* r, T i) : left(l), right(r), inf(i) {}
};

template <typename T>
class BinaryTree
{
	Node<T>* root;
	void copyHelp(Node<T>*& _root, Node<T>*& otherRoot);
	void copy(const BinaryTree<T>& other);
	void deleteHelp(Node<T>*& _root);
	void del();
	void addHelp(Node<T>*& _root, T& elem);
	void addHelpOrdinary(Node<T>*& pos) const;
	void printHelp(Node<T>*& _root);
	bool memberHelp(Node<T>*& _root, T& elem);
	T minElemHelp(Node<T>* _root);
	T maxElemHelp(Node<T>* _root);
	void removeHelp(Node<T>*& _root, T& elem);
	void bfsHelp(Node<T>*& _root);
	bool isMirrorHelp(Node<T>*& leftroot, Node<T>*& rightroot);
	void levelPrintHelp(Node<T>*& _root, int level, queue<T>& q);
	bool isIsomorphHelp(Node<T>*& root1, Node<T>*& root2);

	//simple actions with trees(helpers):
	int countNodesHelp(Node<T>*& _root);
	int countEvensHelp(Node<T>*& _root);
	int heightHelp(Node<T>*& _root);
	int sumOfNodesHelp(Node<T>*& _root);
	int countLeavesHelp(Node<T>*& _root);
	int maxLeafHelp(Node<T>*& _root);
	int searchCountHelp(bool(*pred)(const T&), Node<T>*& _root);
	void isBOTHelp(Node<T>*& _root, vector<T> v);
	
	void checkTreeHelp(Node<string>*& _root, string& str, int level);
	void serializeHelp(Node<T>*& _root, ostream& out);
	void mapTreeHelp(Node<T>*& _root, mapFn<T> f);

public:
	BinaryTree();
	BinaryTree(const BinaryTree<T>& other);
	~BinaryTree();
	BinaryTree<T>& operator=(const BinaryTree<T>& other);
	void add(T& elem);
	void addOrdinary();
	void printTree();
	void isMember(T& elem);
	T minElem() const;
	T maxElem() const;
	void remove(T& elem);
	void bfs();
	bool isMirror();
	void levelPrint(int level, queue<T>& q);
	bool isIsomorph(BinaryTree<T>& t);
	//simple actions with binary trees:
	void countNodes();
	void countEvenNodes();
	void height();
	void sumOfNodes();
	void countLeaves();
	void maxLeaf();
	void searchCount(bool(*pred)(const T&));
	bool isBOT();

	bool checkTree(int level);
	void serialize(ostream& out);
	void mapTree(mapFn<T> f);
};

template<typename T>
void BinaryTree<T>::copyHelp(Node<T>*& _root, Node<T>*& otherRoot)
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

template<typename T>
void BinaryTree<T>::copy(const BinaryTree<T>& other)
{
	copyHelp(root, other.root);
}

template<typename T>
void BinaryTree<T>::deleteHelp(Node<T>*& _root)
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

template<typename T>
void BinaryTree<T>::del()
{
	deleteHelp(root);
}

template<typename T>
void BinaryTree<T>::addHelp(Node<T>*& _root, T& elem)
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
			addHelp(_root->left, elem);
		}
		if (_root->inf < elem)
		{
			addHelp(_root->right, elem);
		}
		if (_root->inf == elem)
		{
			cout << "Node exists!" << endl;
		}
	}
}

template<typename T>
void BinaryTree<T>::addHelpOrdinary(Node<T>*& pos) const
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

template<typename T>
void BinaryTree<T>::printHelp(Node<T>*& _root)
{
	if (_root == NULL)
	{
		return;
	}
	printHelp(_root->left);
	cout << _root->inf << " ";
	printHelp(_root->right);
}

template<typename T>
bool BinaryTree<T>::memberHelp(Node<T>*& _root, T& elem)
{
	if (_root == NULL)
	{
		return false;
	}
	if (_root->inf == elem)
	{
		return true;
	}
	return memberHelp(_root->left, elem) || memberHelp(_root->right, elem);
}

template<typename T>
T BinaryTree<T>::minElemHelp(Node<T>* _root)
{
	assert(_root != NULL);
	Node<T>* crr = _root;
	while (crr->left != NULL)
	{
		crr = crr->left;
	}
	return crr->inf;
}

template<typename T>
T BinaryTree<T>::maxElemHelp(Node<T>* _root)
{
	assert(_root != NULL);
	Node<T>* crr = _root;
	while (crr->right != NULL)
	{
		crr = crr->right;
	}
	return crr->inf;
}

template<typename T>
void BinaryTree<T>::removeHelp(Node<T>*& _root, T& elem)
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
		removeHelp(_root->left, elem);
	}
	if (_root->inf < elem)
	{
		removeHelp(_root->right, elem);
	}
	if (_root->left == NULL)
	{
		Node<T>* temp = _root;
		_root = _root->right;
		delete temp;
		return;
	}
	if (_root->right == _NULL)
	{
		Node<T>* temp = _root;
		_root = _root->left;
		delete temp;
		return;
	}
	T minEl = minElemHelp(_root->right);
	_root->inf = minEl;
	removeHelp(_root->right, minEl);

}

template<typename T>
void BinaryTree<T>::bfsHelp(Node<T>*& _root)
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
		if (temp - left)
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

template<typename T>
bool BinaryTree<T>::isMirrorHelp(Node<T>*& leftroot, Node<T>*& rightroot)
{
	if (leftroot == NULL && rightroot == NULL)
	{
		return true;
	}
	if (leftroot == NULL && rightroot != NULL
		|| leftroot != NULL && rightroot == NULL)
	{
		return false;
	}
	return isMirrorHelp(leftroot->right, rightroot->left)
		&& isMirrorHelp(leftroot->left, rightroot->right);
}

template<typename T>
void BinaryTree<T>::levelPrintHelp(Node<T>*& _root, int level, queue<T>& q)
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

template<typename T>
bool BinaryTree<T>::isIsomorphHelp(Node<T>*& root1, Node<T>*& root2)
{
	if (root1 == NULL && root2 == NULL)
	{
		return true;
	}
	if (root1 == NULL && root2 != NULL || root1 != NULL && root2 == NULL)
	{
		return false;
	}
	return isIsomorphHelp(root1->left, root2->left)
		&& isIsomorphHelp(root1->right, root2->right);
}

//simple actions with binary trees:
template<typename T>
int BinaryTree<T>::countNodesHelp(Node<T>*& _root)
{
	if (_root == NULL)
	{
		return 0;
	}
	return 1 + countNodesHelp(_root->left) + countNodesHelp(_root->right);
}

template<typename T>
int BinaryTree<T>::countEvensHelp(Node<T>*& _root)
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

template<typename T>
int BinaryTree<T>::heightHelp(Node<T>*& _root)
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

template<typename T>
int BinaryTree<T>::sumOfNodesHelp(Node<T>*& _root)
{
	if (_root == NULL)
	{
		return 0;
	}
	return _root->inf + sumOfNodesHelp(_root->left) + sumOfNodesHelp(_root->right);
}

template<typename T>
int BinaryTree<T>::countLeavesHelp(Node<T>*& _root)
{
	if (_root == NULL)
	{
		return 0;
	}
	if (_root->left == NULL && _root->right == NULL)
	{
		return 1;
	}
	return countLeavesHelp(_root->left) + countLeavesHelp(_root->right);
}

template<typename T>
int BinaryTree<T>::maxLeafHelp(Node<T>*& _root)
{
	if (_root->left == NULL && _root->right == NULL)
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

template<typename T>
int BinaryTree<T>::searchCountHelp(bool(*pred)(const T &), Node<T>*& _root)
{
	if (_root == NULL)
	{
		return 0;
	}
	if ((pred)(_root->inf))
	{
		return 1 + searchCountHelp(pred, _root->left) + searchCountHelp(pred,_root->right);
	}
	else
	{
		return searchCountHelp(pred, _root->left) + searchCountHelp(pred, _root->right);
	}
}

template<typename T>
void BinaryTree<T>::isBOTHelp(Node<T>*& _root, vector<T> v)
{
	if (_root == NULL)
	{
		return;
	}
	isBOTHelp(_root->left, v);
	v.push_back(_root->inf);
	isBOTHelp(_root->right);
}

template<typename T>
void BinaryTree<T>::checkTreeHelp(Node<string>*& _root, string& str, int level)
{
	if (_root)
	{
		if (level == 0)
		{
			str += _root->inf;
		}
		else
		{
			level--;
			checkTreeHelp(_root->left, str, level);
			checkTreeHelp(_root->right, str, level);
		}
	}
}

template<typename T>
void BinaryTree<T>::serializeHelp(Node<T>*& _root, ostream & out)
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

template<typename T>
void BinaryTree<T>::mapTreeHelp(Node<T>*& _root, mapFn<T> f)
{
	if (_root == NULL)
	{
		return;
	}
	_root->inf = f(_root->inf);
	mapTreeHelp(_root->left,f);
	mapTreeHelp(_root->right,f);
	
}

template<typename T>
BinaryTree<T>::BinaryTree()
{
	_root == NULL;
}

template<typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other)
{
	copy(other);
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	del();
}

template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other)
{
	if (this != &other)
	{
		del();
		copy(other);
	}
	return *this;
}

template<typename T>
void BinaryTree<T>::add(T& elem)
{
	addHelp(elem, root);
}

template<typename T>
void BinaryTree<T>::addOrdinary()
{
	addHelpOrdinary(root);
}

template<typename T>
void BinaryTree<T>::printTree()
{
	printHelp(root);
}

template<typename T>
void BinaryTree<T>::isMember(T& elem)
{
	cout << "member test: " << memberHelp(root, elem) << endl;
}

template<typename T>
T BinaryTree<T>::minElem() const
{
	return minElemHelp(root);
}

template<typename T>
T BinaryTree<T>::maxElem() const
{
	return maxElemHelp(root);
}

template<typename T>
void BinaryTree<T>::remove(T& elem)
{
	removeHelp(root, elem);
}

template<typename T>
void BinaryTree<T>::bfs()
{
	cout << "BFS print:";
	bfsHelp(root);
}

template<typename T>
bool BinaryTree<T>::isMirror()
{
	if (root == NULL)
	{
		return false;
	}
	return isMirrorHelp(root->left, root->right);
}

template<typename T>
void BinaryTree<T>::levelPrint(int level, queue<T>& q)
{
	levelPrintHelp(root, level, q);
}

template<typename T>
bool BinaryTree<T>::isIsomorph(BinaryTree<T>& t)
{
	return isIsomorphHelp(root, t->root);
}

//simple actions with binary trees:
template<typename T>
void BinaryTree<T>::countNodes()
{
	cout << "Number of nodes in tree: " << countNodesHelp(root) << endl;
}

template<typename T>
void BinaryTree<T>::countEvenNodes()
{
	cout << "Number of even nodes in tree: " << countEvensHelp(root) << endl;
}

template<typename T>
void BinaryTree<T>::height()
{
	cout << "height of tree: " << heightHelp(root) << endl;
}

template<typename T>
void BinaryTree<T>::sumOfNodes()
{
	cout << "Sum of nodes in tree: " << sumOfNodesHelp(root) << endl;
}

template<typename T>
void BinaryTree<T>::countLeaves()
{
	cout << "Number of leaves in tree: " << countLeavesHelp(root) << endl;
}

template<typename T>
void BinaryTree<T>::maxLeaf()
{
	cout << "Max leaf in tree: " << maxLeafHelp(root) << endl;
}

template<typename T>
void BinaryTree<T>::searchCount(bool(*pred)(const T&))
{
	cout << "searchCount test: " << searchCountHelp(pred, root) << endl;
}

template<typename T>
bool BinaryTree<T>::isBOT()
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

template<typename T>
bool BinaryTree<T>::checkTree(int level)
{
	string str;
	checkTreeHelp(root, str, level);
	return (str.compare(root->inf) == 0);
}

template<typename T>
void BinaryTree<T>::serialize(ostream& out)
{
	serializeHelp(root, out);
	cout << endl;
}

template<typename T>
void BinaryTree<T>::mapTree(mapFn<T> f)
{
	mapTreeHelp(root, f);
}

int main()
{

	return 0;
}
