#ifndef COMMON_INPUT_OUTPUT_STREAM_HPP
#define COMMON_INPUT_OUTPUT_STREAM_HPP

#include "../Internal.hpp"
#include "CInputStream.hpp"
#include "COutputStream.hpp"

namespace Common
{

class InputOutputStream: public InputStream, public OutputStream
{
};

}

#endif /* COMMON_INPUT_OUTPUT_STREAM_HPP */

/* EOF */
