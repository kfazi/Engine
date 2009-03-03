/**
 * @file vector3.hpp
 * @brief Three element vector class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2008
 */

#ifndef ENGINE_VECTOR3_HPP
#define ENGINE_VECTOR3_HPP

#include "../common.hpp"
#include <iostream>
#include <limits>
#include <cmath>

namespace engine
{

/**
 * Class encapsulating a standard 3-element vector.
 */
class CVector3
{
	public:
		double X; /**< An X component of the vector. */
		double Y; /**< A Y component of the vector. */
		double Z; /**< A Z component of the vector. */

		static const CVector3 ZERO; /**< A zero 3 dimensional vector. */

		static const CVector3 ONE; /**< An one 3 dimensional vector. */

		/**
		 * Default constructor.
		 */
		CVector3()
		{
			*this = ZERO;
		}

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector3(const double fX, const double fY, const double fZ)
		{
			X = fX;
			Y = fY;
			Z = fZ;
		}

		/**
		 * Creates a copy of a vector.
		 */
		CVector3(const CVector3 &cVector)
		{
			X = cVector.X;
			Y = cVector.Y;
			Z = cVector.Z;
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
			Z /= fLength;
		}

		/**
		 * Returns a length of a vector.
		 */
		inline double GetLength() const
		{
			return std::sqrt(X * X + Y * Y + Z * Z);
		}

		/**
		 * Tests two vectors for equality.
		 */
		inline bool operator == (const CVector3 &cVector) const
		{
			return (X == cVector.X) && (Y == cVector.Y) && (Z == cVector.Z);
		}

		/**
		 * Tests two vectors for inequality.
		 */
		inline bool operator != (const CVector3 &cVector) const
		{
			return !(*this == cVector);
		}

		/**
		 * Assignment operator.
		 */
		inline CVector3 &operator = (const CVector3 &cVector)
		{
			X = cVector.X;
			Y = cVector.Y;
			Z = cVector.Z;
			return *this;
		}

		/**
		 * Vector negation.
		 */
		inline CVector3 &operator - ()
		{
			X = -X;
			Y = -Y;
			Z = -Z;
			return *this;
		}

		/**
		 * Vector addition with assignment.
		 */
		inline CVector3 &operator += (const CVector3 &cVector)
		{
			X += cVector.X;
			Y += cVector.Y;
			Z += cVector.Z;
			return *this;
		}

		/**
		 * Vector subtraction with assignment.
		 */
		inline CVector3 &operator -= (const CVector3 &cVector)
		{
			X -= cVector.X;
			Y -= cVector.Y;
			Z -= cVector.Z;
			return *this;
		}

		/**
		 * Vector multiplication with assignment.
		 */
		inline CVector3 &operator *= (const CVector3 &cVector)
		{
			X *= cVector.X;
			Y *= cVector.Y;
			Z *= cVector.Z;
			return *this;
		}

		/**
		 * Tests if vector is zero vector.
		 */
		inline operator bool ()
		{
			return X != 0.0 || Y != 0.0 || Z != 0.0;
		}

		/**
		 * Vector multiplication by a number with assignment.
		 */
		template<typename TType> CVector3 &operator *= (TType tValue)
		{
			X *= tValue;
			Y *= tValue;
			Z *= tValue;
			return *this;
		}

		/**
		 * Vector division by a number with assignment.
		 */
		template<typename TType> CVector3 &operator /= (TType tValue)
		{
			X /= tValue;
			Y /= tValue;
			Z /= tValue;
			return *this;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename TType> friend CVector3 operator * (TType tValue, const CVector3 &cVector)
		{
			return CVector3(cVector) * tValue;
		}

		/**
		 * Vector multiplication by a number.
		 */
		template<typename TType> friend CVector3 operator * (const CVector3 &cVector, TType tValue)
		{
			return CVector3(cVector) * tValue;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename TType> friend CVector3 operator / (TType tValue, const CVector3 &cVector)
		{
			return CVector3(cVector) / tValue;
		}

		/**
		 * Vector division by a number.
		 */
		template<typename TType> friend CVector3 operator / (const CVector3 &cVector, TType tValue)
		{
			return CVector3(cVector) / tValue;
		}

		/**
		 * A sum of two vectors.
		 */
		inline friend const CVector3 operator + (const CVector3 &cVector1, const CVector3 &cVector2)
		{
			return CVector3(cVector1) += cVector2;
		}

		/**
		 * A subtraction of two vectors.
		 */
		inline friend const CVector3 operator - (const CVector3 &cVector1, const CVector3 &cVector2)
		{
			return CVector3(cVector1) -= cVector2;
		}

		/**
		 * A multiplication of two vectors.
		 */
		inline friend const CVector3 operator * (const CVector3 &cVector1, const CVector3 &cVector2)
		{
			return CVector3(cVector1) *= cVector2;
		}

		/**
		 * Writing to a stream.
		 */
		inline friend std::ostream &operator << (std::ostream &cOutputStream, const CVector3 &cVector)
		{
			cOutputStream << "CVector3(" << cVector.X << ", " << cVector.Y << ", " << cVector.Z << ")";
			return cOutputStream;
		}
};

}

#endif /* ENGINE_VECTOR3_HPP */

/* EOF */

