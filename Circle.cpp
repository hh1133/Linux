#include "Circle.h"

// 中点画圆：只在 1/8 圆弧上递推，其余点用对称得到
// 判别式只用整数加减，和直线的 Bresenham 是同一类做法
VecPt CCircle::ToPoints()
{
	VecPt ptVec;

	int radius = m_radius;
	if (radius < 0)
	{
		radius = -radius;
	}
	if (radius == 0)
	{
		ptVec.push_back(CPoint(m_center.x, m_center.y, m_color));
		return ptVec;
	}

	int x = 0;
	int y = radius;
	int p = 1 - radius;
	AddPts(ptVec, x, y);

	while (x < y)
	{
		x++;
		if (p < 0)
		{
			// 中点在圆内，下一个点仍取当前 y
			p += 2 * x + 1;
		}
		else
		{
			// 中点在圆外，y 向圆心收一格
			y--;
			p += 2 * (x - y) + 1;
		}
		AddPts(ptVec, x, y);
	}

	return ptVec;
}

void CCircle::AddPts(VecPt &ptVec, int x, int y)
{
	ptVec.push_back(CPoint(m_center.x + x, m_center.y + y, m_color));
	ptVec.push_back(CPoint(m_center.x - x, m_center.y + y, m_color));
	ptVec.push_back(CPoint(m_center.x + x, m_center.y - y, m_color));
	ptVec.push_back(CPoint(m_center.x - x, m_center.y - y, m_color));

	ptVec.push_back(CPoint(m_center.x + y, m_center.y + x, m_color));
	ptVec.push_back(CPoint(m_center.x - y, m_center.y + x, m_color));
	ptVec.push_back(CPoint(m_center.x + y, m_center.y - x, m_color));
	ptVec.push_back(CPoint(m_center.x - y, m_center.y - x, m_color));
}
