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
class COMMONDLLIMPORTEXPORT CVector2D
{
	public:
		static const CVector2D ZERO; /**< A zero 2 dimensional vector. */
		static const CVector2D ONE; /**< An one 2 dimensional vector. */

		double X; /**< An X component of the vector. */
		double Y; /**< A Y component of the vector. */

		/**
		 * Default constructor.
		 */
		CVector2D();

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector2D(const double fX, const double fY);

		/**
		 * Creates a copy of a vector.
		 */
		CVector2D(const CVector2D& cVector);

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
		bool operator== (const CVector2D& cVector) const;

		/**
		 * Tests two vectors for inequality.
		 */
		bool operator!= (const CVector2D& cVector) const;

		/**
		 * Assignment operator.
		 */
		CVector2D& operator= (const CVector2D& cVector);

		/**
		 * Vector negation.
		 */
		CVector2D& operator- ();

		/**
		 * Vector addition with assignment.
		 */
		CVector2D& operator+= (const CVector2D& cVector);

		/**
		 * Vector subtraction with assignment.
		 */
		CVector2D& operator-= (const CVector2D& cVector);

		/**
		 * Vector multiplication with assignment.
		 */
		CVector2D& operator*= (const CVector2D& cVector);

		/**
		 * Tests if vector is zero vector.
		 */
		operator bool ();

		/**
		 * Vector multiplication by a number with assignment.
		 */
		template<typename TType> CVector2D& operator*= (TType tValue)
		{
			X *= tValue;
			Y *= tValue;
			return *this;
		}

		/**
		 * Vector division by a number with assignment.
		 */
		template<typename TType> CVector2D& operator/= (TType tValue)
		{
			X /= tValue;
			Y /= tValue;
			return *this;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename TType> friend CVector2D operator* (TType tValue, const CVector2D& cVector)
		{
			return operator* (cVector, tValue);
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename TType> friend CVector2D operator* (const CVector2D& cVector, TType tValue)
		{
			CVector2D cResult(cVector);
			cResult *= tValue;
			return cResult;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename TType> friend CVector2D operator/ (TType tValue, const CVector2D& cVector)
		{
			return operator/ (cVector, tValue);
		}

		/**
		 * Vector division by a number.
		 */
		template<typename TType> friend CVector2D operator/ (const CVector2D& cVector, TType tValue)
		{
			CVector2D cResult(cVector);
			cResult /= tValue;
			return cResult;
		}

		/**
		 * A sum of two vectors.
		 */
		friend const CVector2D operator+ (const CVector2D& cVector1, const CVector2D& cVector2);

		/**
		 * A subtraction of two vectors.
		 */
		friend const CVector2D operator- (const CVector2D& cVector1, const CVector2D& cVector2);

		/**
		 * A multiplication of two vectors.
		 */
		friend const CVector2D operator* (const CVector2D& cVector1, const CVector2D& cVector2);
};

}

#endif /* COMMON_VECTOR2D_HPP */

/* EOF */

