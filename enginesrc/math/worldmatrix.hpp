#ifndef ENGINE_WORLD_MATRIX_HPP
#define ENGINE_WORLD_MATRIX_HPP

#include "../common.hpp"
#include "../useful.hpp"
#include "matrix4.hpp"
#include "quaternion.hpp"
#include <set>

namespace engine
{

class CWorldMatrix
{
	private:
		CMatrix4 m_cAbsoluteMatrix;
		CMatrix4 m_cRelativeMatrix;
		CMatrix4 m_cRotationMatrix;
		std::set<CWorldMatrix *> m_cChildMatrices;
		CWorldMatrix *m_cParentMatrix;

		CQuaternion m_cQuaternion;
		CVector3 m_cPosition;
		CVector3 m_cScale;
		CVector3 m_cRotation;

		bool m_bRecalculateAbsoluteMatrix;
		bool m_bRecalculateRelativeMatrix;

	public:
		CWorldMatrix(): m_cPosition(0.0, 0.0, 0.0), m_cScale(1.0, 1.0, 1.0), m_cRotation(0.0, 0.0, 0.0)
		{
			m_bRecalculateAbsoluteMatrix = false;
			m_bRecalculateRelativeMatrix = false;
			m_cParentMatrix = NULL;
		}
		~CWorldMatrix()
		{
			if (m_cParentMatrix)
				m_cParentMatrix->RemoveChild(*this);
		}
		const CMatrix4 &GetRelativeMatrix()
		{
			if (m_bRecalculateRelativeMatrix)
			{
				m_cRelativeMatrix = CMatrix4::IDENTITY;
				m_cRelativeMatrix.Translate(m_cPosition);
				m_cRelativeMatrix.Scale(m_cScale);
				m_cRelativeMatrix *= m_cRotationMatrix;
				m_bRecalculateAbsoluteMatrix = true;
				m_bRecalculateRelativeMatrix = false;
			}
			return m_cRelativeMatrix;
		}
		const CMatrix4 &GetAbsoluteMatrix()
		{
			if (m_bRecalculateAbsoluteMatrix)
			{
				m_cAbsoluteMatrix = GetRelativeMatrix();
				if (m_cParentMatrix != NULL)
					m_cAbsoluteMatrix *= m_cParentMatrix->GetAbsoluteMatrix();
				m_bRecalculateAbsoluteMatrix = false;
			}
			return m_cAbsoluteMatrix;
		}
		void AddChild(CWorldMatrix &cMatrix)
		{
			if (cMatrix.m_cParentMatrix != NULL)
			{
				Debug(Format("CWorldMatrix::AddChild - Forcing child removal in previous parent matrix"));
				cMatrix.m_cParentMatrix->RemoveChild(cMatrix);
			}
			cMatrix.m_bRecalculateAbsoluteMatrix = true;
			m_cChildMatrices.insert(&cMatrix);
		}
		void RemoveChild(CWorldMatrix &cMatrix)
		{
			cMatrix.m_cParentMatrix = NULL;
			m_cChildMatrices.erase(&cMatrix);
		}
		void SetPosition(const CVector3 &cPosition)
		{
			m_cPosition = cPosition;
			m_bRecalculateRelativeMatrix = true;
		}
		const CVector3 &GetPosition() const
		{
			return m_cPosition;
		}
		void SetScale(const CVector3 &cScale)
		{
			m_cScale = cScale;
			m_bRecalculateRelativeMatrix = true;
		}
		const CVector3 &GetScale() const
		{
			return m_cScale;
		}
		void SetRotation(const CVector3 &cRotation)
		{
			m_cQuaternion = CQuaternion(cRotation);
			m_cRotationMatrix = m_cQuaternion.ToMatrix4();
			m_cRotation = cRotation;
			m_bRecalculateRelativeMatrix = true;
		}
		void SetRotation(const CQuaternion &cRotation)
		{
			m_cQuaternion = cRotation;
			m_cRotationMatrix = cRotation.ToMatrix4();
			m_cRotation = cRotation.GetEulerAngles();
			m_bRecalculateRelativeMatrix = true;
		}
		const CVector3 &GetRotation() const
		{
			return m_cRotation;
		}
		const CQuaternion &GetQuaternion() const
		{
			return m_cQuaternion;
		}
		const CVector3 GetAbsolutePosition() const
		{
			return m_cAbsoluteMatrix.GetTranslation();
		}
};

}

#endif /* ENGINE_WORLD_MATRIX_HPP */

/* EOF */
