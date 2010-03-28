#include "../Internal.hpp"
#include "Matrix4x4.hpp"
#include "Vector3D.hpp"
#include "Vector4D.hpp"
#include <cstring>
#include <cmath>

#include "../Ranges/MemoryRange.hpp"

namespace Common
{

const Matrix4x4 Matrix4x4::ZERO(0.0, 0.0, 0.0, 0.0,
																	0.0, 0.0, 0.0, 0.0,
																	0.0, 0.0, 0.0, 0.0,
																	0.0, 0.0, 0.0, 0.0);

const Matrix4x4 Matrix4x4::IDENTITY(1.0, 0.0, 0.0, 0.0,
																			0.0, 1.0, 0.0, 0.0,
																			0.0, 0.0, 1.0, 0.0,
																			0.0, 0.0, 0.0, 1.0);

Matrix4x4::Matrix4x4()
{
	*this = IDENTITY;
	CreateRange(mData);
}

Matrix4x4::Matrix4x4(double cell00, double cell01, double cell02,	double cell03, double cell10,
	double cell11, double cell12, double cell13, double cell20, double cell21, double cell22,
	double cell23, double cell30, double cell31, double cell32, double cell33)
{
	mCell[0][0] = cell00;
	mCell[0][1] = cell01;
	mCell[0][2] = cell02;
	mCell[0][3] = cell03;
	mCell[1][0] = cell10;
	mCell[1][1] = cell11;
	mCell[1][2] = cell12;
	mCell[1][3] = cell13;
	mCell[2][0] = cell20;
	mCell[2][1] = cell21;
	mCell[2][2] = cell22;
	mCell[2][3] = cell23;
	mCell[3][0] = cell30;
	mCell[3][1] = cell31;
	mCell[3][2] = cell32;
	mCell[3][3] = cell33;
}

Matrix4x4::Matrix4x4(const Matrix4x4& matrix)
{
	*this = matrix;
}

bool Matrix4x4::operator== (const Matrix4x4& matrix) const
{
	return !std::memcmp(mData, matrix.mData, 16 * sizeof(double));
}

bool Matrix4x4::operator!= (const Matrix4x4& matrix) const
{
	return !(*this == matrix);
}

double Matrix4x4::GetCell(unsigned int x, unsigned int y) const
{
	Assert(x < 4 && y < 4, "Index out of range");
	return mCell[x][y];
}

void Matrix4x4::SetCell(unsigned int x, unsigned int y, double data)
{
	Assert(x < 4 && y < 4, "Index out of range");
	mCell[x][y] = data;
}

double Matrix4x4::GetDeterminant() const
{
	double sub_determinant1 = mCell[1][1] * mCell[2][2] * mCell[3][3] + mCell[1][2] * mCell[2][3] *
		mCell[3][1] + mCell[1][3] * mCell[2][1] * mCell[3][2] - mCell[1][1] * mCell[2][3] *
		mCell[3][2] - mCell[1][2] * mCell[2][1] * mCell[3][3] - mCell[1][3] * mCell[2][2] * mCell[3][1];
	double sub_determinant2 = mCell[1][0] * mCell[2][2] * mCell[3][3] + mCell[1][2] * mCell[2][3] *
		mCell[3][0] + mCell[1][3] * mCell[2][0] * mCell[3][2] - mCell[1][0] * mCell[2][3] *
		mCell[3][2] - mCell[1][2] * mCell[2][0] * mCell[3][3] - mCell[1][3] * mCell[2][2] * mCell[3][0];
	double sub_determinant3 = mCell[1][0] * mCell[2][1] * mCell[3][3] + mCell[1][1] * mCell[2][3] *
		mCell[3][0] + mCell[1][3] * mCell[2][0] * mCell[3][1] - mCell[1][0] * mCell[2][3] *
		mCell[3][1] - mCell[1][1] * mCell[2][0] * mCell[3][3] - mCell[1][3] * mCell[2][1] * mCell[3][0];
	double sub_determinant4 = mCell[1][0] * mCell[2][1] * mCell[3][2] + mCell[1][1] * mCell[2][2] *
		mCell[3][0] + mCell[1][2] * mCell[2][0] * mCell[3][1] - mCell[1][0] * mCell[2][2] *
		mCell[3][1] - mCell[1][1] * mCell[2][0] * mCell[3][2] - mCell[1][2] * mCell[2][1] * mCell[3][0];
	return mCell[0][0] * sub_determinant1 - mCell[0][1] * sub_determinant2 + mCell[0][2] *
		sub_determinant3 - mCell[0][3] * sub_determinant4;
}

Matrix4x4 Matrix4x4::GetTranspose()
{
	Matrix4x4 result;
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
			result.mCell[row][column] = mCell[column][row];
	}
	return result;
}

Matrix4x4 Matrix4x4::GetInverse() const
{
	Matrix4x4 result;
	double v0 = mCell[2][0] * mCell[3][1] - mCell[2][1] * mCell[3][0];
	double v1 = mCell[2][0] * mCell[3][2] - mCell[2][2] * mCell[3][0];
	double v2 = mCell[2][0] * mCell[3][3] - mCell[2][3] * mCell[3][0];
	double v3 = mCell[2][1] * mCell[3][2] - mCell[2][2] * mCell[3][1];
	double v4 = mCell[2][1] * mCell[3][3] - mCell[2][3] * mCell[3][1];
	double v5 = mCell[2][2] * mCell[3][3] - mCell[2][3] * mCell[3][2];
	double t00 = (v5 * mCell[1][1] - v4 * mCell[1][2] + v3 * mCell[1][3]);
	double t10 = -(v5 * mCell[1][0] - v2 * mCell[1][2] + v1 * mCell[1][3]);
	double t20 = (v4 * mCell[1][0] - v2 * mCell[1][1] + v0 * mCell[1][3]);
	double t30 = -(v3 * mCell[1][0] - v1 * mCell[1][1] + v0 * mCell[1][2]);
	double inverse_determinant = 1 / (t00 * mCell[0][0] + t10 * mCell[0][1] + t20 * mCell[0][2] +
		t30 * mCell[0][3]);
	result.mCell[0][0] = t00 * inverse_determinant;
	result.mCell[1][0] = t10 * inverse_determinant;
	result.mCell[2][0] = t20 * inverse_determinant;
	result.mCell[3][0] = t30 * inverse_determinant;
	result.mCell[0][1] = -(v5 * mCell[0][1] - v4 * mCell[0][2] + v3 * mCell[0][3]) *
		inverse_determinant;
	result.mCell[1][1] = (v5 * mCell[0][0] - v2 * mCell[0][2] + v1 * mCell[0][3]) *
		inverse_determinant;
	result.mCell[2][1] = -(v4 * mCell[0][0] - v2 * mCell[0][1] + v0 * mCell[0][3]) *
		inverse_determinant;
	result.mCell[3][1] = (v3 * mCell[0][0] - v1 * mCell[0][1] + v0 * mCell[0][2]) *
		inverse_determinant;
	v0 = mCell[1][0] * mCell[3][1] - mCell[1][1] * mCell[3][0];
	v1 = mCell[1][0] * mCell[3][2] - mCell[1][2] * mCell[3][0];
	v2 = mCell[1][0] * mCell[3][3] - mCell[1][3] * mCell[3][0];
	v3 = mCell[1][1] * mCell[3][2] - mCell[1][2] * mCell[3][1];
	v4 = mCell[1][1] * mCell[3][3] - mCell[1][3] * mCell[3][1];
	v5 = mCell[1][2] * mCell[3][3] - mCell[1][3] * mCell[3][2];
	result.mCell[0][2] = (v5 * mCell[0][1] - v4 * mCell[0][2] + v3 * mCell[0][3]) *
		inverse_determinant;
	result.mCell[1][2] = -(v5 * mCell[0][0] - v2 * mCell[0][2] + v1 * mCell[0][3]) *
		inverse_determinant;
	result.mCell[2][2] = (v4 * mCell[0][0] - v2 * mCell[0][1] + v0 * mCell[0][3]) *
		inverse_determinant;
	result.mCell[3][2] = -(v3 * mCell[0][0] - v1 * mCell[0][1] + v0 * mCell[0][2]) *
		inverse_determinant;
	v0 = mCell[2][1] * mCell[1][0] - mCell[2][0] * mCell[1][1];
	v1 = mCell[2][2] * mCell[1][0] - mCell[2][0] * mCell[1][2];
	v2 = mCell[2][3] * mCell[1][0] - mCell[2][0] * mCell[1][3];
	v3 = mCell[2][2] * mCell[1][1] - mCell[2][1] * mCell[1][2];
	v4 = mCell[2][3] * mCell[1][1] - mCell[2][1] * mCell[1][3];
	v5 = mCell[2][3] * mCell[1][2] - mCell[2][2] * mCell[1][3];
	result.mCell[0][3] = -(v5 * mCell[0][1] - v4 * mCell[0][2] + v3 * mCell[0][3]) *
		inverse_determinant;
	result.mCell[1][3] = (v5 * mCell[0][0] - v2 * mCell[0][2] + v1 * mCell[0][3]) *
		inverse_determinant;
	result.mCell[2][3] = -(v4 * mCell[0][0] - v2 * mCell[0][1] + v0 * mCell[0][3]) *
		inverse_determinant;
	result.mCell[3][3] = (v3 * mCell[0][0] - v1 * mCell[0][1] + v0 * mCell[0][2]) *
		inverse_determinant;
	return result;
}

Vector3D Matrix4x4::GetTranslation() const
{
	return Vector3D(mCell[3][0], mCell[3][1], mCell[3][2]);
}

void Matrix4x4::Translate(double x, double y, double z)
{
	Matrix4x4 matrix;
	matrix.mCell[3][0] = x;
	matrix.mCell[3][1] = y;
	matrix.mCell[3][2] = z;
	*this *= matrix;
}

void Matrix4x4::Translate(const Vector3D& vector)
{
	Translate(vector.X, vector.Y, vector.Z);
}

void Matrix4x4::Scale(double x, double y, double z)
{
	Matrix4x4 matrix;
	matrix.mCell[0][0] = x;
	matrix.mCell[1][1] = y;
	matrix.mCell[2][2] = z;
	*this *= matrix;
}

void Matrix4x4::Scale(const Vector3D& vector)
{
	Scale(vector.X, vector.Y, vector.Z);
}

void Matrix4x4::RotateX(double theta)
{
	Matrix4x4 matrix;
	matrix.mCell[1][1] = cos(theta);
	matrix.mCell[2][1] = -sin(theta);
	matrix.mCell[1][2] = sin(theta);
	matrix.mCell[2][2] = cos(theta);
	*this *= matrix;
}

void Matrix4x4::RotateY(double theta)
{
	Matrix4x4 matrix;
	matrix.mCell[0][0] = cos(theta);
	matrix.mCell[2][0] = sin(theta);
	matrix.mCell[0][2] = -sin(theta);
	matrix.mCell[2][2] = cos(theta);
	*this *= matrix;
}

void Matrix4x4::RotateZ(double theta)
{
	Matrix4x4 matrix;
	matrix.mCell[0][0] = cos(theta);
	matrix.mCell[1][1] = sin(theta);
	matrix.mCell[0][1] = -sin(theta);
	matrix.mCell[1][1] = cos(theta);
	*this *= matrix;
}

void Matrix4x4::Rotate(const Vector3D& vector, double theta)
{
	Rotate(vector.X, vector.Y, vector.Z, theta);
}

void Matrix4x4::Rotate(double x, double y, double z, double theta)
{
	double c = cos(theta);
	double s = sin(theta);
	double t = 1.0 - cos(theta);
	Matrix4x4 matrix;
	matrix.mCell[0][0] = t * x * x + c;
	matrix.mCell[1][0] = t * x * y - s * z;
	matrix.mCell[2][0] = t * x * z + s * y;
	matrix.mCell[0][1] = t * x * y + s * z;
	matrix.mCell[1][1] = t * y * y + c;
	matrix.mCell[2][1] = t * y * z - s * x;
	matrix.mCell[0][2] = t * x * z - s * y;
	matrix.mCell[1][2] = t * y * z + s * x;
	matrix.mCell[2][2] = t * z * z + c;
	*this *= matrix;
}

void Matrix4x4::ShearXY(double x, double y)
{
	Matrix4x4 matrix;
	matrix.mCell[2][0] = x;
	matrix.mCell[2][1] = y;
	*this *= matrix;
}

void Matrix4x4::ShearXZ(double x, double z)
{
	Matrix4x4 matrix;
	matrix.mCell[1][0] = x;
	matrix.mCell[1][2] = z;
	*this *= matrix;
}

void Matrix4x4::ShearYZ(double y, double z)
{
	Matrix4x4 matrix;
	matrix.mCell[0][1] = y;
	matrix.mCell[0][2] = z;
	*this *= matrix;
}

Matrix4x4& Matrix4x4::operator= (const Matrix4x4& matrix)
{
	for (int i = 0; i < 16; ++i)
		mData[i] = matrix.mData[i];
	return *this;
}

Matrix4x4& Matrix4x4::operator- ()
{
	for (int i = 0; i < 16; ++i)
		mData[i] = -mData[i];
	return *this;
}

Matrix4x4& Matrix4x4::operator+= (const Matrix4x4& matrix)
{
	for (int i = 0; i < 16; ++i)
		mData[i] += matrix.mData[i];
	return *this;
}

Matrix4x4& Matrix4x4::operator-= (const Matrix4x4& matrix)
{
	for (int i = 0; i < 16; ++i)
		mData[i] -= matrix.mData[i];
	return *this;
}

Matrix4x4& Matrix4x4::operator*= (const Matrix4x4& matrix)
{
	Matrix4x4 result;
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			result.mCell[row][column] = 0;
			for (int i = 0; i < 4; ++i)
				result.mCell[row][column] += mCell[row][i] * matrix.mCell[i][column];
		}
	}
	*this = result;
	return *this;
}

const Matrix4x4 operator* (int c, const Matrix4x4& matrix)
{
	Matrix4x4 result(matrix);
	for (int i = 0; i < 16; ++i)
		result.mData[i] *= c;
	return result;
}

const Matrix4x4 operator* (double c, const Matrix4x4& matrix)
{
	Matrix4x4 result(matrix);
	for (int i = 0; i < 16; ++i)
		result.mData[i] *= c;
	return result;
}

const Matrix4x4 operator* (const Matrix4x4& matrix, int c)
{
	return c * matrix;
}

const Matrix4x4 operator* (const Matrix4x4& matrix, double c)
{
	return c * matrix;
}

const Matrix4x4 operator/ (const Matrix4x4& matrix, int c)
{
	Matrix4x4 result(matrix);
	for (int i = 0; i < 16; ++i)
		result.mData[i] /= c;
	return result;
}

const Matrix4x4 operator/ (const Matrix4x4& matrix, double c)
{
	Matrix4x4 result(matrix);
	for (int i = 0; i < 16; ++i)
		result.mData[i] /= c;
	return result;
}

const Vector3D operator* (const Matrix4x4& matrix, const Vector3D& vector)
{
	double x = vector.X * matrix.mCell[0][0] + vector.Y * matrix.mCell[1][0] + vector.Z *
		matrix.mCell[2][0] + matrix.mCell[3][0];
	double y = vector.X * matrix.mCell[0][1] + vector.Y * matrix.mCell[1][1] + vector.Z *
		matrix.mCell[2][1] + matrix.mCell[3][1];
	double z = vector.X * matrix.mCell[0][2] + vector.Y * matrix.mCell[1][2] + vector.Z *
		matrix.mCell[2][2] + matrix.mCell[3][2];
	return Vector3D(x, y, z);
}

const Vector4D operator* (const Matrix4x4& matrix, const Vector4D& vector)
{
	double x = vector.X * matrix.mCell[0][0] + vector.Y * matrix.mCell[1][0] + vector.Z *
		matrix.mCell[2][0] + vector.W * matrix.mCell[3][0];
	double y = vector.X * matrix.mCell[0][1] + vector.Y * matrix.mCell[1][1] + vector.Z *
		matrix.mCell[2][1] + vector.W * matrix.mCell[3][1];
	double z = vector.X * matrix.mCell[0][2] + vector.Y * matrix.mCell[1][2] + vector.Z *
		matrix.mCell[2][2] + vector.W * matrix.mCell[3][2];
	double w = vector.X * matrix.mCell[0][3] + vector.Y * matrix.mCell[1][3] + vector.Z *
		matrix.mCell[2][3] + vector.W * matrix.mCell[3][3];
	return Vector4D(x, y, z, w);
}

const Matrix4x4 operator+ (const Matrix4x4& matrix1, const Matrix4x4& matrix2)
{
	return Matrix4x4(matrix1) += matrix2;
}

const Matrix4x4 operator- (const Matrix4x4& matrix1, const Matrix4x4& matrix2)
{
	return Matrix4x4(matrix1) -= matrix2;
}

const Matrix4x4 operator* (const Matrix4x4& matrix1, const Matrix4x4& matrix2)
{
	return Matrix4x4(matrix1) *= matrix2;
}

const Matrix4x4 ScalarMultiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2)
{
	Matrix4x4 result;
	for (int i = 0; i < 16; ++i)
		result.mData[i] = matrix1.mData[i] * matrix2.mData[i];
	return result;
}

}

/* EOF */
