#pragma once
#include <GL\glut.h>

class NPC
{
private:
	// Other
	GLuint texture;
	// Float
	float x;
	float tempX;
	float y;
public:
	// Constructor
	NPC(float x, float y, GLuint texture);
	~NPC();
	// Float
	float GetX();
	float SetX(float newX);
	// Void
	void DefauldPos();
	void Render();


};

