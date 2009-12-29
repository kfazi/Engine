#include <CommonLib.hpp>
#include <iostream>

using namespace Common;
using namespace std;

class Test
{
	public:
		int mSomeData;
		Test()
		{
			cout << "Constructor\n";
			mSomeData = 10;
		}
		~Test()
		{
			cout << "Destructor\n";
			mSomeData = 11;
		}
		Test(const Test&)
		{
			cout << "Copy constructor\n";
			mSomeData = 12;
		}
		Test& operator= (const Test&)
		{
			cout << "Assignment operator\n";
			mSomeData = 13;
			return *this;
		}
};

void PrintVector(string name, const Vector<int>& vec)
{
	cout << name.c_str() << ": ";
	for (Vector<int>::ConstIterator i = vec.Begin(); i != vec.End(); ++i)
		cout << *i << " ";
	cout << "\n";
}

void PrintList(string name, const SinglyLinkedList<int>& list)
{
	cout << name.c_str() << ": ";
	for (SinglyLinkedList<int>::ConstIterator i = list.Begin(); i != list.End(); ++i)
		cout << *i << " ";
	cout << "\n";
}

void Do()
{
	cout << "Creating vector\n";
	Vector<Test> cVector1;
	cout << "Creating list\n";
	SinglyLinkedList<Test> list1;

	cout << "Vector PushBack\n";
	cVector1.PushBack(Test());
	cout << "Vector PushBack\n";
	cVector1.PushBack(Test());

	cout << "List PushFront\n";
	list1.PushFront(Test());
	cout << "List PushFront\n";
	list1.PushFront(Test());
	cout << "Do finished\n";
}

int main(int argc, char **argv)
{
	Do();

	int dummy;
	cin >> dummy;

	return 0;
}

/* EOF */
