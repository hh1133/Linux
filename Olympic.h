#ifndef OLYMPIC_H
#define OLYMPIC_H

#include "Geometry.h"

// 五个圆耦合而成。传统黑环按题目要求画成白环
class COlympicRings : public CGeometry
{
public:
	COlympicRings(CPoint center, int radius)
	{
		m_center = center;
		m_radius = radius;
	};

protected:
	virtual VecPt ToPoints();

protected:
	CPoint m_center;
	int m_radius;
};

#endif // OLYMPIC_H
