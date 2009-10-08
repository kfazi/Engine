#ifndef COMMON_INPUT_OUTPUT_STREAM_HPP
#define COMMON_INPUT_OUTPUT_STREAM_HPP

#include "../Internal.hpp"
#include "IInputStream.hpp"
#include "IOutputStream.hpp"

namespace Common
{

class IInputOutputStream: public IInputStream, public IOutputStream
{
};

}

#endif /* COMMON_INPUT_OUTPUT_STREAM_HPP */

/* EOF */
