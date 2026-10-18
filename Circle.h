#ifndef CIRCLE_H
#define CIRCLE_H

#include "Geometry.h"

class CCircle : public CGeometry
{
public:
	CCircle(CPoint center, int radius, CColor cc)
	{
		m_center = center;
		m_radius = radius;
		m_color = cc;
	};

	void Set(CPoint center, int radius, CColor cc)
	{
		m_center = center;
		m_radius = radius;
		m_color = cc;
	};

protected:
	virtual VecPt ToPoints();
	void AddPts(VecPt &ptVec, int x, int y);

protected:
	CPoint m_center;
	int m_radius;
};

#endif // CIRCLE_H
