/**
 */

#include "matrix4.hpp"

namespace engine
{

const CMatrix4 CMatrix4::ZERO(0.0, 0.0, 0.0, 0.0,
															0.0, 0.0, 0.0, 0.0,
															0.0, 0.0, 0.0, 0.0,
															0.0, 0.0, 0.0, 0.0);

const CMatrix4 CMatrix4::IDENTITY(1.0, 0.0, 0.0, 0.0,
																	0.0, 1.0, 0.0, 0.0,
																	0.0, 0.0, 1.0, 0.0,
																	0.0, 0.0, 0.0, 1.0);

}

/* EOF */
