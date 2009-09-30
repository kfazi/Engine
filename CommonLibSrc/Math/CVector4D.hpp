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
class COMMONDLLIMPORTEXPORT CVector4D
{
	public:
		double X; /**< An X component of the vector. */
		double Y; /**< A Y component of the vector. */
		double Z; /**< A Z component of the vector. */
		double W; /**< A W component of the vector. */

		static const CVector4D ZERO; /**< A zero 4 dimensional vector. */

		static const CVector4D ONE; /**< An one 4 dimensional vector. */

		/**
		 * Default constructor.
		 */
		CVector4D();

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector4D(const double fX, const double fY, const double fZ, const double fW);

		/**
		 * Creates a copy of a vector.
		 */
		CVector4D(const CVector4D &cVector);

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
		bool operator == (const CVector4D &cVector) const;

		/**
		 * Tests two vectors for inequality.
		 */
		bool operator != (const CVector4D &cVector) const;

		/**
		 * Assignment operator.
		 */
		CVector4D &operator = (const CVector4D &cVector);

		/**
		 * Vector negation.
		 */
		CVector4D operator - ();

		/**
		 * Vector addition with assignment.
		 */
		CVector4D &operator += (const CVector4D &cVector);

		/**
		 * Vector subtraction with assignment.
		 */
		CVector4D &operator -= (const CVector4D &cVector);

		/**
		 * Vector multiplication with assignment.
		 */
		CVector4D &operator *= (const CVector4D &cVector);

		/**
		 * Tests if vector is zero vector.
		 */
		operator bool ();

		/**
		 * Vector multiplication by a scalar with assignment.
		 */
		template<typename TType> CVector4D &operator *= (TType tScalar)
		{
			X *= tScalar;
			Y *= tScalar;
			Z *= tScalar;
			W *= tScalar;
			return *this;
		}

		/**
		 * Vector division by a scalar with assignment.
		 */
		template<typename TType> CVector4D &operator /= (TType tScalar)
		{
			X /= tScalar;
			Y /= tScalar;
			Z /= tScalar;
			W /= tScalar;
			return *this;
		}

		/**
		 * Vector multiplication by a scalar.
		 */
		template<typename TType> friend CVector4D operator * (TType tScalar, const CVector4D &cVector)
		{
			return CVector4D(cVector) * tScalar;
		}

		/**
		 * Vector multiplication by a scalar.
		 */
		template<typename TType> friend CVector4D operator * (const CVector4D &cVector, TType tScalar)
		{
			return CVector4D(cVector) * tScalar;
		}

		/**
		 * Vector division by a scalar.
		 */
		template<typename TType> friend CVector4D operator / (TType tScalar, const CVector4D &cVector)
		{
			return CVector4D(cVector) / tScalar;
		}

		/**
		 * Vector division by a scalar.
		 */
		template<typename TType> friend CVector4D operator / (const CVector4D &cVector, TType tScalar)
		{
			return CVector4D(cVector) / tScalar;
		}

		/**
		 * A sum of two vectors.
		 */
		friend const CVector4D operator + (const CVector4D &cVector1, const CVector4D &cVector2);

		/**
		 * A subtraction of two vectors.
		 */
		friend const CVector4D operator - (const CVector4D &cVector1, const CVector4D &cVector2);

		/**
		 * A multiplication of two vectors.
		 */
		friend const CVector4D operator * (const CVector4D &cVector1, const CVector4D &cVector2);
};

}

#endif /* COMMON_VECTOR4D_HPP */

/* EOF */
