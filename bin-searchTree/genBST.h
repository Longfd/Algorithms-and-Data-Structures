//************** genBST.h **************
// generic binary search tree

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <queue>
#include <stack>
using namespace std;

template<class T>
class Stack : public stack<T> {}

template<class T>
class Queue : public queque<T> {
public:
	T dequeue() {
		T tmp = front();
		queue<T>::dequeue();
		return tmp;
	}

	void enqueue(const T& el) {
		push(el);
	}
}

template<class T>
class BSTNode {
public:
	BSTNode() : el(),left(0),right(0)
	{}
	BSTNode(const T& e, BSTNode<T>* l = 0, BSTNode<T>* r = 0) : 
		el(e), left(l), right(r)
	{}

	T el;
	BSTNode<T>* left;
	BSTNode<T>* right;
};

template<class T>
class BST {
public:
	BST() : root(0) {}
	~BST() { clear(); }

	void clear() { clear(root); root = 0; }
	bool isEmpty() const { return root == 0; }
	void preorder() { preorder(root); }
	void inorder() { inorder(root); }
	void postorder() { postorder(root); }
	T* search(const T& el) const { return search(root, el); }

	void breadthFirst();
	void iterativePreorder();
	void iterativeInorder();
	void iterativePostorder();
	void MorrisInorder();
	void insert(const T&);
 	void deleteByMerging(BSTNode<T>*&);
	void findAndDeleteByMerging(const T&);
	void deleteByCoping(BSTNode<T>*&);
	void balance(T*, int, int);

protected:
	BSTNode<T>* root;
	void clear(BSTNode<T>*);
	T* search(BSTNode<T>*, const T&) const;
	void preorder(BSTNode<T>*);
	void inorder(BSTNode<T>*);
	void postorder(BSTNode<T>*);

	virtual void visit(BSTNode<T>* p) { cout << p->el << ' '; }
};

template<class T>
T* BST<T>::search(BSTNode<T>*p, const T& el) const {
	while(p != 0) {
		if(p->el == el)
			return &p->el;
		else if(p->el < el)
			p = p->right;
		else
			p = p->left;
	}
	return 0;
}

template<class T>
void BST<T>::breadthFirst() {
	Queue<BSTNode<T>*> que;
	BSTNode<T>* p = root;

	if(p != 0) {
		que.enqueue(root);

		while(p != 0) {
			p = que.dequeue();
			visit(p);

			if(p->left != 0)
				que.enqueue(p->left);
			if(p->right != 0)
				que.enqueue(p->right);
		}
	}
}

#endif
