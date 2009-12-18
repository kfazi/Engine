#include <CommonLib.hpp>
#include <iostream>

using namespace Common;
using namespace std;

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
	CVector<int> cVector1;
	CVector<int> cVector2;

	cVector1.PushBack(0);
	cVector1.PushBack(1);
	cVector1.PushBack(2);
	cVector1.PushBack(3);
	cVector1.PushBack(4);
	cVector1.PushBack(5);

	size_t iIndex;
	if (Find(cVector1.GetRange(), 5, iIndex))
		cout << "Index: " << iIndex << "\n";

	cVector2 = cVector1;
	CVector<int> cVector3(cVector1.GetRange());

	cVector1.PopBack();
	cVector1.PushBack(50);

	cVector1.ErasePreserveOrder(5);

	PrintVector("VEC1", cVector1);
	PrintVector("VEC2", cVector2);
	PrintVector("VEC3", cVector3);

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
