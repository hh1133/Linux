#ifndef XXXXX_FRAMEBUFFER
#define XXXXX_FRAMEBUFFER

#include "Point.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/kd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

class CFramebuffer
{
public:
	CFramebuffer();
	~CFramebuffer();
	int Init();
	void DrawPoint(CPoint pt);
	void DrawPoints(VecPt ptVec);
	
	int GetWidth();
	int GetHeight();
	CPoint GetCenter();


protected:
	void UnInit();

protected:
	char *buf;
	int fbfd;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	long int screensize;
};

#endif // XXXXX_FRAMEBUFFER
