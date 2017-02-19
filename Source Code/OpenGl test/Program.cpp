//is only using this in debug mode
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
#include <GL/freeglut.h>
#include <SOIL.h>
#include "GameWorld.h"
#include "Player.h"
#include <iostream>
#include "Platform.h"
#include <ctime>
#include "include\irrKlang.h"
#pragma comment(lib, "irrKlang.lib")

using namespace std;
using namespace irrklang;
// Field
bool clockOn = false;
bool bridgeFall = false;
bool hsIsDisplayed = false;
double duration;
// Class
GameWorld * world;
ISoundEngine * se;
clock_t start;

// Method
void InitOpenGL()
{
	glShadeModel(GL_SMOOTH); //Enable smooth shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); //Set clear color
	glClearDepth(1.0f); // Set clearing depth for depth buffer
	glEnable(GL_DEPTH_TEST); //Enable depth testing
	glDepthFunc(GL_LEQUAL); //Set depth buffer testing to less then or equal

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Specifies how colors/textures are interpolized on surfaces
}
void Reshape(int width, int height)
{
	if (height == 0){ height = 1; } //Make sure no divide by zero can happen 
	glViewport(0, 0, width, height);//Reset the current viewport

	glMatrixMode(GL_PROJECTION); //Specify projection matrix stack
	glLoadIdentity(); //Reset projection matrix stack - top matrix

	gluPerspective(45.0f, width / height, 0.0f, 100.0f); //Set perspective to match current display size

	glMatrixMode(GL_MODELVIEW); //Specify model view matrix
	glLoadIdentity(); //reset model view matrix - top matrix

}
void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: //ESC
		exit(0);
		break;
	// Ensures that when k is pressed and bridgefall is not in progress, that the bridge is being raised.
	case 32://Space 
		// The clockOn bool starts the Timer method, which is then updated continously
		if (!clockOn && !bridgeFall && !world->GetEnd())
		{
			// Clock starts to calculate size of bridge, depending on how long the key is held down
			start = clock();
			clockOn = true;
			// Ensures that the platforms stops their functionality
			world->objects[1]->SetActive(false);
		}
		world->SetStartUp(false);
		break;
	case 9: //TAB     
		// Doesnt Display Highscore
		if (hsIsDisplayed)
		{
			hsIsDisplayed = false;
			world->SetRenderHighscore(false);
		}
		else
		// Displays highscore
		{
			hsIsDisplayed = true;
			world->SetRenderHighscore(true);
		}
		break;
	case 'r':
	case 'R':
		// If game has ended, the game is restarted
		if (world->GetEnd())
			world->SetRestart(true);
		break;
	case 'T':
	case 't':
		// Enables the user to write name onto highscore list
		if (world->GetEnd())
		{
			world->ReadKeyboardText();
			world->SetHasWriteName(true);
			world->SetRestart(true);
		}
	default:
		break;
	}

}
void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 32: // When key is released, clock is restarted to use for timed bridgefall
		if (clockOn)
		{
			// Clock starts to calculate speed of fall of bridge to ensure that it can be timed. 
			clockOn = false;
			// bridgeFall decides that the falling bridge event should start
			bridgeFall = true;
			start = clock();
		}
		break;
	default:
		break;
	}
}
void Timer()
{
	// If the timer running and it is not being used for bridgefall, the time is being calculated
	if (clockOn && !bridgeFall)
	{
		duration = (clock() - start) / 10;
		// Runs the players raisebridge method
		world->player->RaiseBridge(duration);
	}
	// If the bridgefall bool is true, then time is calculated so that its falltime can be specified
	if (bridgeFall && !clockOn)
	{
		duration = (clock() - start) / 10;
		// Runs the players bridgefall method
		world->player->FallBridge(duration);
		// When the angle reaches -90, the bridgefall event is over, NPCs are moved
		if (world->player->bridgeAngle <= -90)
		{
			bridgeFall = false;
			se->play2D("explosion.wav");
			world->SetEngageMovement(true);
			world->SetBridgeRaised(true);
		}
	}
}
void GameLoop()
{
	// Gameloop
	world->Render();
	world->Update();
	Timer();
}
void SetupSound()
{
	// Setup sound through the IrrKlang library
	se = createIrrKlangDevice();
	se->play2D("Kalimba.mp3", true);
	se->setSoundVolume(0.2f);
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);//Init GLUT
	glutInitDisplayMode(GLUT_DOUBLE); //Initialize glut display mode with rgb and alpha colors and Depth
	glutInitWindowSize(1024, 768); //Set window size
	glutInitWindowPosition(0, 0); //Set window position

	glutCreateWindow("Friendzone Bridge Builder"); //Create GLUT OpenGL Window

	InitOpenGL();
	SetupSound();
	glutReshapeFunc(&Reshape);
	glutDisplayFunc(&GameLoop);
	glutKeyboardFunc(&Keyboard);
	glutKeyboardUpFunc(&KeyboardUp);
	world = new GameWorld();
	world->UpdateHighScore();
	glutMainLoop();
}