#ifndef ENGINE_SYSTEM_MODULE_HPP
#define ENGINE_SYSTEM_MODULE_HPP

#include "../common.hpp"
#include "../string.hpp"
#include <map>

namespace engine
{

/**
 * Class for managing modules.
 * Modules are dynamically loaded libraries.
 * Use it through CCore singleton.
 */
class CSystemModule
{
	/** Allow CCore to create this class. */
	friend class CCore;

	protected:
		/**
		 * Structure containing module data.
		 */
		struct SModule
		{
			unsigned int iReferences: 31; /**< Amount of references to this module. */
			bool bResidential: 1; /**< True if this module is residential and shouldn't be removed. */
			void *pHandle; /**< Handle to the system data of this module. */
			CString cName; /**< Name of the file. */

			/**
			 * Constructor.
			 *
			 * @param[in] cName File name of this module.
			 * @param[in] pHandle System data of this module.
			 */
			SModule(const CString &cName, void *pHandle);
		};

	private:
		/** Map of modules and their IDs. */
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
		/**
		 * Adds module.
		 *
		 * @param[in] pModule Module data.
		 * @return ID of added module.
		 */
		unsigned int AddModule(SModule *pModule);

		/**
		 * Removes module with given ID.
		 *
		 * @param[in] iModuleId Module ID.
		 */
		void RemoveModule(unsigned int iModuleId);

		/**
		 * Searches for module with given name.
		 *
		 * @param[out] iModuleId ID of found module. Unspecified if module wasn't found.
		 * @param[in] cName File name of the module to find.
		 * @return True if module was found.
		 */
		bool FindModule(unsigned int &iModuleId, const CString &cName);

		/**
		 * Gets pointer to the module with given ID.
		 *
		 * @param[in] iModuleId ID of the module.
		 * @return Module data or NULL if module wasn't found.
		 */
		SModule *GetModule(unsigned int iModuleId);

	public:
		/**
		 * Constructor.
		 */
		CSystemModule();

		/**
		 * Virtual destructor.
		 */
		virtual ~CSystemModule();

		/**
		 * Makes selected module residential.
		 * This process can't be reversed.
		 *
		 * @param[in] iModuleId ID of the module.
		 */
		void MakeResident(const unsigned int iModuleId);

		/**
		 * Gets system file name of the module.
		 * This method adds prefix and extension to the file name if necessary.
		 *
		 * @param[in] cDirectory Directory in which the module is located.
		 * @param[in] cFileName Name of the file.
		 * @return Whole path to the module.
		 */
		virtual CString GetSystemName(const CString &cDirectory, const CString &cFileName) = 0;

		/**
		 * Loads module.
		 *
		 * @throws CLoadException Module can't be loaded because of operating system error.
		 * @param[in] cFileName File name of the module. Usage of GetSystemName() is suggested.
		 * @return ID of loaded module.
		 */
		virtual unsigned int Load(const CString &cFileName) = 0;

		/**
		 * Gets address of the symbol located in module.
		 *
		 * @param[in] iModuleId ID of the module.
		 * @param[in] cSymbolName Name of the symbol.
		 * @return Address of the symbol.
		 */
		virtual void *GetSymbol(const unsigned int iModuleId, const CString &cSymbolName) = 0;

		/**
		 * Closes module.
		 * Module will be fully closed if all references to it will be closed and if this module isn't residential.
		 *
		 * @throws CCloseException Module can't be closed because of operating system error.
		 * @param[in] iModuleId ID of the module to close.
		 */
		virtual void Close(const unsigned int iModuleId) = 0;
};

}

#endif /* ENGINE_SYSTEM_MODULE_HPP */

/* EOF */
