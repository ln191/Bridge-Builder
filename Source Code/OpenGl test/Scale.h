#pragma once
#include "Platform.h"
class Scale :
	public Platform
{
private:
	// Float
	float x1, x2, y1, y2;
	// Bool
	bool scaleOut;
public:
	// Constructor
	Scale(float x1, float x2, float y1, float y2);
	~Scale();
	// Void
	void Render() override;
	void Update(float gameTime);
};

