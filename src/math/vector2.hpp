/**
 * @file vector2.hpp
 * @brief Two element vector class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2008
 */

#ifndef ENGINE_VECTOR2_HPP
#define ENGINE_VECTOR2_HPP

#include "../common.hpp"
#include <iostream>
#include <limits>
#include <cmath>

namespace engine
{

/**
 * Class encapsulating a standard 2-element vector.
 */
class CVector2
{
	public:
		double X; /**< An X component of the vector. */
		double Y; /**< A Y component of the vector. */

		static const CVector2 ZERO; /**< A zero 2 dimensional vector. */

		static const CVector2 ONE; /**< An one 2 dimensional vector. */

		/**
		 * Default constructor.
		 */
		CVector2()
		{
			*this = ZERO;
		}

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector2(const double fX, const double fY)
		{
			X = fX;
			Y = fY;
		}

		/**
		 * Creates a copy of a vector.
		 */
		CVector2(const CVector2 &cVector)
		{
			X = cVector.X;
			Y = cVector.Y;
		}

		/**
		 * Normalizes a vector.
		 */
		inline void Normalize()
		{
			double fLength = GetLength();
			if (fLength == 1.0 || fLength < std::numeric_limits<double>::epsilon())
				return;
			X /= fLength;
			Y /= fLength;
		}

		/**
		 * Returns a length of a vector.
		 */
		inline double GetLength() const
		{
			return std::sqrt(X * X + Y * Y);
		}

		/**
		 * Tests two vectors for equality.
		 */
		inline bool operator == (const CVector2 &cVector) const
		{
			return (X == cVector.X) && (Y == cVector.Y);
		}

		/**
		 * Tests two vectors for inequality.
		 */
		inline bool operator != (const CVector2 &cVector) const
		{
			return !(*this == cVector);
		}

		/**
		 * Assignment operator.
		 */
		inline CVector2 &operator = (const CVector2 &cVector)
		{
			X = cVector.X;
			Y = cVector.Y;
			return *this;
		}

		/**
		 * Vector negation.
		 */
		inline CVector2 &operator - ()
		{
			X = -X;
			Y = -Y;
			return *this;
		}

		/**
		 * Vector addition with assignment.
		 */
		inline CVector2 &operator += (const CVector2 &cVector)
		{
			X += cVector.X;
			Y += cVector.Y;
			return *this;
		}

		/**
		 * Vector subtraction with assignment.
		 */
		inline CVector2 &operator -= (const CVector2 &cVector)
		{
			X -= cVector.X;
			Y -= cVector.Y;
			return *this;
		}

		/**
		 * Vector multiplication with assignment.
		 */
		inline CVector2 &operator *= (const CVector2 &cVector)
		{
			X *= cVector.X;
			Y *= cVector.Y;
			return *this;
		}

		/**
		 * Tests if vector is zero vector.
		 */
		inline operator bool ()
		{
			return X != 0.0 || Y != 0.0;
		}

		/**
		 * Vector multiplication by a number with assignment.
		 */
		template<typename TType> CVector2 &operator *= (TType tValue)
		{
			X *= tValue;
			Y *= tValue;
			return *this;
		}

		/**
		 * Vector division by a number with assignment.
		 */
		template<typename TType> CVector2 &operator /= (TType tValue)
		{
			X /= tValue;
			Y /= tValue;
			return *this;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename TType> friend CVector2 operator * (TType tValue, const CVector2 &cVector)
		{
			return CVector2(cVector) * tValue;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename TType> friend CVector2 operator * (const CVector2 &cVector, TType tValue)
		{
			return CVector2(cVector) * tValue;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename TType> friend CVector2 operator / (TType tValue, const CVector2 &cVector)
		{
			return CVector2(cVector) / tValue;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename TType> friend CVector2 operator / (const CVector2 &cVector, TType tValue)
		{
			return CVector2(cVector) / tValue;
		}

		/**
		 * A sum of two vectors.
		 */
		inline friend const CVector2 operator + (const CVector2 &cVector1, const CVector2 &cVector2)
		{
			return CVector2(cVector1) += cVector2;
		}

		/**
		 * A subtraction of two vectors.
		 */
		inline friend const CVector2 operator - (const CVector2 &cVector1, const CVector2 &cVector2)
		{
			return CVector2(cVector1) -= cVector2;
		}

		/**
		 * A multiplication of two vectors.
		 */
		inline friend const CVector2 operator * (const CVector2 &cVector1, const CVector2 &cVector2)
		{
			return CVector2(cVector1) *= cVector2;
		}

		/**
		 * Writing to a stream.
		 */
		inline friend std::ostream &operator << (std::ostream &cOutputStream, const CVector2 &cVector)
		{
			cOutputStream << "CVector2(" << cVector.X << ", " << cVector.Y <<  ")";
			return cOutputStream;
		}
};

}

#endif /* ENGINE_VECTOR2_HPP */

/* EOF */

