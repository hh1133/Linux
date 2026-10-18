#include "Framebuffer.h"
#include "Line.h"
#include "Polyline.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Olympic.h"
#include "FractalDragon.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int dragonStep = 10;

static int MinSide(CFramebuffer &fb)
{
	int w = fb.GetWidth();
	int h = fb.GetHeight();
	return w < h ? w : h;
}

static void Draw(CFramebuffer &fb, CGeometry &geo)
{
	fb.Clear();
	fb.DrawPoints(geo.GetPoints());
}

static void PrintMenu()
{
	printf("c -> clean screen\n");
	printf("q -> quit\n");
	printf("l -> draw line\n");
	printf("o -> draw circle\n");
	printf("e -> draw ellipse\n");
	printf("y -> draw polyline\n");
	printf("g -> draw polygon\n");
	printf("p -> draw olympic circles\n");
	printf("d -> draw fractal dragon\n");
}

static void DrawLines(CFramebuffer &fb)
{
	fb.Clear();
	CPoint c = fb.GetCenter();
	int len = MinSide(fb) / 3;
	if (len < 20)
	{
		len = 20;
	}

	CLine horizontal(CPoint(c.x - len, c.y), CPoint(c.x + len, c.y), CColor(255, 0, 0));
	CLine vertical(CPoint(c.x, c.y - len), CPoint(c.x, c.y + len), CColor(0, 255, 0));
	CLine diagonal(CPoint(c.x - len, c.y - len), CPoint(c.x + len, c.y + len), CColor(0, 128, 255));
	CLine shallow(CPoint(c.x - len, c.y + len / 2), CPoint(c.x + len, c.y - len / 3), CColor(255, 255, 0));

	fb.DrawPoints(horizontal.GetPoints());
	fb.DrawPoints(vertical.GetPoints());
	fb.DrawPoints(diagonal.GetPoints());
	fb.DrawPoints(shallow.GetPoints());
}

static void DrawCircle(CFramebuffer &fb)
{
	CPoint c = fb.GetCenter();
	int radius = MinSide(fb) / 4;
	if (radius < 10)
	{
		radius = 10;
	}
	CCircle circle(c, radius, CColor(255, 255, 0));
	Draw(fb, circle);
}

static void DrawEllipse(CFramebuffer &fb)
{
	CPoint c = fb.GetCenter();
	int rx = MinSide(fb) / 3;
	int ry = MinSide(fb) / 6;
	if (rx < 10)
	{
		rx = 10;
	}
	if (ry < 6)
	{
		ry = 6;
	}
	CEllipse ellipse(c, rx, ry, CColor(255, 0, 255));
	Draw(fb, ellipse);
}

static void DrawPolyline(CFramebuffer &fb)
{
	CPoint c = fb.GetCenter();
	int len = MinSide(fb) / 4;
	if (len < 20)
	{
		len = 20;
	}

	VecPt vertexs;
	vertexs.push_back(CPoint(c.x - len, c.y));
	vertexs.push_back(CPoint(c.x - len / 2, c.y - len));
	vertexs.push_back(CPoint(c.x, c.y + len / 2));
	vertexs.push_back(CPoint(c.x + len / 2, c.y - len / 2));
	vertexs.push_back(CPoint(c.x + len, c.y));

	CPolyline polyline(vertexs, CColor(0, 255, 255), false);
	Draw(fb, polyline);
}

static void DrawPolygon(CFramebuffer &fb)
{
	CPoint c = fb.GetCenter();
	double radius = MinSide(fb) / 4.0;
	if (radius < 20)
	{
		radius = 20;
	}

	const int n = 6;
	VecPt vertexs;
	for (int i = 0; i < n; ++i)
	{
		double ang = i * 2.0 * PI / n - PI / 2.0;
		vertexs.push_back(CPoint(c.x + radius * cos(ang),
								 c.y + radius * sin(ang)));
	}

	CPolyline polygon(vertexs, CColor(255, 128, 0), true);
	Draw(fb, polygon);
}

static void DrawOlympic(CFramebuffer &fb)
{
	int w = fb.GetWidth();
	int h = fb.GetHeight();
	int r = w / 6;
	if (r > h / 4)
	{
		r = h / 4;
	}
	if (r < 8)
	{
		r = 8;
	}

	COlympicRings rings(fb.GetCenter(), r);
	Draw(fb, rings);
}

static void DrawDragon(CFramebuffer &fb)
{
	CPoint c = fb.GetCenter();
	int len = MinSide(fb) / 4;
	if (len < 30)
	{
		len = 30;
	}

	CFractalDragon dragon(CPoint(c.x - len, c.y), CPoint(c.x + len, c.y),
						  dragonStep, CColor(0, 255, 0));
	Draw(fb, dragon);
}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		dragonStep = atoi(argv[1]);
		if (dragonStep < 0)
		{
			dragonStep = 0;
		}
		if (dragonStep > 16)
		{
			dragonStep = 16;
		}
	}

	CFramebuffer framebuffer;
	if (framebuffer.Init() != 0)
	{
		return 1;
	}
	framebuffer.Clear();
	PrintMenu();

	char cmd = 0;
	while (1)
	{
		if (scanf(" %c", &cmd) != 1)
		{
			break;
		}
		if (cmd >= 'A' && cmd <= 'Z')
		{
			cmd = cmd - 'A' + 'a';
		}

		switch (cmd)
		{
		case 'c':
			framebuffer.Clear();
			printf("clean screen\n");
			break;
		case 'q':
			printf("quit\n");
			return 0;
		case 'l':
			DrawLines(framebuffer);
			printf("draw line\n");
			break;
		case 'o':
			DrawCircle(framebuffer);
			printf("draw circle\n");
			break;
		case 'e':
			DrawEllipse(framebuffer);
			printf("draw ellipse\n");
			break;
		case 'y':
			DrawPolyline(framebuffer);
			printf("draw polyline\n");
			break;
		case 'g':
			DrawPolygon(framebuffer);
			printf("draw polygon\n");
			break;
		case 'p':
			DrawOlympic(framebuffer);
			printf("draw olympic circles\n");
			break;
		case 'd':
			DrawDragon(framebuffer);
			printf("draw fractal dragon\n");
			break;
		default:
			break;
		}
	}

	return 0;
}
