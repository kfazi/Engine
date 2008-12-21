/**
*/

#include <limits>
#include <cmath>
#include "vector3.hpp"

namespace engine
{

CVector3::CVector3()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

CVector3::CVector3(const double fX, const double fY, const double fZ)
{
	x = fX;
	y = fY;
	z = fZ;
}

CVector3::CVector3(const CVector3 &cVector)
{
	x = cVector.x;
	y = cVector.y;
	z = cVector.z;
}

void CVector3::Normalize()
{
	double fLength = std::sqrt(x * x + y * y + z * z);
	if (fLength == 1.0 || fLength < std::numeric_limits<double>::epsilon())
		return;
	x /= fLength;
	y /= fLength;
	z /= fLength;
}

double CVector3::Length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

bool CVector3::operator == (const CVector3 &cVector) const
{
	return (x == cVector.x) && (y == cVector.y) && (z == cVector.z);
}

bool CVector3::operator != (const CVector3 &cVector) const
{
	return !(*this == cVector);
}

CVector3 &CVector3::operator = (const CVector3 &cVector)
{
	x = cVector.x;
	y = cVector.y;
	z = cVector.z;
	return *this;
}

CVector3 &CVector3::operator - ()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

CVector3 &CVector3::operator += (const CVector3 &cVector)
{
	x += cVector.x;
	y += cVector.y;
	z += cVector.z;
	return *this;
}

CVector3 &CVector3::operator -= (const CVector3 &cVector)
{
	x -= cVector.x;
	y -= cVector.y;
	z -= cVector.z;
	return *this;
}

CVector3 &CVector3::operator *= (const CVector3 &cVector)
{
	x *= cVector.x;
	y *= cVector.y;
	z *= cVector.z;
	return *this;
}

CVector3::operator bool()
{
	return x != 0 || y != 0 || z != 0;
}

CVector3 operator * (const int iValue, const CVector3 &cVector)
{
	return CVector3(cVector.x * iValue, cVector.y * iValue, cVector.z * iValue);
}

CVector3 operator * (const double fValue, const CVector3 &cVector)
{
	return CVector3(cVector.x * fValue, cVector.y * fValue, cVector.z * fValue);
}

CVector3 operator * (const CVector3 &cVector, const int iValue)
{
	return CVector3(cVector.x * iValue, cVector.y * iValue, cVector.z * iValue);
}

CVector3 operator * (const CVector3 &cVector, const unsigned int iValue)
{
	return CVector3(cVector.x * iValue, cVector.y * iValue, cVector.z * iValue);
}

CVector3 operator * (const CVector3 &cVector, const double fValue)
{
	return CVector3(cVector.x * fValue, cVector.y * fValue, cVector.z * fValue);
}

CVector3 operator / (const CVector3 &cVector, const int iValue)
{
	return CVector3(cVector.x / iValue, cVector.y / iValue, cVector.z / iValue);
}

CVector3 operator / (const CVector3 &cVector, const unsigned int iValue)
{
	return CVector3(cVector.x / iValue, cVector.y / iValue, cVector.z / iValue);
}

CVector3 operator / (const CVector3 &cVector, const double fValue)
{
	return CVector3(cVector.x / fValue, cVector.y / fValue, cVector.z / fValue);
}

const CVector3 operator + (const CVector3 &cVector1, const CVector3 &cVector2)
{
	return CVector3(cVector1) += cVector2;
}

const CVector3 operator - (const CVector3 &cVector1, const CVector3 &cVector2)
{
	return CVector3(cVector1) -= cVector2;
}

const CVector3 operator * (const CVector3 &cVector1, const CVector3 &cVector2)
{
	return CVector3(cVector1) *= cVector2;
}

std::ostream &operator << (std::ostream &cOutputStream, const CVector3 &cVector)
{
	cOutputStream << "CVector3(" << cVector.x << ", " << cVector.y << ", " << cVector.z << ")";
	return cOutputStream;
}

}

/* EOF */

