#include <CommonLib.hpp>
#include <iostream>

using namespace Common;
using namespace std;

void PrintList(string name, CSinglyLinkedList<int>& list)
{
	cout << name.c_str() << ": ";
	for (int i = 0; i < list.GetLength(); ++i)
		cout << list[i] << " ";
	cout << "\n";
}

void PrintVector(string name, CVector<int>& vec)
{
	cout << name.c_str() << ": ";
	for (int i = 0; i < vec.GetLength(); ++i)
		cout << vec[i] << " ";
	cout << "\n";
}

void Modify(CVector<int>& vec)
{
	vec[2] = 8;
}

int main(int argc, char **argv)
{
	CSinglyLinkedList<int> cList1;
	CVector<int> cVector1;
	CVector<int> cVector2;

	cList1.PushBack(0);
	cList1.PushFront(1);
	cList1.PushFront(2);
	PrintList("LIST1", cList1);

	cVector1.PushBack(0);
	cVector1.PushBack(10);
	cVector1.PushBack(12);
	cVector1.PushBack(3);
	cVector1.PushBack(45);
	cVector1.PushBack(5);
	QuickSort(cVector1.GetRange());
	PrintVector("VEC1", cVector1);

	size_t iIndex;
	if (Find(cVector1.GetRange(), 5, iIndex))
		cout << "Index: " << iIndex << "\n";

	CVector<int>::CRange bla = cVector1.GetAppendRange();
	bla.Put(10);
	bla.Put(11);
	bla.Put(12);

	cVector2 = cVector1;
	CVector<int> cVector3(cVector1.GetRange());

	cVector1.PopBack();
	cVector1.PushBack(50);

	cVector1.ErasePreserveOrder(5);

	PrintVector("VEC1", cVector1);
	PrintVector("VEC2", cVector2);
	PrintVector("VEC3", cVector3);

	CSinglyLinkedList<int> cList2(cVector3.GetRange());
	PrintList("LIST2", cList2);

	Modify(cVector2);
	cVector1[0] = 9;
	PrintVector("VEC1", cVector1);
	PrintVector("VEC2", CVector<int>(cVector2));
	PrintVector("VEC3", cVector3);

	int dummy;
	cin >> dummy;

	return 0;
}

/* EOF */
