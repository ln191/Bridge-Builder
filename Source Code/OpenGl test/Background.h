#pragma once
#include <GL/glut.h>

class Background
{
private:
	// Attributes
	GLuint tex;
	float x1, x2, y1, y2;
public:
	// Constructors
	Background(GLuint texture, float x1, float x2, float y1, float y2);
	~Background();
	// Voids
	void Render();
};

