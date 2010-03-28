#include "../Internal.hpp"
#include "Quaternion.hpp"
#include "Matrix4x4.hpp"
#include "Vector3D.hpp"
#include <cmath>
#include <limits>

namespace Common
{

const Quaternion Quaternion::ZERO(0.0, 0.0, 0.0, 0.0);

const Quaternion Quaternion::IDENTITY(1.0, 0.0, 0.0, 0.0);

Vector3D Quaternion::GetVector() const
{
	return Vector3D(X, Y, Z);
}

Quaternion::Quaternion()
{
	*this = IDENTITY;
}

Quaternion::Quaternion(double w, double x, double y, double z) : W(w), X(x), Y(y), Z(z)
{
}

Quaternion::Quaternion(double real, const Vector3D& vector) : W(real), X(vector.X), Y(vector.Y),
	Z(vector.Z)
{
}

Quaternion::Quaternion(double thetaZ, double thetaY, double thetaX)
{
	FromEulerAngles(thetaZ, thetaY, thetaX);
}

Quaternion::Quaternion(const Vector3D& angles)
{
	FromEulerAngles(angles);
} 

Quaternion::Quaternion(const Vector3D& axis, double angle)
{
	double sin_angle = sin(angle / 2.0);
	W = cos(angle / 2.0);
	X = axis.X * sin_angle;
	Y = axis.Y * sin_angle;
	Z = axis.Z * sin_angle;
}

Quaternion& Quaternion::operator= (const Quaternion& quaternion)		
{
	W = quaternion.W;
	X = quaternion.X;
	Y = quaternion.Y;
	Z = quaternion.Z;
	return *this;
}

Quaternion Quaternion::operator- () const
{
	return Quaternion(-W, -X, -Y, -Z);
}

const Quaternion& Quaternion::operator+= (const Quaternion& quaternion)		
{
	W += quaternion.W;
	X += quaternion.X;
	Y += quaternion.Y;
	Z += quaternion.Z;
	return *this;
}

const Quaternion& Quaternion::operator-= (const Quaternion& quaternion)		
{
	W -= quaternion.W;
	X -= quaternion.X;
	Y -= quaternion.Y;
	Z -= quaternion.Z;
	return *this;
}

const Quaternion& Quaternion::operator*= (const Quaternion& quaternion)		
{
	double w = W * quaternion.W - X * quaternion.X - Y * quaternion.Y - Z * quaternion.Z;
	double x = W * quaternion.X + X * quaternion.W + Y * quaternion.Z - Z * quaternion.Y;
	double y = W * quaternion.Y + Y * quaternion.W + Z * quaternion.X - X * quaternion.Z;
	double z = W * quaternion.Z + Z * quaternion.W + X * quaternion.Y - Y * quaternion.X;
	W = w;
	X = x;
	Y = y;
	Z = z;
	return *this;
}

const Quaternion operator+ (const Quaternion& quaternion1, const Quaternion& quaternion2)
{
	return Quaternion(quaternion1) += quaternion2;
}

const Quaternion operator- (const Quaternion& quaternion1, const Quaternion& quaternion2)
{
	return Quaternion(quaternion1) -= quaternion2;
}

const Quaternion operator* (const Quaternion& quaternion1, const Quaternion& quaternion2)
{
	return Quaternion(quaternion1) *= quaternion2;
}

double Quaternion::GetLength() const
{
	return std::sqrt(W * W + X * X + Y * Y + Z * Z);
}

double Quaternion::GetLengthSquared() const
{
	return W * W + X * X + Y * Y + Z * Z;
}

void Quaternion::Normalize()
{
	double length = GetLength();
	if (length == 1.0 || length < std::numeric_limits<double>::epsilon())
		return;
	W /= length;
	X /= length;
	Y /= length;
	Z /= length;
}

Quaternion Quaternion::GetNormalized() const
{
	Quaternion quaternion(*this);
	quaternion.Normalize();
	return quaternion;
}

void Quaternion::FromEulerAngles(double thetaZ, double thetaY, double thetaX)
{
	double cos_z2 = cos(0.5 * thetaZ);
	double cos_y2 = cos(0.5 * thetaY);
	double cos_x2 = cos(0.5 * thetaX);

	double sin_z2 = sin(0.5 * thetaZ);
	double sin_y2 = sin(0.5 * thetaY);
	double sin_x2 = sin(0.5 * thetaX);

	// and now compute quaternion
	W = cos_z2 * cos_y2 * cos_x2 + sin_z2 * sin_y2 * sin_x2;
	X = cos_z2 * cos_y2 * sin_x2 - sin_z2 * sin_y2 * cos_x2;
	Y = cos_z2 * sin_y2 * cos_x2 + sin_z2 * cos_y2 * sin_x2;
	Z = sin_z2 * cos_y2 * cos_x2 - cos_z2 * sin_y2 * sin_x2;
}

void Quaternion::FromEulerAngles(const Vector3D& angles)
{
	FromEulerAngles(angles.Z, angles.Y, angles.X);
}

void Quaternion::Conjugate()
{
	X = -X;
	Y = -Y;
	Z = -Z;
}

void Quaternion::Invert()
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
	CQuaternion result;

	result.SetW(0);
	if (fSinA > 0)
	{
		result.SetX(fA * GetX() / fSinA);
		result.SetY(fA * GetY() / fSinA);
		result.SetZ(fA * GetZ() / fSinA);
	}
	else
	{
		result.SetX(0);
		result.SetY(0);
		result.SetZ(0);
	}
	return result;
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

Matrix4x4 Quaternion::ToMatrix4() const
{			
	return Matrix4x4(W, -X, -Y, -Z,
										X, W, -Z, Y,
										Y, Z, W, -X,
										Z, -Y, X, W);
}

void Quaternion::ToAxisAngle(Vector3D& axis, double& angle) const
{
	angle = acos(W);

	// pre-compute to save time
	double sin_theta_inv = 1.0 / sin(angle);

	// now the vector
	axis.X *= sin_theta_inv;
	axis.Y *= sin_theta_inv;
	axis.Z *= sin_theta_inv;

	// multiply by 2
	angle *= 2.0;
}

Vector3D Quaternion::GetEulerAngles() const
{
	double squared_w = W * W;    
	double squared_x = X * X;    
	double squared_y = Y * Y;    
	double squared_z = Z * Z;    

	Vector3D euler;
	euler.X = atan2(2.0 * (X * Y + Z * W), squared_x - squared_y - squared_z + squared_w);
	euler.Y = asin(-2.0 * (X * Z - Y * W));
	euler.Z = atan2(2.0 * (Y * Z + X * W), -squared_x - squared_y + squared_z + squared_w);
	return euler;
}

}

/* EOF */
