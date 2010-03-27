#ifndef COMMON_DELETE_POLICY_HPP
#define COMMON_DELETE_POLICY_HPP

#include "../Internal.hpp"

namespace Common
{

class DeletePolicy
{
	public:
		template<typename Type> static void Delete(Type *data)
		{
			delete data;
		}
};

}

#endif /* COMMON_DELETE_POLICY_HPP */

/* EOF */