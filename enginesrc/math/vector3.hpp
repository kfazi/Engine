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

namespace engine
{

/**
 * Class encapsulating a standard 3-element vector.
 */
class CVector3
{
	public:
		union
		{
			struct
			{
				double x; /**< An X component of the vector. */
				double y; /**< An Y component of the vector. */
				double z; /**< An Z component of the vector. */
			};
			double m_aCell[3]; /**< A one dimensional array of vector data. */
		};
		/**
		 * Default constructor.
		 */
		CVector3();
		/**
		 * Creates new vector filled with data given in parameters.
		 */
		CVector3(const double fX, const double fY, const double fZ);
		/**
		 * Creates a copy of a vector.
		 */
		CVector3(const CVector3 &cVector);
		/**
		 * Normalizes a vector.
		 */
		void Normalize();
		/**
		 * Returns a length of a vector.
		 */
		double Length() const;
		/**
		 * Tests two vectors for equality.
		 */
		bool operator == (const CVector3 &cVector) const;
		/**
		 * Tests two vectors for inequality.
		 */
		bool operator != (const CVector3 &cVector) const;
		/**
		 * Assignment operator.
		 */
		CVector3 &operator = (const CVector3 &cVector);
		/**
		 * Vector negation.
		 */
		CVector3 &operator - ();
		/**
		 * Vector addition with assignment.
		 */
		CVector3 &operator += (const CVector3 &cVector);
		/**
		 * Vector subtraction with assignment.
		 */
		CVector3 &operator -= (const CVector3 &cVector);
		/**
		 * Vector multiplication with assignment.
		 */
		CVector3 &operator *= (const CVector3 &cVector);
		/**
		 * Tests if vector is zero vector.
		 */
		operator bool ();
		/**
		 * Vector multiplication with an integer.
		 */
		friend CVector3 operator * (const int iValue, const CVector3 &cVector);
		/**
		 * Vector multiplication with a double number.
		 */
		friend CVector3 operator * (const double fValue, const CVector3 &cVector);
		/**
		 * Vector multiplication with an integer.
		 */
		friend CVector3 operator * (const CVector3 &cVector, const int fValue);
		/**
		 * Vector multiplication with a unsigned integer.
		 */
		friend CVector3 operator * (const CVector3 &cVector, const unsigned int iValue);
		/**
		 * Vector multiplication with a double number.
		 */
		friend CVector3 operator * (const CVector3 &cVector, const double fValue);
		/**
		 * Vector division by an integer.
		 */
		friend CVector3 operator / (const CVector3 &cVector, const int iValue);
		/**
		 * Vector division by a unsigned integer.
		 */
		friend CVector3 operator / (const CVector3 &cVector, const unsigned int iValue);
		/**
		 * Vector division by a double number.
		 */
		friend CVector3 operator / (const CVector3 &cVector, const double fValue);
		/**
		 * A sum of two vectors.
		 */
		friend const CVector3 operator + (const CVector3 &cVector1, const CVector3 &cVector2);
		/**
		 * A subtraction of two vectors.
		 */
		friend const CVector3 operator - (const CVector3 &cVector1, const CVector3 &cVector2);
		/**
		 * A multiplication of two vectors.
		 */
		friend const CVector3 operator * (const CVector3 &cVector1, const CVector3 &cVector2);
		/**
		 * Writing to a stream.
		 */
		friend std::ostream &operator << (std::ostream &cOutputStream, const CVector3 &cVector);
};

}

#endif /* ENGINE_VECTOR3_HPP */

/* EOF */

