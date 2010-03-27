#ifndef COMMON_OUTPUT_STREAM_HPP
#define COMMON_OUTPUT_STREAM_HPP

#include "../Internal.hpp"
#include "StreamBase.hpp"

namespace Common
{

class OutputStream: public StreamBase
{
	private:
		void IntegerToString(unsigned long long value);

	protected:
		virtual String& GetWriteBuffer() = 0;

	public:
		virtual void SetWritePosition(size_t position) = 0;
		virtual size_t GetWritePosition() = 0;
		virtual void Write(const char* data, size_t dataSize) = 0;

		OutputStream& operator<< (bool value);
		OutputStream& operator<< (short value);
		OutputStream& operator<< (unsigned short value);
		OutputStream& operator<< (int value);
		OutputStream& operator<< (unsigned int value);
		OutputStream& operator<< (long value);
		OutputStream& operator<< (unsigned long value);
		OutputStream& operator<< (long long value);
		OutputStream& operator<< (unsigned long long value);
		OutputStream& operator<< (float value);
		OutputStream& operator<< (double value);
		OutputStream& operator<< (long double value);
		OutputStream& operator<< (const void* value);

};

}

#endif /* COMMON_OUTPUT_STREAM_HPP */

/* EOF */
