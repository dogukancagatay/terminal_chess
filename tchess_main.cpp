//============================================================================
// Name        : tchess_main.hpp
// Author      : Dogukan Cagatay
// E-mail	   : dcagatay@gmail.com
// Description : A terminal chess game that runs minimax algorithm and alpha beta prunning
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include "tchess_board.hpp"
#include "tchess_piece.hpp"
#include "tchess_algorithms.hpp"

int main() {

	cout<< "Welcome to my chess program. If your terminal doesn't support Unicode characters you will not be able to play the game."<<endl;
	cout<< "To play the game, basically when you move is asked enter your move as source letter source number destination letter destination number."<<endl;
	cout<< "For example, 'a 2 a 3' will move your piece at a 2 to a 3."<<endl;
	cout<< "Have good time =D"<<endl<<endl;

	Board *b = new Board();
	Board *test;
	b->initialize();
	cout << "Board:" << endl;
	b->print();
	//	int i = 1;

	char src_x = 0, src_y = 0, dest_x = 0, dest_y = 0;


	while (true) {
		cout << "Enter your move: ";
		cin >> src_y >> src_x >> dest_y >> dest_x;
		cout << endl;
		//integerize
		src_x -= '1';
		dest_x -= '1';

		src_y -= 'a';
		dest_y -= 'a';

		test = b->move(src_x, src_y, dest_x, dest_y);
		if (test == NULL) {
			cout << "Invalid move. Try again." << endl << endl;
		} else {
			b = test;
			b->print();
		}
		//cout << "White: " << b->evaluate_board(White) << endl;
		//cout << "Black: " << b->evaluate_board(Black) << endl;

		//enemy turn

		time_t start = time(NULL);
		b = ABMinMax(b,6);
		cout<< "passed time = "<< time(NULL) - start <<endl;

//		start = time(NULL);
//		b = MinMax(b,5);
//		cout<< "passed time = "<< time(NULL) - start <<endl;

		if(b!=NULL){
			b->print();
		}
		else{
			cout<< "null dondu exiting"<<endl;
			break;
		}
	}

	return 0;
}
