#ifndef ENGINE_HARDWARE_BUFFER_HPP
#define ENGINE_HARDWARE_BUFFER_HPP

#include "common.hpp"

namespace engine
{

class DLLEXPORTIMPORT CHardwareBuffer
{
	private:
		enum ELockOptions
		{
			Normal,
			Discard,
			ReadOnly
		};

		void *m_pShadowData;
		unsigned int m_iSize;
		bool m_bLocked;
		ELockOptions m_eLockOption;

	protected:
		ELockOptions GetLockOption() const;
		virtual void LockImplementation(unsigned int iOffset, unsigned int iLength, ELockOptions eOptions) = 0;
		virtual void UnlockImplementation() = 0;
		virtual void ReadImplementation(void *pTargetBuffer, unsigned int iOffset, unsigned int iSize) = 0;
		virtual void WriteImplementation(void *pSourceBuffer, unsigned int iOffset, unsigned int iSize) = 0;

	public:
		CHardwareBuffer(unsigned int iSize, bool bShadowed);
		virtual ~CHardwareBuffer();

		void Lock(unsigned int iOffset, unsigned int iLength, ELockOptions eOptions);
		void Lock(ELockOptions eOptions);
		void Unlock();
		void Read(void *pTargetBuffer, unsigned int iOffset, unsigned int iSize);
		void Read(void *pTargetBuffer, unsigned int iSize);
		void Read(void *pTargetBuffer);
		void Write(void *pSourceBuffer, unsigned int iOffset, unsigned int iSize);
		void Write(void *pSourceBuffer, unsigned int iSize);
		void Write(void *pSourceBuffer);
		void Copy(CHardwareBuffer &pSourceBuffer, unsigned int iSourceOffset, unsigned int iDestinationOffset, unsigned int iSize);
		void Copy(CHardwareBuffer &pSourceBuffer, unsigned int iSize);
		void Copy(CHardwareBuffer &pSourceBuffer);
		unsigned int GetSize() const;
		void UpdateFromShadow();
		bool IsLocked() const;
		bool IsShadowed() const;
};

}

#endif /* ENGINE_HARDWARE_BUFFER_HPP */

/* EOF */
