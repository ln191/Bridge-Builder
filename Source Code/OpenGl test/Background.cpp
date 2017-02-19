#include "Background.h"


Background::Background(GLuint texture, float X1, float X2, float Y1, float Y2)
{
	tex = texture;
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;
}

void Background::Render()
{
	glPushMatrix(); //This background is ensured to only use this matrix
	glBindTexture(GL_TEXTURE_2D, tex); //Binds texture
	glBegin(GL_QUADS);
	// Front Face
	glColor3f(1, 1, 1);
	// Left top
	glVertex2d(x1, y1);
	glTexCoord2f(1.0f, 1.0f);
	// Right top
	glVertex2d(x2, y1);
	glTexCoord2f(1.0f, 0.0f);
	// Right Bottom
	glVertex2d(x2, y2);
	glTexCoord2f(0.0f, 0.0f);
	// Left bottom
	glVertex2d(x1, y2);
	glTexCoord2f(0.0f, 1.0f);

	glEnd();

	glPopMatrix(); //This background is ensured to only use this matrix
}

Background::~Background()
{
}
