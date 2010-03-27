#include <CommonLib.hpp>
#include <iostream>

using namespace Common;
using namespace std;

class Test
{
	public:
		int mSomeData;
		Test(int i)
		{
			cout << "Constructor\n";
			mSomeData = i;
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

void DoVector()
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

void DoList()
{
	LinkedList<int> list1;

	list1.PushFront(5);
	list1.PushBack(10);
	list1.PushBack(15);

	Print("List1", list1);
}

void DoHash()
{
	HashMap<const char*, int> hash1;

	hash1.Insert(MakePair("dupa", 5));
	hash1.Insert(MakePair("hehehehe", 50));
	hash1.Insert(MakePair("wow", 500));

	cout << "Hash: ";
	HashMap<const char*, int>::ConstReverseIterator end = hash1.ReverseEnd();
	for (HashMap<const char*, int>::ConstReverseIterator i = hash1.ReverseBegin(); i != end; ++i)
		cout << "(" << (*i).first << " = " << (*i).second << ") ";
	cout << "\n";
	cout << hash1["hehehehe"] << "\n";
	cout << "Load: " << hash1.GetLoad() << "\n";
}

void DoString()
{
	String string;
	string = "dupska";
	string = string.ToUpper();
	cout << *(string.GetRaw() + 1) << "\n";
}

int main(int argc, char **argv)
{
//	DoVector();
//	DoList();
//	DoHash();

	StringStatic::Initialize();

	DoString();

	cout << "\nTHE END\n";
	int dummy;
	cin >> dummy;

	return 0;
}

/* EOF */
