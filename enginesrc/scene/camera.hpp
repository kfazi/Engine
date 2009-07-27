#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include "../common.hpp"
#include "../renderer/rendertarget.hpp"
#include <vector>

namespace engine
{

class CCamera
{
	public:
		enum EMode
		{
			Frustum,
			Orthogonal
		};
	private:
		std::vector<CCamera *> m_cParents;
		CRenderTarget *m_pRenderTarget;
		EMode m_eMode;
		double m_fFov;
	public:
		CCamera(const double fFov = 60.0, const EMode eMode = Frustum);
		int GetParentCamerasNumber() const;
		const CCamera *GetParentCamera(const int iCameraNumber) const;
		CRenderTarget *GetRenderTarget() const;
		void SetRenderTarget(const CRenderTarget &cRenderTarget);
		const CRect &GetRenderPosition() const;
		void SetRenderPosition(const CRect &cRect);
		const EMode GetMode() const;
		void SetMode(const EMode eMode);
};

}

#endif /* ENGINE_CAMERA_HPP */

/* EOF */
