#pragma once

const int LOWEST_ANSWER_NUM = 0;
const int HIGHEST_ANSWER_NUM = 9;
const int WRONG_ANSWER_NUM = 7;

bool answerIsCorrect(int lowerLimit = LOWEST_ANSWER_NUM, int upperLimit = HIGHEST_ANSWER_NUM);
bool winnerFound(Game &aGame, bool answerIsCorrect);