#include "Olympic.h"
#include "Circle.h"

static void Append(VecPt &dst, CCircle &circle)
{
	VecPt one = circle.GetPoints();
	dst.insert(dst.end(), one.begin(), one.end());
}

VecPt COlympicRings::ToPoints()
{
	VecPt ptVec;

	int r = m_radius;
	if (r < 1)
	{
		r = 1;
	}

	// 圆心距小于直径，相邻圆环会交叉
	int spacing = r * 2 - r / 4;
	int rise = r / 2;

	CPoint c = m_center;
	CCircle blue(CPoint(c.x - spacing, c.y - rise), r, CColor(0, 0, 255));
	CCircle white(CPoint(c.x, c.y - rise), r, CColor(255, 255, 255));
	CCircle red(CPoint(c.x + spacing, c.y - rise), r, CColor(255, 0, 0));
	CCircle yellow(CPoint(c.x - spacing / 2, c.y + rise), r, CColor(255, 255, 0));
	CCircle green(CPoint(c.x + spacing / 2, c.y + rise), r, CColor(0, 255, 0));

	Append(ptVec, blue);
	Append(ptVec, yellow);
	Append(ptVec, white);
	Append(ptVec, green);
	Append(ptVec, red);
	return ptVec;
}
