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
 * Class encapsulating a standard 3-element vector.
 */
class CRect
{
	public:
		double x;
		double y;
		double width;
		double height;

		CRect();
		~CRect();
		double GetArea();
		bool operator == (const CRect &cRect) const;
		bool operator != (const CRect &cRect) const;
		CRect &operator = (const CRect &cRect);
		CRect &operator - ();
};

}

#endif /* ENGINE_RECT_HPP */

/* EOF */
