#ifndef COMMON_INPUT_STREAM_HPP
#define COMMON_INPUT_STREAM_HPP

#include "../Internal.hpp"
#include "CStreamBase.hpp"

namespace Common
{

class CInputStream: public CStreamBase
{
	public:
		virtual void SetReadPosition(long long iPosition) = 0;
		virtual unsigned int GetReadPosition() = 0;
		virtual void Read(const char* pData, unsigned int iDataSize) = 0;

		CInputStream& operator>> (bool& bTarget);
		CInputStream& operator>> (short& iTarget);
		CInputStream& operator>> (unsigned short& iTarget);
		CInputStream& operator>> (int& iTarget);
		CInputStream& operator>> (unsigned int& iTarget);
		CInputStream& operator>> (long& iTarget);
		CInputStream& operator>> (unsigned long& iTarget);
		CInputStream& operator>> (long long& iTarget);
		CInputStream& operator>> (unsigned long long& iTarget);
		CInputStream& operator>> (float& fTarget);
		CInputStream& operator>> (double& fTarget);
		CInputStream& operator>> (long double& fTarget);
		CInputStream& operator>> (const void*& pTarget);
//		IInputStream& operator>> (IInputStream& (*pf)(IInputStream& ));
};

}

#endif /* COMMON_INPUT_STREAM_HPP */

/* EOF */
