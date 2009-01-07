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

namespace engine
{

/**
 * Class encapsulating a standard 3-element vector.
 */
class CVector4
{
	private:
		double m_fX; /**< An X component of the vector. */
		double m_fY; /**< A Y component of the vector. */
		double m_fZ; /**< A Z component of the vector. */
		double m_fW; /**< A W component of the vector. */

	public:
		/**
		 * Default constructor.
		 */
		CVector4()
		{
			SetX(0.0);
			SetY(0.0);
			SetZ(0.0);
			SetW(0.0);
		}

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector4(const double fX, const double fY, const double fZ, const double fW)
		{
			SetX(fX);
			SetY(fY);
			SetZ(fZ);
			SetW(fW);
		}

		/**
		 * Creates a copy of a vector.
		 */
		CVector4(const CVector4 &cVector)
		{
			SetX(cVector.GetX());
			SetY(cVector.GetY());
			SetZ(cVector.GetZ());
			SetW(cVector.GetW());
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

		inline double GetW() const
		{
			return m_fW;
		}

		inline void SetW(const double fW)
		{
			m_fW = fW;
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
			SetW(GetW() / fLength);
		}

		/**
		 * Returns a length of a vector.
		 */
		inline double GetLength() const
		{
			return std::sqrt(GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ() + GetW() * GetW());
		}

		/**
		 * Tests two vectors for equality.
		 */
		inline bool operator == (const CVector4 &cVector) const
		{
			return (GetX() == cVector.GetX()) && (GetY() == cVector.GetY()) && (GetZ() == cVector.GetZ()) && (GetW() == cVector.GetW());
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
			SetX(cVector.GetX());
			SetY(cVector.GetY());
			SetZ(cVector.GetZ());
			SetW(cVector.GetW());
			return *this;
		}

		/**
		 * Vector negation.
		 */
		inline CVector4 operator - ()
		{
			return CVector4(-GetX(), -GetY(), -GetZ(), -GetW());
		}

		/**
		 * Vector addition with assignment.
		 */
		inline CVector4 &operator += (const CVector4 &cVector)
		{
			SetX(GetX() + cVector.GetX());
			SetY(GetY() + cVector.GetY());
			SetZ(GetZ() + cVector.GetZ());
			SetW(GetW() + cVector.GetW());
			return *this;
		}

		/**
		 * Vector subtraction with assignment.
		 */
		inline CVector4 &operator -= (const CVector4 &cVector)
		{
			SetX(GetX() - cVector.GetX());
			SetY(GetY() - cVector.GetY());
			SetZ(GetZ() - cVector.GetZ());
			SetW(GetW() - cVector.GetW());
			return *this;
		}

		/**
		 * Vector multiplication with assignment.
		 */
		inline CVector4 &operator *= (const CVector4 &cVector)
		{
			SetX(GetX() * cVector.GetX());
			SetY(GetY() * cVector.GetY());
			SetZ(GetZ() * cVector.GetZ());
			SetW(GetW() * cVector.GetW());
			return *this;
		}

		/**
		 * Tests if vector is zero vector.
		 */
		inline operator bool ()
		{
			return GetX() != 0.0 || GetY() != 0.0 || GetZ() != 0.0 || GetW() != 0.0;
		}

		/**
		 * Vector multiplication by a scalar with assignment.
		 */
		template<typename TType> CVector4 &operator *= (TType tScalar)
		{
			SetX(GetX() * tScalar);
			SetY(GetY() * tScalar);
			SetZ(GetZ() * tScalar);
			SetW(GetW() * tScalar);
			return *this;
		}

		/**
		 * Vector division by a scalar with assignment.
		 */
		template<typename TType> CVector4 &operator /= (TType tScalar)
		{
			SetX(GetX() / tScalar);
			SetY(GetY() / tScalar);
			SetZ(GetZ() / tScalar);
			SetW(GetW() / tScalar);
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
			cOutputStream << "CVector4(" << cVector.GetX() << ", " << cVector.GetY() << ", " << cVector.GetZ() << ", " << cVector.GetW() << ")";
			return cOutputStream;
		}
};

}

#endif /* ENGINE_VECTOR4_HPP */

/* EOF */

