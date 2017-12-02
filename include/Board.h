/*
 * Board.h
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <array>
#include <exception>

namespace game {

constexpr int NUM_HOLES = 4;

enum class KeyPeg {
	EMPTY, WHITE, BLACK
};

enum class CodePeg {
	EMPTY, GREEN, BLUE, RED, ORANGE, YELLOW, PURPLE
};

using KeyPegs = std::array<KeyPeg, NUM_HOLES>;
using CodePegs = std::array<CodePeg, NUM_HOLES>;

class BoardException : public std::exception {
public:
	BoardException(const std::string& message) noexcept :
		msg(message) {
	}
	const char* what() const noexcept {
		return msg.c_str();
	}
private:
	std::string msg;
};

struct Row {
	CodePegs codePegs;
	KeyPegs keyPegs;
};

class Board {
private:

	std::vector<Row> rows;
	bool redacted = false;
	CodePegs secretPegs { {CodePeg::EMPTY, CodePeg::EMPTY, CodePeg::EMPTY, CodePeg::EMPTY} };

	CodePeg toCodePeg(const std::string& str) const;
	std::string toString(const CodePeg& peg) const;
	std::string toString(const KeyPeg& peg) const;
	KeyPegs evaluate(const CodePegs& codePegs) const;

public:
	static constexpr int MAX_ROWS = 12;

	Board() {
		rows.reserve(MAX_ROWS);
	}

	/**
	 * Return true if all rows are filled
	 */
	bool isFull() const {
		return rows.size() == MAX_ROWS;
	}

	/**
	 * Set secret code pegs
	 */
	void setSecretCode(const CodePegs& pegs);

	/**
	 * Return a string representation the board with visible secret code
	 */
	std::string reveal();

	/**
	 * Return a string representation the board
	 */
	std::string toString() const;

	/**
	 * Clear board
	 */
	void clear();

	/**
	 * Set code pegs and set the resulting key pegs
	 */
	void addGuessCode(const CodePegs& codePegs);

	/**
	 * Retrieve the resulting key pegs
	 */
	KeyPegs getResultKeyPegs() const;
};

} // namespace game

#endif /* BOARD_H_ */
