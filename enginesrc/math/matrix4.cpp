/**
 */

#include "matrix4.hpp"
#include <cstring>
#include <cmath>
#include <cassert>

namespace engine
{

const CMatrix4 CMatrix4::ZERO(0, 0, 0, 0,
															0, 0, 0, 0,
															0, 0, 0, 0,
															0, 0, 0, 0);

const CMatrix4 CMatrix4::IDENTITY(1, 0, 0, 0,
																	0, 1, 0, 0,
																	0, 0, 1, 0,
																	0, 0, 0, 1);

CMatrix4::CMatrix4()
{
	*this = IDENTITY;
}

CMatrix4::CMatrix4(const double fCell00, const double fCell01, const double fCell02, const double fCell03, const double fCell10, const double fCell11, const double fCell12, const double fCell13, const double fCell20, const double fCell21, const double fCell22, const double fCell23, const double fCell30, const double fCell31, const double fCell32, const double fCell33)
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

CMatrix4::CMatrix4(const CMatrix4 &cMatrix)
{
	*this = cMatrix;
}

bool CMatrix4::operator == (const CMatrix4 &cMatrix) const
{
	return !std::memcmp(m_aData, cMatrix.m_aData, 16 * sizeof(double));
}

bool CMatrix4::operator != (const CMatrix4 &cMatrix) const
{
	return !(*this == cMatrix);
}

double CMatrix4::GetCell(const unsigned int iX, const unsigned int iY) const
{
	if (iX > 3 || iY > 3)
		throw "error";
	return m_fCell[iX][iY];
}

void CMatrix4::SetCell(const unsigned int iX, const unsigned int iY, const double fData)
{
	if (iX > 3 || iY > 3)
		throw "error";
	m_fCell[iX][iY] = fData;
}

double CMatrix4::GetDeterminant() const
{
	double fSubDeterminant1 = m_fCell[1][1] * m_fCell[2][2] * m_fCell[3][3] + m_fCell[1][2] * m_fCell[2][3] * m_fCell[3][1] + m_fCell[1][3] * m_fCell[2][1] * m_fCell[3][2] - m_fCell[1][1] * m_fCell[2][3] * m_fCell[3][2] - m_fCell[1][2] * m_fCell[2][1] * m_fCell[3][3] - m_fCell[1][3] * m_fCell[2][2] * m_fCell[3][1];
	double fSubDeterminant2 = m_fCell[1][0] * m_fCell[2][2] * m_fCell[3][3] + m_fCell[1][2] * m_fCell[2][3] * m_fCell[3][0] + m_fCell[1][3] * m_fCell[2][0] * m_fCell[3][2] - m_fCell[1][0] * m_fCell[2][3] * m_fCell[3][2] - m_fCell[1][2] * m_fCell[2][0] * m_fCell[3][3] - m_fCell[1][3] * m_fCell[2][2] * m_fCell[3][0];
	double fSubDeterminant3 = m_fCell[1][0] * m_fCell[2][1] * m_fCell[3][3] + m_fCell[1][1] * m_fCell[2][3] * m_fCell[3][0] + m_fCell[1][3] * m_fCell[2][0] * m_fCell[3][1] - m_fCell[1][0] * m_fCell[2][3] * m_fCell[3][1] - m_fCell[1][1] * m_fCell[2][0] * m_fCell[3][3] - m_fCell[1][3] * m_fCell[2][1] * m_fCell[3][0];
	double fSubDeterminant4 = m_fCell[1][0] * m_fCell[2][1] * m_fCell[3][2] + m_fCell[1][1] * m_fCell[2][2] * m_fCell[3][0] + m_fCell[1][2] * m_fCell[2][0] * m_fCell[3][1] - m_fCell[1][0] * m_fCell[2][2] * m_fCell[3][1] - m_fCell[1][1] * m_fCell[2][0] * m_fCell[3][2] - m_fCell[1][2] * m_fCell[2][1] * m_fCell[3][0];
	return m_fCell[0][0] * fSubDeterminant1 - m_fCell[0][1] * fSubDeterminant2 + m_fCell[0][2] * fSubDeterminant3 - m_fCell[0][3] * fSubDeterminant4;
}

CMatrix4 CMatrix4::GetTranspose()
{
	CMatrix4 cResult;
	for (int iRow = 0; iRow < 4; ++iRow)
	{
		for (int iColumn = 0; iColumn < 4; ++iColumn)
			cResult.m_fCell[iRow][iColumn] = m_fCell[iColumn][iRow];
	}
	return cResult;
}

CMatrix4 CMatrix4::GetInverse() const
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

CVector3 CMatrix4::GetTranslation() const
{
	return CVector3(m_fCell[3][0], m_fCell[3][1], m_fCell[3][2]);
}

void CMatrix4::Translate(const double fX, const double fY, const double fZ)
{
	CMatrix4 cMatrix;
	cMatrix.m_fCell[3][0] = fX;
	cMatrix.m_fCell[3][1] = fY;
	cMatrix.m_fCell[3][2] = fZ;
	*this *= cMatrix;
}

void CMatrix4::Translate(const CVector3 &cVector)
{
	Translate(cVector.GetX(), cVector.GetY(), cVector.GetZ());
}

void CMatrix4::Scale(const double fX, const double fY, const double fZ)
{
	CMatrix4 cMatrix;
	cMatrix.m_fCell[0][0] = fX;
	cMatrix.m_fCell[1][1] = fY;
	cMatrix.m_fCell[2][2] = fZ;
	*this *= cMatrix;
}

void CMatrix4::Scale(const CVector3 &cVector)
{
	Scale(cVector.GetX(), cVector.GetY(), cVector.GetZ());
}

void CMatrix4::RotateX(const double fTheta)
{
	CMatrix4 cMatrix;
	cMatrix.m_fCell[1][1] = cos(fTheta);
	cMatrix.m_fCell[2][1] = -sin(fTheta);
	cMatrix.m_fCell[1][2] = sin(fTheta);
	cMatrix.m_fCell[2][2] = cos(fTheta);
	*this *= cMatrix;
}

void CMatrix4::RotateY(const double fTheta)
{
	CMatrix4 cMatrix;
	cMatrix.m_fCell[0][0] = cos(fTheta);
	cMatrix.m_fCell[2][0] = sin(fTheta);
	cMatrix.m_fCell[0][2] = -sin(fTheta);
	cMatrix.m_fCell[2][2] = cos(fTheta);
	*this *= cMatrix;
}

void CMatrix4::RotateZ(const double fTheta)
{
	CMatrix4 cMatrix;
	cMatrix.m_fCell[0][0] = cos(fTheta);
	cMatrix.m_fCell[1][1] = sin(fTheta);
	cMatrix.m_fCell[0][1] = -sin(fTheta);
	cMatrix.m_fCell[1][1] = cos(fTheta);
	*this *= cMatrix;
}

void CMatrix4::Rotate(const double fX, const double fY, const double fZ, const double fTheta)
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

void CMatrix4::Rotate(const CVector3 &cVector, const double fTheta)
{
	Rotate(cVector.GetX(), cVector.GetY(), cVector.GetZ(), fTheta);
}

void CMatrix4::ShearXY(const double fX, const double fY)
{
	CMatrix4 cMatrix;
	cMatrix.m_fCell[2][0] = fX;
	cMatrix.m_fCell[2][1] = fY;
	*this *= cMatrix;
}

void CMatrix4::ShearXZ(const double fX, const double fZ)
{
	CMatrix4 cMatrix;
	cMatrix.m_fCell[1][0] = fX;
	cMatrix.m_fCell[1][2] = fZ;
	*this *= cMatrix;
}

void CMatrix4::ShearYZ(const double fY, const double fZ)
{
	CMatrix4 cMatrix;
	cMatrix.m_fCell[0][1] = fY;
	cMatrix.m_fCell[0][2] = fZ;
	*this *= cMatrix;
}

CMatrix4 &CMatrix4::operator = (const CMatrix4 &cMatrix)
{
	for (int i = 0; i < 16; ++i)
		m_aData[i] = cMatrix.m_aData[i];
	return *this;
}

CMatrix4 &CMatrix4::operator - ()
{
	for (int i = 0; i < 16; ++i)
		m_aData[i] = -m_aData[i];
	return *this;
}

CMatrix4 &CMatrix4::operator += (const CMatrix4 &cMatrix)
{
	for (int i = 0; i < 16; ++i)
		m_aData[i] += cMatrix.m_aData[i];
	return *this;
}

CMatrix4 &CMatrix4::operator -= (const CMatrix4 &cMatrix)
{
	for (int i = 0; i < 16; ++i)
		m_aData[i] -= cMatrix.m_aData[i];
	return *this;
}

CMatrix4 &CMatrix4::operator *= (const CMatrix4 &cMatrix)
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

const CMatrix4 operator * (const int iC, const CMatrix4 &cMatrix)
{
	CMatrix4 cResult(cMatrix);
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] *= iC;
	return cResult;
}

const CMatrix4 operator * (const double fC, const CMatrix4 &cMatrix)
{
	CMatrix4 cResult(cMatrix);
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] *= fC;
	return cResult;
}

const CMatrix4 operator * (const CMatrix4 &cMatrix, const int iC)
{
	return iC * cMatrix;
}

const CMatrix4 operator * (const CMatrix4 &cMatrix, const double fC)
{
	return fC * cMatrix;
}

const CMatrix4 operator / (const CMatrix4 &cMatrix, const int iC)
{
	CMatrix4 cResult(cMatrix);
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] /= iC;
	return cResult;
}

const CMatrix4 operator / (const CMatrix4 &cMatrix, const double fC)
{
	CMatrix4 cResult(cMatrix);
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] /= fC;
	return cResult;
}

const CMatrix4 operator + (const CMatrix4 &cMatrix1, const CMatrix4 &cMatrix2)
{
	return CMatrix4(cMatrix1) += cMatrix2;
}

const CMatrix4 operator - (const CMatrix4 &cMatrix1, const CMatrix4 &cMatrix2)
{
	return CMatrix4(cMatrix1) -= cMatrix2;
}

const CMatrix4 operator * (const CMatrix4 &cMatrix1, const CMatrix4 &cMatrix2)
{
	return CMatrix4(cMatrix1) *= cMatrix2;
}

const CMatrix4 ScalarMultiply(const CMatrix4 &cMatrix1, const CMatrix4 &cMatrix2)
{
	CMatrix4 cResult;
	for (int i = 0; i < 16; ++i)
		cResult.m_aData[i] = cMatrix1.m_aData[i] * cMatrix2.m_aData[i];
	return cResult;
}

const CVector3 operator * (const CMatrix4 &cMatrix, const CVector3 &cVector)
{
	double fX = cVector.GetX() * cMatrix.m_fCell[0][0] + cVector.GetY() * cMatrix.m_fCell[1][0] + cVector.GetZ() * cMatrix.m_fCell[2][0] + cMatrix.m_fCell[3][0];
	double fY = cVector.GetX() * cMatrix.m_fCell[0][1] + cVector.GetY() * cMatrix.m_fCell[1][1] + cVector.GetZ() * cMatrix.m_fCell[2][1] + cMatrix.m_fCell[3][1];
	double fZ = cVector.GetX() * cMatrix.m_fCell[0][2] + cVector.GetY() * cMatrix.m_fCell[1][2] + cVector.GetZ() * cMatrix.m_fCell[2][2] + cMatrix.m_fCell[3][2];
	return CVector3(fX, fY, fZ);
}

const CVector4 operator * (const CMatrix4 &cMatrix, const CVector4 &cVector)
{
	double fX = cVector.GetX() * cMatrix.m_fCell[0][0] + cVector.GetY() * cMatrix.m_fCell[1][0] + cVector.GetZ() * cMatrix.m_fCell[2][0] + cVector.GetW() * cMatrix.m_fCell[3][0];
	double fY = cVector.GetX() * cMatrix.m_fCell[0][1] + cVector.GetY() * cMatrix.m_fCell[1][1] + cVector.GetZ() * cMatrix.m_fCell[2][1] + cVector.GetW() * cMatrix.m_fCell[3][1];
	double fZ = cVector.GetX() * cMatrix.m_fCell[0][2] + cVector.GetY() * cMatrix.m_fCell[1][2] + cVector.GetZ() * cMatrix.m_fCell[2][2] + cVector.GetW() * cMatrix.m_fCell[3][2];
	double fW = cVector.GetX() * cMatrix.m_fCell[0][3] + cVector.GetY() * cMatrix.m_fCell[1][3] + cVector.GetZ() * cMatrix.m_fCell[2][3] + cVector.GetW() * cMatrix.m_fCell[3][3];
	return CVector4(fX, fY, fZ, fW);
}

std::ostream &operator << (std::ostream &cOutputStream, const CMatrix4 &cMatrix)
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

}

/* EOF */

