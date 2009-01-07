#ifndef ENGINE_QUATERNION_HPP
#define ENGINE_QUATERNION_HPP

#include "matrix4.hpp"

namespace engine
{

class CQuaternion
{
	private:
		double m_fW;
		double m_fX;
		double m_fY;
		double m_fZ;

	public:
		inline double GetW() const
		{
			return m_fW;
		}

		inline void SetW(const double fW)
		{
			m_fW = fW;
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

		inline CVector3 GetVector() const
		{
			return CVector3(GetX(), GetY(), GetZ());
		}

	//! constructors
		CQuaternion()
		{
		}
	
		CQuaternion(const double fW, const double fX, const double fY, const double fZ)
		{
			SetW(fW);
			SetX(fX);
			SetY(fY);
			SetZ(fZ);
		}

		CQuaternion(const double fReal, const CVector3 &cVector)
		{
			SetW(fReal);
			SetX(cVector.GetX());
			SetY(cVector.GetY());
			SetZ(cVector.GetZ());
		}

	//! from 3 euler angles
		CQuaternion(const double fThetaZ, const double fThetaY, const double fThetaX)
		{
			double fCosZ2 = cos(0.5 * fThetaZ);
			double fCosY2 = cos(0.5 * fThetaY);
			double fCosX2 = cos(0.5 * fThetaX);

			double fSinZ2 = sin(0.5 * fThetaZ);
			double fSinY2 = sin(0.5 * fThetaY);
			double fSinX2 = sin(0.5 * fThetaX);

			// and now compute quaternion
			SetW(fCosZ2 * fCosY2 * fCosX2 + fSinZ2 * fSinY2 * fSinX2);
			SetX(fCosZ2 * fCosY2 * fSinX2 - fSinZ2 * fSinY2 * fCosX2);
			SetY(fCosZ2 * fSinY2 * fCosX2 + fSinZ2 * fCosY2 * fSinX2);
			SetZ(fSinZ2 * fCosY2 * fCosX2 - fCosZ2 * fSinY2 * fSinX2);
		}
		
		//! from 3 euler angles 
		CQuaternion(const CVector3 &cAngles)
		{	
			double fCosZ2 = cos(0.5 * cAngles.GetZ());
			double fCosY2 = cos(0.5 * cAngles.GetY());
			double fCosX2 = cos(0.5 * cAngles.GetX());

			double fSinZ2 = sin(0.5 * cAngles.GetZ());
			double fSinY2 = sin(0.5 * cAngles.GetY());
			double fSinX2 = sin(0.5 * cAngles.GetX());

			// and now compute quaternion
			SetW(fCosZ2 * fCosY2 * fCosX2 + fSinZ2 * fSinY2 * fSinX2);
			SetX(fCosZ2 * fCosY2 * fSinX2 - fSinZ2 * fSinY2 * fCosX2);
			SetY(fCosZ2 * fSinY2 * fCosX2 + fSinZ2 * fCosY2 * fSinX2);
			SetZ(fSinZ2 * fCosY2 * fCosX2 - fCosZ2 * fSinY2 * fSinX2);
		} 

		//! from a normalized axis - angle pair rotation
		CQuaternion(const CVector3 &cAxis, double fAngle)
		{
			double fSinAngle = sin(fAngle / 2.0);
			SetW(cos(fAngle / 2.0));
			SetX(cAxis.GetX() * fSinAngle);
			SetY(cAxis.GetY() * fSinAngle);
			SetZ(cAxis.GetZ() * fSinAngle);
		}

		//! basic operations
		CQuaternion &operator = (const CQuaternion &cQuaternion)		
		{
			SetW(cQuaternion.GetW());
			SetX(cQuaternion.GetX());
			SetY(cQuaternion.GetY());
			SetZ(cQuaternion.GetZ());
			return *this;
		}

		/**
		 * Quaternion negation.
		 */
		inline CQuaternion operator - () const
		{
			return CQuaternion(-GetW(), -GetX(), -GetY(), -GetZ());
		}

		const CQuaternion &operator += (const CQuaternion &cQuaternion)		
		{
			SetW(GetW() + cQuaternion.GetW());
			SetX(GetX() + cQuaternion.GetX());
			SetY(GetY() + cQuaternion.GetY());
			SetZ(GetZ() + cQuaternion.GetZ());
			return *this;
		}

		const CQuaternion &operator -= (const CQuaternion &cQuaternion)		
		{
			SetW(GetW() - cQuaternion.GetW());
			SetX(GetX() - cQuaternion.GetX());
			SetY(GetY() - cQuaternion.GetY());
			SetZ(GetZ() - cQuaternion.GetZ());
			return *this;
		}

		const CQuaternion &operator *= (const CQuaternion &cQuaternion)		
		{
			SetW(GetW() * cQuaternion.GetW() - GetX() * cQuaternion.GetX() - GetY() * cQuaternion.GetY() - GetZ() * cQuaternion.GetZ());
			SetX(GetW() * cQuaternion.GetX() + GetX() * cQuaternion.GetW() + GetY() * cQuaternion.GetZ() - GetZ() * cQuaternion.GetY());
			SetY(GetW() * cQuaternion.GetY() + GetY() * cQuaternion.GetW() + GetZ() * cQuaternion.GetX() - GetX() * cQuaternion.GetZ());
			SetZ(GetW() * cQuaternion.GetZ() + GetZ() * cQuaternion.GetW() + GetX() * cQuaternion.GetY() - GetY() * cQuaternion.GetX());
			return *this;
		}
		
		/* TODO: Correct equations */
		const CQuaternion &operator /= (const CQuaternion &cQuaternion)		
		{
			SetW(GetW() * cQuaternion.GetW() - GetX() * cQuaternion.GetX() - GetY() * cQuaternion.GetY() - GetZ() * cQuaternion.GetZ());
			SetX(GetW() * cQuaternion.GetX() + GetX() * cQuaternion.GetW() + GetY() * cQuaternion.GetZ() - GetZ() * cQuaternion.GetY());
			SetY(GetW() * cQuaternion.GetY() + GetY() * cQuaternion.GetW() + GetZ() * cQuaternion.GetX() - GetX() * cQuaternion.GetZ());
			SetZ(GetW() * cQuaternion.GetZ() + GetZ() * cQuaternion.GetW() + GetX() * cQuaternion.GetY() - GetY() * cQuaternion.GetX());
			return *this;
		}

		template<typename TType> CQuaternion &operator *= (TType tScalar)
		{
			SetW(GetW() * tScalar);
			SetX(GetX() * tScalar);
			SetY(GetY() * tScalar);
			SetZ(GetZ() * tScalar);
			return *this;
		}

		template<typename TType> CQuaternion &operator /= (TType tScalar)
		{
			SetW(GetW() / tScalar);
			SetX(GetX() / tScalar);
			SetY(GetY() / tScalar);
			SetZ(GetZ() / tScalar);
			return *this;
		}

		inline friend const CQuaternion operator + (const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2)
		{
			return CQuaternion(cQuaternion1) += cQuaternion2;
		}

		inline friend const CQuaternion operator - (const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2)
		{
			return CQuaternion(cQuaternion1) -= cQuaternion2;
		}

		inline friend const CQuaternion operator * (const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2)
		{
			return CQuaternion(cQuaternion1) *= cQuaternion2;
		}

		inline friend const CQuaternion operator / (const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2)
		{
			return CQuaternion(cQuaternion1) /= cQuaternion2;
		}

		/**
		 * Quaternion multiplication by a scalar.
		 */
		template<typename TType> friend CQuaternion operator * (TType tScalar, const CQuaternion &cQuaternion)
		{
			return CQuaternion(cQuaternion) * tScalar;
		}

		/**
		 * Quaternion multiplication by a scalar.
		 */
		template<typename TType> friend CQuaternion operator * (const CQuaternion &cQuaternion, TType tScalar)
		{
			return CQuaternion(cQuaternion) * tScalar;
		}

		/**
		 * Quaternion division by a scalar.
		 */
		template<typename TType> friend CQuaternion operator / (TType tScalar, const CQuaternion &cQuaternion)
		{
			return CQuaternion(cQuaternion) / tScalar;
		}

		/**
		 * Quaternion division by a scalar.
		 */
		template<typename TType> friend CQuaternion operator / (const CQuaternion &cQuaternion, TType tScalar)
		{
			return CQuaternion(cQuaternion) / tScalar;
		}
		
		/**
		 * Returns a length of a quaternion.
		 */
		inline double GetLength() const
		{
			return std::sqrt(GetW() * GetW() + GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ());
		}

		/**
		 * Returns a length of a quaternion.
		 */
		inline double GetLengthSquared() const
		{
			return GetW() * GetW() + GetX() * GetX() + GetY() * GetY() + GetZ() * GetZ();
		}

		/**
		 * Normalizes a quaternion.
		 */
		inline void Normalize()
		{
			double fLength = GetLength();
			if (fLength == 1.0 || fLength < std::numeric_limits<double>::epsilon())
				return;
			SetW(GetW() / fLength);
			SetX(GetX() / fLength);
			SetY(GetY() / fLength);
			SetZ(GetZ() / fLength);
		}

		inline CQuaternion GetNormalized() const
		{
			CQuaternion cQuaternion(*this);
			cQuaternion.Normalize();
			return cQuaternion;
		}

		//! computes the conjugate of this quaternion
		void Conjugate()
		{
			SetX(-GetX());
			SetY(-GetY());
			SetZ(-GetZ());
		}

		//! inverts this quaternion
		void Invert()
		{
			Conjugate();
			*this /= GetLengthSquared();
		}

#if 0
		//! returns the logarithm of a quaternion = v*a where q = [cos(a),v*sin(a)]
		CQuaternion Log() const
		{
			double fA = std::acos(GetW());
			double fSinA = std::sin(fA);
			CQuaternion cResult;

			cResult.SetW(0);
			if (fSinA > 0)
			{
				cResult.SetX(fA * GetX() / fSinA);
				cResult.SetY(fA * GetY() / fSinA);
				cResult.SetZ(fA * GetZ() / fSinA);
			}
			else
			{
				cResult.SetX(0);
				cResult.SetY(0);
				cResult.SetZ(0);
			}
			return cResult;
		}

		//! returns e^quaternion = exp(v*a) = [cos(a),vsin(a)]
		quaternion exp() const
		{
			float a = (float)v.length();
			float sina = (float)sin(a);
			float cosa = (float)cos(a);
			quaternion ret;

			ret.s = cosa;
			if (a > 0)
			{
				ret.v.x = sina * v.x / a;
				ret.v.y = sina * v.y / a;
				ret.v.z = sina * v.z / a;
			} else {
				ret.v.x = ret.v.y = ret.v.z = 0;
			}
			return ret;
		}
#endif

		//! casting to a 4x4 isomorphic matrix for right multiplication with vector
		CMatrix4 ToMatrix4() const
		{			
			return CMatrix4(GetW(), -GetX(), -GetY(), -GetZ(),
					GetX(), GetW(), -GetZ(), GetY(),
					GetY(), GetZ(), GetW(), -GetX(),
					GetZ(), -GetY(), GetX(), GetW());
		}
		

		//! returns the axis and angle of this unit quaternion
		void ToAxisAngle(CVector3 &cAxis, double &fAngle) const
		{
			fAngle = acos(GetW());

			// pre-compute to save time
			double SinThetaInv = 1.0 / sin(fAngle);

			// now the vector
			cAxis.SetX(GetX() * SinThetaInv);
			cAxis.SetY(GetY() * SinThetaInv);
			cAxis.SetZ(GetZ() * SinThetaInv);

			// multiply by 2
			fAngle *= 2.0;
		}


		//! returns the euler angles from a rotation quaternion
		CVector3 GetEulerAngles() const
		{
			double fSquaredW = GetW() * GetW();    
			double fSquaredX = GetX() * GetX();    
			double fSquaredY = GetY() * GetY();    
			double fSquaredZ = GetZ() * GetZ();    

			CVector3 cEuler;
			cEuler.SetX(atan2(2.0 * (GetX() * GetY() + GetZ() * GetW()), fSquaredX - fSquaredY - fSquaredZ + fSquaredW));
			cEuler.SetY(asin(-2.0 * (GetX() * GetZ() - GetY() * GetW())));
			cEuler.SetZ(atan2(2.0 * (GetY() * GetZ() + GetX() * GetW()), -fSquaredX - fSquaredY + fSquaredZ + fSquaredW));
			return cEuler;
		}
};

}

#endif /* ENGINE_QUATERNION_HPP */

/* EOF */
