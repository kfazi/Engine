#ifndef ENGINE_RENDERER_BUFFER_MANAGER_HPP
#define ENGINE_RENDERER_BUFFER_MANAGER_HPP

#include "../common.hpp"

namespace engine
{

class CHardwareConstantBuffer;
class CHardwareIndexBuffer;
class CHardwarePixelBuffer;
class CHardwareVertexBuffer;

class DLLEXPORTIMPORT CRendererBufferManager
{
	friend class CRenderer;

	private:
		CRendererBufferManager();

	public:
		~CRendererBufferManager();

		CHardwareConstantBuffer *CreateConstantBuffer(unsigned int iAmount);
		CHardwareIndexBuffer *CreateIndexBuffer(unsigned int iAmount, int bits, bool bUseShadowing = false);
		CHardwarePixelBuffer *CreatePixelBuffer(unsigned int iWidth, unsigned int iHeight, unsigned int iDepth, int pixelformat, bool bUseShadowing = false);
		CHardwareVertexBuffer *CreateVertexBuffer(unsigned int iAmount, bool bUseShadowing = false);
};

}

#endif /* ENGINE_RENDERER_BUFFER_MANAGER_HPP */

/* EOF */
