/**
 * @file CQuaternion.hpp
 * @brief Quaternion class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2009
 */

#ifndef COMMON_QUATERNION_HPP
#define COMMON_QUATERNION_HPP

#include "../Internal.hpp"

namespace Common
{

class CMatrix4x4;
class CVector3D;

class COMMONDLLIMPORTEXPORT CQuaternion
{
	public:
		double W;
		double X;
		double Y;
		double Z;

		static const CQuaternion ZERO; /**< A zero quaternion. */

		static const CQuaternion IDENTITY; /**< An identity quaternion. */

		CVector3D GetVector() const;

		//! constructors
		CQuaternion();
	
		CQuaternion(const double fW, const double fX, const double fY, const double fZ);

		CQuaternion(const double fReal, const CVector3D& cVector);

		//! from 3 euler angles
		CQuaternion(const double fThetaZ, const double fThetaY, const double fThetaX);
		
		//! from 3 euler angles 
		CQuaternion(const CVector3D& cAngles);

		//! from a normalized axis - angle pair rotation
		CQuaternion(const CVector3D& cAxis, double fAngle);

		//! basic operations
		CQuaternion& operator= (const CQuaternion& cQuaternion);	

		/**
		 * Quaternion negation.
		 */
		CQuaternion operator- () const;

		const CQuaternion& operator+= (const CQuaternion& cQuaternion);	

		const CQuaternion& operator-= (const CQuaternion& cQuaternion);	

		const CQuaternion& operator*= (const CQuaternion& cQuaternion);	
		
		template<typename TType> CQuaternion& operator*= (TType tScalar)
		{
			W *= tScalar;
			X *= tScalar;
			Y *= tScalar;
			Z *= tScalar;
			return *this;
		}

		template<typename TType> CQuaternion& operator/= (TType tScalar)
		{
			W /= tScalar;
			X /= tScalar;
			Y /= tScalar;
			Z /= tScalar;
			return *this;
		}

		friend const CQuaternion operator+ (const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2);

		friend const CQuaternion operator- (const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2);

		friend const CQuaternion operator* (const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2);

		/**
		 * Quaternion multiplication by a scalar.
		 */
		template<typename TType> friend CQuaternion operator* (TType tScalar, const CQuaternion& cQuaternion)
		{
			return CQuaternion(cQuaternion) *= tScalar;
		}

		/**
		 * Quaternion multiplication by a scalar.
		 */
		template<typename TType> friend CQuaternion operator* (const CQuaternion& cQuaternion, TType tScalar)
		{
			return CQuaternion(cQuaternion) *= tScalar;
		}

		/**
		 * Quaternion division by a scalar.
		 */
		template<typename TType> friend CQuaternion operator/ (TType tScalar, const CQuaternion& cQuaternion)
		{
			return CQuaternion(cQuaternion) /= tScalar;
		}

		/**
		 * Quaternion division by a scalar.
		 */
		template<typename TType> friend CQuaternion operator/ (const CQuaternion& cQuaternion, TType tScalar)
		{
			return CQuaternion(cQuaternion) /= tScalar;
		}
		
		/**
		 * Returns a length of a quaternion.
		 */
		double GetLength() const;

		/**
		 * Returns a length of a quaternion.
		 */
		double GetLengthSquared() const;

		/**
		 * Normalizes a quaternion.
		 */
		void Normalize();

		CQuaternion GetNormalized() const;

		void FromEulerAngles(const double fThetaZ, const double fThetaY, const double fThetaX);

		void FromEulerAngles(const CVector3D& cAngles);

		//! computes the conjugate of this quaternion
		void Conjugate();

		//! inverts this quaternion
		void Invert();

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
		CMatrix4x4 ToMatrix4() const;
		
		//! returns the axis and angle of this unit quaternion
		void ToAxisAngle(CVector3D& cAxis, double& fAngle) const;

		//! returns the euler angles from a rotation quaternion
		CVector3D GetEulerAngles() const;
};

}

#endif /* COMMON_QUATERNION_HPP */

/* EOF */
