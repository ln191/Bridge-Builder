#include "Moving.h"
#include <GL/glut.h>

Moving::Moving(float X1, float X2, float Y1, float Y2)
	: Platform(X1, X2, Y1, Y2)
{
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;
	left = true;
}
void Moving::Render()
{
	Platform::Render();
}

void Moving::Update(float gameTime)
{
	// If the object is active
	if (active)
		// If the object needs to move to the left
		if (left == true)
		{
			// Gametime is subtracted from the position
			Platform::x1 -= gameTime;
			Platform::x2 -= gameTime;
			// If the x values are lower than 1, it is moved in the other direction
			if (Platform::x1 <= 1)
			{
				left = false;
			}
		}
		// If the object needs to move to the left
		else if (left == false)
		{
			// Gametime is added to the position
			Platform::x1 += gameTime;
			Platform::x2 += gameTime;
			// If the x values are higher than 4, it is moved in the other direction
			if (Platform::x1 >= 4)
			{
				left = true;
			}
		}
}


Moving::~Moving()
{

}
