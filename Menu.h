#pragma once

#ifndef MENU
#define MENU

#include <iostream>
#include <cmath>

#include "Common.h"
#include "List.h"

template <typename T>
class Menu {
	public:
		List<T>* list;
		int rows, cols, cx, cy;

		Menu<T>(List<T>* MenList, int Cols) {
			list = MenList;
			cols = Cols;
			rows = ceil(list->getSize() / cols);
			cx = 0;
			cy = 0;
		}

		int getSize() {
			return list->getSize();
		}	

		// Movement
		// Going up
		void up() {
			Common* com = new Common();
			cy = com->modulo(cy - 1, rows);
			delete com;
		}

		// Going right
		void right() {
			Common* com = new Common();
			cx = com->modulo(cx + 1, cols);
			delete com;
		}

		// Going down
		void down() {
			Common* com = new Common();
			cy = com->modulo(cy + 1, rows);
			delete com;
		}

		// Going left
		void left() {
			Common* com = new Common();
			cx = com->modulo(cx - 1, cols);
			delete com;
		}

		// Retrieve item
		T get() {
			return list->get(cx + cy * cols);
		}

		T get(int x, int y) {
			return list->get(x + y * cols);
		}

		void set(int x, int y, T data) {
			list->edit(data, x + cols * y);
		}

		void setCX(int CX) {
			cx = CX;
		}

		void setCY(int CY) {
			cy = CY;
		}

		void showPosition() {
			std::cout << "Position (x, y): (" << cx << ", " << cy << ")" << std::endl;
		}

		void showMenu() {
			Node<T>* node = list->head;

			for(int i = 0; i < list->getSize(); i++) {
				if (i % cols != 0) { std::cout << " "; }
				std::cout << node->data;
				node = node->next;
				if (i % cols == cols - 1 || i == list->getSize() - 1) {std::cout << std::endl;}
			}
		}
};

#endif
