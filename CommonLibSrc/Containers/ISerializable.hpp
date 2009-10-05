#ifndef COMMON_SERIALIZABLE_HPP
#define COMMON_SERIALIZABLE_HPP

#include "../Internal.hpp"

namespace Common
{

class ISerializable
{
	public:
		virtual void Serialize() = 0;
		virtual void Deserialize() = 0;
};

}

#endif /* COMMON_SERIALIZABLE_HPP */

/* EOF */
