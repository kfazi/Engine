#include "../Internal.hpp"
#include "CMatrix4x4.hpp"
#include "CVector3D.hpp"
#include "CVector4D.hpp"
#include <cstring>
#include <cmath>

#include "../Ranges/CMemoryRange.hpp"

namespace Common
{

const CMatrix4x4 CMatrix4x4::ZERO(0.0, 0.0, 0.0, 0.0,
																	0.0, 0.0, 0.0, 0.0,
																	0.0, 0.0, 0.0, 0.0,
																	0.0, 0.0, 0.0, 0.0);

const CMatrix4x4 CMatrix4x4::IDENTITY(1.0, 0.0, 0.0, 0.0,
																			0.0, 1.0, 0.0, 0.0,
																			0.0, 0.0, 1.0, 0.0,
																			0.0, 0.0, 0.0, 1.0);

CMatrix4x4::CMatrix4x4()
{
	*this = IDENTITY;
	CreateRange(m_aData);
}

CMatrix4x4::CMatrix4x4(const double fCell00, const double fCell01, const double fCell02, const double fCell03, const double fCell10, const double fCell11, const double fCell12, const double fCell13, const double fCell20, const double fCell21, const double fCell22, const double fCell23, const double fCell30, const double fCell31, const double fCell32, const double fCell33)
{
	m_aCell[0][0] = fCell00;
	m_aCell[0][1] = fCell01;
	m_aCell[0][2] = fCell02;
	m_aCell[0][3] = fCell03;
	m_aCell[1][0] = fCell10;
	m_aCell[1][1] = fCell11;
	m_aCell[1][2] = fCell12;
	m_aCell[1][3] = fCell13;
	m_aCell[2][0] = fCell20;
	m_aCell[2][1] = fCell21;
	m_aCell[2][2] = fCell22;
	m_aCell[2][3] = fCell23;
	m_aCell[3][0] = fCell30;
	m_aCell[3][1] = fCell31;
	m_aCell[3][2] = fCell32;
	m_aCell[3][3] = fCell33;
}

CMatrix4x4::CMatrix4x4(const CMatrix4x4& cMatrix)
{
	*this = cMatrix;
}

bool CMatrix4x4::operator == (const CMatrix4x4& cMatrix) const
{
	return !std::memcmp(m_aData, cMatrix.m_aData, 16 * sizeof(double));
}

bool CMatrix4x4::operator != (const CMatrix4x4& cMatrix) const
{
	return !(*this == cMatrix);
}

double CMatrix4x4::GetCell(const unsigned int iX, const unsigned int iY) const
{
	if (iX > 3 || iY > 3)
		;//Error(Format("CMatrix4::GetCell() - Wrong coordinates %1%, %2%!") % iX % iY);;
	return m_aCell[iX][iY];
}

void CMatrix4x4::SetCell(const unsigned int iX, const unsigned int iY, const double fData)
{
	if (iX > 3 || iY > 3)
		;//Error(Format("CMatrix4::GetCell() - Wrong coordinates %1%, %2%!") % iX % iY);;
	m_aCell[iX][iY] = fData;
}

double CMatrix4x4::GetDeterminant() const
{
	double fSubDeterminant1 = m_aCell[1][1] * m_aCell[2][2] * m_aCell[3][3] + m_aCell[1][2] * m_aCell[2][3] * m_aCell[3][1] + m_aCell[1][3] * m_aCell[2][1] * m_aCell[3][2] - m_aCell[1][1] * m_aCell[2][3] * m_aCell[3][2] - m_aCell[1][2] * m_aCell[2][1] * m_aCell[3][3] - m_aCell[1][3] * m_aCell[2][2] * m_aCell[3][1];
	double fSubDeterminant2 = m_aCell[1][0] * m_aCell[2][2] * m_aCell[3][3] + m_aCell[1][2] * m_aCell[2][3] * m_aCell[3][0] + m_aCell[1][3] * m_aCell[2][0] * m_aCell[3][2] - m_aCell[1][0] * m_aCell[2][3] * m_aCell[3][2] - m_aCell[1][2] * m_aCell[2][0] * m_aCell[3][3] - m_aCell[1][3] * m_aCell[2][2] * m_aCell[3][0];
	double fSubDeterminant3 = m_aCell[1][0] * m_aCell[2][1] * m_aCell[3][3] + m_aCell[1][1] * m_aCell[2][3] * m_aCell[3][0] + m_aCell[1][3] * m_aCell[2][0] * m_aCell[3][1] - m_aCell[1][0] * m_aCell[2][3] * m_aCell[3][1] - m_aCell[1][1] * m_aCell[2][0] * m_aCell[3][3] - m_aCell[1][3] * m_aCell[2][1] * m_aCell[3][0];
	double fSubDeterminant4 = m_aCell[1][0] * m_aCell[2][1] * m_aCell[3][2] + m_aCell[1][1] * m_aCell[2][2] * m_aCell[3][0] + m_aCell[1][2] * m_aCell[2][0] * m_aCell[3][1] - m_aCell[1][0] * m_aCell[2][2] * m_aCell[3][1] - m_aCell[1][1] * m_aCell[2][0] * m_aCell[3][2] - m_aCell[1][2] * m_aCell[2][1] * m_aCell[3][0];
	return m_aCell[0][0] * fSubDeterminant1 - m_aCell[0][1] * fSubDeterminant2 + m_aCell[0][2] * fSubDeterminant3 - m_aCell[0][3] * fSubDeterminant4;
}

CMatrix4x4 CMatrix4x4::GetTranspose()
{
	CMatrix4x4 cResult;
	for (int iRow = 0; iRow < 4; ++iRow)
	{
		for (int iColumn = 0; iColumn < 4; ++iColumn)
			cResult.m_aCell[iRow][iColumn] = m_aCell[iColumn][iRow];
	}
	return cResult;
}

CMatrix4x4 CMatrix4x4::GetInverse() const
{
	CMatrix4x4 cResult;
	double fV0 = m_aCell[2][0] * m_aCell[3][1] - m_aCell[2][1] * m_aCell[3][0];
	double fV1 = m_aCell[2][0] * m_aCell[3][2] - m_aCell[2][2] * m_aCell[3][0];
	double fV2 = m_aCell[2][0] * m_aCell[3][3] - m_aCell[2][3] * m_aCell[3][0];
	double fV3 = m_aCell[2][1] * m_aCell[3][2] - m_aCell[2][2] * m_aCell[3][1];
	double fV4 = m_aCell[2][1] * m_aCell[3][3] - m_aCell[2][3] * m_aCell[3][1];
	double fV5 = m_aCell[2][2] * m_aCell[3][3] - m_aCell[2][3] * m_aCell[3][2];
	double fT00 = (fV5 * m_aCell[1][1] - fV4 * m_aCell[1][2] + fV3 * m_aCell[1][3]);
	double fT10 = -(fV5 * m_aCell[1][0] - fV2 * m_aCell[1][2] + fV1 * m_aCell[1][3]);
	double fT20 = (fV4 * m_aCell[1][0] - fV2 * m_aCell[1][1] + fV0 * m_aCell[1][3]);
	double fT30 = -(fV3 * m_aCell[1][0] - fV1 * m_aCell[1][1] + fV0 * m_aCell[1][2]);
	double fInverseDeterminant = 1 / (fT00 * m_aCell[0][0] + fT10 * m_aCell[0][1] + fT20 * m_aCell[0][2] + fT30 * m_aCell[0][3]);
	cResult.m_aCell[0][0] = fT00 * fInverseDeterminant;
	cResult.m_aCell[1][0] = fT10 * fInverseDeterminant;
	cResult.m_aCell[2][0] = fT20 * fInverseDeterminant;
	cResult.m_aCell[3][0] = fT30 * fInverseDeterminant;
	cResult.m_aCell[0][1] = -(fV5 * m_aCell[0][1] - fV4 * m_aCell[0][2] + fV3 * m_aCell[0][3]) * fInverseDeterminant;
	cResult.m_aCell[1][1] = (fV5 * m_aCell[0][0] - fV2 * m_aCell[0][2] + fV1 * m_aCell[0][3]) * fInverseDeterminant;
	cResult.m_aCell[2][1] = -(fV4 * m_aCell[0][0] - fV2 * m_aCell[0][1] + fV0 * m_aCell[0][3]) * fInverseDeterminant;
	cResult.m_aCell[3][1] = (fV3 * m_aCell[0][0] - fV1 * m_aCell[0][1] + fV0 * m_aCell[0][2]) * fInverseDeterminant;
	fV0 = m_aCell[1][0] * m_aCell[3][1] - m_aCell[1][1] * m_aCell[3][0];
	fV1 = m_aCell[1][0] * m_aCell[3][2] - m_aCell[1][2] * m_aCell[3][0];
	fV2 = m_aCell[1][0] * m_aCell[3][3] - m_aCell[1][3] * m_aCell[3][0];
	fV3 = m_aCell[1][1] * m_aCell[3][2] - m_aCell[1][2] * m_aCell[3][1];
	fV4 = m_aCell[1][1] * m_aCell[3][3] - m_aCell[1][3] * m_aCell[3][1];
	fV5 = m_aCell[1][2] * m_aCell[3][3] - m_aCell[1][3] * m_aCell[3][2];
	cResult.m_aCell[0][2] = (fV5 * m_aCell[0][1] - fV4 * m_aCell[0][2] + fV3 * m_aCell[0][3]) * fInverseDeterminant;
	cResult.m_aCell[1][2] = -(fV5 * m_aCell[0][0] - fV2 * m_aCell[0][2] + fV1 * m_aCell[0][3]) * fInverseDeterminant;
	cResult.m_aCell[2][2] = (fV4 * m_aCell[0][0] - fV2 * m_aCell[0][1] + fV0 * m_aCell[0][3]) * fInverseDeterminant;
	cResult.m_aCell[3][2] = -(fV3 * m_aCell[0][0] - fV1 * m_aCell[0][1] + fV0 * m_aCell[0][2]) * fInverseDeterminant;
	fV0 = m_aCell[2][1] * m_aCell[1][0] - m_aCell[2][0] * m_aCell[1][1];
	fV1 = m_aCell[2][2] * m_aCell[1][0] - m_aCell[2][0] * m_aCell[1][2];
	fV2 = m_aCell[2][3] * m_aCell[1][0] - m_aCell[2][0] * m_aCell[1][3];
	fV3 = m_aCell[2][2] * m_aCell[1][1] - m_aCell[2][1] * m_aCell[1][2];
	fV4 = m_aCell[2][3] * m_aCell[1][1] - m_aCell[2][1] * m_aCell[1][3];
	fV5 = m_aCell[2][3] * m_aCell[1][2] - m_aCell[2][2] * m_aCell[1][3];
	cResult.m_aCell[0][3] = -(fV5 * m_aCell[0][1] - fV4 * m_aCell[0][2] + fV3 * m_aCell[0][3]) * fInverseDeterminant;
	cResult.m_aCell[1][3] = (fV5 * m_aCell[0][0] - fV2 * m_aCell[0][2] + fV1 * m_aCell[0][3]) * fInverseDeterminant;
	cResult.m_aCell[2][3] = -(fV4 * m_aCell[0][0] - fV2 * m_aCell[0][1] + fV0 * m_aCell[0][3]) * fInverseDeterminant;
	cResult.m_aCell[3][3] = (fV3 * m_aCell[0][0] - fV1 * m_aCell[0][1] + fV0 * m_aCell[0][2]) * fInverseDeterminant;
	return cResult;
}

CVector3D CMatrix4x4::GetTranslation() const
{
	return CVector3D(m_aCell[3][0], m_aCell[3][1], m_aCell[3][2]);
}

void CMatrix4x4::Translate(const double fX, const double fY, const double fZ)
{
	CMatrix4x4 cMatrix;
	cMatrix.m_aCell[3][0] = fX;
	cMatrix.m_aCell[3][1] = fY;
	cMatrix.m_aCell[3][2] = fZ;
	*this *= cMatrix;
}

void CMatrix4x4::Translate(const CVector3D& cVector)
{
	Translate(cVector.X, cVector.Y, cVector.Z);
}

void CMatrix4x4::Scale(const double fX, const double fY, const double fZ)
{
	CMatrix4x4 cMatrix;
	cMatrix.m_aCell[0][0] = fX;
	cMatrix.m_aCell[1][1] = fY;
	cMatrix.m_aCell[2][2] = fZ;
	*this *= cMatrix;
}

void CMatrix4x4::Scale(const CVector3D& cVector)
{
	Scale(cVector.X, cVector.Y, cVector.Z);
}

void CMatrix4x4::RotateX(const double fTheta)
{
	CMatrix4x4 cMatrix;
	cMatrix.m_aCell[1][1] = cos(fTheta);
	cMatrix.m_aCell[2][1] = -sin(fTheta);
	cMatrix.m_aCell[1][2] = sin(fTheta);
	cMatrix.m_aCell[2][2] = cos(fTheta);
	*this *= cMatrix;
}

void CMatrix4x4::RotateY(const double fTheta)
{
	CMatrix4x4 cMatrix;
	cMatrix.m_aCell[0][0] = cos(fTheta);
	cMatrix.m_aCell[2][0] = sin(fTheta);
	cMatrix.m_aCell[0][2] = -sin(fTheta);
	cMatrix.m_aCell[2][2] = cos(fTheta);
	*this *= cMatrix;
}

void CMatrix4x4::RotateZ(const double fTheta)
{
	CMatrix4x4 cMatrix;
	cMatrix.m_aCell[0][0] = cos(fTheta);
	cMatrix.m_aCell[1][1] = sin(fTheta);
	cMatrix.m_aCell[0][1] = -sin(fTheta);
	cMatrix.m_aCell[1][1] = cos(fTheta);
	*this *= cMatrix;
}

void CMatrix4x4::Rotate(const CVector3D& cVector, const double fTheta)
{
	Rotate(cVector.X, cVector.Y, cVector.Z, fTheta);
}

void CMatrix4x4::Rotate(const double fX, const double fY, const double fZ, const double fTheta)
{
	double fC = cos(fTheta);
	double fS = sin(fTheta);
	double fT = 1.0 - cos(fTheta);
	CMatrix4x4 cMatrix;
	cMatrix.m_aCell[0][0] = fT * fX * fX + fC;
	cMatrix.m_aCell[1][0] = fT * fX * fY - fS * fZ;
	cMatrix.m_aCell[2][0] = fT * fX * fZ + fS * fY;
	cMatrix.m_aCell[0][1] = fT * fX * fY + fS * fZ;
	cMatrix.m_aCell[1][1] = fT * fY * fY + fC;
	cMatrix.m_aCell[2][1] = fT * fY * fZ - fS * fX;
	cMatrix.m_aCell[0][2] = fT * fX * fZ - fS * fY;
	cMatrix.m_aCell[1][2] = fT * fY * fZ + fS * fX;
	cMatrix.m_aCell[2][2] = fT * fZ * fZ + fC;
	*this *= cMatrix;
}

void CMatrix4x4::ShearXY(const double fX, const double fY)
{
	CMatrix4x4 cMatrix;
	cMatrix.m_aCell[2][0] = fX;
	cMatrix.m_aCell[2][1] = fY;
	*this *= cMatrix;
}

void CMatrix4x4::ShearXZ(const double fX, const double fZ)
{
	CMatrix4x4 cMatrix;
	cMatrix.m_aCell[1][0] = fX;
	cMatrix.m_aCell[1][2] = fZ;
	*this *= cMatrix;
}

void CMatrix4x4::ShearYZ(const double fY, const double fZ)
{
	CMatrix4x4 cMatrix;
	cMatrix.m_aCell[0][1] = fY;
	cMatrix.m_aCell[0][2] = fZ;
	*this *= cMatrix;
}

CMatrix4x4& CMatrix4x4::operator = (const CMatrix4x4& cMatrix)
{
	for (int i = 0; i < 16; ++i)
		m_aData[i] = cMatrix.m_aData[i];
	return *this;
}

CMatrix4x4& CMatrix4x4::operator - ()
{
	for (int i = 0; i < 16; ++i)
		m_aData[i] = -m_aData[i];
	return *this;
}

CMatrix4x4& CMatrix4x4::operator += (const CMatrix4x4& cMatrix)
{
	for (int i = 0; i < 16; ++i)
		m_aData[i] += cMatrix.m_aData[i];
	return *this;
}

CMatrix4x4& CMatrix4x4::operator -= (const CMatrix4x4& cMatrix)
{
	for (int i = 0; i < 16; ++i)
		m_aData[i] -= cMatrix.m_aData[i];
	return *this;
}

CMatrix4x4& CMatrix4x4::operator *= (const CMatrix4x4& cMatrix)
{
	CMatrix4x4 cResult;
	for (int iRow = 0; iRow < 4; ++iRow)
	{
		for (int iColumn = 0; iColumn < 4; ++iColumn)
		{
			cResult.m_aCell[iRow][iColumn] = 0;
			for (int i = 0; i < 4; ++i)
				cResult.m_aCell[iRow][iColumn] += m_aCell[iRow][i] * cMatrix.m_aCell[i][iColumn];
		}
	}
	*this = cResult;
	return *this;
}

const CMatrix4x4 operator * (const int iC, const CMatrix4x4& cMatrix)
{
	CMatrix4x4 cResult(cMatrix);
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] *= iC;
	return cResult;
}

const CMatrix4x4 operator * (const double fC, const CMatrix4x4& cMatrix)
{
	CMatrix4x4 cResult(cMatrix);
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] *= fC;
	return cResult;
}

const CMatrix4x4 operator * (const CMatrix4x4& cMatrix, const int iC)
{
	return iC * cMatrix;
}

const CMatrix4x4 operator * (const CMatrix4x4& cMatrix, const double fC)
{
	return fC * cMatrix;
}

const CMatrix4x4 operator / (const CMatrix4x4& cMatrix, const int iC)
{
	CMatrix4x4 cResult(cMatrix);
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] /= iC;
	return cResult;
}

const CMatrix4x4 operator / (const CMatrix4x4& cMatrix, const double fC)
{
	CMatrix4x4 cResult(cMatrix);
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] /= fC;
	return cResult;
}

const CVector3D operator * (const CMatrix4x4& cMatrix, const CVector3D& cVector)
{
	double fX = cVector.X * cMatrix.m_aCell[0][0] + cVector.Y * cMatrix.m_aCell[1][0] + cVector.Z * cMatrix.m_aCell[2][0] + cMatrix.m_aCell[3][0];
	double fY = cVector.X * cMatrix.m_aCell[0][1] + cVector.Y * cMatrix.m_aCell[1][1] + cVector.Z * cMatrix.m_aCell[2][1] + cMatrix.m_aCell[3][1];
	double fZ = cVector.X * cMatrix.m_aCell[0][2] + cVector.Y * cMatrix.m_aCell[1][2] + cVector.Z * cMatrix.m_aCell[2][2] + cMatrix.m_aCell[3][2];
	return CVector3D(fX, fY, fZ);
}

const CVector4D operator * (const CMatrix4x4& cMatrix, const CVector4D& cVector)
{
	double fX = cVector.X * cMatrix.m_aCell[0][0] + cVector.Y * cMatrix.m_aCell[1][0] + cVector.Z * cMatrix.m_aCell[2][0] + cVector.W * cMatrix.m_aCell[3][0];
	double fY = cVector.X * cMatrix.m_aCell[0][1] + cVector.Y * cMatrix.m_aCell[1][1] + cVector.Z * cMatrix.m_aCell[2][1] + cVector.W * cMatrix.m_aCell[3][1];
	double fZ = cVector.X * cMatrix.m_aCell[0][2] + cVector.Y * cMatrix.m_aCell[1][2] + cVector.Z * cMatrix.m_aCell[2][2] + cVector.W * cMatrix.m_aCell[3][2];
	double fW = cVector.X * cMatrix.m_aCell[0][3] + cVector.Y * cMatrix.m_aCell[1][3] + cVector.Z * cMatrix.m_aCell[2][3] + cVector.W * cMatrix.m_aCell[3][3];
	return CVector4D(fX, fY, fZ, fW);
}

const CMatrix4x4 operator + (const CMatrix4x4& cMatrix1, const CMatrix4x4& cMatrix2)
{
	return CMatrix4x4(cMatrix1) += cMatrix2;
}

const CMatrix4x4 operator - (const CMatrix4x4& cMatrix1, const CMatrix4x4& cMatrix2)
{
	return CMatrix4x4(cMatrix1) -= cMatrix2;
}

const CMatrix4x4 operator * (const CMatrix4x4& cMatrix1, const CMatrix4x4& cMatrix2)
{
	return CMatrix4x4(cMatrix1) *= cMatrix2;
}

const CMatrix4x4 ScalarMultiply(const CMatrix4x4& cMatrix1, const CMatrix4x4& cMatrix2)
{
	CMatrix4x4 cResult;
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] = cMatrix1.m_aData[i] * cMatrix2.m_aData[i];
	return cResult;
}

}

/* EOF */
