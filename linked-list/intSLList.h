//******************* intSLList.h *******************
// singly-linked class to store integers

#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST

class IntSLLNode {
public:
	IntSLLNode() :
		info(0),
		next(0)
	{}
	~IntSLLNode(){}

	IntSLLNode(int el, IntSLLNode* ptr = 0) :
		info(el),
		next(ptr)
	{}

	int info;
	IntSLLNode* next;
};

class IntSLList {
public:
	IntSLList() :
		head(0), tail(0)
	{}
	~IntSLList();

	bool isEmpty() { return head == 0;}

	void addToHead(int);
	void addToTail(int);
	int deleteFromHead();
	int deleteFromTail();
	void deleteNode(int);
	bool isInList(int)const;

private:
	IntSLLNode* head;
	IntSLLNode* tail;
};

#endif
