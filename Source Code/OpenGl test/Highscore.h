#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
//bibliotek til at kune skrive og læse til en fil 
#include <fstream>
#include <vector>
#include <iterator>
#include "Score.h"

class Score;
using namespace  std;
class Highscore
{
private:
	// Int
	unsigned int highscoreCount;
	// vector
	vector<Score> highscore;
public:
	// Int
	int GetMaxNrOfHighscore();
	// Bool
	bool scoreCompere(Score * s1, Score * s2);
	// Vector
	vector<Score> GetHighscoreList();
	// Constructor
	Highscore(unsigned int highscoreCount);
	~Highscore();
	// Void
	void AddNewHighscore(Score & newScore);
	void writeToFile();
	void ReadHighscoreFile();




};

