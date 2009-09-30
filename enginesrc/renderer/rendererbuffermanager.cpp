#include "../common.hpp"
#include "rendererbuffermanager.hpp"
#include "hardwareconstantbuffer.hpp"
#include "hardwareindexbuffer.hpp"
#include "hardwarepixelbuffer.hpp"
#include "hardwarevertexbuffer.hpp"

namespace engine
{

CRendererBufferManager::CRendererBufferManager()
{
}

CRendererBufferManager::~CRendererBufferManager()
{

}

CHardwareConstantBuffer *CRendererBufferManager::CreateConstantBuffer(unsigned int iAmount)
{
	return 0;
}

CHardwareIndexBuffer *CRendererBufferManager::CreateIndexBuffer(unsigned int iAmount, int bits, bool bUseShadowing)
{
	return 0;
}

CHardwarePixelBuffer *CRendererBufferManager::CreatePixelBuffer(unsigned int iWidth, unsigned int iHeight, unsigned int iDepth, int pixelformat, bool bUseShadowing)
{
	return 0;
}

CHardwareVertexBuffer *CRendererBufferManager::CreateVertexBuffer(unsigned int iAmount, bool bUseShadowing)
{
	return 0;
}

}

/* EOF */
