#pragma once
#include "Platform.h"
#include <iostream>

class Moving :
	public Platform
{
private:
	// Float
	float x1, x2, y1, y2, sizing;
	// Bool
	bool left, collision;
public:
	// Constructor
	Moving(float x1, float x2, float y1, float y2);
	~Moving();
	// Void
	void Render() override;
	void Update(float gameTime);
};

