#include "Ellipse.h"
#include "Line.h"

// 中点画椭圆。椭圆没有圆的八分对称，分成两段：
// 区域1切线较平，沿 x 步进；区域2切线较陡，沿 y 步进
VecPt CEllipse::ToPoints()
{
	VecPt ptVec;

	int rx = m_rx < 0 ? -m_rx : m_rx;
	int ry = m_ry < 0 ? -m_ry : m_ry;

	if (rx == 0 && ry == 0)
	{
		ptVec.push_back(CPoint(m_center.x, m_center.y, m_color));
		return ptVec;
	}
	if (rx == 0)
	{
		CLine line(CPoint(m_center.x, m_center.y - ry),
				   CPoint(m_center.x, m_center.y + ry), m_color);
		return line.GetPoints();
	}
	if (ry == 0)
	{
		CLine line(CPoint(m_center.x - rx, m_center.y),
				   CPoint(m_center.x + rx, m_center.y), m_color);
		return line.GetPoints();
	}

	long long rx2 = (long long)rx * rx;
	long long ry2 = (long long)ry * ry;
	long long twoRx2 = 2 * rx2;
	long long twoRy2 = 2 * ry2;

	long long x = 0;
	long long y = ry;
	long long px = 0;
	long long py = twoRx2 * y;
	AddPts(ptVec, (int)x, (int)y);

	// 区域1初值：ry^2 - rx^2*ry + rx^2/4，除以4用整数四舍五入
	long long p = ry2 - rx2 * ry + (rx2 + 2) / 4;
	while (px < py)
	{
		x++;
		px += twoRy2;
		if (p < 0)
		{
			p += ry2 + px;
		}
		else
		{
			y--;
			py -= twoRx2;
			p += ry2 + px - py;
		}
		AddPts(ptVec, (int)x, (int)y);
	}

	// 区域2。起点判别式里 (x+0.5)^2 乘开后带 ry^2/4
	p = ry2 * (x * x + x) + (ry2 + 2) / 4
		+ rx2 * (y - 1) * (y - 1) - rx2 * ry2;
	while (y > 0)
	{
		y--;
		py -= twoRx2;
		if (p > 0)
		{
			p += rx2 - py;
		}
		else
		{
			x++;
			px += twoRy2;
			p += rx2 - py + px;
		}
		AddPts(ptVec, (int)x, (int)y);
	}

	return ptVec;
}

void CEllipse::AddPts(VecPt &ptVec, int x, int y)
{
	ptVec.push_back(CPoint(m_center.x + x, m_center.y + y, m_color));
	ptVec.push_back(CPoint(m_center.x - x, m_center.y + y, m_color));
	ptVec.push_back(CPoint(m_center.x + x, m_center.y - y, m_color));
	ptVec.push_back(CPoint(m_center.x - x, m_center.y - y, m_color));
}
