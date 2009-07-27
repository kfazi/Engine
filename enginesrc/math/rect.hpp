/**
 * @file rect.hpp
 * @brief Rectangle class and functions.
 * @author Marek Antoniak <kfazol@gmail.com>
 * @date 2008
 */

#ifndef ENGINE_RECT_HPP
#define ENGINE_RECT_HPP

#include "../common.hpp"
#include "math.hpp"
#include "vector2.hpp"
#include <iostream>

namespace engine
{

/**
 * Class encapsulating a rectangle.
 */
class CRect
{
	private:
		/**
		 * Initializes values, so Left is less than Right and Top is less than Bottom.
		 * @param[in] fLeft Position of left edge along X axis.
		 * @param[in] fTop Position of top edge along Y axis.
		 * @param[in] fRight Position of right edge along X axis.
		 * @param[in] fBottom Position of bottom edge along Y axis.
		 */
		inline void Initialize(const double fLeft, const double fTop, const double fRight, const double fBottom)
		{
			Left = CMath::Min(fLeft, fRight);
			Top = CMath::Min(fTop, fBottom);
			Right = CMath::Max(fLeft, fRight);
			Bottom = CMath::Max(fTop, fBottom);
		}

	public:
		double Left; /**< Left edge. */
		double Top; /**< Top edge. */
		double Right; /**< Right edge. */
		double Bottom; /**< Bottom edge. */

		/**
		 * Default constructor.
		 */
		CRect()
		{
			Left = 0.0;
			Top = 0.0;
			Right = 0.0;
			Bottom = 0.0;
		}

		/**
		 * Constructor.
		 * @param[in] fLeft Position of left edge along X axis.
		 * @param[in] fTop Position of top edge along Y axis.
		 * @param[in] fRight Position of right edge along X axis.
		 * @param[in] fBottom Position of bottom edge along Y axis.
		 */
		CRect(const double fLeft, const double fTop, const double fRight, const double fBottom)
		{
			Initialize(fLeft, fTop, fRight, fBottom);
		}

		/**
		 * Constructor.
		 * @param[in] cPoint1 Top-left point.
		 * @param[in] cPoint2 Bottom-right point.
		 */
		CRect(const CVector2 &cPoint1, const CVector2 &cPoint2)
		{
			Initialize(cPoint1.X, cPoint1.Y, cPoint2.X, cPoint2.Y);
		}

		/**
		 * Repairs broken rectangle.
		 * Makes sure Left is less than Right and Top is less than Bottom.
		 */
		inline void Repair()
		{
			Initialize(Left, Top, Right, Bottom);
		}

		/**
		 * @return Width of rectangle.
		 */
		inline double GetWidth() const
		{
			return Right - Left;
		}

		/**
		 * @return Height of rectangle.
		 */
		inline double GetHeight() const
		{
			return Bottom - Top;
		}

		/**
		 * @return Area of rectangle.
		 */
		inline double GetArea() const
		{
			return GetWidth() * GetHeight();
		}

		/**
		 * Tests two rectangles for equality.
		 */
		inline bool operator == (const CRect &cRect) const
		{
			return (Left == cRect.Left && Top == cRect.Top && Right == cRect.Right && Bottom == cRect.Bottom);
		}

		/**
		 * Tests two rectangles for inequality.
		 */
		inline bool operator != (const CRect &cRect) const
		{
			return !(*this == cRect);
		}

		/**
		 * Assignment operator.
		 */
		inline CRect &operator = (const CRect &cRect)
		{
			Left = cRect.Left;
			Top = cRect.Top;
			Right = cRect.Right;
			Bottom = cRect.Bottom;
		}
};

}

#endif /* ENGINE_RECT_HPP */

/* EOF */
