/*
 * Utils.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */

#include "Utils.h"

using namespace std;

namespace utils {

vector<string> splitString(const string& input, char delimiter) {
	vector<string> strings;

	size_t idx = 0;
	size_t found = 0;
	auto len = input.size();
	while (idx < len && (found = input.find(delimiter, idx)) != string::npos) {
		strings.push_back(input.substr(idx, found - idx));
		idx = found + 1;
	}

	if (idx < len) {
		strings.push_back(input.substr(idx, found - idx));
	}
	// add empty if last char is a delimeter
	if (len > 0 && input[len - 1] == delimiter) {
		strings.push_back("");
	}

	return strings;
}

string trimLeft(const string& input) {
	if (input.empty()) {
		return "";
	}

	size_t idx = 0;
	auto len = input.size();
	while (idx < len && (input[idx] == ' ' || input[idx] == '\t')) {
		++idx;
	}
	if (idx >= len) {
		return "";
	}
	return input.substr(idx);
}

string trimRight(const string& input) {
	if (input.empty()) {
		return "";
	}

	auto count = input.size();
	while (count > 0 && (input[count - 1] == ' ' || input[count - 1] == '\t')) {
		--count;
	}
	return input.substr(0, count);
}

string trim(const string& input) {
	if (input.empty()) {
		return "";
	}

	return trimLeft(trimRight(input));
}

} // namespace utils
