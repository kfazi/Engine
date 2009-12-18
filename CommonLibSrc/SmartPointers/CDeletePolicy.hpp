#ifndef COMMON_DELETE_POLICY_HPP
#define COMMON_DELETE_POLICY_HPP

#include "../Internal.hpp"

namespace Common
{

class CDeletePolicy
{
	public:
		template<typename tType> static void Delete(tType *pData)
		{
			delete pData;
		}
};

}

#endif /* COMMON_DELETE_POLICY_HPP */

/* EOF */
