/*
 * Board.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */

#include "Board.h"
#include "Utils.h"

#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

namespace game {

void Board::clear() {
	secretPegs = { CodePeg::EMPTY, CodePeg::EMPTY, CodePeg::EMPTY, CodePeg::EMPTY };
	rows.clear();
	redacted = false;
}

void Board::addGuessCode(const CodePegs& codePegs) {
	if (rows.size() >= MAX_ROWS) {
		throw BoardException("Cannot add pegs beyond max row");
	}
	auto keyPegs = evaluate(codePegs);
	rows.push_back(Row(codePegs, keyPegs));
}

KeyPegs Board::evaluate(const CodePegs& codePegs) const {
	KeyPegs keyPegs { KeyPeg::EMPTY, KeyPeg::EMPTY, KeyPeg::EMPTY, KeyPeg::EMPTY };
	map<int, bool> unmatchIdx;
	auto keyPegIdx = 0;
	for (auto i = 0; i < NUM_HOLES; ++i) {
		if (secretPegs[i] == codePegs[i]) {
			keyPegs[keyPegIdx] = KeyPeg::BLACK;
			++keyPegIdx;
		}
		else {
			unmatchIdx[i] = false;
		}
	}

	for (const auto & codeIdxs : unmatchIdx) {
		auto codeIdx = codeIdxs.first;

		for (auto & secretIdxs : unmatchIdx) {
			auto secretIdx = secretIdxs.first;
			auto & counted = secretIdxs.second;
			if (!counted && secretPegs[secretIdx] == codePegs[codeIdx]) {
				keyPegs[keyPegIdx] = KeyPeg::WHITE;
				++keyPegIdx;
				counted = true;
				break;
			}
		}
	}
	return keyPegs;
}

KeyPegs Board::getResultKeyPegs() const {
	if (rows.empty()) {
		throw BoardException("Cannot get result key pegs from empty rows");
	}

	return rows.back().keyPegs;
}

void Board::setSecretCode(const CodePegs& pegs) {
	redacted = true;
	secretPegs = pegs;
}
string Board::reveal() {
	redacted = false;
	return toString();
}

string Board::toString(const CodePeg& peg) const {
	switch (peg) {
	case CodePeg::GREEN:
		return "g";
	case CodePeg::BLUE:
		return "b";
	case CodePeg::RED:
		return "r";
	case CodePeg::ORANGE:
		return "o";
	case CodePeg::YELLOW:
		return "y";
	case CodePeg::PURPLE:
		return "p";
	case CodePeg::EMPTY:
		return " ";
	default:
		throw BoardException("Unrecoginize code peg on CodePeg enum");
	}
}

string Board::toString(const KeyPeg& peg) const {
	switch (peg) {
	case KeyPeg::BLACK:
		return "B";
	case KeyPeg::WHITE:
		return "W";
	case KeyPeg::EMPTY:
		return " ";
	default:
		throw BoardException("Unrecoginize key peg on KeyPeg enum");
	}
}

string Board::toString() const {
	stringstream ss;
	ss << "+---------+" << endl;
	ss << "| ";
	for (const auto & peg : secretPegs) {
		ss << (redacted ? "?" : toString(peg)) << " ";
	}
	ss << "|" << endl;
	ss << "|---------|------+" << endl;
	for (size_t n = 0; n < MAX_ROWS - rows.size(); ++n) {
		ss << "|         |      |" << endl;
	}
	for (auto rowIter = rows.rbegin(); rowIter != rows.rend(); ++rowIter) {
		ss << "| ";
		for (const auto & peg : rowIter->codePegs) {
			ss << toString(peg) << " ";
		}
		ss << "| ";
		for (const auto & peg : rowIter->keyPegs) {
			ss << toString(peg);
		}
		ss << " |" << endl;
	}
	ss << "+---------+------+" << endl;
	return ss.str();
}

} // namespace game


