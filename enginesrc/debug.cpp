#include "debug.hpp"
#include <cstdarg>

namespace engine
{

void Debug(const std::string &sFormat, ...)
{
	va_list vaList;
	va_start(vaList, sFormat);
	vprintf(sFormat.c_str(), vaList);
	va_end(vaList);
}

void Panic(const std::string &sFormat, ...)
{
	va_list vaList;
	va_start(vaList, sFormat);
	printf("Engine Panic: ");
	vprintf(sFormat.c_str(), vaList);
	va_end(vaList);
	exit(-1);
}

}

/* EOF */

