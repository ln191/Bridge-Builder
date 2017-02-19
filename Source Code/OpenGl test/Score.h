#pragma once
#include <string>
using namespace std;

class Score
{
private:
	// Attributes
	unsigned int score;
	string name;
public:
	// Constructor
	Score(int score, string name);
	~Score();
	// Properties
	int getScore();
	string getName();

};

