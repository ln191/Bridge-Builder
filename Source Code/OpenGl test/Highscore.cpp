#include "Highscore.h"

// The constructer wants the number of highscore we want in the txt file and a refence to a highscore list
Highscore::Highscore(unsigned int nrOfScore)
{
	highscoreCount = nrOfScore;
}

Highscore::~Highscore()
{
}
vector<Score> Highscore::GetHighscoreList()
{
	return highscore;
}
int Highscore::GetMaxNrOfHighscore()
{
	return highscoreCount;
}
// This mehtod defince what shall be compered of values in the score object
// It takes int 2 pointers and comperes them
bool Highscore::scoreCompere(Score * s1, Score * s2)
{
	// If the to scores is not equal
	if (s1->getScore() != s2->getScore())
	{
		// Return true or false depending on if the first score is higher than the second or not
		return s1->getScore() > s2->getScore();
	}
	// If the 2 scores is equal then it sort it after the name 
	return s1->getName() < s2->getName();
}
	// Writes to a txt file
void Highscore::writeToFile()
{
	// Makes a output stream
	ofstream myFile;
	// Opens the file i want to write the highscore to
	myFile.open("HighScoreList.txt");
	// Check to see if the file has been opened
	if (myFile.is_open())
	{
		// We only want the top 10 highscores in our txt file
		// So we checks and see if the highscore list contains 10 our less scores
		// If so it will loop the whole list through 
		if (highscore.size() <= highscoreCount)
		{
			// Loops the highscore list for scores
			for (Score var : highscore)
			{
				// Write the name and score to the txt file
				myFile << var.getName() << "\t" << var.getScore() << "\n";
			}
		}
		// If it contains more than 10 scores the it will only loop through the ten first in the list
		// It will be the top 10 highscores because we sorted the highscore list before calling this methode
		else
		{
			vector<Score>::iterator it;// Makes an iterator
			for (it = highscore.begin(); it < highscore.begin() + 10; it++)
			{
				// Write the name and score to the txt file
				myFile << it->getName() << "\t" << it->getScore() << "\n";
			}
		}


		// Closes the file again 
		myFile.close();
	}
	// If the file wasn´t opened it will print this message to the console window
	else
	{
		cout << "Uable to open file";
	}

}
// Reads data form a txt file
void Highscore::ReadHighscoreFile()
{
	// Make an Input stream 
	ifstream myfile;
	string line;
	string name;
	int score;
	// Open the txt file
	myfile.open("HighScoreList.txt");
	// Checks if the txt file is open
	if (myfile.is_open())
	{
		// Loops through all the lines in the txt file
		while (getline(myfile, line))
		{
			// Makes a string stream
			// The string stream reads a line and can seperate the data by look after the whitespace in the line
			// We have a name and a score on each line so we seperate the values and give them each their on attribute
			// The string stream have the ability to parse a string to an int value. So when it see a seperate number it automaticly parse it to a int value 
			// Be aware that if the number starts with 0, then 0 will not be in the atribute so, 0990 will be 990    
			stringstream lineStream(line);
			if (lineStream >> name >> score)
			{
				// Take the to attributes and make a new score and adds it to the highscore list
				highscore.push_back(Score(score, name));
			}
		}
		// Closes the txt file
		myfile.close();
		cout << "Highscore has been read";
	}
	else
	{
		cout << "Uable to open file";

	}
}
// This mehtod takes in a refence of a score and adds it to the highscore
void Highscore::AddNewHighscore(Score& newScore)
{
	// Adds the new score to the highscore
	highscore.push_back(newScore);
	// Sort the highscore list 			this is a lamda expression to get the scoreCompere because the sort algrithm is in C code and they don´t understand classes   
	std::sort(highscore.begin(), highscore.end(), [this](Score & a, Score& b) { return scoreCompere(&a, &b); });
	// Write the highscore to the txt file
	writeToFile();
	cout << "Score Added";
}