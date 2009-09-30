#include "../Internal.hpp"
#include "CVector3D.hpp"
#include <limits>

namespace Common
{

const CVector3D CVector3D::ZERO(0.0, 0.0, 0.0);

const CVector3D CVector3D::ONE(1.0, 1.0, 1.0);

CVector3D::CVector3D()
{
	*this = ZERO;
}

CVector3D::CVector3D(const double fX, const double fY, const double fZ)
{
	X = fX;
	Y = fY;
	Z = fZ;
}

CVector3D::CVector3D(const CVector3D &cVector)
{
	X = cVector.X;
	Y = cVector.Y;
	Z = cVector.Z;
}

void CVector3D::Normalize()
{
	double fLength = GetLength();
	if (fLength == 1.0 || fLength < std::numeric_limits<double>::epsilon())
		return;
	X /= fLength;
	Y /= fLength;
	Z /= fLength;
}

double CVector3D::GetLength() const
{
	return std::sqrt(X * X + Y * Y + Z * Z);
}

bool CVector3D::operator == (const CVector3D &cVector) const
{
	return (X == cVector.X) && (Y == cVector.Y) && (Z == cVector.Z);
}

bool CVector3D::operator != (const CVector3D &cVector) const
{
	return !(*this == cVector);
}

CVector3D &CVector3D::operator = (const CVector3D &cVector)
{
	X = cVector.X;
	Y = cVector.Y;
	Z = cVector.Z;
	return *this;
}

CVector3D &CVector3D::operator - ()
{
	X = -X;
	Y = -Y;
	Z = -Z;
	return *this;
}

CVector3D &CVector3D::operator += (const CVector3D &cVector)
{
	X += cVector.X;
	Y += cVector.Y;
	Z += cVector.Z;
	return *this;
}

CVector3D &CVector3D::operator -= (const CVector3D &cVector)
{
	X -= cVector.X;
	Y -= cVector.Y;
	Z -= cVector.Z;
	return *this;
}

CVector3D &CVector3D::operator *= (const CVector3D &cVector)
{
	X *= cVector.X;
	Y *= cVector.Y;
	Z *= cVector.Z;
	return *this;
}

CVector3D::operator bool ()
{
	return X != 0.0 || Y != 0.0 || Z != 0.0;
}

const CVector3D operator + (const CVector3D &cVector1, const CVector3D &cVector2)
{
	return CVector3D(cVector1) += cVector2;
}

const CVector3D operator - (const CVector3D &cVector1, const CVector3D &cVector2)
{
	return CVector3D(cVector1) -= cVector2;
}

const CVector3D operator * (const CVector3D &cVector1, const CVector3D &cVector2)
{
	return CVector3D(cVector1) *= cVector2;
}

}

/* EOF */
