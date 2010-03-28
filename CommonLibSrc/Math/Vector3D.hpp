/**
 * @file CVector3D.hpp
 * @brief Three element vector class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2009
 */

#ifndef COMMON_VECTOR3D_HPP
#define COMMON_VECTOR3D_HPP

#include "../Internal.hpp"

namespace Common
{

/**
 * Class encapsulating a standard 3-element vector.
 */
class COMMONDLLIMPORTEXPORT Vector3D
{
	public:
		static const Vector3D ZERO; /**< A zero 3 dimensional vector. */
		static const Vector3D ONE; /**< An one 3 dimensional vector. */

		double X; /**< An X component of the vector. */
		double Y; /**< A Y component of the vector. */
		double Z; /**< A Z component of the vector. */

		/**
		 * Default constructor.
		 */
		Vector3D();

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		Vector3D(double x, double y, double z);

		/**
		 * Creates a copy of a vector.
		 */
		Vector3D(const Vector3D& vector);

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
		bool operator== (const Vector3D& vector) const;

		/**
		 * Tests two vectors for inequality.
		 */
		bool operator!= (const Vector3D& vector) const;

		/**
		 * Assignment operator.
		 */
		Vector3D& operator= (const Vector3D& vector);

		/**
		 * Vector negation.
		 */
		Vector3D& operator- ();

		/**
		 * Vector addition with assignment.
		 */
		Vector3D& operator+= (const Vector3D& vector);

		/**
		 * Vector subtraction with assignment.
		 */
		Vector3D& operator-= (const Vector3D& vector);

		/**
		 * Vector multiplication with assignment.
		 */
		Vector3D& operator*= (const Vector3D& vector);

		/**
		 * Tests if vector is zero vector.
		 */
		operator bool ();

		/**
		 * Vector multiplication by a number with assignment.
		 */
		template<typename Type> Vector3D& operator*= (Type value)
		{
			X *= value;
			Y *= value;
			Z *= value;
			return *this;
		}

		/**
		 * Vector division by a number with assignment.
		 */
		template<typename Type> Vector3D& operator/= (Type value)
		{
			X /= value;
			Y /= value;
			Z /= value;
			return *this;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename Type> friend Vector3D operator* (Type value, const Vector3D& vector)
		{
			return Vector3D(vector) * value;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename Type> friend Vector3D operator* (const Vector3D& vector, Type value)
		{
			return Vector3D(vector) * value;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename Type> friend Vector3D operator/ (Type value, const Vector3D& vector)
		{
			return Vector3D(vector) / value;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename Type> friend Vector3D operator/ (const Vector3D& vector, Type value)
		{
			return Vector3D(vector) / value;
		}

		/**
		 * A sum of two vectors.
		 */
		friend const Vector3D operator+ (const Vector3D& vector1, const Vector3D& vector2);

		/**
		 * A subtraction of two vectors.
		 */
		friend const Vector3D operator- (const Vector3D& vector1, const Vector3D& vector2);

		/**
		 * A multiplication of two vectors.
		 */
		friend const Vector3D operator* (const Vector3D& vector1, const Vector3D& vector2);
};

}

#endif /* COMMON_VECTOR3D_HPP */

/* EOF */

