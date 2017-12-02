/*
 * Utils.h
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <vector>
#include <string>

namespace utils {

/**
 * Split string by delimiter to vector
 */
std::vector<std::string> splitString(const std::string& input, char delimiter);

/**
 * Remove trailing spaces and tabs
 */
std::string trimRight(const std::string& input);

/**
 * Remove leading spaces and tabs
 */
std::string trimLeft(const std::string& input);

/**
 * Remove trailing and leading spaces and tabs
 */
std::string trim(const std::string& input);

}

#endif /* UTILS_H_ */
