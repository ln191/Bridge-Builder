#include "Scale.h"
#include <GL/glut.h>

Scale::Scale(float X1, float X2, float Y1, float Y2) : Platform(X1, X2, Y1, Y2)
{
	scaleOut = true;
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;
}
void Scale::Update(float gameTime)
{
	// If the object is active
	if (active)
	{
		// If the scale should scale out
		if (scaleOut == true)
		{
			// x1 is subtracted, x2 is added
			Platform::x1 -= gameTime;
			Platform::x2 += gameTime;
			// If the platform has scaled below 2, it will be scaled in
			if (Platform::x1 <= 2)
				scaleOut = false;
		}
		// If the scale should scale int
		if (scaleOut == false)
		{
			// x1 is added, x2 is subtracted
			Platform::x1 += gameTime;
			Platform::x2 -= gameTime;
			// If the platform has scaled beyond 2.5, it will be scaled out
			if (Platform::x1 >= 2.5f)
				scaleOut = true;
		}
	}
}

void Scale::Render()
{
	Platform::Render();
}

Scale::~Scale()
{
}
