#include "chainWithIterator.h"

template<typename T>
void iteratorTest(chain<T>& list);

void chainUnitTest()
{
	try
	{
		chain<int> list;
		list.insert(0, 1);
		list.insert(0, 1);
		list.insert(0, 1);
		list.insert(0, 1);
		list.insert(0, 1);
		list.insert(0, 6);

		//test iterator
		iteratorTest(list);

		//test palindrome
		list.checkPalindromeList2() ? std::cout << "is palindrome\n" : std::cout << "not palindrome\n";
	}
	catch (const std::exception& e) {
		std::cout << "std::exception:" << e.what();
	}
	catch (illegalParameterValue& e) {
		std::cout << "illegalParameterValue:" << e.what();
	}

	getchar();
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

template<typename T>
void iteratorTest(chain<T>& list)
{
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
