/*
 * Player.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */

#ifndef PLAYER_CPP_
#define PLAYER_CPP_

#include "Board.h"

namespace game {

class Player {
private:
	std::string name;
	int score;

public:
	Player(std::string name) : name(name), score(0) {
	}

	/**
	 * Add 1 point
	 */
	void incScore() {
		++score;
	}

	/**
	 * Return the current score
	 */
	int getScore() const {
		return score;
	}

	/**
	 * Return the player name
	 */
	std::string getName() const {
		return name;
	}
};

} // namespace game

#endif /* PLAYER_CPP_ */
