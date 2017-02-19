#include "Score.h"


Score::Score(int newScore, string Name)
{
	score = newScore;
	name = Name;
}


Score::~Score()
{
}
int Score::getScore()
{
	return score;
}
string Score::getName()
{
	return name;
}