#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include "../common.hpp"

namespace engine
{

class CRendererBufferManager;

class DLLEXPORTIMPORT CRenderer
{
	friend class CRenderersManager;

	private:
		CRenderer();

	public:
		virtual ~CRenderer();
		virtual CRendererBufferManager *GetBufferManager() = 0;
};

}

#endif /* ENGINE_RENDERER_HPP */

/* EOF */
