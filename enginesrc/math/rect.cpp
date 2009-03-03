#include "../common.hpp"
#include "math.hpp"
#include "rect.hpp"

namespace engine
{

CRect::CRect()
{
	x = 0.0;
	y = 0.0;
	width = 0.0;
	height = 0.0;
}

double CRect::GetArea() const
{
	return width * height;
}

}
