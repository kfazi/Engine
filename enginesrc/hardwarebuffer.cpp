#include "common.hpp"
#include "hardwarebuffer.hpp"
#include "useful.hpp"

namespace engine
{

CHardwareBuffer::ELockOptions CHardwareBuffer::GetLockOption() const
{
	return m_eLockOption;
}

CHardwareBuffer::CHardwareBuffer(unsigned int iSize, bool bShadowed)
{
	m_iSize = iSize;
	if (bShadowed)
		m_pShadowData = new char[iSize];
	else
		m_pShadowData = NULL;
}

CHardwareBuffer::~CHardwareBuffer()
{
	delete [] m_pShadowData;
}

void CHardwareBuffer::Lock(unsigned int iOffset, unsigned int iLength, CHardwareBuffer::ELockOptions eOptions)
{
	if (IsLocked())
		Error("Hardware buffer is already locked.");
	m_bLocked = true;
	m_eLockOption = eOptions;
	LockImplementation(iOffset, iLength, eOptions);
}

void CHardwareBuffer::Lock(CHardwareBuffer::ELockOptions eOptions)
{
	Lock(0, m_iSize, eOptions);
}

void CHardwareBuffer::Unlock()
{
	if (!IsLocked())
		Error("Hardware buffer is not locked.");
	m_bLocked = false;
	UnlockImplementation();
}

void CHardwareBuffer::Read(void *pTargetBuffer, unsigned int iOffset, unsigned int iSize)
{
	if (!IsLocked() || GetLockOption() == Discard)
		Error("Hardware buffer is not properly locked.");
	if (m_iSize < iSize)
		Error("Hardware buffer is too small.");
	ReadImplementation(pTargetBuffer, iOffset, iSize);
}

void CHardwareBuffer::Read(void *pTargetBuffer, unsigned int iSize)
{
	Read(pTargetBuffer, 0, iSize);
}

void CHardwareBuffer::Read(void *pTargetBuffer)
{
	Read(pTargetBuffer, 0, m_iSize);
}

void CHardwareBuffer::Write(void *pSourceBuffer, unsigned int iOffset, unsigned int iSize)
{
	if (!IsLocked() || GetLockOption() == ReadOnly)
		Error("Hardware buffer is not properly locked.");
	if (m_iSize < iSize)
		Error("Hardware buffer is too small.");
	WriteImplementation(pSourceBuffer, iOffset, iSize);
}

void CHardwareBuffer::Write(void *pSourceBuffer, unsigned int iSize)
{
	Write(pSourceBuffer, 0, iSize);
}

void CHardwareBuffer::Write(void *pSourceBuffer)
{
	Write(pSourceBuffer, 0, m_iSize);
}

void CHardwareBuffer::Copy(CHardwareBuffer &cSourceBuffer, unsigned int iSourceOffset, unsigned int iDestinationOffset, unsigned int iSize)
{
	if (!IsLocked() || GetLockOption() == ReadOnly)
		Error("Target hardware buffer is not properly locked.");
	if (!cSourceBuffer.IsLocked() || cSourceBuffer.GetLockOption() == Discard)
		Error("Source hardware buffer is not properly locked.");
	if (m_iSize < iSize)
		Error("Target hardware buffer is too small.");
	if (cSourceBuffer.m_iSize < iSize)
		Error("Source hardware buffer is too small.");
	char *pBuffer = new char[iSize];
	cSourceBuffer.Read(pBuffer, iSourceOffset, iSize);
	Write(pBuffer, iDestinationOffset, iSize);
	delete [] pBuffer;
}

void CHardwareBuffer::Copy(CHardwareBuffer &pSourceBuffer, unsigned int iSize)
{
	Copy(pSourceBuffer, 0, 0, iSize);
}

void CHardwareBuffer::Copy(CHardwareBuffer &pSourceBuffer)
{
	Copy(pSourceBuffer, 0, 0, m_iSize);
}

unsigned int CHardwareBuffer::GetSize() const
{
	return m_iSize;
}

void CHardwareBuffer::UpdateFromShadow()
{
	if (!IsShadowed())
		Error("This hardware buffer is not shadowed.");
}

bool CHardwareBuffer::IsLocked() const
{
	return m_bLocked;
}

bool CHardwareBuffer::IsShadowed() const
{
	return m_pShadowData != NULL;
}

}

/* EOF */
