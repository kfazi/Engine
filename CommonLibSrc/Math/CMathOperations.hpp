#ifndef COMMON_MATH_OPERATIONS_HPP
#define COMMON_MATH_OPERATIONS_HPP

#include "../Internal.hpp"
#include "CVector3D.hpp"
#include "CQuaternion.hpp"
#include "cmath"

namespace Common
{

class COMMONDLLIMPORTEXPORT CMathOperations
{
	public:
		/**
		 * Returns minimum of its two arguments.
		 * This function is here only because of Microsoft's fuckups.
		 * \param[in] x First value.
		 * \param[in] y Second value.
		 * \return Minimum value.
		 */
		template<class CType> inline static const CType& Min(const CType& x, const CType& y)
		{
			return (x < y) ? x : y;
		}

		/**
		 * Returns maximum of its two arguments.
		 * This function is here only because of Microsoft's fuckups.
		 * \param[in] x First value.
		 * \param[in] y Second value.
		 * \return Maximum value.
		 */
		template<class CType> inline static const CType& Max(const CType& x, const CType& y)
		{
			return (x < y) ? y : x;
		}

		/**
		 * Converts degrees to radians.
		 * \param[in] fDegrees Value in degrees.
		 * \return Value in radians.
		 */
		inline static double DegToRad(const double fDegrees)
		{
			return fDegrees * 0.017453292519943295769236907684888; /* fDegrees * pi / 180 */
		}

		/**
		 * Converts radians to degrees.
		 * \param[in] fRadians Value in radians.
		 * \return Value in degrees.
		 */
		inline static double RadToDeg(const double fRadians)
		{
			return fRadians * 57.295779513082320876798154814105; /* fRadians * 180 / pi */
		}

		inline static double DotProduct(const CVector3D& cVector1, const CVector3D& cVector2)
		{
			return cVector1.X * cVector2.X + cVector1.Y * cVector2.Y + cVector1.Z * cVector2.Z;
		}

		inline static double DotProduct(const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2)
		{
			return DotProduct(cQuaternion1.GetVector(), cQuaternion2.GetVector()) + cQuaternion1.W * cQuaternion1.W;
		}

		inline static CVector3D CrossProduct(const CVector3D& cVector1, const CVector3D& cVector2)
		{
			return CVector3D(cVector1.Y * cVector2.Z - cVector1.Z * cVector2.Y, cVector1.Z * cVector2.X - cVector1.X * cVector2.Z, cVector1.X * cVector2.Y - cVector1.Y * cVector2.X);
		}

		inline static CVector3D Rotate(const CVector3D& cVector, const CQuaternion& cQuaternion)
		{
			CQuaternion cVectorQuaternion(0, cVector);
			CQuaternion cConjugate(cQuaternion);
			cConjugate.Conjugate();
			return (cQuaternion * cVectorQuaternion * cConjugate).GetVector();
		}

		//! linear quaternion interpolation
		static CQuaternion Lerp(const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2, const double fT)
		{
			return (cQuaternion1 * (1.0 - fT) + cQuaternion2 * fT).GetNormalized();
		}

		//! spherical linear interpolation
		static CQuaternion Slerp(const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2, const double fT)
		{
			CQuaternion cQuaternion3;
			double fDot = DotProduct(cQuaternion1, cQuaternion2);

			/*	dot = cos(theta)
				if (dot < 0), q1 and q2 are more than 90 degrees apart,
				so we can invert one to reduce spinning	*/
			if (fDot < 0)
			{
				fDot = -fDot;
				cQuaternion3 = -cQuaternion2;
			}
			else
				cQuaternion3 = cQuaternion2;

			if (fDot < 0.95)
			{
				double fAngle = acos(fDot);
				return (cQuaternion1 * sin(fAngle * (1.0 - fT)) + cQuaternion3 * sin(fAngle * fT)) / sin(fAngle);
			}
			else // if the angle is small, use linear interpolation
				return Lerp(cQuaternion1, cQuaternion3, fT);
		}

		//! This version of slerp, used by squad, does not check for theta > 90.
		static CQuaternion SlerpNoInvert(const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2, const double fT)
		{
			double fDot = DotProduct(cQuaternion1, cQuaternion2);

			if (fDot > -0.95 && fDot < 0.95)
			{
				double fAngle = acos(fDot);
				return (cQuaternion1 * sin(fAngle * (1.0 - fT)) + cQuaternion2 * sin(fAngle * fT)) / sin(fAngle);
			}
			else // if the angle is small, use linear interpolation
				return Lerp(cQuaternion1, cQuaternion2, fT);
		}

		//! spherical cubic interpolation
		static CQuaternion Squad(const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2, const CQuaternion& cQuaternionA, const CQuaternion& cQuaternionB, const double fT)
		{
			CQuaternion cQuaternionC = SlerpNoInvert(cQuaternion1, cQuaternion2, fT);
			CQuaternion cQuaternionD = SlerpNoInvert(cQuaternionA, cQuaternionB, fT);
			return SlerpNoInvert(cQuaternionC, cQuaternionD, 2.0 * fT * (1.0 - fT));
		}

		//! Shoemake-Bezier interpolation using De Castlejau algorithm
		static CQuaternion Bezier(const CQuaternion& cQuaternion1, const CQuaternion& cQuaternion2, const CQuaternion& cQuaternionA, const CQuaternion& cQuaternionB, const double fT)
		{
			// level 1
			CQuaternion cQuaternion11 = SlerpNoInvert(cQuaternion1, cQuaternionA, fT);
			CQuaternion cQuaternion12 = SlerpNoInvert(cQuaternionA, cQuaternionB, fT);
			CQuaternion cQuaternion13 = SlerpNoInvert(cQuaternionB, cQuaternion2, fT);
			// level 2 and 3
			return SlerpNoInvert(SlerpNoInvert(cQuaternion11, cQuaternion12, fT), SlerpNoInvert(cQuaternion12, cQuaternion13, fT), fT);
		}

#if 0
		//! Given 3 quaternions, qn-1,qn and qn+1, calculate a control point to be used in spline interpolation
		static quaternion spline(const quaternion& qnm1,const quaternion& qn,const quaternion& qnp1)
		{
			quaternion qni(qn.s, -qn.v);
			return qn * (( (qni*qnm1).log()+(qni*qnp1).log() )/-4).exp();
		}
#endif
};

}

#endif /* COMMON_MATH_OPERATIONS_HPP */

/* EOF */
