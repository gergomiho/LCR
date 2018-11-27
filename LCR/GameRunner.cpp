#include <stdlib.h>
#include "Game.h"
#include "GameRunner.h"

static bool notAWinner;

int main()
{
	IOutput* output = new Output();
	Game game(output);

	game.add("Chet");
	game.add("Pat");
	game.add("Sue");

	int dice;

	do {
		dice = rand() % 5 + 1;
		game.roll(dice);
	} while (!winnerFound(game, answerIsCorrect()));

}

bool answerIsCorrect(int lowerLimit, int upperLimit) {
	int range = upperLimit - lowerLimit;
	if (range < 1)
		range = 1;
	return rand() % range + lowerLimit != WRONG_ANSWER_NUM;
}
bool winnerFound(Game &aGame, bool answerIsCorrect) {
	if (answerIsCorrect)
		return ! aGame.correctAnswer();
	else
		return ! aGame.wrongAnswer();
}