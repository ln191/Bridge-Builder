#pragma once
#include <GL\glut.h>

class Player
{
private:
	// Attributes
	GLuint texture;
	float x, y;
public:
	// Attribues
	double bridgeHeight;
	float x1 = -.2f, x2 = -0;
	double bridgeAngle;
	// Constructors
	Player(double bHeight, double bAngle);
	~Player();
	// Voids
	void RaiseBridge(double duration);
	void FallBridge(double duration);
	void Render();
	void SetAngle(double angle);
};

