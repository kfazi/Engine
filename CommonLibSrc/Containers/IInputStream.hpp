#ifndef COMMON_INPUT_STREAM_HPP
#define COMMON_INPUT_STREAM_HPP

#include "../Internal.hpp"

namespace Common
{

class IInputStream
{
	public:
		virtual void SetReadPosition(unsigned int iPosition) = 0;
		virtual unsigned int GetReadPosition() = 0;
		virtual const CString &GetString() = 0;
		virtual void Read(const char *pData, unsigned int iDataSize) = 0;
};

}

#endif /* COMMON_INPUT_STREAM_HPP */

/* EOF */
