#ifndef ENGINE_DEBUG_HPP
#define ENGINE_DEBUG_HPP

#include <string>

namespace engine
{

void Debug(const std::string &sFormat, ...);
void Panic(const std::string &sFormat, ...);

/*
inline void Debug(const std::string &sFormat, ...)
{
}
*/

}

#endif /* ENGINE_DEBUG_HPP */

/* EOF */

