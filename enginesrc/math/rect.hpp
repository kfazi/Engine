/**
 * @file rect.hpp
 * @brief Rectangle class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2008
 */

#ifndef ENGINE_RECT_HPP
#define ENGINE_RECT_HPP

#include "../common.hpp"
#include <iostream>

namespace engine
{

/**
 * Class encapsulating a rectangle.
 */
class CRect
{
	public:
		double x;
		double y;
		double width;
		double height;

		CRect();
		double GetArea() const;
		inline bool operator == (const CRect &cRect) const
		{
			return (x == cRect.x && y == cRect.y && width == cRect.width && height == cRect.height);
		}
		inline bool operator != (const CRect &cRect) const
		{
			return !(*this == cRect);
		}
		inline CRect &operator = (const CRect &cRect)
		{
			x = cRect.x;
			y = cRect.y;
			width = cRect.width;
			height = cRect.height;
		}
		inline CRect &operator - ()
		{
			x -= width;
			y -= height;
		}
};

}

#endif /* ENGINE_RECT_HPP */

/* EOF */
