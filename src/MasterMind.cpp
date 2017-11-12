/*
 * MasterMind.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */

#include "MasterMind.h"
#include "Player.h"
#include "Board.h"
#include "Utils.h"

#include <iostream>
#include <algorithm>

using namespace std;

namespace game {

CodePegs MasterMind::askCodePegs() const {
	CodePegs codePegs;
	auto success = false;
	while (!success) {
		try {
			string str = "";
			cout << "(g = green, b = blue, r = red, o = orange, y = yellow, p = purple)" << endl;
			cin >> str;
			std::transform(str.begin(), str.end(), str.begin(), ::tolower);
			codePegs = toCodePegs(str);
			success = true;
		}
		catch (const MasterMindException& e) {
			cout << e.what() << endl;
		}
	}
	return codePegs;
}

CodePegs MasterMind::askSecretCode(const Player& player) const {
	cout << "***make sure code breaker is not looking***" << endl
		<< "CodeMaker " << player.getName() << ", enter 4 secret code pegs seperated by comma"
		<< endl;

	auto codePegs = askCodePegs();
	// clear screen
	for (auto i = 0; i < 50; ++i) {
		cout << endl;
	}
	return codePegs;
}

CodePegs MasterMind::askGuessCode(const Player& player) const {
	cout << "CodeBreaker " << player.getName() << ", enter 4 code pegs seperated by comma"
		<< endl;

	return askCodePegs();
}

void MasterMind::play() {
	const KeyPegs allBlackPegs
		{ KeyPeg::BLACK, KeyPeg::BLACK, KeyPeg::BLACK, KeyPeg::BLACK };

	for (auto count = 0; count < numberOfGames; ++count) {
		board.clear();

		auto secretCode = askSecretCode(codeMaker);
		board.setSecretCode(secretCode);

		cout << "*** GAME " << count + 1 << " ***" << endl;
		auto isGameOver = false;
		while (!isGameOver) {
			cout << board.toString();
			auto guessPegs = askGuessCode(codeBreaker);
			codeMaker.incScore();

			board.addGuessCode(guessPegs);
			auto keyPegs = board.getResultKeyPegs();

			if (keyPegs == allBlackPegs) {
				cout << codeBreaker.getName() << " won the game!!!" << endl;
				isGameOver = true;
			}

			if (board.isFull()) {
				codeMaker.incScore();
				cout << codeMaker.getName() << " won the game!!!" << endl;
				isGameOver = true;
			}
		}

		cout << board.reveal();

		cout << endl
			<< codeMaker.getName() << " has " << codeMaker.getScore() << " points" << endl
			<< codeBreaker.getName() << " has " << codeBreaker.getScore() << " points" << endl;

		if (count <  numberOfGames - 1) {
			swap(codeBreaker, codeMaker);
			cout << "*** Now CodeBreaker is " << codeBreaker.getName()
				 << " and CodeMaker is " << codeMaker.getName() << endl;
		}
	}
}


CodePegs MasterMind::toCodePegs(const string& str) const {
	auto tokens = utils::splitString(str, ',');
	if (tokens.size() != NUM_HOLES) {
		throw MasterMindException("Invalid number of code pegs! Must be 4 code pegs");
	}
	CodePegs codePegs;
	for (size_t idx = 0; idx < tokens.size(); ++idx) {
		codePegs[idx] = toCodePeg(utils::trim(tokens[idx]));
	}
	return codePegs;
}

CodePeg MasterMind::toCodePeg(const string& str) const {
	if (str == "g") {
		return CodePeg::GREEN;
	}
	else if (str == "b") {
		return CodePeg::BLUE;
	}
	else if (str == "r") {
		return CodePeg::RED;
	}
	else if (str == "o") {
		return CodePeg::ORANGE;
	}
	else if (str == "y") {
		return CodePeg::YELLOW;
	}
	else if (str == "p") {
		return CodePeg::PURPLE;
	}
	else if (str.empty()) {
		throw MasterMindException("Cannot use empty code peg as per normal rule");
	}
	throw MasterMindException("Invalid code peg \'" + str +"\'");
}

} // namespace game
