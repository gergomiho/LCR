#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

Game::Game(IOutput* output) {
	this->output = output;
	int questionPerCatgeory = 50;

	for (int i = 0; i < questionPerCatgeory; i++)
	{
		ostringstream popQ(ostringstream::out);
		popQ << "Pop Question " << i;
		output->questionCatMap["Pop"].push_back(popQ.str());

		ostringstream scienceQ(ostringstream::out);
		scienceQ << "Science Question " << i;
		output->questionCatMap["Science"].push_back(scienceQ.str());

		ostringstream sportsQ(ostringstream::out);
		sportsQ << "Sports Question " << i;
		output->questionCatMap["Sports"].push_back(sportsQ.str());

		ostringstream rockQ(ostringstream::out);
		rockQ << "Rock Question " << i;
		output->questionCatMap["Rock"].push_back(rockQ.str());
	}
}

bool Game::isPlayable() {
	return (howManyPlayers() >= reqPlayerAmount);
}

bool Game::add(string playerName) {
	players.push_back(playerName);
	setupPlayerDefaults(howManyPlayers());

	output->displayPlayerAdded(playerName);
	output->displayPlayerCount(players.size());
	return true;
}

void Game::setupPlayerDefaults(int playerNumber) {
	places[playerNumber] = 0;
	purses[playerNumber] = 0;
	inPenaltyBox[playerNumber] = false;
}

int Game::howManyPlayers() {
	return players.size();
}

void Game::roll(int rolledDice) {
	displayRoundStart(rolledDice);
	if (inPenaltyBox[currentPlayer]) 
		playInPenalty(rolledDice);
	else
		play(rolledDice);
}
void Game::displayRoundStart(int rolledDice) {
	output->displayPlayerName(players[currentPlayer]);
	output->displayRolledNumber(rolledDice);
}
void Game::play(int rolledDice) {
	movePlayer(rolledDice);
	output->displayPlayersPosition(players[currentPlayer], places[currentPlayer]);
	output->displayCurrentCategory(currentCategory());
	askQuestion();
}
void Game::playInPenalty(int rolledDice) {
	if (isOdd(rolledDice))
		breakPenaltyAndPlay(rolledDice);
	else
		keepPenalty();
}
void Game::breakPenaltyAndPlay(int rolledDice) {
	isGettingOutOfPenaltyBox = true;
	displayPenaltyStatus();
	play(rolledDice);
}
void Game::keepPenalty() {
	isGettingOutOfPenaltyBox = false;
	displayPenaltyStatus();
}
void Game::displayPenaltyStatus() {
	if (isGettingOutOfPenaltyBox)
		output->displayPlayerBreakPenalty(players[currentPlayer]);
	else
		output->displayPlayerStayPenalty(players[currentPlayer]);
}
void Game::movePlayer(int rolledDice) {
	places[currentPlayer] = places[currentPlayer] + rolledDice;
	if (playerReachesMapEnd())
		places[currentPlayer] = places[currentPlayer] - mapSize;
}



bool Game::playerReachesMapEnd() {
	return places[currentPlayer] + 1 > mapSize;
}

bool Game::isOdd(int roll) {
	return roll % 2 != 0;
}

void Game::askQuestion() {
	string currentCat = currentCategory();
	output->displayCategory(currentCat);
	output->questionCatMap[currentCat].pop_front();
}


string Game::currentCategory() {
	string popCat = "Pop";
	string scienceCat = "Science";
	string sportsCat = "Sports";
	string rockCat = "Rock";

	if (places[currentPlayer] % 4 == 0)
		return popCat;
	else if (places[currentPlayer] % 4 == 1)
		return scienceCat;
	else if (places[currentPlayer] % 4 == 2)
		return sportsCat;
	else
		return rockCat;
}

bool Game::correctAnswer()
{
#ifdef TEST_MODE
	if (TestMode)
	{
		return false;
	}		
#endif // TestMode

	if (inPenaltyBox[currentPlayer])
		return correctAnswerInPenalty();
	else
		return correctAnswerNoPenalty();
}

bool Game::correctAnswerInPenalty() {
	if (isGettingOutOfPenaltyBox)
		return correctAnswerBreakPenalty();
	else
		return correctAnswerRemainPenalty();
}
bool Game::correctAnswerNoPenalty()
{
	output->displayAnswerCorrent();
	giveCoinCurrentPlayer();
	output->displayGoldCoin(players[currentPlayer], purses[currentPlayer]);

	bool notWinner = didPlayerNotWin();
	advancePlayer();
	return notWinner;
}
bool Game::correctAnswerRemainPenalty() {
	advancePlayer();
	return true;
}
bool Game::correctAnswerBreakPenalty() {
	output->displayAnswerCorrect();
	giveCoinCurrentPlayer();
	output->displayGoldCoin(players[currentPlayer], purses[currentPlayer]);
	bool notWinner = didPlayerNotWin();
	advancePlayer();
	return notWinner;
}

bool Game::wrongAnswer()
{
#ifdef TEST_MODE
	if (TestMode)
	{
		return true;
	}	
#endif // TestMode

	output->displayAnswerIncorrect();
	output->displayPlayerSentPenalty(players[currentPlayer]);
	inPenaltyBox[currentPlayer] = true;

	advancePlayer();
	return true;
}

void Game::giveCoinCurrentPlayer() {
	purses[currentPlayer]++;
}

void Game::advancePlayer()
{
	currentPlayer++;
	if (playerOutOfBound())
		currentPlayer = 0;
}
bool Game::playerOutOfBound() {
	return currentPlayer == players.size();
}
bool Game::didPlayerNotWin() {
	return !(purses[currentPlayer] == pointsToWin);
}