#include "derivedLinkedStack.h"

void derivLinkStackTest()
{
	derivedLinkedStack<int> stack;
	stack.push(0);
	stack.push(1);
	stack.push(2);
	stack.push(3);


	while (!stack.empty())
	{
		std::cout << stack.top() << " ";
		stack.pop();
	}

	assert(stack.empty());
	std::cout << "size:" << stack.size() << '\n';

	try {
		stack.pop();
	}
	catch (stackEmpty e) {
		std::cout << e.what() << '\n';
	}
}
