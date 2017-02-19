#include "NPC.h"
#include "GameWorld.h"
#include <GL\glut.h>
#include <SOIL.h>


NPC::NPC(float xStart, float yStart, GLuint npcTex)
{
	x = xStart;
	y = yStart;
	tempX = xStart;
	texture = npcTex;
	glBindTexture(GL_TEXTURE_2D, texture);
}
#pragma region Prop
float NPC::GetX()
{
	return x;
}
float NPC::SetX(float newX)
{
	x += newX;
	return x;
}
#pragma endregion Properties
void NPC::DefauldPos()
{
	x = tempX;
}
void NPC::Render()
{
	glPushMatrix();
	glTranslatef(x, y, 0);
	// Enables blend
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Ensures that the blend removes transparant background
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, -0.3f, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.1f, -0.3f, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.1f, 0.6f, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, 0.6f, 0);
	glEnd();
	// Disables blend
	glDisable(GL_BLEND);
	glPopMatrix();
}
NPC::~NPC()
{
}