#pragma once

#ifndef CARDGOD
#define CARDGOD

#include <iostream>
#include <vector>
#include <cmath>

#include "List.h"
#include "Menu.h"
#include "Card.h"

class CardinalGods {
    public:
		int cols, rows;
		Menu<Card*>* board;
		List<Card*>* hands[2];

		CardinalGods(int BoardSize, vector<int> pATickets, vector<int> pBTickets) {
			// We want the board to be of an odd sidelength
			if (BoardSize % 2 == 0) { BoardSize--; }
			if (BoardSize < 3) { BoardSize = 3; }
			// We need to set up the board
			List<Card*>* list = new List<Card*>();
			for(int i = 0; i < BoardSize*BoardSize; i++) { list->push(new Card(0, 0)); }
			cols = BoardSize;
			rows = BoardSize;
			board = new Menu<Card*>(list, cols);

			// Decide turn order
			if(true) {
				hands[0] = fillHand(pATickets, 1);
				hands[1] = fillHand(pBTickets, 2);
			} else {
				hands[0] = fillHand(pBTickets, 1);
				hands[1] = fillHand(pATickets, 2);
			}
		}

		List<Card*>* fillHand(vector<int> tickets, int playerNum) {
			List<Card*>* list = new List<Card*>();
			int size = ((cols*rows) + 1) / 2; 
			for(int i = 0; i < size; i++) {
				if(i >= tickets.size()) {
					list->push(new Card(0, playerNum));
				} else {
					list->push(new Card(tickets[i], playerNum));
				}
			}
			return list;
		}

		void consoleShowBoard() {
			// Show player 1's hand
			/*cout << "Player 1's Hand: " << endl << "+";
			for(int i = 0; i < hands[0]->getSize(); i++) {
				cout << "-----+";
			}
			cout << endl;
			for(int i = 0; i < 3; i++) {
				cout << "|";
				for(int j = 0; j < hands[0]->getSize(); j++) {
					switch(i) {
						case 0:
							cout << "  " << hands[0]->get(j)->n << "  |";
							break;
						case 1:
							cout << hands[0]->get(j)->w << " "
								 << hands[0]->get(j)->consolePrintTileState() << " "
								 << hands[0]->get(j)->e << "|";
							break;
						case 2:
							cout << "  " << hands[0]->get(j)->s << "  |";
							break;
					}
				}
				cout << endl;
			}
			cout << "+";
			for(int i = 0; i < hands[0]->getSize(); i++) {
				cout << "-----+";
			}
			cout << endl << endl;

			// Show player 2's hand
			cout << "Player 2's Hand: " << endl << "+";
			for(int i = 0; i < hands[1]->getSize(); i++) {
				cout << "-----+";
			}
			cout << endl;
			for(int i = 0; i < 3; i++) {
				cout << "|";
				for(int j = 0; j < hands[1]->getSize(); j++) {
					switch(i) {
						case 0:
							cout << "  " << hands[1]->get(j)->n << "  |";
							break;
						case 1:
							cout << hands[1]->get(j)->w << " "
								 << hands[1]->get(j)->consolePrintTileState() << " "
								 << hands[1]->get(j)->e << "|";
							break;
						case 2:
							cout << "  " << hands[1]->get(j)->s << "  |";
							break;
					}
				}
				cout << endl;
			}
			cout << "+";
			for(int i = 0; i < hands[1]->getSize(); i++) {
				cout << "-----+";
			}
			cout << endl << endl;*/

			cout << "Player 1's Hand" << endl;
			consoleShowHand(0);
			cout << "Player 2's Hand" << endl;
			consoleShowHand(1);
			
			// Show the board
			cout << "Board:" << endl;
			for(int i = 0; i < 3 * rows; i++) {
				if (i % 3 == 0) {
					cout << "+";
					for(int j = 0; j < cols; j++) {
						cout << "-----+";
					}
					cout << endl;
					//
					for (int j = 0; j < cols; j++) {
						cout << "|  " << board->get(j, floor(i/3))->n << "  ";
					}
					cout << "|" << endl;
				} else if (i % 3 == 1) {
					for(int j = 0; j < cols; j++) {
						cout << "|" << board->get(j, floor(i/3))->w << " "
									<< board->get(j, floor(i/3))->consolePrintTileState() << " "
									<< board->get(j, floor(i/3))->e;
					}
					cout << "|" << endl;
				} else {
					for(int j = 0; j < cols; j++) {
						cout << "|  " << board->get(j, floor(i/3))->s << "  ";
					}
					cout << "|" << endl;
				}
			}
			cout << "+";
			for(int j = 0; j < cols; j++) {
				cout << "-----+";
			}
			cout << endl;
		}

		void consoleShowHand(int playerNum) {
			for(int i = 0; i < 5; i++) {
				if(i == 0 || i == 4) {
					cout << "+";
				} else {
					cout << "|";
				}

				for(int j = 0; j < hands[playerNum]->getSize(); j++) {
					switch (i) {
						case 0:
							cout << "-----+";
							break;
						case 1:
							cout << "  " << hands[playerNum]->get(j)->n << "  |";
							break;
						case 2:
							cout << hands[playerNum]->get(j)->w << " "
								 << hands[playerNum]->get(j)->consolePrintTileState() << " "
								 << hands[playerNum]->get(j)->e << "|";
							break;
						case 3:
							cout << "  " << hands[playerNum]->get(j)->s << "  |";
							break;
						case 4:
							cout << "-----+";
							break;
					}
				}
				cout << endl;
			}
		}

		int* chooseCard(int player) {
			int* choice = new int;
			while(true) {
				cout << "Choose a card (1-" << hands[player]->getSize() << "): ";
				cin >> *choice;
				cout << endl;

				*choice--;
				if(*choice < 0 || *choice >= hands[player]->getSize()) {
					cout << "Invalid choice. Your choice = " << choice << endl;
					continue;
				}

				break;
			}

			return choice;
		}

		int* placeCard() {
			int posX, posY;
			while(true) {
				cout << "Choose a column (1-" << cols <<  "): ";
				cin >> posX;
				cout << endl << "Choose a row (1-" << rows << "): ";
				cin >> posY;
				cout << endl;

				posX--;
				posY--;
				if(posX < 0 || posX >= cols || posY < 0 || posY >= rows) {
					cout << "Invalid x or y position: x=" << posX+1 << ", y=" << posY+1 << endl;
					continue;
				}

				if(board->get(posX, posY)->tileState != 0) {
					cout << "A card already has claimed this tile" << endl;
					continue;
				}

				break;
			}

			int* pos = new int[2];
			pos[0] = posX;
			pos[1] = posY;
			return pos;
		}

		void pointBattle(int posX, int posY) {
			int* battles = new int[4]; // [N E S W] relative to the card placed
			
			// populate all items in the array with 0 to indicate stalemate/no battle
			for(int i = 0; i < 4; i++) { battles[i] = 0; }

			// Check to the north for an existing tile, if it exists and is not empty, initiate a battle
			if(posY > 0) {
				if(board->get(posX, posY-1)->tileState != 0) {
					battles[0] = board->get(posX, posY)->n -
								 board->get(posX, posY-1)->s;
				}
			}
			// Check to the east for an existing tile, if it exists and is not empty, initiate a battle
			if(posX < 2) {
				if(board->get(posX+1, posY)->tileState != 0) {
					battles[1] = board->get(posX, posY)->e -
								 board->get(posX+1, posY)->w;
				}
			}
			// Check to the south for an existing tile, if it exists and is not empty, initiate a battle
			if(posY < 2) {
				if(board->get(posX, posY+1)->tileState != 0) {
					battles[2] = board->get(posX, posY * cols)->s -
								 board->get(posX,  posY+1)->n;
				}
			}
			// Check to the west for an existing tile, if it exists and is not empty, initiate a battle
			if(posX > 0) {
				if(board->get(posX-1, posY)->tileState != 0) {
					battles[3] = board->get(posX, posY)->w -
								 board->get(posX-1, posY)->e;
				}
			}

			// Check to see if there is a loss
			// A loss value of -1 means there was no loss
			// anything higher means that a loss occurred
			int* loss = new int;
			*loss = -1;
			for(int i = 0; i < 4; i++) {
				if(battles[i] < 0) {
					*loss = i;
					break;
				}
			}

			// The case of losing
			if (*loss > 0) {
				// Find which card we lost to and change our current tileState to its tileState
				switch (*loss) {
					case 0:
						board->get(posX, posY)->tileState = board->get(posX, posY-1)->tileState;
						break;
					case 1:
						board->get(posX, posY)->tileState = board->get(posX+1, posY)->tileState;
						break;
					case 2:
						board->get(posX, posY)->tileState = board->get(posX, posY+1)->tileState;
						break;
					case 3:
						board->get(posX, posY)->tileState = board->get(posX-1, posY)->tileState;
						break;
				}
			} else { // The case of winning
				// Cycle through each direction, if we won in that direction
				// change their tileState to our tileState
				if(battles[0] > 0) {
					board->get(posX, posY-1)->tileState = board->get(posX, posY)->tileState;
				}
				if(battles[1] > 0) {
					board->get(posX+1, posY)->tileState = board->get(posX, posY)->tileState;
				}
				if(battles[2] > 0) {
					board->get(posX, posY+1)->tileState = board->get(posX, posY)->tileState;
				}
				if(battles[3] > 0) {
					board->get(posX-1, posY)->tileState = board->get(posX, posY)->tileState;
				}
			}
			delete loss;
		}

		bool fullBoard() {
			for(int y = 0; y < rows; y++) {
				for(int x = 0; x < cols; x++) {
					if(board->get(x, y)->tileState == 0) {
						return false;
					}
				}
			}
			return true;
		}

		void play() {
			int currPlayer = 1;

			while(!fullBoard()) {
				// Play the game
				// Choosing current player
				if(++currPlayer > 1)
					currPlayer = 0;

				// Show the board and cards
				consoleShowBoard();

				// Variables hold onto player choices
				int* choice = new int;
				int* pos = new int[2];
				// Putting data into these variables
				cout << endl;
				consoleShowHand(currPlayer);
				choice = chooseCard(currPlayer);
				pos = placeCard();
				// Executing on the commands given
				//cout << board->getSize() << endl;
				board->set(pos[0], pos[1], hands[currPlayer]->remove(*choice));
				pointBattle(pos[0], pos[1]);
			}

			consoleShowBoard();

			int* tally = new int[2];
			for(int i = 0; i < rows; i++) 
				for(int j = 0; j < cols; j++)
					tally[board->get(j, i)->tileState-1]++;

			if(tally[0] > tally[1]) {
				cout << "Player 1 wins!" << endl;
			} else {
				cout << "Player 2 wins!" << endl;
			}
			delete[] tally;
		}
};

#endif
