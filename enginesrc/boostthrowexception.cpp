#include <boost/throw_exception.hpp>
#include <stdlib.h>

namespace boost
{

void throw_exception(std::exception const &e)
{
	exit(-1);
}

}

/* EOF */
