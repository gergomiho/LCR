#include <iostream>
#include <list>
#include <vector>
#include <map>
#include "Output.h"
using namespace std;

#ifndef GAME_H_
#define GAME_H_

#define TEST_MODE

class Game {
#ifdef TEST_MODE
public:
#else
private:
#endif
	IOutput* output;
	vector<string> players;

	list<string> popQuestions;
	list<string> scienceQuestions;
	list<string> sportsQuestions;
	list<string> rockQuestions;

	map<string, list<string>> questionCatMap = {	{ "Pop", popQuestions },
													{ "Science", scienceQuestions },
													{ "Sports", sportsQuestions },
													{ "Rock", rockQuestions },};
	

	int places[6] = {};
	int purses[6] = {};
	bool inPenaltyBox[6];

	int currentPlayer = 0;
	bool isGettingOutOfPenaltyBox;

	void askQuestion();
	string currentCategory();

	bool didPlayerNotWin();

public:
	Game(IOutput* output);
	const int mapSize = 12;
	const int pointsToWin = 6;
	const int reqPlayerAmount = 2;
	bool isPlayable();
	bool add(string playerName);

	void setupPlayerDefaults(int playerNumber);

	int howManyPlayers();
	void roll(int roll);

	void displayRoundStart(int rolledDice);

	void playInPenalty(int rolledDice);

	void play(int rolledDice);

	void keepPenalty();

	void breakPenaltyAndPlay(int rolledDice);

	void displayPenaltyStatus();

	void movePlayer(int rolledDice);

	bool playerReachesMapEnd();

	bool isOdd(int roll);

	bool correctAnswer();
	bool correctAnswerInPenalty();
	bool correctAnswerNoPenalty();
	void giveCoinCurrentPlayer();
	bool correctAnswerRemainPenalty();
	bool correctAnswerBreakPenalty();
	void advancePlayer();
	bool wrongAnswer();

	bool playerOutOfBound();

	bool TestMode = false;
};

#endif /* GAME_H_ */