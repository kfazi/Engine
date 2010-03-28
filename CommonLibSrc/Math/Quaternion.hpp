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

class Matrix4x4;
class Vector3D;

class COMMONDLLIMPORTEXPORT Quaternion
{
	public:
		double W;
		double X;
		double Y;
		double Z;

		static const Quaternion ZERO; /**< A zero quaternion. */

		static const Quaternion IDENTITY; /**< An identity quaternion. */

		Vector3D GetVector() const;

		//! constructors
		Quaternion();
	
		Quaternion(double w, double x, double y, double z);

		Quaternion(double real, const Vector3D& vector);

		//! from 3 euler angles
		Quaternion(double thetaZ, double thetaY, double thetaX);
		
		//! from 3 euler angles 
		Quaternion(const Vector3D& angles);

		//! from a normalized axis - angle pair rotation
		Quaternion(const Vector3D& axis, double angle);

		//! basic operations
		Quaternion& operator= (const Quaternion& quaternion);	

		/**
		 * Quaternion negation.
		 */
		Quaternion operator- () const;

		const Quaternion& operator+= (const Quaternion& quaternion);	

		const Quaternion& operator-= (const Quaternion& quaternion);	

		const Quaternion& operator*= (const Quaternion& quaternion);	
		
		template<typename Type> Quaternion& operator*= (Type scalar)
		{
			W *= scalar;
			X *= scalar;
			Y *= scalar;
			Z *= scalar;
			return *this;
		}

		template<typename Type> Quaternion& operator/= (Type scalar)
		{
			W /= scalar;
			X /= scalar;
			Y /= scalar;
			Z /= scalar;
			return *this;
		}

		friend const Quaternion operator+ (const Quaternion& quaternion1, const Quaternion& quaternion2);

		friend const Quaternion operator- (const Quaternion& quaternion1, const Quaternion& quaternion2);

		friend const Quaternion operator* (const Quaternion& quaternion1, const Quaternion& quaternion2);

		/**
		 * Quaternion multiplication by a scalar.
		 */
		template<typename Type> friend Quaternion operator* (Type scalar, const Quaternion& quaternion)
		{
			return Quaternion(quaternion) *= scalar;
		}

		/**
		 * Quaternion multiplication by a scalar.
		 */
		template<typename Type> friend Quaternion operator* (const Quaternion& quaternion, Type scalar)
		{
			return Quaternion(quaternion) *= scalar;
		}

		/**
		 * Quaternion division by a scalar.
		 */
		template<typename Type> friend Quaternion operator/ (Type scalar, const Quaternion& quaternion)
		{
			return Quaternion(quaternion) /= scalar;
		}

		/**
		 * Quaternion division by a scalar.
		 */
		template<typename Type> friend Quaternion operator/ (const Quaternion& quaternion, Type scalar)
		{
			return Quaternion(quaternion) /= scalar;
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

		Quaternion GetNormalized() const;

		void FromEulerAngles(double thetaZ, double thetaY, double thetaX);

		void FromEulerAngles(const Vector3D& angles);

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
			CQuaternion result;

			result.SetW(0);
			if (fSinA > 0)
			{
				result.SetX(fA * GetX() / fSinA);
				result.SetY(fA * GetY() / fSinA);
				result.SetZ(fA * GetZ() / fSinA);
			}
			else
			{
				result.SetX(0);
				result.SetY(0);
				result.SetZ(0);
			}
			return result;
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
		Matrix4x4 ToMatrix4() const;
		
		//! returns the axis and angle of this unit quaternion
		void ToAxisAngle(Vector3D& axis, double& angle) const;

		//! returns the euler angles from a rotation quaternion
		Vector3D GetEulerAngles() const;
};

}

#endif /* COMMON_QUATERNION_HPP */

/* EOF */
