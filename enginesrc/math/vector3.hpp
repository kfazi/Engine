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

namespace engine
{

/**
 * Class encapsulating a standard 3-element vector.
 */
class CVector3
{
	private:
		double m_fX; /**< An X component of the vector. */
		double m_fY; /**< A Y component of the vector. */
		double m_fZ; /**< A Z component of the vector. */

	public:
		/**
		 * Default constructor.
		 */
		CVector3()
		{
			SetX(0.0);
			SetY(0.0);
			SetZ(0.0);
		}

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector3(const double fX, const double fY, const double fZ)
		{
			SetX(fX);
			SetY(fY);
			SetZ(fZ);
		}

		/**
		 * Creates a copy of a vector.
		 */
		CVector3(const CVector3 &cVector)
		{
			SetX(cVector.GetX());
			SetY(cVector.GetY());
			SetZ(cVector.GetZ());
		}

		inline double GetX() const
		{
			return m_fX;
		}

		inline void SetX(const double fX)
		{
			m_fX = fX;
		}

		inline double GetY() const
		{
			return m_fY;
		}

		inline void SetY(const double fY)
		{
			m_fY = fY;
		}

		inline double GetZ() const
		{
			return m_fZ;
		}

		inline void SetZ(const double fZ)
		{
			m_fZ = fZ;
		}

		/**
		 * Normalizes a vector.
		 */
		inline void Normalize()
		{
			double fLength = GetLength();
			if (fLength == 1.0 || fLength < std::numeric_limits<double>::epsilon())
				return;
			SetX(GetX() / fLength);
			SetY(GetY() / fLength);
			SetZ(GetZ() / fLength);
		}

		/**
		 * Returns a length of a vector.
		 */
		inline double GetLength() const
		{
			return std::sqrt(GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ());
		}

		/**
		 * Tests two vectors for equality.
		 */
		inline bool operator == (const CVector3 &cVector) const
		{
			return (GetX() == cVector.GetX()) && (GetY() == cVector.GetY()) && (GetZ() == cVector.GetZ());
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
			SetX(cVector.GetX());
			SetY(cVector.GetY());
			SetZ(cVector.GetZ());
			return *this;
		}

		/**
		 * Vector negation.
		 */
		inline CVector3 &operator - ()
		{
			SetX(-GetX());
			SetY(-GetY());
			SetZ(-GetZ());
			return *this;
		}

		/**
		 * Vector addition with assignment.
		 */
		inline CVector3 &operator += (const CVector3 &cVector)
		{
			SetX(GetX() + cVector.GetX());
			SetY(GetY() + cVector.GetY());
			SetZ(GetZ() + cVector.GetZ());
			return *this;
		}

		/**
		 * Vector subtraction with assignment.
		 */
		inline CVector3 &operator -= (const CVector3 &cVector)
		{
			SetX(GetX() - cVector.GetX());
			SetY(GetY() - cVector.GetY());
			SetZ(GetZ() - cVector.GetZ());
			return *this;
		}

		/**
		 * Vector multiplication with assignment.
		 */
		inline CVector3 &operator *= (const CVector3 &cVector)
		{
			SetX(GetX() * cVector.GetX());
			SetY(GetY() * cVector.GetY());
			SetZ(GetZ() * cVector.GetZ());
			return *this;
		}

		/**
		 * Tests if vector is zero vector.
		 */
		inline operator bool ()
		{
			return GetX() != 0.0 || GetY() != 0.0 || GetZ() != 0.0;
		}

		/**
		 * Vector multiplication by a number with assignment.
		 */
		template<typename TType> CVector3 &operator *= (TType tValue)
		{
			SetX(GetX() * tValue);
			SetY(GetY() * tValue);
			SetZ(GetZ() * tValue);
			return *this;
		}

		/**
		 * Vector division by a number with assignment.
		 */
		template<typename TType> CVector3 &operator /= (TType tValue)
		{
			SetX(GetX() / tValue);
			SetY(GetY() / tValue);
			SetZ(GetZ() / tValue);
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
			cOutputStream << "CVector3(" << cVector.GetX() << ", " << cVector.GetY() << ", " << cVector.GetZ() << ")";
			return cOutputStream;
		}
};

}

#endif /* ENGINE_VECTOR3_HPP */

/* EOF */

