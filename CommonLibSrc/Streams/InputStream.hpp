#ifndef COMMON_INPUT_STREAM_HPP
#define COMMON_INPUT_STREAM_HPP

#include "../Internal.hpp"
#include "CStreamBase.hpp"

namespace Common
{

class InputStream: public StreamBase
{
	public:
		virtual void SetReadPosition(size_t position) = 0;
		virtual size_t GetReadPosition() = 0;
		virtual void Read(const char* data, size_t dataSize) = 0;

		InputStream& operator>> (bool& target);
		InputStream& operator>> (short& target);
		InputStream& operator>> (unsigned short& target);
		InputStream& operator>> (int& target);
		InputStream& operator>> (unsigned int& target);
		InputStream& operator>> (long& target);
		InputStream& operator>> (unsigned long& target);
		InputStream& operator>> (long long& target);
		InputStream& operator>> (unsigned long long& target);
		InputStream& operator>> (float& target);
		InputStream& operator>> (double& target);
		InputStream& operator>> (long double& target);
		InputStream& operator>> (const void*& target);
//		IInputStream& operator>> (IInputStream& (*pf)(IInputStream& ));
};

}

#endif /* COMMON_INPUT_STREAM_HPP */

/* EOF */
