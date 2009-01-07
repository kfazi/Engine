#ifndef ENGINE_MATH_HPP
#define ENGINE_MATH_HPP

#include "vector3.hpp"
#include "quaternion.hpp"

namespace engine
{

class CMath
{
	public:
		inline static double DotProduct(const CVector3 &cVector1, const CVector3 &cVector2)
		{
			return cVector1.GetX() * cVector2.GetX() + cVector1.GetY() * cVector2.GetY() + cVector1.GetZ() * cVector2.GetZ();
		}

		inline static double DotProduct(const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2) 
		{
			return DotProduct(cQuaternion1.GetVector(), cQuaternion2.GetVector()) + cQuaternion1.GetW() * cQuaternion1.GetW();
		}

		inline static CVector3 CrossProduct(const CVector3 &cVector1, const CVector3 &cVector2)
		{
			return CVector3(cVector1.GetY() * cVector2.GetZ() - cVector1.GetZ() * cVector2.GetY(), cVector1.GetZ() * cVector2.GetX() - cVector1.GetX() * cVector2.GetZ(), cVector1.GetX() * cVector2.GetY() - cVector1.GetY() * cVector2.GetX());
		}

		inline static CVector3 Rotate(const CVector3 &cVector, const CQuaternion &cQuaternion)
		{   
			CQuaternion cVectorQuaternion(0, cVector);
			CQuaternion cConjugate(cQuaternion);
			cConjugate.Conjugate();
			return (cQuaternion * cVectorQuaternion * cConjugate).GetVector();
		}

		//! linear quaternion interpolation
		static CQuaternion Lerp(const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2, const double fT) 
		{
			return (cQuaternion1 * (1.0 - fT) + cQuaternion2 * fT).GetNormalized();
		}

		//! spherical linear interpolation
		static CQuaternion Slerp(const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2, const double fT)
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
		static CQuaternion SlerpNoInvert(const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2, const double fT)
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
		static CQuaternion Squad(const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2, const CQuaternion &cQuaternionA, const CQuaternion &cQuaternionB, const double fT)
		{
			CQuaternion cQuaternionC = SlerpNoInvert(cQuaternion1, cQuaternion2, fT);
			CQuaternion cQuaternionD = SlerpNoInvert(cQuaternionA, cQuaternionB, fT);		
			return SlerpNoInvert(cQuaternionC, cQuaternionD, 2.0 * fT * (1.0 - fT));
		}

		//! Shoemake-Bezier interpolation using De Castlejau algorithm
		static CQuaternion Bezier(const CQuaternion &cQuaternion1, const CQuaternion &cQuaternion2, const CQuaternion &cQuaternionA, const CQuaternion &cQuaternionB, const double fT)
		{
			// level 1
			CQuaternion cQuaternion11 = SlerpNoInvert(cQuaternion1, cQuaternionA, fT);
			CQuaternion cQuaternion12 = SlerpNoInvert(cQuaternionA, cQuaternionB, fT);
			CQuaternion cQuaternion13 = SlerpNoInvert(cQuaternionB, cQuaternion2, fT);
			// level 2 and 3
			return SlerpNoInvert(SlerpNoInvert(cQuaternion11, cQuaternion12, fT), SlerpNoInvert(cQuaternion12,cQuaternion13, fT), fT);
		}

#if 0
		//! Given 3 quaternions, qn-1,qn and qn+1, calculate a control point to be used in spline interpolation
		static quaternion spline(const quaternion &qnm1,const quaternion &qn,const quaternion &qnp1)
		{
			quaternion qni(qn.s, -qn.v);	
			return qn * (( (qni*qnm1).log()+(qni*qnp1).log() )/-4).exp();
		}
#endif
};

}

#endif /* ENGINE_MATH_HPP */

/* EOF */
