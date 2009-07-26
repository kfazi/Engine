#ifndef ENGINE_CONFIG_HPP
#define ENGINE_CONFIG_HPP

#include "common.hpp"
#include "string.hpp"
#include <map>

namespace engine
{

/**
 * Class for managing configuration.
 * This is just an interface, you should use specialized class such as CSQLiteConfig.
 */
class CConfig
{
	private:
		/** Marks if configuration was modified. */
		bool m_bModified;

		/** Map of the configuration values. */
		std::map<CString, CString> m_cValues;

		/** Name of the configuration file. */
		CString m_cFileName;

		/**
		 * Replaces all backslashes (\) with slashes (/) and checks if at least one slash exists.
		 *
		 * @param[out] cOutput Output string with replaced backslashes.
		 * @param[in] cInput Input string.
		 * @return True when there is at least one slash in output string.
		 */
		bool CopyWithoutBackSlashes(CString &cOutput, const CString &cInput) const;

	protected:
		/**
		 * Returns map of the configuration values.
		 * Should be used during saving.
		 *
		 * @return Map of the configuration values.
		 */
		const std::map<CString, CString> &GetValues();

		/**
		 * Constructor.
		 */
		CConfig();

		/**
		 * Checks if configuration has been modified.
		 *
		 * @return True when configuration is modified.
		 */
		bool IsModified() const;

		/**
		 * Sets file name.
		 *
		 * @param[in] cFileName Name of the configuration file.
		 */
		void SetFileName(const CString &cFileName);

		/**
		 * Clears configuration.
		 */
		void Clear();

	public:
		/**
		 * Virtual destructor.
		 */
		virtual ~CConfig();

		/**
		 * Loads given configuration file.
		 *
		 * @throws CLoadException Configuration file can't be loaded.
		 * @param[in] cFileName File name of the configuration to load.
		 * @param[in] bSave Should be saved if modified.
		 */
		virtual void Load(const CString &cFileName, bool bSave = true) = 0;

		/**
		 * Saves configuration.
		 *
		 * @throws CSaveException Configuration file can't be saved.
		 */
		virtual void Save() = 0;

		/**
		 * Returns name of the configuration file.
		 *
		 * @return File name.
		 */
		const CString &GetFileName();

		/**
		 * Returns value as string.
		 *
		 * @param[in] cName Name of the variable.
		 * @param[in] cDefaultValue Default value of the variable if it was not found in the configuration.
		 * @return Value of the variable.
		 */
		const CString &GetString(const CString &cName, const CString &cDefaultValue = "");

		/**
		 * Returns value as signed integer.
		 *
		 * @param[in] cName Name of the variable.
		 * @param[in] iDefaultValue Default value of the variable if it was not found in the configuration.
		 * @return Value of the variable.
		 */
		int GetInt(const CString &cName, int iDefaultValue = 0);

		/**
		 * Returns value as unsigned integer.
		 *
		 * @param[in] cName Name of the variable.
		 * @param[in] iDefaultValue Default value of the variable if it was not found in the configuration.
		 * @return Value of the variable.
		 */
		unsigned int GetUnsignedInt(const CString &cName, unsigned int iDefaultValue = 0);

		/**
		 * Returns value as real.
		 *
		 * @param[in] cName Name of the variable.
		 * @param[in] fDefaultValue Default value of the variable if it was not found in the configuration.
		 * @return Value of the variable.
		 */
		double GetReal(const CString &cName, double fDefaultValue = 0.0);

		/**
		 * Sets variable to given value.
		 *
		 * @param[in] cName Name of the variable.
		 * @param[in] cValue Value of the variable.
		 */
		void Set(const CString &cName, const CString &cValue);

		/**
		 * Sets variable to given value.
		 *
		 * @param[in] cName Name of the variable.
		 * @param[in] iValue Value of the variable.
		 */
		void Set(const CString &cName, int iValue);

		/**
		 * Sets variable to given value.
		 *
		 * @param[in] cName Name of the variable.
		 * @param[in] iValue Value of the variable.
		 */
		void Set(const CString &cName, unsigned int iValue);

		/**
		 * Sets variable to given value.
		 *
		 * @param[in] cName Name of the variable.
		 * @param[in] fValue Value of the variable.
		 */
		void Set(const CString &cName, double fValue);
};

}

#endif /* ENGINE_CONFIG_HPP */

/* EOF */
