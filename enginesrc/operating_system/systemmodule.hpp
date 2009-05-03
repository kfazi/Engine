#ifndef ENGINE_SYSTEM_MODULE_HPP
#define ENGINE_SYSTEM_MODULE_HPP

#include "../common.hpp"
#include "../string.hpp"
#include <map>

namespace engine
{

class CSystemModule
{
	friend class CCore;

	protected:
		struct SModule
		{
			unsigned int iReferences: 31;
			bool bResidential: 1;
			void *pHandle;
			CString cName;
			SModule(const CString &cName, void *pHandle);
		};

	private:
		std::map<unsigned int, SModule *> m_cModulesMap;

		/** Next ID to assign when new module is added. */
		unsigned int m_iNextId;

		/**
		 * Generates next ID for new module.
		 *
		 * @return Next ID.
		 */
		unsigned int GetNextId();

	protected:
		unsigned int AddModule(SModule *pModule);
		void RemoveModule(unsigned int iModuleId);
		bool FindModule(unsigned int &iModuleId, const CString &cName);
		SModule *GetModule(unsigned int iModuleId);

	public:
		CSystemModule();
		virtual ~CSystemModule();
		void MakeResident(const unsigned int iModuleId);
		virtual CString GetSystemName(const CString &cDirectory, const CString &cFileName) = 0;
		virtual unsigned int Load(const CString &cFileName) = 0;
		virtual void *GetSymbol(const unsigned int iModuleId, const CString &cSymbolName) = 0;
		virtual void Close(const unsigned int iModuleId) = 0;
};

}

#endif /* ENGINE_SYSTEM_MODULE_HPP */

/* EOF */
