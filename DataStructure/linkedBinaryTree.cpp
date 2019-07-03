#include "linkedBinaryTree.h"

using namespace std;

void linkedBinaryTreeTest()
{
	linkedBinaryTree<char> nullTree;
	linkedBinaryTree<char> nodeB('B', nullTree, nullTree);
	linkedBinaryTree<char> nodeC('C', nullTree, nullTree);
	linkedBinaryTree<char> nodeA('A', nodeB, nodeC);

	cout << "nodeA.inorderPrint:"; nodeA.inorderPrint();
	cout << "nodeA.preorderPrint:"; nodeA.preorderPrint();
	cout << "nodeA.postorderPrint:"; nodeA.postorderPrint();
	cout << "nodeA.breadthFirstPrint:"; nodeA.breadthFirstPrint();
	cout << "nodeA.size:" << nodeA.size() << endl;
	cout << "nodeA.height:" << nodeA.height() 
		<< " height(recursion):" << nodeA.height(nodeA.getRoot()) <<  endl;

	cout << "-----------------------------------------------\n";

	linkedBinaryTree<char> nodeE('E', nullTree, nullTree);
	linkedBinaryTree<char> nodeD('D', nodeE, nullTree);
	linkedBinaryTree<char> nodeR('R', nodeA, nodeD);
	cout << "nodeR.inorderPrint:"; nodeR.inorderPrint();
	cout << "nodeR.preorderPrint:"; nodeR.preorderPrint();
	cout << "nodeR.postorderPrint:"; nodeR.postorderPrint();
	cout << "nodeR.breadthFirstPrint:"; nodeR.breadthFirstPrint();
	cout << "nodeR.size:" << nodeR.size() << endl;
	cout << "nodeR.height:" << nodeR.height() 
		<< " height(recursion):" << nodeR.height(nodeR.getRoot()) <<  endl;
}
