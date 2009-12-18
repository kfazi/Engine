#ifndef COMMON_DELETE_ARRAY_POLICY_HPP
#define COMMON_DELETE_ARRAY_POLICY_HPP

#include "../Internal.hpp"

namespace Common
{

class CDeleteArrayPolicy
{
	public:
		template<typename tType> static void Delete(tType *pData)
		{
			delete [] pData;
		}
};

}

#endif /* COMMON_DELETE_ARRAY_POLICY_HPP */

/* EOF */
