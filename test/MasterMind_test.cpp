/*
 * MasterMind_test.cpp
 *
 *  Created on: Nov 13, 2016
 *      Author: vergel
 */

#include "gtest/gtest.h"
#define private public
#include "MasterMind.h"

using namespace std;
using namespace game;

TEST(ToCodePegTest, ValidString) {
	MasterMind game(2, "jack", "jill");
	CodePegs pegs = game.toCodePegs("y,b,o,r");
	ASSERT_EQ(4u, pegs.size());
	EXPECT_EQ(CodePeg::YELLOW, pegs[0]);
	EXPECT_EQ(CodePeg::BLUE, pegs[1]);
	EXPECT_EQ(CodePeg::ORANGE, pegs[2]);
	EXPECT_EQ(CodePeg::RED, pegs[3]);

	pegs = game.toCodePegs("  p,r, g , r");
	ASSERT_EQ(4u, pegs.size());
	EXPECT_EQ(CodePeg::PURPLE, pegs[0]);
	EXPECT_EQ(CodePeg::RED, pegs[1]);
	EXPECT_EQ(CodePeg::GREEN, pegs[2]);
	EXPECT_EQ(CodePeg::RED, pegs[3]);
}

TEST(ToCodePegTest, InvalidString) {
	MasterMind game(2, "jack", "jill");
	EXPECT_THROW(game.toCodePegs("invalid"), MasterMindException);
	EXPECT_THROW(game.toCodePegs("r,g,b"), MasterMindException);
	EXPECT_THROW(game.toCodePegs("r,g,b, "), MasterMindException);
}
