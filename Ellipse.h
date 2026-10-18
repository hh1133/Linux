#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "Geometry.h"

class CEllipse : public CGeometry
{
public:
	CEllipse(CPoint center, int rx, int ry, CColor cc)
	{
		m_center = center;
		m_rx = rx;
		m_ry = ry;
		m_color = cc;
	};

	void Set(CPoint center, int rx, int ry, CColor cc)
	{
		m_center = center;
		m_rx = rx;
		m_ry = ry;
		m_color = cc;
	};

protected:
	virtual VecPt ToPoints();
	void AddPts(VecPt &ptVec, int x, int y);

protected:
	CPoint m_center;
	int m_rx;
	int m_ry;
};

#endif // ELLIPSE_H
