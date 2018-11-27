#pragma once
#include <iostream>
#include "IOutput.h"

class Output : public IOutput {
public:
	Output();
	~Output();
	virtual void displayRoundStart(int rolledDice, int currentPlayer);
	virtual void displayPlayerName(string currentPlayer);
	virtual void displayRolledNumber(int rolledDice);
	virtual void displayCurrentCategory(string currentCategory);
	virtual void displayPlayersPosition(string currentPlayer, int currentPlayerPosition);
	virtual void displayPlayerBreakPenalty(string currentPlayer);
	virtual void displayPlayerStayPenalty(string currentPlayer);
	virtual void displayCategory(string currentCategory);
	virtual void displayAnswerCorrect();
	virtual void displayAnswerCorrent();
	virtual void displayAnswerIncorrect();
	virtual void displayGoldCoin(string currentPlayer, int goldCoin);
	virtual void displayPlayerSentPenalty(string currentPlayer);
	virtual void displayPlayerAdded(string currentPlayer);
	virtual void displayPlayerCount(int playerCount);
};