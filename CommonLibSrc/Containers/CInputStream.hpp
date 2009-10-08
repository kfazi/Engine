#ifndef COMMON_INPUT_STREAM_HPP
#define COMMON_INPUT_STREAM_HPP

#include "../Internal.hpp"
#include "CStreamBase.hpp"

namespace Common
{

class IInputStream: public CStreamBase
{
	public:
		virtual void SetReadPosition(long long iPosition) = 0;
		virtual unsigned int GetReadPosition() = 0;
		virtual void Read(const char *pData, unsigned int iDataSize) = 0;

		IInputStream &operator >> (bool &bTarget);
		IInputStream &operator >> (short &iTarget);
		IInputStream &operator >> (unsigned short &iTarget);
		IInputStream &operator >> (int &iTarget);
		IInputStream &operator >> (unsigned int &iTarget);
		IInputStream &operator >> (long &iTarget);
		IInputStream &operator >> (unsigned long &iTarget);
		IInputStream &operator >> (long long &iTarget);
		IInputStream &operator >> (unsigned long long &iTarget);
		IInputStream &operator >> (float &fTarget);
		IInputStream &operator >> (double &fTarget);
		IInputStream &operator >> (long double &fTarget);
		IInputStream &operator >> (const void *&pTarget);
//		IInputStream &operator >> (IInputStream &(*pf)(IInputStream &));
};

}

#endif /* COMMON_INPUT_STREAM_HPP */

/* EOF */
