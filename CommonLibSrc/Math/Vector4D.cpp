#include "../Internal.hpp"
#include "Vector4D.hpp"
#include <limits>

namespace Common
{

const Vector4D Vector4D::ZERO(0.0, 0.0, 0.0, 0.0);

const Vector4D Vector4D::ONE(1.0, 1.0, 1.0, 1.0);

Vector4D::Vector4D()
{
	*this = ZERO;
}

Vector4D::Vector4D(double x, double y, double z, double w) : X(x), Y(y), Z(z), W(w)
{
}

Vector4D::Vector4D(const Vector4D& vector) : X(vector.X), Y(vector.Y), Z(vector.Z), W(vector.W)
{
}

void Vector4D::Normalize()
{
	double length = GetLength();
	if (length == 1.0 || length < std::numeric_limits<double>::epsilon())
		return;
	X /= length;
	Y /= length;
	Z /= length;
	W /= length;
}

double Vector4D::GetLength() const
{
	return std::sqrt(X * X + Y * Y + Z * Z + W * W);
}

bool Vector4D::operator== (const Vector4D& vector) const
{
	return (X == vector.X) && (Y == vector.Y) && (Z == vector.Z) && (W == vector.W);
}

bool Vector4D::operator!= (const Vector4D& vector) const
{
	return !(*this == vector);
}

Vector4D& Vector4D::operator= (const Vector4D& vector)
{
	X = vector.X;
	Y = vector.Y;
	Z = vector.Z;
	W = vector.W;
	return *this;
}

Vector4D Vector4D::operator- ()
{
	return Vector4D(-X, -Y, -Z, -W);
}

Vector4D& Vector4D::operator+= (const Vector4D& vector)
{
	X += vector.X;
	Y += vector.Y;
	Z += vector.Z;
	W += vector.W;
	return *this;
}

Vector4D& Vector4D::operator-= (const Vector4D& vector)
{
	X -= vector.X;
	Y -= vector.Y;
	Z -= vector.Z;
	W -= vector.W;
	return *this;
}

Vector4D& Vector4D::operator*= (const Vector4D& vector)
{
	X *= vector.X;
	Y *= vector.Y;
	Z *= vector.Z;
	W *= vector.W;
	return *this;
}

Vector4D::operator bool ()
{
	return X != 0.0 || Y != 0.0 || Z != 0.0 || W != 0.0;
}

const Vector4D operator+ (const Vector4D& vector1, const Vector4D& vector2)
{
	return Vector4D(vector1) += vector2;
}

const Vector4D operator- (const Vector4D& vector1, const Vector4D& vector2)
{
	return Vector4D(vector1) -= vector2;
}

const Vector4D operator* (const Vector4D& vector1, const Vector4D& vector2)
{
	return Vector4D(vector1) *= vector2;
}

}

/* EOF */
