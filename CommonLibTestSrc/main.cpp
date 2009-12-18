#include <CommonLib.hpp>
#include <iostream>

using namespace Common;
using namespace std;

void PrintVector(string name, CVector<int> &vec)
{
	cout << name.c_str() << ": ";
	for (int i = 0; i < vec.GetLength(); ++i)
		cout << vec[i] << " ";
	cout << "\n";
}

void Modify(CVector<int> vec)
{
	vec[2] = 8;
}

int main(int argc, char **argv)
{
	CVector<int> cVector1;
	CVector<int> cVector2;

	cVector1.Put(0);
	cVector1.Put(1);
	cVector1.Put(2);
	cVector1.Put(3);
	cVector1.Put(4);
	cVector1.Put(5);
	cVector2 = cVector1;
	CVector<int> cVector3(cVector1);

	cVector1.PopBack();
	cVector1.Put(50);

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
