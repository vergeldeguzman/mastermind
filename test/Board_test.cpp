/*
 * Board_test.cpp
 *
 *  Created on: Nov 13, 2016
 *      Author: vergel
 */

#include "gtest/gtest.h"
#include "Board.h"

using namespace std;
using namespace game;

TEST(InitialTest, StartEmpty) {
	Board board;
	EXPECT_EQ(
			"+---------+\n"
			"|         |\n"
			"|---------|------+\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"+---------+------+\n",
			board.toString());
}

TEST(SecretCodeTest, RedactedBoard) {
	Board board;
	board.setSecretCode({CodePeg::BLUE, CodePeg::GREEN, CodePeg::BLUE, CodePeg::RED});
	EXPECT_EQ(
			"+---------+\n"
			"| ? ? ? ? |\n"
			"|---------|------+\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"+---------+------+\n",
			board.toString());
}

TEST(SecretCodeTest, RevealBoard) {
	Board board;
	board.setSecretCode({CodePeg::BLUE, CodePeg::GREEN, CodePeg::BLUE, CodePeg::RED});
	EXPECT_EQ(
			"+---------+\n"
			"| b g b r |\n"
			"|---------|------+\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"+---------+------+\n",
			board.reveal());
}

TEST(addGuessCodesTest, EvaluateRGBY) {
	Board board;
	board.setSecretCode({CodePeg::RED, CodePeg::GREEN, CodePeg::BLUE, CodePeg::YELLOW});
	board.addGuessCode({CodePeg::ORANGE, CodePeg::ORANGE, CodePeg::PURPLE, CodePeg::PURPLE});
	board.addGuessCode({CodePeg::ORANGE, CodePeg::ORANGE, CodePeg::RED, CodePeg::GREEN});
	board.addGuessCode({CodePeg::RED, CodePeg::BLUE, CodePeg::GREEN, CodePeg::YELLOW});
	board.addGuessCode({CodePeg::GREEN, CodePeg::RED, CodePeg::YELLOW, CodePeg::BLUE});
	board.addGuessCode({CodePeg::ORANGE, CodePeg::ORANGE, CodePeg::PURPLE, CodePeg::YELLOW});
	board.addGuessCode({CodePeg::BLUE, CodePeg::BLUE, CodePeg::BLUE, CodePeg::BLUE});
	board.addGuessCode({CodePeg::RED, CodePeg::GREEN, CodePeg::BLUE, CodePeg::YELLOW});
	EXPECT_EQ(
			"+---------+\n"
			"| ? ? ? ? |\n"
			"|---------|------+\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"| r g b y | BBBB |\n"
			"| b b b b | B    |\n"
			"| o o p y | B    |\n"
			"| g r y b | WWWW |\n"
			"| r b g y | BBWW |\n"
			"| o o r g | WW   |\n"
			"| o o p p |      |\n"
			"+---------+------+\n",
			board.toString());
}

TEST(addGuessCodesTest, EvaluateRRRY) {
	Board board;
	board.setSecretCode({CodePeg::RED, CodePeg::RED, CodePeg::RED, CodePeg::YELLOW});
	board.addGuessCode({CodePeg::RED, CodePeg::RED, CodePeg::RED, CodePeg::RED});
	board.addGuessCode({CodePeg::YELLOW, CodePeg::YELLOW, CodePeg::RED, CodePeg::RED});
	board.addGuessCode({CodePeg::YELLOW, CodePeg::YELLOW, CodePeg::YELLOW, CodePeg::YELLOW});
	EXPECT_EQ(
			"+---------+\n"
			"| ? ? ? ? |\n"
			"|---------|------+\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"| y y y y | B    |\n"
			"| y y r r | BWW  |\n"
			"| r r r r | BBB  |\n"
			"+---------+------+\n",
			board.toString());
}

TEST(addGuessCodesTest, EvaluateRRRR) {
	Board board;
	board.setSecretCode({CodePeg::RED, CodePeg::RED, CodePeg::RED, CodePeg::RED});
	board.addGuessCode({CodePeg::YELLOW, CodePeg::YELLOW, CodePeg::YELLOW, CodePeg::YELLOW});
	board.addGuessCode({CodePeg::RED, CodePeg::YELLOW, CodePeg::YELLOW, CodePeg::YELLOW});
	board.addGuessCode({CodePeg::RED, CodePeg::RED, CodePeg::YELLOW, CodePeg::YELLOW});
	board.addGuessCode({CodePeg::RED, CodePeg::RED, CodePeg::RED, CodePeg::RED});
	EXPECT_EQ(
			"+---------+\n"
			"| ? ? ? ? |\n"
			"|---------|------+\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"| r r r r | BBBB |\n"
			"| r r y y | BB   |\n"
			"| r y y y | B    |\n"
			"| y y y y |      |\n"
			"+---------+------+\n",
			board.toString());
}

TEST(addGuessCodesTest, ClearBoard) {
	Board board;
	board.setSecretCode({CodePeg::BLUE, CodePeg::GREEN, CodePeg::BLUE, CodePeg::RED});
	board.addGuessCode({CodePeg::RED, CodePeg::GREEN, CodePeg::ORANGE, CodePeg::RED});
	board.clear();
	EXPECT_EQ(
			"+---------+\n"
			"|         |\n"
			"|---------|------+\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"|         |      |\n"
			"+---------+------+\n",
			board.toString());
}

TEST(addGuessCodesTest, Exception) {
	Board board;
	board.setSecretCode({CodePeg::BLUE, CodePeg::GREEN, CodePeg::BLUE, CodePeg::RED});
	for (auto i = 0; i < Board::MAX_ROWS; ++i) {
		board.addGuessCode({CodePeg::RED, CodePeg::GREEN, CodePeg::ORANGE, CodePeg::RED});
	}
	EXPECT_THROW(
		board.addGuessCode(
			{CodePeg::YELLOW, CodePeg::GREEN, CodePeg::ORANGE, CodePeg::PURPLE}),
		BoardException);
}
