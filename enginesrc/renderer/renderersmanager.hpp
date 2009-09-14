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
	public:
		struct DLLEXPORTIMPORT SRendererVersion
		{
			unsigned int iMajor;
			unsigned int iMinor;
			unsigned int iBuild;

			SRendererVersion(unsigned int iMajor, unsigned int iMinor, unsigned int iBuild);
			SRendererVersion();
		};

		struct SRendererInfo
		{
			SRendererVersion sVersion;
			CString cName;
		};

	private:
		typedef CRenderer *(*TRendererCreateFunction)(const CSystemWindow &cWindow);
		typedef void (*TRendererDestroyFunction)(CRenderer *pRenderer);
		typedef SRendererInfo *(*TGetRendererInfoFunction)();

		struct SRendererDescription
		{
			unsigned int iModuleId;
			SRendererInfo sInfo;
			TRendererCreateFunction pCreateRenderer;
			TRendererDestroyFunction pDestroyRenderer;
			TGetRendererInfoFunction pGetRendererInfo;
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
