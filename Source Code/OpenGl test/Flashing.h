#pragma once
#include "Platform.h"
#include <ctime>
#include <GL/glut.h>
#include <iostream>

class Flashing :
	public Platform
{
private:
	// Bool
	bool bRender = true;
	// Other
	clock_t timer;
public:
	// Float
	float x1, x2, y1, y2;
	// Property
	bool GetBRender();
	// Constructor
	Flashing(float x1, float x2, float y1, float y2);
	~Flashing();
	// Void
	void Update();
	void Render() override;
};

