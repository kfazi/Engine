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

class Vector3D;
class Vector4D;

/**
 * Class encapsulating a standard 4x4 homogeneous matrix.
 *
 * The layout of the matrix entries is:
 *
 * <pre>
 * --                                               --
 * | mCell[0][0] mCell[0][1] mCell[0][2] mCell[0][3] |
 * | mCell[1][0] mCell[1][1] mCell[1][2] mCell[1][3] |
 * | mCell[2][0] mCell[2][1] mCell[2][2] mCell[2][3] |
 * | mCell[3][0] mCell[3][1] mCell[3][2] mCell[3][3] |
 * --                                               --
 * </pre>
 */
class COMMONDLLIMPORTEXPORT Matrix4x4
{
	protected:
		union
		{
			double mData[16]; /**< A one dimensional array of matrix data. */
			double mCell[4][4]; /**< A two dimensional array of matrix data. */
		};

	public:
		static const Matrix4x4 ZERO; /**< A zero 4x4 matrix. */

		static const Matrix4x4 IDENTITY; /**< An identity 4x4 matrix. */

		/**
		 * Default constructor.
		 */
		Matrix4x4();

		/**
		 * Creates new matrix filled with data given in parameters.
		 */
		Matrix4x4(double cell00, double cell01, double cell02, double cell03,	double cell10,
			double cell11, double cell12, double cell13, double cell20, double cell21, double cell22,
			double cell23, double cell30, double cell31, double cell32, double cell33);

		/**
		 * Creates a copy of a matrix.
		 */
		Matrix4x4(const Matrix4x4& matrix);

		/**
		 * Tests two matrices for equality.
		 */
		bool operator== (const Matrix4x4& matrix) const;

		/**
		 * Tests two matrices for inequality.
		 */
		bool operator!= (const Matrix4x4& matrix) const;

		/**
		 * Returns a cell data.
		 */
		double GetCell(unsigned int x, unsigned int y) const;

		/**
		 * Sets a cell data.
		 */
		void SetCell(unsigned int x, unsigned int y, double data);

		/**
		 * Calculates matrix determinant.
		 */
		double GetDeterminant() const;

		/**
		 * Transposes the matrix.
		 */
		Matrix4x4 GetTranspose();

		/**
		 * Returns an inverse of a matrix.
		 */
		Matrix4x4 GetInverse() const;

		/**
		 * Returns translation vector.
		 */
		Vector3D GetTranslation() const;

		/**
		 * Sets the translation transformation part of the matrix.
		 */
		void Translate(double x, double y, double z);

		/**
		 * Sets the translation transformation part of the matrix.
		 */
		void Translate(const Vector3D& vector);

		/**
		 * Sets the scale part of the matrix.
		 */
		void Scale(double x, double y, double z);

		/**
		 * Sets the scale part of the matrix.
		 */
		void Scale(const Vector3D& vector);

		/**
		 * Sets the rotation part about x axis of the matrix.
		 *
		 * \param[in] theta The angle in radians.
		 */
		void RotateX(double theta);

		/**
		 * Sets the rotation part about y axis of the matrix.
		 *
		 * \param[in] theta The angle in radians.
		 */
		void RotateY(double theta);

		/**
		 * Sets the rotation part about z axis of the matrix.
		 *
		 * \param[in] theta The angle in radians.
		 */
		void RotateZ(double theta);

		/**
		 * Sets the rotation part of the matrix.
		 *
		 * \param[in] vector The axis of rotation vector.
		 * \param[in] theta The angle in radians.
		 */
		void Rotate(const Vector3D& vector, double theta);

		/**
		 * Sets the rotation part of the matrix.
		 */
		void Rotate(double x, double y, double z, double theta);

		/**
		 * Sets the shear about X-Y plane of the matrix.
		 */
		void ShearXY(double x, double y);

		/**
		 * Sets the shear about X-Z plane of the matrix.
		 */
		void ShearXZ(double x, double z);

		/**
		 * Sets the shear about Y-Z plane of the matrix.
		 */
		void ShearYZ(double y, double z);

		/**
		 * Assignment from 4x4 matrix.
		 */
		Matrix4x4& operator= (const Matrix4x4& matrix);

		/**
		 * Matrix negation.
		 */
		Matrix4x4& operator- ();

		/**
		 * Matrix addition with assignment.
		 */
		Matrix4x4& operator+= (const Matrix4x4& matrix);

		/**
		 * Matrix subtraction with assignment.
		 */
		Matrix4x4& operator-= (const Matrix4x4& matrix);

		/**
		 * Matrix multiplication with assignment.
		 */
		Matrix4x4& operator*= (const Matrix4x4& matrix);

		/**
		 * Matrix multiplication with an integer.
		 */
		friend const Matrix4x4 operator* (int c, const Matrix4x4& matrix);

		/**
		 * Matrix multiplication with a double number.
		 */
		friend const Matrix4x4 operator* (double c, const Matrix4x4& matrix);

		/**
		 * Matrix multiplication with an integer.
		 */
		friend const Matrix4x4 operator* (const Matrix4x4& matrix, int c);

		/**
		 * Matrix multiplication with a double number.
		 */
		friend const Matrix4x4 operator* (const Matrix4x4& matrix, double c);

		/**
		 * Matrix division by an integer.
		 */
		friend const Matrix4x4 operator/ (const Matrix4x4& matrix, int c);

		/**
		 * Matrix division by a double number.
		 */
		friend const Matrix4x4 operator/ (const Matrix4x4& matrix, double c);

		/**
		 * Vector transformation.
		 */
		friend const Vector3D operator* (const Matrix4x4& matrix, const Vector3D& vector);

		/**
		 * Vector transformation.
		 */
		friend const Vector4D operator* (const Matrix4x4& matrix, const Vector4D& vector);

		/**
		 * A sum of two 4x4 matrices.
		 */
		friend const Matrix4x4 operator+ (const Matrix4x4& matrix1, const Matrix4x4& matrix2);

		/**
		 * A subtraction of two 4x4 matrices.
		 */
		friend const Matrix4x4 operator- (const Matrix4x4& matrix1, const Matrix4x4& matrix2);

		/**
		 * A multiplication of two 4x4 matrices.
		 */
		friend const Matrix4x4 operator* (const Matrix4x4& matrix1, const Matrix4x4& matrix2);

		/**
		 * A scalar multiplication of two 4x4 matrices.
		 */
		friend const Matrix4x4 ScalarMultiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2);
};

}

#endif /* COMMON_MATRIX4X4_HPP */

/* EOF */

