#include "../Internal.hpp"
#include "Vector2D.hpp"
#include <limits>

namespace Common
{

const Vector2D Vector2D::ZERO(0.0, 0.0);

const Vector2D Vector2D::ONE(1.0, 1.0);

Vector2D::Vector2D()
{
	*this = ZERO;
}

Vector2D::Vector2D(double x, double y) : X(x), Y(y)
{
}

Vector2D::Vector2D(const Vector2D& vector) : X(vector.X), Y(vector.Y)
{
}

void Vector2D::Normalize()
{
	double length = GetLength();
	if (length == 1.0 || length < std::numeric_limits<double>::epsilon())
		return;
	X /= length;
	Y /= length;
}

double Vector2D::GetLength() const
{
	return std::sqrt(X * X + Y * Y);
}

bool Vector2D::operator== (const Vector2D& vector) const
{
	return (X == vector.X) && (Y == vector.Y);
}

bool Vector2D::operator!= (const Vector2D& vector) const
{
	return !(*this == vector);
}

Vector2D& Vector2D::operator= (const Vector2D& vector)
{
	X = vector.X;
	Y = vector.Y;
	return *this;
}

Vector2D& Vector2D::operator- ()
{
	X = -X;
	Y = -Y;
	return *this;
}

Vector2D& Vector2D::operator+= (const Vector2D& vector)
{
	X += vector.X;
	Y += vector.Y;
	return *this;
}

Vector2D& Vector2D::operator-= (const Vector2D& vector)
{
	X -= vector.X;
	Y -= vector.Y;
	return *this;
}

Vector2D& Vector2D::operator*= (const Vector2D& vector)
{
	X *= vector.X;
	Y *= vector.Y;
	return *this;
}

Vector2D::operator bool ()
{
	return X != 0.0 || Y != 0.0;
}

const Vector2D operator+ (const Vector2D& vector1, const Vector2D& vector2)
{
	return Vector2D(vector1) += vector2;
}

const Vector2D operator- (const Vector2D& vector1, const Vector2D& vector2)
{
	return Vector2D(vector1) -= vector2;
}

const Vector2D operator* (const Vector2D& vector1, const Vector2D& vector2)
{
	return Vector2D(vector1) *= vector2;
}

}

/* EOF */

