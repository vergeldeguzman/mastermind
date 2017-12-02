/*
 * MasterMind.h
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */

#ifndef MASTERMIND_H_
#define MASTERMIND_H_

#include "Board.h"
#include "Player.h"

#include <array>
#include <exception>

namespace game {

class MasterMindException : public std::exception {
public:
	MasterMindException(const std::string& message) noexcept :
		msg(message) {
	}
	const char* what() const noexcept {
		return msg.c_str();
	}
private:
	std::string msg;
};

class MasterMind {
private:
	static const int NUM_PLAYERS = 2;

	int numberOfGames;
	Player codeBreaker;
	Player codeMaker;
	Board board;

	CodePegs toCodePegs(const std::string& str) const;
	CodePeg toCodePeg(const std::string& str) const;
	CodePegs askSecretCode(const Player& player) const;
	CodePegs askGuessCode(const Player& player) const;
	CodePegs askCodePegs() const;

public:
	MasterMind(int numGames, const std::string& player1, const std::string& player2) :
		numberOfGames(numGames),
		codeBreaker(player1),
		codeMaker(player2) {
	}

	void play();
};

} // namespace game

#endif /* MASTERMIND_H_ */
