//============================================================================
// Name        : tchess_algorithms.hpp
// Author      : Dogukan Cagatay
// E-mail	   : dcagatay@gmail.com
// Description : A terminal chess game minimax algorithm and alpha beta pruning implementations.
//============================================================================

#ifndef TCHESS_ALGORITHMS_HPP
#define TCHESS_ALGORITHMS_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include "tchess_board.hpp"
#include "tchess_piece.hpp"

Board* MinMax(Board* board, short int depth_limit);
Board* MinMove(Board* board, short int depth_limit, short int depth);
Board* MaxMove(Board* board, short int depth_limit, short int depth);
Board* ABMinMax(Board* board, short int depth_limit);
Board* ABMaxMove(Board* board, short int depth_limit, short int depth, int a, int b);
Board* ABMinMove(Board* board, short int depth_limit, short int depth, int a, int b);

Board* MinMax(Board* board, short int depth_limit) {
	return MaxMove(board, depth_limit, 0);
}
Board* MaxMove(Board* board, short int depth_limit, short int depth) {
	vector<Board*> *moves;
	Board* best_real_move = NULL;
	Board* best_move = NULL;
	Board* move = NULL;

	if (depth >= depth_limit) {//if depth limit is reached
		return board;
	} else {
		moves = board->list_all_moves();
		for (vector<Board*>::iterator it = moves->begin(); it != moves->end(); it++) {
			move = MinMove(*it, depth_limit, depth+1);
			if (best_move == NULL || move->evaluate_board(Black)
					> best_move->evaluate_board(Black)) {
				best_move = move;
				best_real_move = *it;
			}
		}
		return best_real_move;
	}
}
Board* MinMove(Board* board, short int depth_limit, short int depth) {
	vector<Board*> *moves;
	Board* best_move = NULL;
	Board* best_real_move = NULL;
	Board* move = NULL;

	if (depth >= depth_limit) {//if depth limit is reached
		return board;
	} else {
		moves = board->list_all_moves();
		for (vector<Board*>::iterator it = moves->begin(); it != moves->end(); it++) {
			move = MaxMove(*it, depth_limit, depth+1);
			if (best_move == NULL || move->evaluate_board(White)
					< best_move->evaluate_board(White)) {
				best_move = move;
				best_real_move = *it;
			}
		}
		return best_real_move;
	}
}

Board* ABMinMax(Board* board, short int depth_limit) {
	return ABMaxMove(board, depth_limit, 1, 0, 0);
}
Board* ABMaxMove(Board* board, short int depth_limit, short int depth, int a, int b) {
	vector<Board*> *moves;
	Board* best_move = NULL;
	Board* best_real_move = NULL;
	Board* move = NULL;
	int alpha = a,beta = b;

	if (depth >= depth_limit) {//if depth limit is reached
		return board;
	} else {
		moves = board->list_all_moves();
		for (vector<Board*>::iterator it = moves->begin(); it != moves->end(); it++) {
			move = ABMinMove(*it, depth_limit, depth+1, alpha, beta);
			if (best_move == NULL || move->evaluate_board(Black)
					> best_move->evaluate_board(Black)) {
				best_move = move;
				best_real_move = *it;
				alpha = move->evaluate_board(Black);
			}
			if(beta > alpha){
				return best_real_move;
			}
		}
		return best_real_move;
	}
}
Board* ABMinMove(Board* board, short int depth_limit, short int depth, int a, int b) {
	vector<Board*> *moves;
	Board* best_move = NULL;
	Board* best_real_move = NULL;
	Board* move = NULL;
	int alpha = a,beta = b;

	if (depth >= depth_limit) {//if depth limit is reached
		return board;
	} else {
		moves = board->list_all_moves();
		for (vector<Board*>::iterator it = moves->begin(); it != moves->end(); it++) {
			move = ABMaxMove(*it, depth_limit, depth+1, alpha, beta);
			if (best_move == NULL || move->evaluate_board(White)
					< best_move->evaluate_board(White)) {
				best_move = move;
				best_real_move = *it;
				beta = move->evaluate_board(White);
			}
			if(beta < alpha){
				return best_real_move;
			}
		}
		return best_real_move;
	}
}

#endif
