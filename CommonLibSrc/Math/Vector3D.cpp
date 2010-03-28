#include "../Internal.hpp"
#include "Vector3D.hpp"
#include <limits>

namespace Common
{

const Vector3D Vector3D::ZERO(0.0, 0.0, 0.0);

const Vector3D Vector3D::ONE(1.0, 1.0, 1.0);

Vector3D::Vector3D()
{
	*this = ZERO;
}

Vector3D::Vector3D(double x, double y, double z) : X(x), Y(y), Z(z)
{
}

Vector3D::Vector3D(const Vector3D& vector) : X(vector.X), Y(vector.Y), Z(vector.Z)
{
}

void Vector3D::Normalize()
{
	double length = GetLength();
	if (length == 1.0 || length < std::numeric_limits<double>::epsilon())
		return;
	X /= length;
	Y /= length;
	Z /= length;
}

double Vector3D::GetLength() const
{
	return std::sqrt(X * X + Y * Y + Z * Z);
}

bool Vector3D::operator== (const Vector3D& vector) const
{
	return (X == vector.X) && (Y == vector.Y) && (Z == vector.Z);
}

bool Vector3D::operator!= (const Vector3D& vector) const
{
	return !(*this == vector);
}

Vector3D& Vector3D::operator= (const Vector3D& vector)
{
	X = vector.X;
	Y = vector.Y;
	Z = vector.Z;
	return *this;
}

Vector3D& Vector3D::operator- ()
{
	X = -X;
	Y = -Y;
	Z = -Z;
	return *this;
}

Vector3D& Vector3D::operator+= (const Vector3D& vector)
{
	X += vector.X;
	Y += vector.Y;
	Z += vector.Z;
	return *this;
}

Vector3D& Vector3D::operator-= (const Vector3D& vector)
{
	X -= vector.X;
	Y -= vector.Y;
	Z -= vector.Z;
	return *this;
}

Vector3D& Vector3D::operator*= (const Vector3D& vector)
{
	X *= vector.X;
	Y *= vector.Y;
	Z *= vector.Z;
	return *this;
}

Vector3D::operator bool ()
{
	return X != 0.0 || Y != 0.0 || Z != 0.0;
}

const Vector3D operator+ (const Vector3D& vector1, const Vector3D& vector2)
{
	return Vector3D(vector1) += vector2;
}

const Vector3D operator- (const Vector3D& vector1, const Vector3D& vector2)
{
	return Vector3D(vector1) -= vector2;
}

const Vector3D operator* (const Vector3D& vector1, const Vector3D& vector2)
{
	return Vector3D(vector1) *= vector2;
}

}

/* EOF */
