#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "List.h"
#include "Menu.h"
#include "Card.h"
#include "CardinalGods.h"

using namespace std;

int main() {
	vector<int> p1 = {2, 3, 4, 5, 10};
	vector<int> p2 = {1, 6, 7, 8, 9};
    CardinalGods* cg = new CardinalGods(3, p1, p2);
	cg->consoleShowBoard();
	//cg->play();
	
	delete cg;

    return 0;
}
