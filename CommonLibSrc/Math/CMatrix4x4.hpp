/**
 * @file CMatrix4x4.hpp
 * @brief 4x4 matrix class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2009
 */

#ifndef COMMON_MATRIX4X4_HPP
#define COMMON_MATRIX4X4_HPP

#include "../Internal.hpp"

namespace Common
{

class CVector3D;
class CVector4D;

/**
 * Class encapsulating a standard 4x4 homogeneous matrix.
 *
 * The layout of the matrix entries is:
 *
 * <pre>
 * --                                                       --
 * | m_aCell[0][0] m_aCell[0][1] m_aCell[0][2] m_aCell[0][3] |
 * | m_aCell[1][0] m_aCell[1][1] m_aCell[1][2] m_aCell[1][3] |
 * | m_aCell[2][0] m_aCell[2][1] m_aCell[2][2] m_aCell[2][3] |
 * | m_aCell[3][0] m_aCell[3][1] m_aCell[3][2] m_aCell[3][3] |
 * --                                                       --
 * </pre>
 */
class COMMONDLLIMPORTEXPORT CMatrix4x4
{
	protected:
		union
		{
			double m_aData[16]; /**< A one dimensional array of matrix data. */
			double m_aCell[4][4]; /**< A two dimensional array of matrix data. */
		};

	public:
		static const CMatrix4x4 ZERO; /**< A zero 4x4 matrix. */

		static const CMatrix4x4 IDENTITY; /**< An identity 4x4 matrix. */

		/**
		 * Default constructor.
		 */
		CMatrix4x4();

		/**
		 * Creates new matrix filled with data given in parameters.
		 */
		CMatrix4x4(const double fCell00, const double fCell01, const double fCell02, const double fCell03, const double fCell10, const double fCell11, const double fCell12, const double fCell13, const double fCell20, const double fCell21, const double fCell22, const double fCell23, const double fCell30, const double fCell31, const double fCell32, const double fCell33);

		/**
		 * Creates a copy of a matrix.
		 */
		CMatrix4x4(const CMatrix4x4& cMatrix);

		/**
		 * Tests two matrices for equality.
		 */
		bool operator == (const CMatrix4x4& cMatrix) const;

		/**
		 * Tests two matrices for inequality.
		 */
		bool operator != (const CMatrix4x4& cMatrix) const;

		/**
		 * Returns a cell data.
		 */
		double GetCell(const unsigned int iX, const unsigned int iY) const;

		/**
		 * Sets a cell data.
		 */
		void SetCell(const unsigned int iX, const unsigned int iY, const double fData);

		/**
		 * Calculates matrix determinant.
		 */
		double GetDeterminant() const;

		/**
		 * Transposes the matrix.
		 */
		CMatrix4x4 GetTranspose();

		/**
		 * Returns an inverse of a matrix.
		 */
		CMatrix4x4 GetInverse() const;

		/**
		 * Returns translation vector.
		 */
		CVector3D GetTranslation() const;

		/**
		 * Sets the translation transformation part of the matrix.
		 */
		void Translate(const double fX, const double fY, const double fZ);

		/**
		 * Sets the translation transformation part of the matrix.
		 */
		void Translate(const CVector3D& cVector);

		/**
		 * Sets the scale part of the matrix.
		 */
		void Scale(const double fX, const double fY, const double fZ);

		/**
		 * Sets the scale part of the matrix.
		 */
		void Scale(const CVector3D& cVector);

		/**
		 * Sets the rotation part about x axis of the matrix.
		 *
		 * @param[in] theta The angle in radians.
		 */
		void RotateX(const double fTheta);

		/**
		 * Sets the rotation part about y axis of the matrix.
		 *
		 * @param[in] theta The angle in radians.
		 */
		void RotateY(const double fTheta);

		/**
		 * Sets the rotation part about z axis of the matrix.
		 *
		 * @param[in] theta The angle in radians.
		 */
		void RotateZ(const double fTheta);

		/**
		 * Sets the rotation part of the matrix.
		 *
		 * @param[in] v The axis of rotation vector.
		 * @param[in] theta The angle in radians.
		 */
		void Rotate(const CVector3D& cVector, const double fTheta);

		/**
		 * Sets the rotation part of the matrix.
		 */
		void Rotate(const double fX, const double fY, const double fZ, const double fTheta);

		/**
		 * Sets the shear about X-Y plane of the matrix.
		 */
		void ShearXY(const double fX, const double fY);

		/**
		 * Sets the shear about X-Z plane of the matrix.
		 */
		void ShearXZ(const double fX, const double fZ);

		/**
		 * Sets the shear about Y-Z plane of the matrix.
		 */
		void ShearYZ(const double fY, const double fZ);

		/**
		 * Assignment from 4x4 matrix.
		 */
		CMatrix4x4& operator = (const CMatrix4x4& cMatrix);

		/**
		 * Matrix negation.
		 */
		CMatrix4x4& operator - ();

		/**
		 * Matrix addition with assignment.
		 */
		CMatrix4x4& operator += (const CMatrix4x4& cMatrix);

		/**
		 * Matrix subtraction with assignment.
		 */
		CMatrix4x4& operator -= (const CMatrix4x4& cMatrix);

		/**
		 * Matrix multiplication with assignment.
		 */
		CMatrix4x4& operator *= (const CMatrix4x4& cMatrix);

		/**
		 * Matrix multiplication with an integer.
		 */
		friend const CMatrix4x4 operator * (const int iC, const CMatrix4x4& cMatrix);

		/**
		 * Matrix multiplication with a double number.
		 */
		friend const CMatrix4x4 operator * (const double fC, const CMatrix4x4& cMatrix);

		/**
		 * Matrix multiplication with an integer.
		 */
		friend const CMatrix4x4 operator * (const CMatrix4x4& cMatrix, const int iC);

		/**
		 * Matrix multiplication with a double number.
		 */
		friend const CMatrix4x4 operator * (const CMatrix4x4& cMatrix, const double fC);

		/**
		 * Matrix division by an integer.
		 */
		friend const CMatrix4x4 operator / (const CMatrix4x4& cMatrix, const int iC);

		/**
		 * Matrix division by a double number.
		 */
		friend const CMatrix4x4 operator / (const CMatrix4x4& cMatrix, const double fC);

		/**
		 * Vector transformation.
		 */
		friend const CVector3D operator * (const CMatrix4x4& cMatrix, const CVector3D& cVector);

		/**
		 * Vector transformation.
		 */
		friend const CVector4D operator * (const CMatrix4x4& cMatrix, const CVector4D& cVector);

		/**
		 * A sum of two 4x4 matrices.
		 */
		friend const CMatrix4x4 operator + (const CMatrix4x4& cMatrix1, const CMatrix4x4& cMatrix2);

		/**
		 * A subtraction of two 4x4 matrices.
		 */
		friend const CMatrix4x4 operator - (const CMatrix4x4& cMatrix1, const CMatrix4x4& cMatrix2);

		/**
		 * A multiplication of two 4x4 matrices.
		 */
		friend const CMatrix4x4 operator * (const CMatrix4x4& cMatrix1, const CMatrix4x4& cMatrix2);

		/**
		 * A scalar multiplication of two 4x4 matrices.
		 */
		friend const CMatrix4x4 ScalarMultiply(const CMatrix4x4& cMatrix1, const CMatrix4x4& cMatrix2);
};

}

#endif /* COMMON_MATRIX4X4_HPP */

/* EOF */

