/*
 * gtest_main.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */

#include <stdio.h>
#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
  printf("Running main() from gtest_main.cc\n");
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


