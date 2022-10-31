#pragma once

#ifndef CARD
#define CARD

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Common.h"

using namespace std;

class Card {
    public:
		int id;
		string name, rarity;
		int n, e, s, w;
		int tileState;

		Card(int ID, int TileState) {
			id = ID;
			
			fstream file("Cards.csv");
			vector<string> row;
			string line, word;

			getline(file, line);
			getline(file, line);
			stringstream st(line);
			while(getline(st, word, ','))
				row.push_back(word);

			while(getline(file, line)) {
				stringstream str(line);
				getline(str, word, ',');
				if(word == to_string(ID))
					break;
			}
			if (word == to_string(ID)) {
				row.clear();
				stringstream str(line);
				while(getline(str, word, ','))
					row.push_back(word);
			}

			name = (row)[1];
			rarity = (row)[2];
			n = stoi((row)[3]);
			e = stoi((row)[4]);
			s = stoi((row)[5]);
			w = stoi((row)[6]);
			tileState = TileState;

			file.close();
		}

		char consolePrintTileState() {
			switch(tileState) {
				case 1:
					return 'X';

				case 2:
					return 'Y';

				default:
					return 'E';
			}
			return '.';
		}

		void consolePrintCard() {
			cout << name << endl << rarity << endl;
			cout << "+-----+" << endl; // First and last lines
			cout << "|  " << n << "  |" << endl;
			cout << "|" << w << " " <<  consolePrintTileState() << " " << e << "|" << endl;
			cout << "|  " << s << "  |" << endl;
			cout << "+-----+" << endl;
			return;
		}
};

#endif
