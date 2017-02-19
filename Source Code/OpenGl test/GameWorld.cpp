// Custom .h
#include "GameWorld.h"
#include "Player.h"
#include "Platform.h"
#include "Scale.h"
#include "Moving.h"
#include "Flashing.h"
#include "Highscore.h"
#include "Background.h"
// default .h
#include <SOIL.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

// Class
// We are using pointers to create instances of the classes, ensuring that they are not copied and that we can access them
// Also to ensure that we get access of the actual methods, and that we manipulate the actual object that we desire
Highscore * highScore;
Background *bg;
Platform *p;
Flashing *nF;
Moving *nM;
Scale *nS;

// Methods
GameWorld::GameWorld()
{
	glEnable(GL_TEXTURE_2D); //Enablees textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Ensures how textures are placed
	// Classes
	p = new Platform(0, -1, 0, -1);
	bg = new Background(SOIL_load_OGL_texture(".\\original.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y), -6, 9, 10, -4.5f);
	hero = new NPC(-0.5f, .3f, SOIL_load_OGL_texture(".\\protaganist.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y));
	player = new Player(0.1f, 0.0f);
	highScore = new Highscore(10);
	// Adds the first platform to the list
	objects.push_back(p);
	// Creates the second platform
	CreatePlatforms();
	oldTimeSinceStart = 0;
	renderHighscore = false;
	renderName = false;
	nameIsWriten = true;
	check = false;
	scoreCount = 0;
}
#pragma region Property
// Get
bool GameWorld::GetBridgeRaised()
{
	return bridgeRaised;
}
bool GameWorld::GetEngageMovement()
{
	return engageMovement;
}
bool GameWorld::GetEnd()
{
	return end;
}

// Set
bool GameWorld::SetBridgeRaised(bool state)
{
	bridgeRaised = state;
	return bridgeRaised;
}
bool GameWorld::SetStartUp(bool start)
{
	startUp = start;
	return startUp;
}
bool GameWorld::SetEngageMovement(bool state)
{
	engageMovement = state;
	return engageMovement;
}
bool GameWorld::SetRestart(bool state)
{
	restart = state;
	return restart;
}
bool GameWorld::SetHasWriteName(bool hasWriteName)
{
	nameIsWriten = hasWriteName;
	return nameIsWriten;

}
bool GameWorld::SetCheck(bool Check)
{
	check = Check;
	return check;

}

bool GameWorld::SetWiteName(bool state){
	writeName = state;
	return writeName;
}
#pragma endregion Property
#pragma region Highscore
// Highscore
void GameWorld::PlusScore(int* score)
{
	*score += 1;
}
void GameWorld::ResetScore(int* score)
{
	*score = 0;
}

void GameWorld::SetRenderHighscore(bool render)
{
	renderHighscore = render;
}
void GameWorld::SetRenderWriteName(bool render)
{
	renderHighscore = render;
}
//Reads the input from console window and sets it as player name 
void GameWorld::ReadKeyboardText()
{
	cout << "Wrtie name here: " << "\t";
	cin >> playerName;
	//Adds the new score to the highscore list
	highScore->AddNewHighscore(Score(scoreCount, playerName));
}
//This method is ran when the player has lost
void GameWorld::LostSaveScore()
{
	//Then the program will wait for the player to write a name in the console window 
	ReadKeyboardText();

}
//Displays text on screen
void GameWorld::DisplayTextOnScreen(float xPos, float yPos, int r, int g, int b, string str)
{
	//Creates an array that will contain the char from a string, you want to display on the screen 
	char myCharArray[100];
	//Copy the the string into the char array and gives the size of the string
	size_t length = str.copy(myCharArray, str.size(), 0);
	//A null character ('\0') has been added in order to indicate the end of the sequence.
	myCharArray[length] = '\0';
	//Set the coler of the text
	glColor3f(r, g, b);
	//Set the position of the text
	glRasterPos2f(xPos, yPos);
	//Set j to be equal to the length of the array
	int j = strlen(myCharArray);
	//Loop through the array
	for (int i = 0; i < j; i++) {
		//Print the char to the screen in times roman font size 24
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, myCharArray[i]);
	}

}
//Display the your score and tell you to right your name
void GameWorld::DisplayNewScore()
{
	DisplayTextOnScreen(1, 8, 1, 0, 0, "The END ");
	DisplayTextOnScreen(-1, 5, 1, 0, 0, "Your Score:");
	DisplayTextOnScreen(1, 3.5, 1, 0, 0, "Press R to restart");
	DisplayTextOnScreen(1, 4, 1, 0, 0, "Press T to enter Highscore in console window");
	//Convert int to string
	stringstream ss;
	ss << scoreCount;
	string str = ss.str();
	//Display players score
	DisplayTextOnScreen(0.2, 5, 1, 0, 0, str);
}
//Print the highscore to the screen
void GameWorld::PrintHighscoreToScreen(float xpos, float ypos)
{

	//Checks to see if vector list contain less or equal to our set max size value
	if (highScore->GetHighscoreList().size() <= highScore->GetMaxNrOfHighscore())
	{
		//Loops through all the score in the vector list
		for (Score var : highScore->GetHighscoreList())
		{

			int a = var.getScore();
			stringstream ss;
			ss << a;
			string str = ss.str();
			DisplayTextOnScreen(xpos, ypos, 1, 0, 0, var.getName() + ": " + str);

			ypos -= .3;
		}
	}
	//If more it will only loop through the max size value
	else
	{
		//An iterator is actually a pointer ( address) to where in memory the data lies
		vector<Score>::iterator it;//Makes an iterator
		vector<Score> list = highScore->GetHighscoreList();
		for (it = list.begin(); it < list.begin() + highScore->GetMaxNrOfHighscore(); it++)
		{
			int a = it->getScore();
			stringstream ss;
			ss << a;
			string str = ss.str();
			DisplayTextOnScreen(xpos, ypos, 1, 0, 0, it->getName() + ": " + str);

			ypos -= .3;
		}
	}

}
void GameWorld::UpdateHighScore()
{
	//Get The highscores from the highscore txt and adds them to our highscoreList
	highScore->ReadHighscoreFile();
}
// Highscore END
#pragma endregion Highscore

void GameWorld::CreatePlatforms()
{
	// Resets the time for randoms
	srand((time(NULL)));
	// Random int for selecting platform
	int rnd = rand() % 4 + 1;
	// Calculates a random float
	float low = 2, high = 3;
	float rndX1 = low + (rand() / (RAND_MAX / (high - low)));
	// Calculates a random float
	float low2 = 3, high2 = 4;
	float rndX2 = low2 + (rand() / (RAND_MAX / (high2 - low2)));
	// Creates Normal Platform
	if (rnd == 1)
	{
		Platform *nP = new Platform(rndX1, rndX2, 0, -1);
		objects.push_back(nP);
	}
	//Creates Scaling Platform
	else if (rnd == 2)
	{
		nS = new Scale(2, 3, 0, -1);
		objects.push_back(nS);
	}
	//Creates Moving Platform
	else if (rnd == 3)
	{
		nM = new Moving(rndX1, rndX2, 0, -1);
		objects.push_back(nM);
	}
	// Creates Flashing Platform
	else if (rnd == 4)
	{
		nF = new Flashing(rndX1, rndX2, 0, -1);
		objects.push_back(nF);
	}
}

void GameWorld::Update()
{
	// Calculates Gameprogress
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	float deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	//Moves the NPC character and other functionality there
	Movement(deltaTime / 1000);
	// Updates platforms, regarding which type it is.
	if (isFlashing)
		nF->Update();
	if (isMoving)
		nM->Update((deltaTime / 1000) * 3);
	if (isScaling)
		nS->Update((deltaTime / 1000) * 3);
	// Checks if bridge is raised
	if (bridgeRaised)
	{
		// Checks if the bridgeheight is between the two x values of the platform to check if it reaches or not		
		if (player->bridgeHeight >= objects[1]->GetX1() && player->bridgeHeight <= objects[1]->GetX2())
		{
			// Ensures bridgee is reset, score is added
			bridgeRaised = false;
			PlusScore(&scoreCount);
		}
		else
		{
			// If the bridge is not long enough, the game is ended, bridge reset and to render the endtext
			renderName = true;
			end = true;
			bridgeRaised = false;
		}
	}
	// Reset cannot be done before game has ended
	if (restart && end && !npcMoving)
	{
		// Resets everything and creates a new platform
		ResetScore(&scoreCount);
		end = false;
		restart = false;
		check = false;
		playerName = "";
		objects.erase(objects.begin() + 1);
		CreatePlatforms();
	}
}
void GameWorld::Movement(float gameTime)
{
	// Tell if the NPC should move or not
	if (engageMovement)
	{
		// If the x position of the NPC is less than bridgeheight, it is moved.
		if (hero->GetX() <= (player->bridgeHeight))
		{
			//Moves NPC
			hero->SetX(2 * gameTime);
			npcMoving = true;
		}
		else
		// If the Npc is already at the end of the bridge, the information is reset, objects deleted and a new platform created
		{
			isFlashing = false;
			delete nF;
			nF = nullptr;
			engageMovement = false;
			player->bridgeHeight = 0;
			// Adds a bit of delay to give player time to see whats going on
			Sleep(100);
			objects.erase(objects.begin() + 1);
			CreatePlatforms();


		}
	}
	// If movement is false, then NPC and bridge are reset
	else if (!engageMovement)
	{
		player->bridgeAngle = 0;
		hero->DefauldPos();
		npcMoving = false;
	}
}

void GameWorld::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffer
	glLoadIdentity(); //Loads identity matrix and the player view
	glTranslatef(-1.5f, -3.5f, -12.0f);
	bg->Render();
	// If the game has just started instructions are displayed.
	if (startUp)
	{
		DisplayTextOnScreen(1, 3, 1, 0, 0, "Hold SPACE to raise bridge.");
		DisplayTextOnScreen(1, 4, 1, 0, 0, "Press TAB to view highscore.");

	}

	// Renders
	player->Render();
	hero->Render();
	// Renders and checks which type the platform is, so that the functionality is run
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
		if (dynamic_cast<Flashing*>(nF))
		{
			isFlashing = true;
		}
		if (dynamic_cast<Moving*>(nM))
		{
			isMoving = true;
		}
		if (dynamic_cast<Scale*>(nS))
		{
			isScaling = true;
		}
	}
	//if the render Highscore is true it will print highscore list to screen 
	if (renderHighscore)
	{
		PrintHighscoreToScreen(-3, 8);

	}
	// If the game has ended, scores are displayed
	if (end)
	{
		if (renderName)
		{
			DisplayNewScore();
		}
	}
	
	// Buffers are swaepped and it is redisplayed
	glutSwapBuffers();
	glutPostRedisplay();
}
GameWorld::~GameWorld()
{
	// Garbage Collections
	for (size_t i = 0; i < objects.size(); i++)
	{
		delete objects[i];
		objects[i] = nullptr;
	}
	delete player;
	delete highScore;
	delete bg;
	delete p;
	delete nF;
	delete nM;
	delete nS;
	player = nullptr;
	highScore = nullptr;
	bg = nullptr;
	p = nullptr;
	nF = nullptr;
	nM = nullptr;
	nS = nullptr;
}