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
			//mSomeData = 10;
		}
		~Test()
		{
			cout << "Destructor\n";
			//mSomeData = 11;
		}
		Test(const Test& a)
		{
			cout << "Copy constructor\n";
			mSomeData = a.mSomeData;
		}
		Test& operator= (const Test& a)
		{
			cout << "Assignment operator\n";
			mSomeData = a.mSomeData;
			return *this;
		}
};

void PrintVector(string name, const Vector<Test>& vec)
{
	cout << name.c_str() << ": ";
//	for (Vector<Test>::ConstReverseIterator i = vec.ReverseBegin(); i != vec.ReverseEnd(); ++i)
	for (Vector<Test>::ConstIterator i = vec.Begin(); i != vec.End(); ++i)
		cout << i->mSomeData << " ";
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
	cout << "Sizeof(DefaultAllocator<Test>) = " << sizeof(DefaultAllocator<Test>) << "\n";
	cout << "Creating vector\n";
	Vector<Test> cVector1;

//	cout << "Creating list\n";
//	SinglyLinkedList<Test> list1;

	cout << "Vector PushBack\n";
	cVector1.PushBack(Test());
	cout << "Vector PushBack\n";
	cVector1.PushBack(Test());
	cVector1.PushBack(Test());
	cVector1.PushBack(Test());
	cVector1.PushBack(Test());

	cVector1[0].mSomeData = 0;
	cVector1[1].mSomeData = 1;
	cVector1[2].mSomeData = 2;
	cVector1[3].mSomeData = 3;
	cVector1[4].mSomeData = 4;

	cVector1.Erase(1);
	PrintVector("Vec1", cVector1);

//	cout << "List PushFront\n";
//	list1.PushFront(Test());
//	cout << "List PushFront\n";
//	list1.PushFront(Test());
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
