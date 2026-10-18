#include "Line.h"
#include <cstdlib>

// Bresenham 直线：只用整数加减，用判别式决定下一个像素
// 不再计算斜率，避免除法和浮点误差
VecPt CLine::ToPoints()
{
	VecPt ptVec;

	int x0 = (int)m_start.x;
	int y0 = (int)m_start.y;
	int x1 = (int)m_end.x;
	int y1 = (int)m_end.y;

	int dx = std::abs(x1 - x0);
	int dy = std::abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;

	if (dx >= dy)
	{
		// 沿 x 步进。判别式 p 表示真实直线与当前像素的偏差
		// p < 0：下一步仍用当前 y；p >= 0：y 也要跟着走一格
		int p = 2 * dy - dx;
		int y = y0;
		for (int i = 0; i <= dx; ++i)
		{
			ptVec.push_back(CPoint(x0, y, m_color));
			x0 += sx;
			if (p >= 0)
			{
				y += sy;
				p += 2 * dy - 2 * dx;
			}
			else
			{
				p += 2 * dy;
			}
		}
	}
	else
	{
		// 沿 y 步进，x、y 角色对调
		int p = 2 * dx - dy;
		int x = x0;
		for (int i = 0; i <= dy; ++i)
		{
			ptVec.push_back(CPoint(x, y0, m_color));
			y0 += sy;
			if (p >= 0)
			{
				x += sx;
				p += 2 * dx - 2 * dy;
			}
			else
			{
				p += 2 * dx;
			}
		}
	}

	return ptVec;
}
