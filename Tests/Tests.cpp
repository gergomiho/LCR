#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LCR/Game.h"
#include "../LCR/Game.cpp"
#include "../LCR/GameRunner.h"
#include "../LCR/GameRunner.cpp"
#include "../LCR/Output.h"
#include "../LCR/Output.cpp"
#include <stdlib.h>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		IOutput* dummyOutput = new Output();
		

		TEST_METHOD(TrueIsTrue) {
			Assert::IsTrue(true);
		}

		string GenerateMasterOutput(unsigned int seed) {
			stringstream ss;
			auto old_buf = cout.rdbuf(ss.rdbuf());
			srand(seed);

			main();

			std::cout.rdbuf(old_buf);
			return ss.str();
		}
		string GameRunner(unsigned int seed) {
			stringstream ss;
			auto old_buf = cout.rdbuf(ss.rdbuf());
			srand(seed);

			main();

			std::cout.rdbuf(old_buf);
			return ss.str();
		}		

		TEST_METHOD(GoldenMasterTest100) {
			string output;
			ifstream originalOutputFile("gmt100.txt");
			stringstream originalOutput;

			originalOutput << originalOutputFile.rdbuf();

			for (unsigned int i = 0; i < 100; i++)
				output += GameRunner(i);

			Assert::AreEqual(output, originalOutput.str());
		}
		TEST_METHOD(TestFindCorrectAnswer) {
			for (int currentAnswerNum : GenerateCorrectAnswersNumList()) {
				Assert::IsTrue(answerIsCorrect(currentAnswerNum, currentAnswerNum));
			}
		}		
		TEST_METHOD(TestFindWrongAswer) {
			Assert::IsFalse(answerIsCorrect(WRONG_ANSWER_NUM, WRONG_ANSWER_NUM));
		}
		list<int> GenerateCorrectAnswersNumList() {
			list<int> correctAnswersNum;

			for (int i = LOWEST_ANSWER_NUM; i < HIGHEST_ANSWER_NUM; i++) {
				if (i != WRONG_ANSWER_NUM) {
					correctAnswersNum.push_front(i);
				}
			}

			return correctAnswersNum;
		}

		TEST_METHOD(TestNoWinnerCorrectAnswer) {
			Game game(dummyOutput);
			game.TestMode = true;
			Assert::IsTrue(winnerFound(game, true));
		}
		TEST_METHOD(TestNoWinnerWrongAnswer) {
			Game game(dummyOutput);
			game.TestMode = true;
			Assert::IsFalse(winnerFound(game, false));
		}

		TEST_METHOD(TestCreateGame) {
			Game game(dummyOutput);
		}
		TEST_METHOD(TestAddPlayers) {
			Game game(dummyOutput);
			Assert::AreEqual((size_t)0, game.players.size());
			game.add("Player");
			Assert::AreEqual((size_t)1, game.players.size());
		}
		TEST_METHOD(TestHowManyPlayers) {
			Game game(dummyOutput);
			Assert::AreEqual(0, game.howManyPlayers());
			game.add("Player");
			Assert::AreEqual(1, game.howManyPlayers());
		}
		TEST_METHOD(TestGameOnyPlayableAfterEnoughPlayers) {
			Game game(dummyOutput);
			for (int i = 0; i < game.reqPlayerAmount; i++) {
				Assert::IsFalse(game.isPlayable());
				game.add("Player");
			}
			Assert::IsTrue(game.isPlayable());
		}
		TEST_METHOD(TestWrongAnswerPenalty) {
			Game game(dummyOutput);
			game.add("Player");
			game.currentPlayer = 0;
			game.wrongAnswer();
			Assert::IsTrue(game.inPenaltyBox[0]);
		}
		TEST_METHOD(TestWinUponMaxPt) {
			Game game(dummyOutput);
			game.add("Player");
			game.purses[0] = game.pointsToWin;
			Assert::IsFalse(game.didPlayerNotWin());
		}
		TEST_METHOD(TestBreakingPenaltyOdd) {
			Game game(dummyOutput);
			AddPlayer(game, "Player", 0, true);

			game.roll(1);
			Assert::IsTrue(game.isGettingOutOfPenaltyBox);
		}
		TEST_METHOD(TestBreakingPenaltyEven) {
			Game game(dummyOutput);
			AddPlayer(game, "Player", 0, 0, true);

			game.roll(2);
			Assert::IsFalse(game.isGettingOutOfPenaltyBox);
		}
		TEST_METHOD(TestPlayerSetpping) {
			int currentPlace = 5;
			int rolledDice = 5;

			Game game(dummyOutput);
			AddPlayer(game, "Player", 0, currentPlace, false);
			game.roll(rolledDice);

			Assert::AreEqual(currentPlace + rolledDice, game.places[0]);
		}
		TEST_METHOD(TestPlayerResetPosition) {
			int currentPlace = 10;
			int rolledDice = 5;

			Game game(dummyOutput);
			AddPlayer(game, "Player", 0, currentPlace, false);
			game.roll(rolledDice);

			Assert::AreEqual(currentPlace + rolledDice - game.mapSize, game.places[0]);
		}
		TEST_METHOD(TestCurrentCategory) {
			Game game(dummyOutput);
			AddPlayer(game, "Player", 0, 5, false);
			Assert::AreEqual(std::string("Science"), game.currentCategory());
		}

		TEST_METHOD(TestAdvancePlayer) {
			Game game(dummyOutput);
			AddPlayer(game, "Player", 0, 0, false);
			AddPlayer(game, "Player", 0, 0, false);

			Assert::AreEqual(0, game.currentPlayer);

			game.correctAnswer();

			Assert::AreEqual(1, game.currentPlayer);
		}
		TEST_METHOD(TestCorrectAnswerBreakPenaltyGold) {
			int startingGold = 2;

			Game game(dummyOutput);
			AddPlayer(game, "Player", startingGold, 0, true);
			game.isGettingOutOfPenaltyBox = true;

			Assert::AreEqual(startingGold, game.purses[game.currentPlayer]);

			game.correctAnswer();

			Assert::AreEqual(startingGold + 1, game.purses[game.currentPlayer]);
		}
		TEST_METHOD(TestCorrectAnswerStayPenaltyGold) {
			int startingGold = 2;

			Game game(dummyOutput);
			AddPlayer(game, "Player", startingGold, 0, true);
			game.isGettingOutOfPenaltyBox = false;

			Assert::AreEqual(startingGold, game.purses[game.currentPlayer]);

			game.correctAnswer();

			Assert::AreEqual(startingGold, game.purses[game.currentPlayer]);
		}
		TEST_METHOD(TestCorrectAnswerNoPenaltyGold) {
			int startingGold = 2;

			Game game(dummyOutput);
			AddPlayer(game, "Player", startingGold, 0, false);

			Assert::AreEqual(startingGold, game.purses[game.currentPlayer]);

			game.correctAnswer();

			Assert::AreEqual(startingGold + 1, game.purses[game.currentPlayer]);
		}

		void AddPlayer(Game &game, string name = "Player", int gold = 0, int position = 0, bool inPenalty = false) {
			game.add(name);
			game.purses[game.howManyPlayers() - 1] = gold;
			game.places[game.howManyPlayers() - 1] = position;
			game.inPenaltyBox[game.howManyPlayers() - 1] = inPenalty;
		}
		/*TEST_METHOD(GMT)
		{
			string output1, output2;
			ofstream myfile;
			myfile.open("gmt10000.txt", ofstream::trunc | ofstream::out );

			for (unsigned int i = 0; i < 10000; i++)
			{
				output1 = GenerateMasterOutput(i);
				output2 = GenerateMasterOutput(i);

				Assert::AreEqual(output1, output2);

				myfile << output1;
			}

			myfile.close();
		}*/

	};
}