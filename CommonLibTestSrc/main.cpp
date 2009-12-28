#include <CommonLib.hpp>
#include <iostream>

using namespace Common;
using namespace std;

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

int main(int argc, char **argv)
{
	Vector<int> cVector1;
	SinglyLinkedList<int> list1;

	cVector1.PushBack(0);
	cVector1.PushBack(10);
	cVector1.PushBack(12);
	cVector1.PushBack(3);
	cVector1.PushBack(45);
	cVector1.PushBack(5);

	list1.PushFront(0);
	list1.PushFront(1);
	list1.PushFront(2);
	list1.PushFront(3);
	list1.PushFront(4);
	list1.PushFront(5);
	list1.PushFront(6);

	SinglyLinkedList<int> list2(list1);
	PrintVector("VEC1", cVector1);
	PrintList("LIST1", list1);
	PrintList("LIST2", list2);

	int dummy;
	cin >> dummy;

	return 0;
}

/* EOF */
