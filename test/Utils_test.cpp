/*
 * Utils_test.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */


#include "gtest/gtest.h"
#include "Utils.h"

using namespace std;

TEST(SplitStringTest, NormalDelimited) {
	auto output = utils::splitString("a,bc,def", ',');
	ASSERT_EQ(3u, output.size());
	EXPECT_EQ("a", output[0]);
	EXPECT_EQ("bc", output[1]);
	EXPECT_EQ("def", output[2]);
}

TEST(SplitStringTest, ConsecutivelDelimited) {
	auto output = utils::splitString("a,,,b,", ',');
	ASSERT_EQ(5u, output.size());
	EXPECT_EQ("a", output[0]);
	EXPECT_EQ("", output[1]);
	EXPECT_EQ("", output[2]);
	EXPECT_EQ("b", output[3]);
	EXPECT_EQ("", output[4]);
}

TEST(TrimRightTest, All) {
	EXPECT_EQ("", utils::trimRight(""));
	EXPECT_EQ("xyz", utils::trimRight("xyz"));
	EXPECT_EQ("xyz", utils::trimRight("xyz    "));
	EXPECT_EQ("    x y  z", utils::trimRight("    x y  z    "));
}

TEST(TrimLeftTest, All) {
	EXPECT_EQ("", utils::trimLeft(""));
	EXPECT_EQ("xyz", utils::trimLeft("xyz"));
	EXPECT_EQ("xyz", utils::trimLeft("    xyz"));
	EXPECT_EQ("x y  z    ", utils::trimLeft("    x y  z    "));
}

TEST(TrimTest, All) {
	EXPECT_EQ("", utils::trim(""));
	EXPECT_EQ("xyz", utils::trim("xyz"));
	EXPECT_EQ("x y  z", utils::trim("    x y  z    "));
}
