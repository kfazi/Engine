#include "renderer.hpp"

extern "C" void CreateRenderer()
{
}

extern "C" void DestroyRenderer()
{
}

engine::CRenderersManager::SRendererInfo sInfo;

extern "C" engine::CRenderersManager::SRendererInfo *GetRendererInfo()
{
	sInfo.cName = "OpenGL";
	sInfo.sVersion.iMajor = 1;
	sInfo.sVersion.iMinor = 0;
	sInfo.sVersion.iBuild = 0;
	return &sInfo;
}

/* EOF */