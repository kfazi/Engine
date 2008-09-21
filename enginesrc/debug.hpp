#ifndef KFZ_DEBUG_HPP
#define KFZ_DEBUG_HPP

#include <string>

namespace kfz
{

void Debug(const std::string &sFormat, ...);
void Panic(const std::string &sFormat, ...);

/*
inline void Debug(const std::string &sFormat, ...)
{
}
*/

}

#endif /* KFZ_DEBUG_HPP */

/* EOF */

