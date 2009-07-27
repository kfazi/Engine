/**
 * @file matrix4.hpp
 * @brief 4x4 matrix class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2008
 */

#ifndef ENGINE_MATRIX4_HPP
#define ENGINE_MATRIX4_HPP

#include "vector3.hpp"
#include "vector4.hpp"
#include "common.hpp"
#include "../useful.hpp"
#include <iostream>

namespace engine
{

/**
 * Class encapsulating a standard 4x4 homogeneous matrix.
 *
 * The layout of the matrix entries is:
 *
 * <pre>
 * --                                                       --
 * | m_fCell[0][0] m_fCell[0][1] m_fCell[0][2] m_fCell[0][3] |
 * | m_fCell[1][0] m_fCell[1][1] m_fCell[1][2] m_fCell[1][3] |
 * | m_fCell[2][0] m_fCell[2][1] m_fCell[2][2] m_fCell[2][3] |
 * | m_fCell[3][0] m_fCell[3][1] m_fCell[3][2] m_fCell[3][3] |
 * --                                                       --
 * </pre>
 */
class DLLEXPORTIMPORT CMatrix4
{
	protected:
		union
		{
			double m_aData[16]; /**< A one dimensional array of matrix data. */
			double m_fCell[4][4]; /**< A two dimensional array of matrix data. */
		};

	public:
		static const CMatrix4 ZERO; /**< A zero 4x4 matrix. */

		static const CMatrix4 IDENTITY; /**< An identity 4x4 matrix. */

		/**
		 * Default constructor.
		 */
		CMatrix4()
		{
			*this = IDENTITY;
		}

		/**
		 * Creates new matrix filled with data given in parameters.
		 */
		CMatrix4(const double fCell00, const double fCell01, const double fCell02, const double fCell03, const double fCell10, const double fCell11, const double fCell12, const double fCell13, const double fCell20, const double fCell21, const double fCell22, const double fCell23, const double fCell30, const double fCell31, const double fCell32, const double fCell33)
		{
			m_fCell[0][0] = fCell00;
			m_fCell[0][1] = fCell01;
			m_fCell[0][2] = fCell02;
			m_fCell[0][3] = fCell03;
			m_fCell[1][0] = fCell10;
			m_fCell[1][1] = fCell11;
			m_fCell[1][2] = fCell12;
			m_fCell[1][3] = fCell13;
			m_fCell[2][0] = fCell20;
			m_fCell[2][1] = fCell21;
			m_fCell[2][2] = fCell22;
			m_fCell[2][3] = fCell23;
			m_fCell[3][0] = fCell30;
			m_fCell[3][1] = fCell31;
			m_fCell[3][2] = fCell32;
			m_fCell[3][3] = fCell33;
		}

		/**
		 * Creates a copy of a matrix.
		 */
		CMatrix4(const CMatrix4 &cMatrix)
		{
			*this = cMatrix;
		}

		/**
		 * Tests two matrices for equality.
		 */
		bool operator == (const CMatrix4 &cMatrix) const
		{
			return !std::memcmp(m_aData, cMatrix.m_aData, 16 * sizeof(double));
		}

		/**
		 * Tests two matrices for inequality.
		 */
		bool operator != (const CMatrix4 &cMatrix) const
		{
			return !(*this == cMatrix);
		}

		/**
		 * Returns a cell data.
		 */
		double GetCell(const unsigned int iX, const unsigned int iY) const
		{
			if (iX > 3 || iY > 3)
				Error(Format("CMatrix4::GetCell() - Wrong coordinates %1%, %2%!") % iX % iY);;
			return m_fCell[iX][iY];
		}

		/**
		 * Sets a cell data.
		 */
		void SetCell(const unsigned int iX, const unsigned int iY, const double fData)
		{
			if (iX > 3 || iY > 3)
				Error(Format("CMatrix4::GetCell() - Wrong coordinates %1%, %2%!") % iX % iY);;
			m_fCell[iX][iY] = fData;
		}

		/**
		 * Calculates matrix determinant.
		 */
		double GetDeterminant() const
		{
			double fSubDeterminant1 = m_fCell[1][1] * m_fCell[2][2] * m_fCell[3][3] + m_fCell[1][2] * m_fCell[2][3] * m_fCell[3][1] + m_fCell[1][3] * m_fCell[2][1] * m_fCell[3][2] - m_fCell[1][1] * m_fCell[2][3] * m_fCell[3][2] - m_fCell[1][2] * m_fCell[2][1] * m_fCell[3][3] - m_fCell[1][3] * m_fCell[2][2] * m_fCell[3][1];
			double fSubDeterminant2 = m_fCell[1][0] * m_fCell[2][2] * m_fCell[3][3] + m_fCell[1][2] * m_fCell[2][3] * m_fCell[3][0] + m_fCell[1][3] * m_fCell[2][0] * m_fCell[3][2] - m_fCell[1][0] * m_fCell[2][3] * m_fCell[3][2] - m_fCell[1][2] * m_fCell[2][0] * m_fCell[3][3] - m_fCell[1][3] * m_fCell[2][2] * m_fCell[3][0];
			double fSubDeterminant3 = m_fCell[1][0] * m_fCell[2][1] * m_fCell[3][3] + m_fCell[1][1] * m_fCell[2][3] * m_fCell[3][0] + m_fCell[1][3] * m_fCell[2][0] * m_fCell[3][1] - m_fCell[1][0] * m_fCell[2][3] * m_fCell[3][1] - m_fCell[1][1] * m_fCell[2][0] * m_fCell[3][3] - m_fCell[1][3] * m_fCell[2][1] * m_fCell[3][0];
			double fSubDeterminant4 = m_fCell[1][0] * m_fCell[2][1] * m_fCell[3][2] + m_fCell[1][1] * m_fCell[2][2] * m_fCell[3][0] + m_fCell[1][2] * m_fCell[2][0] * m_fCell[3][1] - m_fCell[1][0] * m_fCell[2][2] * m_fCell[3][1] - m_fCell[1][1] * m_fCell[2][0] * m_fCell[3][2] - m_fCell[1][2] * m_fCell[2][1] * m_fCell[3][0];
			return m_fCell[0][0] * fSubDeterminant1 - m_fCell[0][1] * fSubDeterminant2 + m_fCell[0][2] * fSubDeterminant3 - m_fCell[0][3] * fSubDeterminant4;
		}

		/**
		 * Transposes the matrix.
		 */
		CMatrix4 GetTranspose()
		{
			CMatrix4 cResult;
			for (int iRow = 0; iRow < 4; ++iRow)
			{
				for (int iColumn = 0; iColumn < 4; ++iColumn)
					cResult.m_fCell[iRow][iColumn] = m_fCell[iColumn][iRow];
			}
			return cResult;
		}

		/**
		 * Returns an inverse of a matrix.
		 */
		CMatrix4 GetInverse() const
		{
			CMatrix4 cResult;
			double fV0 = m_fCell[2][0] * m_fCell[3][1] - m_fCell[2][1] * m_fCell[3][0];
			double fV1 = m_fCell[2][0] * m_fCell[3][2] - m_fCell[2][2] * m_fCell[3][0];
			double fV2 = m_fCell[2][0] * m_fCell[3][3] - m_fCell[2][3] * m_fCell[3][0];
			double fV3 = m_fCell[2][1] * m_fCell[3][2] - m_fCell[2][2] * m_fCell[3][1];
			double fV4 = m_fCell[2][1] * m_fCell[3][3] - m_fCell[2][3] * m_fCell[3][1];
			double fV5 = m_fCell[2][2] * m_fCell[3][3] - m_fCell[2][3] * m_fCell[3][2];
			double fT00 = (fV5 * m_fCell[1][1] - fV4 * m_fCell[1][2] + fV3 * m_fCell[1][3]);
			double fT10 = -(fV5 * m_fCell[1][0] - fV2 * m_fCell[1][2] + fV1 * m_fCell[1][3]);
			double fT20 = (fV4 * m_fCell[1][0] - fV2 * m_fCell[1][1] + fV0 * m_fCell[1][3]);
			double fT30 = -(fV3 * m_fCell[1][0] - fV1 * m_fCell[1][1] + fV0 * m_fCell[1][2]);
			double fInverseDeterminant = 1 / (fT00 * m_fCell[0][0] + fT10 * m_fCell[0][1] + fT20 * m_fCell[0][2] + fT30 * m_fCell[0][3]);
			cResult.m_fCell[0][0] = fT00 * fInverseDeterminant;
			cResult.m_fCell[1][0] = fT10 * fInverseDeterminant;
			cResult.m_fCell[2][0] = fT20 * fInverseDeterminant;
			cResult.m_fCell[3][0] = fT30 * fInverseDeterminant;
			cResult.m_fCell[0][1] = -(fV5 * m_fCell[0][1] - fV4 * m_fCell[0][2] + fV3 * m_fCell[0][3]) * fInverseDeterminant;
			cResult.m_fCell[1][1] = (fV5 * m_fCell[0][0] - fV2 * m_fCell[0][2] + fV1 * m_fCell[0][3]) * fInverseDeterminant;
			cResult.m_fCell[2][1] = -(fV4 * m_fCell[0][0] - fV2 * m_fCell[0][1] + fV0 * m_fCell[0][3]) * fInverseDeterminant;
			cResult.m_fCell[3][1] = (fV3 * m_fCell[0][0] - fV1 * m_fCell[0][1] + fV0 * m_fCell[0][2]) * fInverseDeterminant;
			fV0 = m_fCell[1][0] * m_fCell[3][1] - m_fCell[1][1] * m_fCell[3][0];
			fV1 = m_fCell[1][0] * m_fCell[3][2] - m_fCell[1][2] * m_fCell[3][0];
			fV2 = m_fCell[1][0] * m_fCell[3][3] - m_fCell[1][3] * m_fCell[3][0];
			fV3 = m_fCell[1][1] * m_fCell[3][2] - m_fCell[1][2] * m_fCell[3][1];
			fV4 = m_fCell[1][1] * m_fCell[3][3] - m_fCell[1][3] * m_fCell[3][1];
			fV5 = m_fCell[1][2] * m_fCell[3][3] - m_fCell[1][3] * m_fCell[3][2];
			cResult.m_fCell[0][2] = (fV5 * m_fCell[0][1] - fV4 * m_fCell[0][2] + fV3 * m_fCell[0][3]) * fInverseDeterminant;
			cResult.m_fCell[1][2] = -(fV5 * m_fCell[0][0] - fV2 * m_fCell[0][2] + fV1 * m_fCell[0][3]) * fInverseDeterminant;
			cResult.m_fCell[2][2] = (fV4 * m_fCell[0][0] - fV2 * m_fCell[0][1] + fV0 * m_fCell[0][3]) * fInverseDeterminant;
			cResult.m_fCell[3][2] = -(fV3 * m_fCell[0][0] - fV1 * m_fCell[0][1] + fV0 * m_fCell[0][2]) * fInverseDeterminant;
			fV0 = m_fCell[2][1] * m_fCell[1][0] - m_fCell[2][0] * m_fCell[1][1];
			fV1 = m_fCell[2][2] * m_fCell[1][0] - m_fCell[2][0] * m_fCell[1][2];
			fV2 = m_fCell[2][3] * m_fCell[1][0] - m_fCell[2][0] * m_fCell[1][3];
			fV3 = m_fCell[2][2] * m_fCell[1][1] - m_fCell[2][1] * m_fCell[1][2];
			fV4 = m_fCell[2][3] * m_fCell[1][1] - m_fCell[2][1] * m_fCell[1][3];
			fV5 = m_fCell[2][3] * m_fCell[1][2] - m_fCell[2][2] * m_fCell[1][3];
			cResult.m_fCell[0][3] = -(fV5 * m_fCell[0][1] - fV4 * m_fCell[0][2] + fV3 * m_fCell[0][3]) * fInverseDeterminant;
			cResult.m_fCell[1][3] = (fV5 * m_fCell[0][0] - fV2 * m_fCell[0][2] + fV1 * m_fCell[0][3]) * fInverseDeterminant;
			cResult.m_fCell[2][3] = -(fV4 * m_fCell[0][0] - fV2 * m_fCell[0][1] + fV0 * m_fCell[0][3]) * fInverseDeterminant;
			cResult.m_fCell[3][3] = (fV3 * m_fCell[0][0] - fV1 * m_fCell[0][1] + fV0 * m_fCell[0][2]) * fInverseDeterminant;
			return cResult;
		}

		/**
		 * Returns translation vector.
		 */
		CVector3 GetTranslation() const
		{
			return CVector3(m_fCell[3][0], m_fCell[3][1], m_fCell[3][2]);
		}

		/**
		 * Sets the translation transformation part of the matrix.
		 */
		void Translate(const double fX, const double fY, const double fZ)
		{
			CMatrix4 cMatrix;
			cMatrix.m_fCell[3][0] = fX;
			cMatrix.m_fCell[3][1] = fY;
			cMatrix.m_fCell[3][2] = fZ;
			*this *= cMatrix;
		}

		/**
		 * Sets the translation transformation part of the matrix.
		 */
		void Translate(const CVector3 &cVector)
		{
			Translate(cVector.X, cVector.Y, cVector.Z);
		}

		/**
		 * Sets the scale part of the matrix.
		 */
		void Scale(const double fX, const double fY, const double fZ)
		{
			CMatrix4 cMatrix;
			cMatrix.m_fCell[0][0] = fX;
			cMatrix.m_fCell[1][1] = fY;
			cMatrix.m_fCell[2][2] = fZ;
			*this *= cMatrix;
		}

		/**
		 * Sets the scale part of the matrix.
		 */
		void Scale(const CVector3 &cVector)
		{
			Scale(cVector.X, cVector.Y, cVector.Z);
		}

		/**
		 * Sets the rotation part about x axis of the matrix.
		 *
		 * @param[in] theta The angle in radians.
		 */
		void RotateX(const double fTheta)
		{
			CMatrix4 cMatrix;
			cMatrix.m_fCell[1][1] = cos(fTheta);
			cMatrix.m_fCell[2][1] = -sin(fTheta);
			cMatrix.m_fCell[1][2] = sin(fTheta);
			cMatrix.m_fCell[2][2] = cos(fTheta);
			*this *= cMatrix;
		}

		/**
		 * Sets the rotation part about y axis of the matrix.
		 *
		 * @param[in] theta The angle in radians.
		 */
		void RotateY(const double fTheta)
		{
			CMatrix4 cMatrix;
			cMatrix.m_fCell[0][0] = cos(fTheta);
			cMatrix.m_fCell[2][0] = sin(fTheta);
			cMatrix.m_fCell[0][2] = -sin(fTheta);
			cMatrix.m_fCell[2][2] = cos(fTheta);
			*this *= cMatrix;
		}

		/**
		 * Sets the rotation part about z axis of the matrix.
		 *
		 * @param[in] theta The angle in radians.
		 */
		void RotateZ(const double fTheta)
		{
			CMatrix4 cMatrix;
			cMatrix.m_fCell[0][0] = cos(fTheta);
			cMatrix.m_fCell[1][1] = sin(fTheta);
			cMatrix.m_fCell[0][1] = -sin(fTheta);
			cMatrix.m_fCell[1][1] = cos(fTheta);
			*this *= cMatrix;
		}

		/**
		 * Sets the rotation part of the matrix.
		 *
		 * @param[in] v The axis of rotation vector.
		 * @param[in] theta The angle in radians.
		 */
		void Rotate(const CVector3 &cVector, const double fTheta)
		{
			Rotate(cVector.X, cVector.Y, cVector.Z, fTheta);
		}

		/**
		 * Sets the rotation part of the matrix.
		 */
		void Rotate(const double fX, const double fY, const double fZ, const double fTheta)
		{
			double fC = cos(fTheta);
			double fS = sin(fTheta);
			double fT = 1.0 - cos(fTheta);
			CMatrix4 cMatrix;
			cMatrix.m_fCell[0][0] = fT * fX * fX + fC;
			cMatrix.m_fCell[1][0] = fT * fX * fY - fS * fZ;
			cMatrix.m_fCell[2][0] = fT * fX * fZ + fS * fY;
			cMatrix.m_fCell[0][1] = fT * fX * fY + fS * fZ;
			cMatrix.m_fCell[1][1] = fT * fY * fY + fC;
			cMatrix.m_fCell[2][1] = fT * fY * fZ - fS * fX;
			cMatrix.m_fCell[0][2] = fT * fX * fZ - fS * fY;
			cMatrix.m_fCell[1][2] = fT * fY * fZ + fS * fX;
			cMatrix.m_fCell[2][2] = fT * fZ * fZ + fC;
			*this *= cMatrix;
		}

		/**
		 * Sets the shear about X-Y plane of the matrix.
		 */
		void ShearXY(const double fX, const double fY)
		{
			CMatrix4 cMatrix;
			cMatrix.m_fCell[2][0] = fX;
			cMatrix.m_fCell[2][1] = fY;
			*this *= cMatrix;
		}

		/**
		 * Sets the shear about X-Z plane of the matrix.
		 */
		void ShearXZ(const double fX, const double fZ)
		{
			CMatrix4 cMatrix;
			cMatrix.m_fCell[1][0] = fX;
			cMatrix.m_fCell[1][2] = fZ;
			*this *= cMatrix;
		}

		/**
		 * Sets the shear about Y-Z plane of the matrix.
		 */
		void ShearYZ(const double fY, const double fZ)
		{
			CMatrix4 cMatrix;
			cMatrix.m_fCell[0][1] = fY;
			cMatrix.m_fCell[0][2] = fZ;
			*this *= cMatrix;
		}

		/**
		 * Assignment from 4x4 matrix.
		 */
		CMatrix4 &operator = (const CMatrix4 &cMatrix)
		{
			for (int i = 0; i < 16; ++i)
				m_aData[i] = cMatrix.m_aData[i];
			return *this;
		}

		/**
		 * Matrix negation.
		 */
		CMatrix4 &operator - ()
		{
			for (int i = 0; i < 16; ++i)
				m_aData[i] = -m_aData[i];
			return *this;
		}

		/**
		 * Matrix addition with assignment.
		 */
		CMatrix4 &operator += (const CMatrix4 &cMatrix)
		{
			for (int i = 0; i < 16; ++i)
				m_aData[i] += cMatrix.m_aData[i];
			return *this;
		}

		/**
		 * Matrix subtraction with assignment.
		 */
		CMatrix4 &operator -= (const CMatrix4 &cMatrix)
		{
			for (int i = 0; i < 16; ++i)
				m_aData[i] -= cMatrix.m_aData[i];
			return *this;
		}

		/**
		 * Matrix multiplication with assignment.
		 */
		CMatrix4 &operator *= (const CMatrix4 &cMatrix)
		{
			CMatrix4 cResult;
			for (int iRow = 0; iRow < 4; ++iRow)
			{
				for (int iColumn = 0; iColumn < 4; ++iColumn)
				{
					cResult.m_fCell[iRow][iColumn] = 0;
					for (int i = 0; i < 4; ++i)
						cResult.m_fCell[iRow][iColumn] += m_fCell[iRow][i] * cMatrix.m_fCell[i][iColumn];
				}
			}
			*this = cResult;
			return *this;
		}

		/**
		 * Matrix multiplication with an integer.
		 */
		friend const CMatrix4 operator * (const int iC, const CMatrix4 &cMatrix)
		{
			CMatrix4 cResult(cMatrix);
			for (int i = 0; i < 16; ++i)
				cResult.m_aData[i] *= iC;
			return cResult;
		}

		/**
		 * Matrix multiplication with a double number.
		 */
		friend const CMatrix4 operator * (const double fC, const CMatrix4 &cMatrix)
		{
			CMatrix4 cResult(cMatrix);
			for (int i = 0; i < 16; ++i)
				cResult.m_aData[i] *= fC;
			return cResult;
		}

		/**
		 * Matrix multiplication with an integer.
		 */
		friend const CMatrix4 operator * (const CMatrix4 &cMatrix, const int iC)
		{
			return iC * cMatrix;
		}

		/**
		 * Matrix multiplication with a double number.
		 */
		friend const CMatrix4 operator * (const CMatrix4 &cMatrix, const double fC)
		{
			return fC * cMatrix;
		}

		/**
		 * Matrix division by an integer.
		 */
		friend const CMatrix4 operator / (const CMatrix4 &cMatrix, const int iC)
		{
			CMatrix4 cResult(cMatrix);
			for (int i = 0; i < 16; ++i)
				cResult.m_aData[i] /= iC;
			return cResult;
		}

		/**
		 * Matrix division by a double number.
		 */
		friend const CMatrix4 operator / (const CMatrix4 &cMatrix, const double fC)
		{
			CMatrix4 cResult(cMatrix);
			for (int i = 0; i < 16; ++i)
				cResult.m_aData[i] /= fC;
			return cResult;
		}

		/**
		 * Vector transformation.
		 */
		friend const CVector3 operator * (const CMatrix4 &cMatrix, const CVector3 &cVector)
		{
			double fX = cVector.X * cMatrix.m_fCell[0][0] + cVector.Y * cMatrix.m_fCell[1][0] + cVector.Z * cMatrix.m_fCell[2][0] + cMatrix.m_fCell[3][0];
			double fY = cVector.X * cMatrix.m_fCell[0][1] + cVector.Y * cMatrix.m_fCell[1][1] + cVector.Z * cMatrix.m_fCell[2][1] + cMatrix.m_fCell[3][1];
			double fZ = cVector.X * cMatrix.m_fCell[0][2] + cVector.Y * cMatrix.m_fCell[1][2] + cVector.Z * cMatrix.m_fCell[2][2] + cMatrix.m_fCell[3][2];
			return CVector3(fX, fY, fZ);
		}

		/**
		 * Vector transformation.
		 */
		friend const CVector4 operator * (const CMatrix4 &cMatrix, const CVector4 &cVector)
		{
			double fX = cVector.X * cMatrix.m_fCell[0][0] + cVector.Y * cMatrix.m_fCell[1][0] + cVector.Z * cMatrix.m_fCell[2][0] + cVector.W * cMatrix.m_fCell[3][0];
			double fY = cVector.X * cMatrix.m_fCell[0][1] + cVector.Y * cMatrix.m_fCell[1][1] + cVector.Z * cMatrix.m_fCell[2][1] + cVector.W * cMatrix.m_fCell[3][1];
			double fZ = cVector.X * cMatrix.m_fCell[0][2] + cVector.Y * cMatrix.m_fCell[1][2] + cVector.Z * cMatrix.m_fCell[2][2] + cVector.W * cMatrix.m_fCell[3][2];
			double fW = cVector.X * cMatrix.m_fCell[0][3] + cVector.Y * cMatrix.m_fCell[1][3] + cVector.Z * cMatrix.m_fCell[2][3] + cVector.W * cMatrix.m_fCell[3][3];
			return CVector4(fX, fY, fZ, fW);
		}

		/**
		 * A sum of two 4x4 matrices.
		 */
		friend const CMatrix4 operator + (const CMatrix4 &cMatrix1, const CMatrix4 &cMatrix2)
		{
			return CMatrix4(cMatrix1) += cMatrix2;
		}

		/**
		 * A subtraction of two 4x4 matrices.
		 */
		friend const CMatrix4 operator - (const CMatrix4 &cMatrix1, const CMatrix4 &cMatrix2)
		{
			return CMatrix4(cMatrix1) -= cMatrix2;
		}

		/**
		 * A multiplication of two 4x4 matrices.
		 */
		friend const CMatrix4 operator * (const CMatrix4 &cMatrix1, const CMatrix4 &cMatrix2)
		{
			return CMatrix4(cMatrix1) *= cMatrix2;
		}

		/**
		 * A scalar multiplication of two 4x4 matrices.
		 */
		friend const CMatrix4 ScalarMultiply(const CMatrix4 &cMatrix1, const CMatrix4 &cMatrix2)
		{
			CMatrix4 cResult;
			for (int i = 0; i < 16; ++i)
				cResult.m_aData[i] = cMatrix1.m_aData[i] * cMatrix2.m_aData[i];
			return cResult;
		}

		/**
		 * Writing to a stream.
		 */
		friend std::ostream &operator << (std::ostream &cOutputStream, const CMatrix4 &cMatrix)
		{
			cOutputStream << "CMatrix4([";
			for (int iColumn = 0; iColumn < 4; ++iColumn)
			{
				for (int iRow = 0; iRow < 4; ++iRow)
					cOutputStream << " " << cMatrix.m_fCell[iRow][iColumn];
				cOutputStream << ";";
			}
			cOutputStream << " ])";
			return cOutputStream;
		}
};

}

#endif /* ENGINE_MATRIX4_HPP */

/* EOF */

