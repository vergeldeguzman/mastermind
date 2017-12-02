/*
 * RunGame.cpp
 *
 *  Created on: Nov 12, 2016
 *      Author: vergel
 */

#include "MasterMind.h"
#include "Player.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool isValidNumberOfGames(const string& str) {
	int value = 0;
	try {
		value = stoi(str);
	}
	catch (const exception& e) {
		cout << "Invalid number of games. Must be 2 or higher even number." << endl;
		return false;
	}

	if (value < 2 || value % 2 != 0) {
		cout << "Invalid number of games. Must be 2 or higher even number." << endl;
		return false;
	}
	return true;
}

int main() {
	try {
		string numGamesStr = "";
		do {
			cout << "Enter number of games (must be even number): ";
			cin >> numGamesStr;
		} while (!isValidNumberOfGames(numGamesStr));
		int numGames = stoi(numGamesStr);

		string name1;
		do {
			cout << "Enter player 1 name: ";
			cin >> name1;
		} while (name1.empty());

		string name2;
		do {
			cout << "Enter player 2 name: ";
			cin >> name2;
		} while (name2.empty());

		game::MasterMind masterMind(numGames, name1, name2);
		masterMind.play();
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		return 1;
	}
	return 0;
}

