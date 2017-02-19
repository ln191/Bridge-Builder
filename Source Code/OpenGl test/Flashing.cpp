#include "Flashing.h"


Flashing::Flashing(float X1, float X2, float Y1, float Y2) : Platform(X1, X2, Y1, Y2)
{
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y2 = Y2;
	timer = clock();
}
void Flashing::Update()
{
	// Checks if the player is active, and is currrently raising bridge
	if (active)
		// Checks if the object is rendered and that 0.5seconds has passed
		if (bRender && ((clock() - timer) / CLOCKS_PER_SEC) >= .5f)
		{
			// Resets timer
			timer = clock();
			bRender = false;
		}
		// Checks if the object is not rendered and that 0.5seconds has passed
		else if (!bRender && ((clock() - timer) / CLOCKS_PER_SEC) >= .5f)
		{
			// Resets timer
			timer = clock();
			bRender = true;
		}
}
bool Flashing::GetBRender(){
	return bRender;
}
void Flashing::Render()
{
	//Checks whether the object should be rendered or not
	if (bRender)
		Platform::Render();
}

Flashing::~Flashing()
{
}
