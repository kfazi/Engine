/**
 * @file CVector4D.hpp
 * @brief Four element vector class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2009
 */

#ifndef COMMON_VECTOR4D_HPP
#define COMMON_VECTOR4D_HPP

#include "../Internal.hpp"

namespace Common
{

/**
 * Class encapsulating a standard 4-element vector.
 */
class COMMONDLLIMPORTEXPORT Vector4D
{
	public:
		double X; /**< An X component of the vector. */
		double Y; /**< A Y component of the vector. */
		double Z; /**< A Z component of the vector. */
		double W; /**< A W component of the vector. */

		static const Vector4D ZERO; /**< A zero 4 dimensional vector. */

		static const Vector4D ONE; /**< An one 4 dimensional vector. */

		/**
		 * Default constructor.
		 */
		Vector4D();

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		Vector4D(double x, double y, double z, double w);

		/**
		 * Creates a copy of a vector.
		 */
		Vector4D(const Vector4D& vector);

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
		bool operator== (const Vector4D& vector) const;

		/**
		 * Tests two vectors for inequality.
		 */
		bool operator!= (const Vector4D& vector) const;

		/**
		 * Assignment operator.
		 */
		Vector4D& operator= (const Vector4D& vector);

		/**
		 * Vector negation.
		 */
		Vector4D operator- ();

		/**
		 * Vector addition with assignment.
		 */
		Vector4D& operator+= (const Vector4D& vector);

		/**
		 * Vector subtraction with assignment.
		 */
		Vector4D& operator-= (const Vector4D& vector);

		/**
		 * Vector multiplication with assignment.
		 */
		Vector4D& operator*= (const Vector4D& vector);

		/**
		 * Tests if vector is zero vector.
		 */
		operator bool ();

		/**
		 * Vector multiplication by a scalar with assignment.
		 */
		template<typename Type> Vector4D& operator*= (Type scalar)
		{
			X *= scalar;
			Y *= scalar;
			Z *= scalar;
			W *= scalar;
			return *this;
		}

		/**
		 * Vector division by a scalar with assignment.
		 */
		template<typename Type> Vector4D& operator/= (Type scalar)
		{
			X /= scalar;
			Y /= scalar;
			Z /= scalar;
			W /= scalar;
			return *this;
		}

		/**
		 * Vector multiplication by a scalar.
		 */
		template<typename Type> friend Vector4D operator* (Type scalar, const Vector4D& vector)
		{
			return Vector4D(vector) * scalar;
		}

		/**
		 * Vector multiplication by a scalar.
		 */
		template<typename Type> friend Vector4D operator* (const Vector4D& vector, Type scalar)
		{
			return Vector4D(vector) * scalar;
		}

		/**
		 * Vector division by a scalar.
		 */
		template<typename Type> friend Vector4D operator/ (Type scalar, const Vector4D& vector)
		{
			return Vector4D(vector) / scalar;
		}

		/**
		 * Vector division by a scalar.
		 */
		template<typename Type> friend Vector4D operator/ (const Vector4D& vector, Type scalar)
		{
			return Vector4D(vector) / scalar;
		}

		/**
		 * A sum of two vectors.
		 */
		friend const Vector4D operator+ (const Vector4D& vector1, const Vector4D& vector2);

		/**
		 * A subtraction of two vectors.
		 */
		friend const Vector4D operator- (const Vector4D& vector1, const Vector4D& vector2);

		/**
		 * A multiplication of two vectors.
		 */
		friend const Vector4D operator* (const Vector4D& vector1, const Vector4D& vector2);
};

}

#endif /* COMMON_VECTOR4D_HPP */

/* EOF */
