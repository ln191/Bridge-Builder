#include "Player.h"
#include <GL\glut.h>

Player::Player(double bHeight, double bAngle)
{
	bridgeHeight = bHeight;
	bridgeAngle = bAngle;
}

#pragma region Prop
void Player::SetAngle(double angle)
{
	bridgeAngle = angle;
}
#pragma endregion Prop
void Player::RaiseBridge(double duration)
{
	// Calculates bridgeheight
	bridgeHeight = (0.01f*duration) + 0.1;
}
void Player::FallBridge(double duration)
{
	// Calculates speed of bridgefall
	bridgeAngle = -1.0f*duration;
}
void Player::Render()
{
	glPushMatrix();
	// Ensures that the object is rotated
	glRotatef(bridgeAngle, 0.0f, 0, 0.0001f);
	glBegin(GL_QUADS);
	// Front Face
	glColor3f(0.1f, 0.1f, 0);
	glVertex3f(0, 0, 0.0f);
	glVertex3f(-.2f, 0, 0.0f);
	glVertex3f(x1, bridgeHeight, 0.0f);
	glVertex3f(x2, bridgeHeight, 0.0f);
	glEnd();

	glPopMatrix();
}

Player::~Player()
{
}