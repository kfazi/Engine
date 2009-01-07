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

namespace engine
{

/**
 * Class encapsulating a standard 3-element vector.
 */
class CVector2
{
	private:
		double m_fX; /**< An X component of the vector. */
		double m_fY; /**< A Y component of the vector. */

	public:
		/**
		 * Default constructor.
		 */
		CVector2()
		{
			SetX(0.0);
			SetY(0.0);
		}

		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector2(const double fX, const double fY)
		{
			SetX(fX);
			SetY(fY);
		}

		/**
		 * Creates a copy of a vector.
		 */
		CVector2(const CVector2 &cVector)
		{
			SetX(cVector.GetX());
			SetY(cVector.GetY());
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
		}

		/**
		 * Returns a length of a vector.
		 */
		inline double GetLength() const
		{
			return std::sqrt(GetX() * GetX() + GetY() * GetY());
		}

		/**
		 * Tests two vectors for equality.
		 */
		inline bool operator == (const CVector2 &cVector) const
		{
			return (GetX() == cVector.GetX()) && (GetY() == cVector.GetY());
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
			SetX(cVector.GetX());
			SetY(cVector.GetY());
			return *this;
		}

		/**
		 * Vector negation.
		 */
		inline CVector2 &operator - ()
		{
			SetX(-GetX());
			SetY(-GetY());
			return *this;
		}

		/**
		 * Vector addition with assignment.
		 */
		inline CVector2 &operator += (const CVector2 &cVector)
		{
			SetX(GetX() + cVector.GetX());
			SetY(GetY() + cVector.GetY());
			return *this;
		}

		/**
		 * Vector subtraction with assignment.
		 */
		inline CVector2 &operator -= (const CVector2 &cVector)
		{
			SetX(GetX() - cVector.GetX());
			SetY(GetY() - cVector.GetY());
			return *this;
		}

		/**
		 * Vector multiplication with assignment.
		 */
		inline CVector2 &operator *= (const CVector2 &cVector)
		{
			SetX(GetX() * cVector.GetX());
			SetY(GetY() * cVector.GetY());
			return *this;
		}

		/**
		 * Tests if vector is zero vector.
		 */
		inline operator bool ()
		{
			return GetX() != 0.0 || GetY() != 0.0;
		}

		/**
		 * Vector multiplication by a number with assignment.
		 */
		template<typename TType> CVector2 &operator *= (TType tValue)
		{
			SetX(GetX() * tValue);
			SetY(GetY() * tValue);
			return *this;
		}

		/**
		 * Vector division by a number with assignment.
		 */
		template<typename TType> CVector2 &operator /= (TType tValue)
		{
			SetX(GetX() / tValue);
			SetY(GetY() / tValue);
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
			cOutputStream << "CVector2(" << cVector.GetX() << ", " << cVector.GetY() <<  ")";
			return cOutputStream;
		}
};

}

#endif /* ENGINE_VECTOR2_HPP */

/* EOF */

