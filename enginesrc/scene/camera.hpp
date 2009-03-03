#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include "../common.hpp"
#include <vector>

namespace engine
{

class CCamera
{
	private:
		std::vector<CCamera *> m_cParents;
		/* CRenderTarget *m_pRenderTarget */
	public:
		int GetParentCamerasNumber() const;
		const CCamera *GetParentCamera(const int iCameraNumber) const;
#if 0
		CRenderTarget *GetRenderTarget() const;
		void SetRenderTarget(const CRenderTarget &cRenderTarget);
		const CRect &GetRenderPosition() const;
		void SetRenderPosition(const CRect &cRect);
#endif
};

}

#endif /* ENGINE_CAMERA_HPP */

/* EOF */
