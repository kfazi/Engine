#include "../Internal.hpp"
#include "CQuaternion.hpp"
#include "CMatrix4x4.hpp"
#include "CVector3D.hpp"
#include <cmath>
#include <limits>

namespace Common
{

const CQuaternion CQuaternion::ZERO(0.0, 0.0, 0.0, 0.0);

const CQuaternion CQuaternion::IDENTITY(1.0, 0.0, 0.0, 0.0);

CVector3D CQuaternion::GetVector() const
{
	return CVector3D(X, Y, Z);
}

CQuaternion::CQuaternion()
{
	*this = IDENTITY;
}

CQuaternion::CQuaternion(const double fW, const double fX, const double fY, const double fZ)
{
	W = fW;
	X = fX;
	Y = fY;
	Z = fZ;
}

CQuaternion::CQuaternion(const double fReal, const CVector3D& cVector)
{
	W = fReal;
	X = cVector.X;
	Y = cVector.Y;
	Z = cVector.Z;
}

CQuaternion::CQuaternion(const double fThetaZ, const double fThetaY, const double fThetaX)
{
	FromEulerAngles(fThetaZ, fThetaY, fThetaX);
}

CQuaternion::CQuaternion(const CVector3D& cAngles)
{
	FromEulerAngles(cAngles);
} 

CQuaternion::CQuaternion(const CVector3D& cAxis, double fAngle)
{
	double fSinAngle = sin(fAngle / 2.0);
	W = cos(fAngle / 2.0);
	X = cAxis.X * fSinAngle;
	Y = cAxis.Y * fSinAngle;
	Z = cAxis.Z * fSinAngle;
}

CQuaternion& CQuaternion::operator = (const CQuaternion& cQuaternion)		
{
	W = cQuaternion.W;
	X = cQuaternion.X;
	Y = cQuaternion.Y;
	Z = cQuaternion.Z;
	return *this;
}

CQuaternion CQuaternion::operator - () const
{
	return CQuaternion(-W, -X, -Y, -Z);
}

const CQuaternion& CQuaternion::operator += (const CQuaternion& cQuaternion)		
{
	W += cQuaternion.W;
	X += cQuaternion.X;
	Y += cQuaternion.Y;
	Z += cQuaternion.Z;
	return *this;
}

const CQuaternion& CQuaternion::operator -= (const CQuaternion& cQuaternion)		
{
	W -= cQuaternion.W;
	X -= cQuaternion.X;
	Y -= cQuaternion.Y;
	Z -= cQuaternion.Z;
	return *this;
}

const CQuaternion& CQuaternion::operator *= (const CQuaternion& cQuaternion)		
{
	double newW = W * cQuaternion.W - X * cQuaternion.X - Y * cQuaternion.Y - Z * cQuaternion.Z;
	double newX = W * cQuaternion.X + X * cQuaternion.W + Y * cQuaternion.Z - Z * cQuaternion.Y;
	double newY = W * cQuaternion.Y + Y * cQuaternion.W + Z * cQuaternion.X - X * cQuaternion.Z;
	double newZ = W * cQuaternion.Z + Z * cQuaternion.W + X * cQuaternion.Y - Y * cQuaternion.X;
	W = newW;
	X = newX;
	Y = newY;
	Z = newZ;
	return *this;
}

const CQuaternion operator + (const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2)
{
	return CQuaternion(cQuaternion1) += cQuaternion2;
}

const CQuaternion operator - (const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2)
{
	return CQuaternion(cQuaternion1) -= cQuaternion2;
}

const CQuaternion operator * (const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2)
{
	return CQuaternion(cQuaternion1) *= cQuaternion2;
}

double CQuaternion::GetLength() const
{
	return std::sqrt(W * W + X * X + Y * Y + Z * Z);
}

double CQuaternion::GetLengthSquared() const
{
	return W * W + X * X + Y * Y + Z * Z;
}

void CQuaternion::Normalize()
{
	double fLength = GetLength();
	if (fLength == 1.0 || fLength < std::numeric_limits<double>::epsilon())
		return;
	W /= fLength;
	X /= fLength;
	Y /= fLength;
	Z /= fLength;
}

CQuaternion CQuaternion::GetNormalized() const
{
	CQuaternion cQuaternion(*this);
	cQuaternion.Normalize();
	return cQuaternion;
}

void CQuaternion::FromEulerAngles(const double fThetaZ, const double fThetaY, const double fThetaX)
{
	double fCosZ2 = cos(0.5 * fThetaZ);
	double fCosY2 = cos(0.5 * fThetaY);
	double fCosX2 = cos(0.5 * fThetaX);

	double fSinZ2 = sin(0.5 * fThetaZ);
	double fSinY2 = sin(0.5 * fThetaY);
	double fSinX2 = sin(0.5 * fThetaX);

	// and now compute quaternion
	W = fCosZ2 * fCosY2 * fCosX2 + fSinZ2 * fSinY2 * fSinX2;
	X = fCosZ2 * fCosY2 * fSinX2 - fSinZ2 * fSinY2 * fCosX2;
	Y = fCosZ2 * fSinY2 * fCosX2 + fSinZ2 * fCosY2 * fSinX2;
	Z = fSinZ2 * fCosY2 * fCosX2 - fCosZ2 * fSinY2 * fSinX2;
}

void CQuaternion::FromEulerAngles(const CVector3D& cAngles)
{
	FromEulerAngles(cAngles.Z, cAngles.Y, cAngles.X);
}

void CQuaternion::Conjugate()
{
	X = -X;
	Y = -Y;
	Z = -Z;
}

void CQuaternion::Invert()
{
	Conjugate();
	*this /= GetLengthSquared();
}

#if 0
//! returns the logarithm of a quaternion = v*a where q = [cos(a),v*sin(a)]
CQuaternion Log() const
{
	double fA = std::acos(GetW());
	double fSinA = std::sin(fA);
	CQuaternion cResult;

	cResult.SetW(0);
	if (fSinA > 0)
	{
		cResult.SetX(fA * GetX() / fSinA);
		cResult.SetY(fA * GetY() / fSinA);
		cResult.SetZ(fA * GetZ() / fSinA);
	}
	else
	{
		cResult.SetX(0);
		cResult.SetY(0);
		cResult.SetZ(0);
	}
	return cResult;
}

//! returns e^quaternion = exp(v*a) = [cos(a),vsin(a)]
quaternion exp() const
{
	float a = (float)v.length();
	float sina = (float)sin(a);
	float cosa = (float)cos(a);
	quaternion ret;

	ret.s = cosa;
	if (a > 0)
	{
		ret.v.x = sina * v.x / a;
		ret.v.y = sina * v.y / a;
		ret.v.z = sina * v.z / a;
	} else {
		ret.v.x = ret.v.y = ret.v.z = 0;
	}
	return ret;
}
#endif

CMatrix4x4 CQuaternion::ToMatrix4() const
{			
	return CMatrix4x4(W, -X, -Y, -Z,
										X, W, -Z, Y,
										Y, Z, W, -X,
										Z, -Y, X, W);
}

void CQuaternion::ToAxisAngle(CVector3D& cAxis, double& fAngle) const
{
	fAngle = acos(W);

	// pre-compute to save time
	double fSinThetaInv = 1.0 / sin(fAngle);

	// now the vector
	cAxis.X *= fSinThetaInv;
	cAxis.Y *= fSinThetaInv;
	cAxis.Z *= fSinThetaInv;

	// multiply by 2
	fAngle *= 2.0;
}

CVector3D CQuaternion::GetEulerAngles() const
{
	double fSquaredW = W * W;    
	double fSquaredX = X * X;    
	double fSquaredY = Y * Y;    
	double fSquaredZ = Z * Z;    

	CVector3D cEuler;
	cEuler.X = atan2(2.0 * (X * Y + Z * W), fSquaredX - fSquaredY - fSquaredZ + fSquaredW);
	cEuler.Y = asin(-2.0 * (X * Z - Y * W));
	cEuler.Z = atan2(2.0 * (Y * Z + X * W), -fSquaredX - fSquaredY + fSquaredZ + fSquaredW);
	return cEuler;
}

}

/* EOF */
