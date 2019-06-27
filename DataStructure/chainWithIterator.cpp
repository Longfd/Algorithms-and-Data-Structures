#include "chainWithIterator.h"

void iteratorTest();
void testPalindrome();

void chainUnitTest()
{
	try
	{
		// test iterator
		iteratorTest();

		// test palindrome
		testPalindrome();

		// test delete
		chain<int> list;
		list.insert(0, 1);
		list.insert(0, 2);
		std::cout << list << '\n';
		list.deleteLastN(1);
		std::cout << list << '\n';

		// test getMiddle
		list.clear();
		list.insert(0, 1);
		list.insert(0, 2);
		list.insert(0, 3);
		std::cout << list << " mid:" << list.getMiddle() <<'\n';
		list.insert(0, 4);
		std::cout << list << " mid:" << list.getMiddle() << '\n';
		list.insert(0, 5);
		std::cout << list << " mid:" << list.getMiddle() << '\n';
		list.insert(0, 6);
		std::cout << list << " mid:" << list.getMiddle() << '\n';
	}
	catch (const std::exception& e) {
		std::cout << "std::exception:" << e.what();
	}
	catch (illegalParameterValue& e) {
		std::cout << "illegalParameterValue:" << e.what();
	}
}

typedef struct Student
{
	Student() :
		name(), age(0)
	{}
	Student(const std::string name, const int age) :
		name(name), age(age)
	{}

	bool operator==(const Student& stu) {
		return (name == stu.name) &&
			(age == stu.age);
	}

	void output(std::ostream& out) const {
		out << "name:" << name
			<< " age:" << age;
	}

	std::string name;
	int age;
}Student;

std::ostream& operator<<(std::ostream& out, const Student& stu) {
	stu.output(out);
	return out;
}

void iteratorTest()
{
	chain<int> list;
	list.insert(0, 1);
	list.insert(0, 2);
	list.insert(0, 3);
	list.insert(0, 4);
	list.insert(0, 5);
	list.insert(0, 6);

	chain<int>::iterator it;
	chain<int>::iterator begin = list.begin();
	chain<int>::iterator end = list.end();

	//Output using forward iterator
	for (it = begin; it != end; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	//Output using backward iterator
	/*for (it = end; it != begin; )
		std::cout << *--it << " ";
	std::cout << std::endl;*/

	// test dereference operator -> and * for iterator
	chain<Student> stuList;
	stuList.insert(0, Student("Allen", 18));
	stuList.insert(0, Student("Kobe", 18));
	chain<Student>::iterator itStu = stuList.begin();
	std::cout << "*iteraotr: " << (*itStu).name << " " << (*itStu).age << "\n";
	itStu++;
	std::cout << "iteraotr->:" << itStu->name << " " << itStu->age << "\n";
	// overload operator <<
	std::cout << "cout<<list:" << stuList << "\n";
}

void testPalindrome()
{
	chain<int> list, list2, list3;

	list.insert(0, 1);
	assert(list.checkPalindromeList());

	list.insert(0, 1);
	assert(list.checkPalindromeList());

	list2.insert(0, 1);
	list2.insert(0, 2);
	list2.insert(0, 1);
	assert(list2.checkPalindromeList());

	list2.insert(0, 1);
	assert(!list2.checkPalindromeList());

	list3.insert(0, 1);
	list3.insert(0, 2);
	list3.insert(0, 2);
	list3.insert(0, 1);
	assert(list3.checkPalindromeList());

	list3.insert(0, 1);
	assert(!list3.checkPalindromeList());
}