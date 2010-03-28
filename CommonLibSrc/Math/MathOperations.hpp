#ifndef COMMON_MATH_OPERATIONS_HPP
#define COMMON_MATH_OPERATIONS_HPP

#include "../Internal.hpp"
#include "Vector3D.hpp"
#include "Quaternion.hpp"
#include "cmath"

namespace Common
{

class COMMONDLLIMPORTEXPORT MathOperations
{
	public:
		/**
		 * Returns minimum of its two arguments.
		 * This function is here only because of Microsoft's fuckups.
		 * \param[in] x First value.
		 * \param[in] y Second value.
		 * \return Minimum value.
		 */
		template<class Type> inline static const Type& Min(const Type& x, const Type& y)
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
		template<class Type> inline static const Type& Max(const Type& x, const Type& y)
		{
			return (x < y) ? y : x;
		}

		/**
		 * Converts degrees to radians.
		 * \param[in] fDegrees Value in degrees.
		 * \return Value in radians.
		 */
		inline static double DegToRad(const double degrees)
		{
			return degrees * 0.017453292519943295769236907684888; /* fDegrees * pi / 180 */
		}

		/**
		 * Converts radians to degrees.
		 * \param[in] fRadians Value in radians.
		 * \return Value in degrees.
		 */
		inline static double RadToDeg(const double radians)
		{
			return radians * 57.295779513082320876798154814105; /* fRadians * 180 / pi */
		}

		inline static double DotProduct(const Vector3D& vector1, const Vector3D& vector2)
		{
			return vector1.X * vector2.X + vector1.Y * vector2.Y + vector1.Z * vector2.Z;
		}

		inline static double DotProduct(const Quaternion& quaternion1, const Quaternion& quaternion2)
		{
			return DotProduct(quaternion1.GetVector(), quaternion2.GetVector()) + quaternion1.W *
				quaternion1.W;
		}

		inline static Vector3D CrossProduct(const Vector3D& vector1, const Vector3D& vector2)
		{
			return Vector3D(vector1.Y * vector2.Z - vector1.Z * vector2.Y, vector1.Z * vector2.X -
				vector1.X * vector2.Z, vector1.X * vector2.Y - vector1.Y * vector2.X);
		}

		inline static Vector3D Rotate(const Vector3D& vector, const Quaternion& quaternion)
		{
			Quaternion vectorQuaternion(0, vector);
			Quaternion cConjugate(quaternion);
			cConjugate.Conjugate();
			return (quaternion * vectorQuaternion * cConjugate).GetVector();
		}

		//! linear quaternion interpolation
		static Quaternion Lerp(const Quaternion& quaternion1, const Quaternion& quaternion2,
			const double t)
		{
			return (quaternion1 * (1.0 - t) + quaternion2 * t).GetNormalized();
		}

		//! spherical linear interpolation
		static Quaternion Slerp(const Quaternion& quaternion1, const Quaternion& quaternion2,
			const double t)
		{
			Quaternion quaternion3;
			double fDot = DotProduct(quaternion1, quaternion2);

			/*	dot = cos(theta)
				if (dot < 0), q1 and q2 are more than 90 degrees apart,
				so we can invert one to reduce spinning	*/
			if (fDot < 0)
			{
				fDot = -fDot;
				quaternion3 = -quaternion2;
			}
			else
				quaternion3 = quaternion2;

			if (fDot < 0.95)
			{
				double angle = acos(fDot);
				return (quaternion1 * sin(angle * (1.0 - t)) + quaternion3 * sin(angle * t)) / sin(angle);
			}
			else // if the angle is small, use linear interpolation
				return Lerp(quaternion1, quaternion3, t);
		}

		//! This version of slerp, used by squad, does not check for theta > 90.
		static Quaternion SlerpNoInvert(const Quaternion& quaternion1, const Quaternion& quaternion2,
			const double t)
		{
			double fDot = DotProduct(quaternion1, quaternion2);

			if (fDot > -0.95 && fDot < 0.95)
			{
				double angle = acos(fDot);
				return (quaternion1 * sin(angle * (1.0 - t)) + quaternion2 * sin(angle * t)) / sin(angle);
			}
			else // if the angle is small, use linear interpolation
				return Lerp(quaternion1, quaternion2, t);
		}

		//! spherical cubic interpolation
		static Quaternion Squad(const Quaternion& quaternion1, const Quaternion& quaternion2,
			const Quaternion& quaternionA, const Quaternion& quaternionB, const double t)
		{
			Quaternion quaternionC = SlerpNoInvert(quaternion1, quaternion2, t);
			Quaternion quaternionD = SlerpNoInvert(quaternionA, quaternionB, t);
			return SlerpNoInvert(quaternionC, quaternionD, 2.0 * t * (1.0 - t));
		}

		//! Shoemake-Bezier interpolation using De Castlejau algorithm
		static Quaternion Bezier(const Quaternion& quaternion1, const Quaternion& quaternion2,
			const Quaternion& quaternionA, const Quaternion& quaternionB, const double t)
		{
			// level 1
			Quaternion quaternion11 = SlerpNoInvert(quaternion1, quaternionA, t);
			Quaternion quaternion12 = SlerpNoInvert(quaternionA, quaternionB, t);
			Quaternion quaternion13 = SlerpNoInvert(quaternionB, quaternion2, t);
			// level 2 and 3
			return SlerpNoInvert(SlerpNoInvert(quaternion11, quaternion12, t), SlerpNoInvert(quaternion12,
				quaternion13, t), t);
		}

#if 0
		//! Given 3 quaternions, qn-1,qn and qn+1, calculate a control point to be used in spline
		//! interpolation
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
