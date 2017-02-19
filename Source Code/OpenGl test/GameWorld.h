#include "Player.h"
#include "NPC.h"
#include <ctime>
#include <vector>
using namespace std;
class Highscore;
class Platform;

class GameWorld
{
private:
	// Bools
	bool renderHighscore;
	bool renderName;
	bool isFlashing = false;
	bool isMoving = false;
	bool isScaling = false;
	bool end = false;
	bool restart = false;
	bool npcMoving = false;
	bool nameIsWriten;
	bool check;
	bool fCheck = true;
	bool startUp = true;
	bool writeName = false;
	// Ints
	int scoreCount;
	int oldTimeSinceStart;
	// Strings
	string playerName;
	// Classes
	Highscore * highScore;
	NPC * hero;
	// Bools
	bool engageMovement = false;
	bool bridgeRaised = false;
public:
	// Classes
	Player * player;
	// Vectors
	// We have chosen this container, as it is a dynamic container, where each element is easy to access and relatively fast.
	// We did not desire any null values, and we needed to access specific locations in the array.
	std::vector<Platform*> objects;
	// Constructor / De-structor
	GameWorld();
	~GameWorld();
	// Property Set
	bool SetEngageMovement(bool state);
	bool SetBridgeRaised(bool state);
	bool SetRestart(bool state);
	bool SetHasWriteName(bool hasWriteName);
	bool SetCheck(bool Check);
	bool SetStartUp(bool start);
	bool SetWiteName(bool state);
	// Property Get
	bool GetEngageMovement();
	bool GetBridgeRaised();
	bool GetEnd();
	// Voids
	void Movement(float gametime);
	void CreatePlatforms();
	void Update();
	void Render();
	void UpdateHighScore();
	void DisplayTextOnScreen(float xPos, float yPos, int r, int g, int b, const string string);
	void PrintHighscoreToScreen(float xpos, float ypos);
	void SetRenderHighscore(bool render);
	void SetRenderWriteName(bool render);
	void DisplayNewScore();
	void LostSaveScore();
	void ReadKeyboardText();
	void PlusScore(int* score);
	void ResetScore(int* score);
};

