//************** dequeInSTL.cpp **************
// demo for deque in STL

#include <iostream>
#include <algorithm>
#include <deque>

void print(const std::deque<int>& dq)
{
	for(auto el : dq) {
		std::cout << el << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	std::deque<int> dq1;
	dq1.push_front(1); //dq1 = (1)
	dq1.push_front(2); //dq1 = (2,1)
	dq1.push_back(3); //dq1 = (2,1,3)
	dq1.push_back(4); //dq1 = (2,1,3,4)

	std::deque<int> dq2(dq1.begin() + 1, dq1.end() - 1); //dq2 = (1,3)
	std::cout << "dq2:";
	print(dq2);

	dq1[3] = 0; //dq1 = (2,1,3,0)
	dq1.erase(dq1.begin() + 1, dq1.end() - 1); //dq1 = (2,0)
	dq1.insert(dq1.end(), 5); //dq1 = (2,0,5)
	dq1.insert(dq1.end() - 1, 2, 6); //dq1 = (2,0,6,6,5)
	sort(dq1.begin(), dq1.end()); //dq1 = (0,2,5,6,6)
	std::cout << "dq1:"; 
	print(dq1);

	std::deque<int> dq3;
	dq3.resize(dq1.size() + dq2.size());
	merge(dq1.begin(), dq1.end(), dq2.begin(), dq2.end(), dq3.begin());
	//dq1()dq3 = (0,1,2,3,5,6,6)
	std::cout << "dq3:";
	print(dq3);

	return 0;
}
