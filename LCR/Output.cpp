#include "Output.h"
#include <string>

using namespace std;

Output::Output() {
}
Output::~Output() {
}
void Output::displayRoundStart(int rolledDice, int currentPlayer) {
	//cout << players[currentPlayer] << " is the current player" << endl;
	cout << "They have rolled a " << rolledDice << endl;
}
void Output::displayPlayerName(string currentPlayer) {
	cout << currentPlayer << " is the current player" << endl;
}
void Output::displayRolledNumber(int rolledDice) {
	cout << "They have rolled a " << rolledDice << endl;
}
void Output::displayCurrentCategory(string currentCategory) {
	cout << "The category is " << currentCategory << endl;
}
void Output::displayPlayersPosition(string currentPlayer, int currentPlayerPosition) {
	cout << currentPlayer << "'s new location is " << currentPlayerPosition << endl;
}
void Output::displayPlayerBreakPenalty(string currentPlayer) {
	cout << currentPlayer << " is getting out of the penalty box" << endl;
}
void Output::displayPlayerStayPenalty(string currentPlayer) {
	cout << currentPlayer << " is not getting out of the penalty box" << endl;
}
void Output::displayCategory(string currentCategory){
	cout << questionCatMap[currentCategory].front() << endl;
}
void Output::displayAnswerCorrect() {
	cout << "Answer was correct!!!!" << endl;
}
void Output::displayAnswerCorrent() {
	cout << "Answer was corrent!!!!" << endl;
}
void Output::displayAnswerIncorrect() {
	cout << "Question was incorrectly answered" << endl;
}
void Output::displayGoldCoin(string currentPlayer, int goldCoin) {
	cout << currentPlayer << " now has " << goldCoin << " Gold Coins." << endl;
}
void Output::displayPlayerSentPenalty(string currentPlayer) {
	cout << currentPlayer + " was sent to the penalty box" << endl;
}
void Output::displayPlayerAdded(string playerName) {
	cout << playerName << " was added" << endl;
}
void Output::displayPlayerCount(int playerCount) {
	cout << "They are player number " << playerCount << endl;
}
