/**
 * @file CVector2D.hpp
 * @brief Two element vector class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2009
 */

#ifndef COMMON_VECTOR2D_HPP
#define COMMON_VECTOR2D_HPP

#include "../Internal.hpp"

namespace Common
{

/**
 * Class encapsulating a standard 2-element vector.
 */
class COMMONDLLIMPORTEXPORT Vector2D
{
	public:
		static const Vector2D ZERO; /**< A zero 2 dimensional vector. */
		static const Vector2D ONE; /**< An one 2 dimensional vector. */

		double X; /**< An X component of the vector. */
		double Y; /**< A Y component of the vector. */

		/**
		 * Default constructor.
		 */
		Vector2D();

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		Vector2D(double x, double y);

		/**
		 * Creates a copy of a vector.
		 */
		Vector2D(const Vector2D& vector);

		/**
		 * Normalizes a vector.
		 */
		void Normalize();

		/**
		 * Returns a length of a vector.
		 */
		double GetLength() const;

		/**
		 * Tests two vectors for equality.
		 */
		bool operator== (const Vector2D& vector) const;

		/**
		 * Tests two vectors for inequality.
		 */
		bool operator!= (const Vector2D& vector) const;

		/**
		 * Assignment operator.
		 */
		Vector2D& operator= (const Vector2D& vector);

		/**
		 * Vector negation.
		 */
		Vector2D& operator- ();

		/**
		 * Vector addition with assignment.
		 */
		Vector2D& operator+= (const Vector2D& vector);

		/**
		 * Vector subtraction with assignment.
		 */
		Vector2D& operator-= (const Vector2D& vector);

		/**
		 * Vector multiplication with assignment.
		 */
		Vector2D& operator*= (const Vector2D& vector);

		/**
		 * Tests if vector is zero vector.
		 */
		operator bool ();

		/**
		 * Vector multiplication by a number with assignment.
		 */
		template<typename Type> Vector2D& operator*= (Type value)
		{
			X *= value;
			Y *= value;
			return *this;
		}

		/**
		 * Vector division by a number with assignment.
		 */
		template<typename Type> Vector2D& operator/= (Type value)
		{
			X /= value;
			Y /= value;
			return *this;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename Type> friend Vector2D operator* (Type value, const Vector2D& vector)
		{
			return operator* (vector, value);
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename Type> friend Vector2D operator* (const Vector2D& vector, Type value)
		{
			Vector2D result(vector);
			result *= value;
			return result;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename Type> friend Vector2D operator/ (Type value, const Vector2D& vector)
		{
			return operator/ (vector, value);
		}

		/**
		 * Vector division by a number.
		 */
		template<typename Type> friend Vector2D operator/ (const Vector2D& vector, Type value)
		{
			Vector2D result(vector);
			result /= value;
			return result;
		}

		/**
		 * A sum of two vectors.
		 */
		friend const Vector2D operator+ (const Vector2D& vector1, const Vector2D& vector2);

		/**
		 * A subtraction of two vectors.
		 */
		friend const Vector2D operator- (const Vector2D& vector1, const Vector2D& vector2);

		/**
		 * A multiplication of two vectors.
		 */
		friend const Vector2D operator* (const Vector2D& vector1, const Vector2D& vector2);
};

}

#endif /* COMMON_VECTOR2D_HPP */

/* EOF */

