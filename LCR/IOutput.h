#pragma once
#include <list>
#include <map>
#include <iostream>

using namespace std;

class IOutput {
public:
	list<string> popQuestions;
	list<string> scienceQuestions;
	list<string> sportsQuestions;
	list<string> rockQuestions;

	map<string, list<string>> questionCatMap = {	{ "Pop", popQuestions },
													{ "Science", scienceQuestions },
													{ "Sports", sportsQuestions },
													{ "Rock", rockQuestions }, };

	virtual void displayRoundStart(int rolledDice, string currentPlayer) {};
	virtual void displayPlayerName(string currentPlayer) {};
	virtual void displayRolledNumber(int rolledDice) {};
	virtual void displayCurrentCategory(string currentCategory) {};
	virtual void displayPlayersPosition(string currentPlayer, int currentPlayerPosition) {};
	virtual void displayPlayerBreakPenalty(string currentPlayer) {};
	virtual void displayPlayerStayPenalty(string currentPlayer) {};
	virtual void displayCategory(string currentCategory) {};
	virtual void displayAnswerCorrect() {};
	virtual void displayAnswerCorrent() {};
	virtual void displayAnswerIncorrect() {};
	virtual void displayGoldCoin(string currentPlayer, int goldCoin) {};
	virtual void displayPlayerSentPenalty(string currentPlayer) {};
	virtual void displayPlayerAdded(string currentPlayer) {};
	virtual void displayPlayerCount(int playerCount) {};
};