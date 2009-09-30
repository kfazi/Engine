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
class COMMONDLLIMPORTEXPORT CVector3D
{
	public:
		static const CVector3D ZERO; /**< A zero 3 dimensional vector. */
		static const CVector3D ONE; /**< An one 3 dimensional vector. */

		double X; /**< An X component of the vector. */
		double Y; /**< A Y component of the vector. */
		double Z; /**< A Z component of the vector. */

		/**
		 * Default constructor.
		 */
		CVector3D();

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector3D(const double fX, const double fY, const double fZ);

		/**
		 * Creates a copy of a vector.
		 */
		CVector3D(const CVector3D &cVector);

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
		bool operator == (const CVector3D &cVector) const;

		/**
		 * Tests two vectors for inequality.
		 */
		bool operator != (const CVector3D &cVector) const;

		/**
		 * Assignment operator.
		 */
		CVector3D &operator = (const CVector3D &cVector);

		/**
		 * Vector negation.
		 */
		CVector3D &operator - ();

		/**
		 * Vector addition with assignment.
		 */
		CVector3D &operator += (const CVector3D &cVector);

		/**
		 * Vector subtraction with assignment.
		 */
		CVector3D &operator -= (const CVector3D &cVector);

		/**
		 * Vector multiplication with assignment.
		 */
		CVector3D &operator *= (const CVector3D &cVector);

		/**
		 * Tests if vector is zero vector.
		 */
		operator bool ();

		/**
		 * Vector multiplication by a number with assignment.
		 */
		template<typename TType> CVector3D &operator *= (TType tValue)
		{
			X *= tValue;
			Y *= tValue;
			Z *= tValue;
			return *this;
		}

		/**
		 * Vector division by a number with assignment.
		 */
		template<typename TType> CVector3D &operator /= (TType tValue)
		{
			X /= tValue;
			Y /= tValue;
			Z /= tValue;
			return *this;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename TType> friend CVector3D operator * (TType tValue, const CVector3D &cVector)
		{
			return CVector3D(cVector) * tValue;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename TType> friend CVector3D operator * (const CVector3D &cVector, TType tValue)
		{
			return CVector3D(cVector) * tValue;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename TType> friend CVector3D operator / (TType tValue, const CVector3D &cVector)
		{
			return CVector3D(cVector) / tValue;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename TType> friend CVector3D operator / (const CVector3D &cVector, TType tValue)
		{
			return CVector3D(cVector) / tValue;
		}

		/**
		 * A sum of two vectors.
		 */
		friend const CVector3D operator + (const CVector3D &cVector1, const CVector3D &cVector2);

		/**
		 * A subtraction of two vectors.
		 */
		friend const CVector3D operator - (const CVector3D &cVector1, const CVector3D &cVector2);

		/**
		 * A multiplication of two vectors.
		 */
		friend const CVector3D operator * (const CVector3D &cVector1, const CVector3D &cVector2);
};

}

#endif /* COMMON_VECTOR3D_HPP */

/* EOF */

