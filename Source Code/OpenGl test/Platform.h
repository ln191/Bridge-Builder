#pragma once

class Platform
{
protected:
	// Float
	float x1;
	float x2;
	float y1;
	float y2; 
	bool active = true;
public:
	// Constructor
	Platform(float x1, float x2, float y1, float y2);
	~Platform();
	// Prop
	float GetX1();
	float GetX2();
	bool GetActive();
	bool SetActive(bool state);
	// Void
	virtual void Render();

};

