#ifndef ENGINE_RENDERERS_MANAGER_HPP
#define ENGINE_RENDERERS_MANAGER_HPP

#include "../common.hpp"
#include "../string.hpp"
#include <vector>

namespace engine
{

class CRenderer;
class CSystemWindow;

class DLLEXPORTIMPORT CRenderersManager
{
	private:
		typedef CRenderer *(*TRendererCreateFunction)(const CSystemWindow &cWindow);
		typedef void (*TRendererDestroyFunction)(CRenderer *pRenderer);

		struct SRendererDescription
		{
			CString cName;
			TRendererCreateFunction pCreateRenderer;
			TRendererDestroyFunction pDestroyRenderer;
		};

		std::vector<SRendererDescription> m_cRendererDescriptions;

		void ScanRenderers();

	public:
		CRenderersManager();
		~CRenderersManager();

		CString GetRendererName(unsigned int iRendererNumber) const;
		unsigned int GetRenderersCount() const;
		CRenderer *CreateRenderer(unsigned int iRendererNumber, const CSystemWindow &cWindow);
		void DestroyRenderer(CRenderer &cRenderer);
};

}

#endif /* ENGINE_RENDERERS_MANAGER_HPP */

/* EOF */
