#ifndef COMMON_OUTPUT_STREAM_HPP
#define COMMON_OUTPUT_STREAM_HPP

#include "../Internal.hpp"

namespace Common
{

class IOutputStream
{
	public:
		virtual void SetWritePosition(unsigned int iPosition) = 0;
		virtual unsigned int GetWritePosition() = 0;
		virtual const CString &GetString() = 0;
		virtual void Write(const char *pData, unsigned int iDataSize) = 0;
};

}

#endif /* COMMON_OUTPUT_STREAM_HPP */

/* EOF */
