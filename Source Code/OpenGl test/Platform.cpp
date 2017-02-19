#include "Platform.h"
#include <GL/glut.h>

Platform::Platform(float X1, float X2, float Y1, float Y2)
{
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;
	active = true;
}

#pragma region Prop
float Platform::GetX1()
{
	return x1;
}
float Platform::GetX2()
{
	return x2;
}
bool Platform::GetActive()
{
	return active;
}
bool Platform::SetActive(bool state)
{
	active = state;
	return active;
}
#pragma endregion Prop

void Platform::Render()
{
	glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	// Left top
	glVertex2d(x1, y1);
	// Right top
	glVertex2d(x2, y1);
	// Right Bottom
	glVertex2d(x2, y2);
	// Left bottom
	glVertex2d(x1, y2);
	glEnd();
	glFlush();
}
Platform::~Platform()
{
}
