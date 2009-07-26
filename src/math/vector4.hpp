/**
 * @file vector4.hpp
 * @brief Four element vector class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2008
 */

#ifndef ENGINE_VECTOR4_HPP
#define ENGINE_VECTOR4_HPP

#include "../common.hpp"
#include <iostream>
#include <limits>
#include <cmath>

namespace engine
{

/**
 * Class encapsulating a standard 4-element vector.
 */
class CVector4
{
	public:
		double X; /**< An X component of the vector. */
		double Y; /**< A Y component of the vector. */
		double Z; /**< A Z component of the vector. */
		double W; /**< A W component of the vector. */

		static const CVector4 ZERO; /**< A zero 4 dimensional vector. */

		static const CVector4 ONE; /**< An one 4 dimensional vector. */

		/**
		 * Default constructor.
		 */
		CVector4()
		{
			*this = ZERO;
		}

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector4(const double fX, const double fY, const double fZ, const double fW)
		{
			X = fX;
			Y = fY;
			Z = fZ;
			W = fW;
		}

		/**
		 * Creates a copy of a vector.
		 */
		CVector4(const CVector4 &cVector)
		{
			X = cVector.X;
			Y = cVector.Y;
			Z = cVector.Z;
			W = cVector.W;
		}

		/**
		 * Normalizes a vector.
		 */
		inline void Normalize()
		{
			double fLength = GetLength();
			if (fLength == 1.0 || fLength < std::numeric_limits<double>::epsilon())
				return;
			X = X / fLength;
			Y = Y / fLength;
			Z = Z / fLength;
			W = W / fLength;
		}

		/**
		 * Returns a length of a vector.
		 */
		inline double GetLength() const
		{
			return std::sqrt(X * X + Y * Y + Z * Z + W * W);
		}

		/**
		 * Tests two vectors for equality.
		 */
		inline bool operator == (const CVector4 &cVector) const
		{
			return (X == cVector.X) && (Y == cVector.Y) && (Z == cVector.Z) && (W == cVector.W);
		}

		/**
		 * Tests two vectors for inequality.
		 */
		inline bool operator != (const CVector4 &cVector) const
		{
			return !(*this == cVector);
		}

		/**
		 * Assignment operator.
		 */
		inline CVector4 &operator = (const CVector4 &cVector)
		{
			X = cVector.X;
			Y = cVector.Y;
			Z = cVector.Z;
			W = cVector.W;
			return *this;
		}

		/**
		 * Vector negation.
		 */
		inline CVector4 operator - ()
		{
			return CVector4(-X, -Y, -Z, -W);
		}

		/**
		 * Vector addition with assignment.
		 */
		inline CVector4 &operator += (const CVector4 &cVector)
		{
			X += cVector.X;
			Y += cVector.Y;
			Z += cVector.Z;
			W += cVector.W;
			return *this;
		}

		/**
		 * Vector subtraction with assignment.
		 */
		inline CVector4 &operator -= (const CVector4 &cVector)
		{
			X -= cVector.X;
			Y -= cVector.Y;
			Z -= cVector.Z;
			W -= cVector.W;
			return *this;
		}

		/**
		 * Vector multiplication with assignment.
		 */
		inline CVector4 &operator *= (const CVector4 &cVector)
		{
			X *= cVector.X;
			Y *= cVector.Y;
			Z *= cVector.Z;
			W *= cVector.W;
			return *this;
		}

		/**
		 * Tests if vector is zero vector.
		 */
		inline operator bool ()
		{
			return X != 0.0 || Y != 0.0 || Z != 0.0 || W != 0.0;
		}

		/**
		 * Vector multiplication by a scalar with assignment.
		 */
		template<typename TType> CVector4 &operator *= (TType tScalar)
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
		template<typename TType> CVector4 &operator /= (TType tScalar)
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
		template<typename TType> friend CVector4 operator * (TType tScalar, const CVector4 &cVector)
		{
			return CVector4(cVector) * tScalar;
		}

		/**
		 * Vector multiplication by a scalar.
		 */
		template<typename TType> friend CVector4 operator * (const CVector4 &cVector, TType tScalar)
		{
			return CVector4(cVector) * tScalar;
		}

		/**
		 * Vector division by a scalar.
		 */
		template<typename TType> friend CVector4 operator / (TType tScalar, const CVector4 &cVector)
		{
			return CVector4(cVector) / tScalar;
		}

		/**
		 * Vector division by a scalar.
		 */
		template<typename TType> friend CVector4 operator / (const CVector4 &cVector, TType tScalar)
		{
			return CVector4(cVector) / tScalar;
		}

		/**
		 * A sum of two vectors.
		 */
		inline friend const CVector4 operator + (const CVector4 &cVector1, const CVector4 &cVector2)
		{
			return CVector4(cVector1) += cVector2;
		}

		/**
		 * A subtraction of two vectors.
		 */
		inline friend const CVector4 operator - (const CVector4 &cVector1, const CVector4 &cVector2)
		{
			return CVector4(cVector1) -= cVector2;
		}

		/**
		 * A multiplication of two vectors.
		 */
		inline friend const CVector4 operator * (const CVector4 &cVector1, const CVector4 &cVector2)
		{
			return CVector4(cVector1) *= cVector2;
		}

		/**
		 * Writing to a stream.
		 */
		inline friend std::ostream &operator << (std::ostream &cOutputStream, const CVector4 &cVector)
		{
			cOutputStream << "CVector4(" << cVector.X << ", " << cVector.Y << ", " << cVector.Z << ", " << cVector.W << ")";
			return cOutputStream;
		}
};

}

#endif /* ENGINE_VECTOR4_HPP */

/* EOF */

