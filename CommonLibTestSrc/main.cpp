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

template<typename Container> void Print(string name, const Container& container)
{
	cout << name.c_str() << ": ";
	for (Container::ConstIterator i = container.Begin(); i != container.End(); ++i)
		cout << *i << " ";
	cout << "\n";
}

template<typename SomeRange> void UseRange(const SomeRange &range)
{
	cout << "IsEmpty() = " << range.IsEmpty() << "\n";
	cout << "Front() = " << range.Front() << "\n";
}

void Do()
{
	cout << "Creating vector\n";
	Vector<int> vector1;

//	cout << "Creating list\n";
//	SinglyLinkedList<Test> list1;

	vector1.PushBack(0);
	//vector1.PushBack(1);
	//vector1.PushBack(2);
	//vector1.PushBack(3);
	//vector1.PushBack(4);

//	vector1.ErasePreserveOrder(1);
	Print("Vec1", vector1);

	UseRange(Range<Vector<int>::Iterator>(vector1.Begin(), vector1.End()));

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
