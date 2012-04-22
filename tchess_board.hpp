//============================================================================
// Name        : tchess_board.hpp
// Author      : Dogukan Cagatay
// E-mail	   : dcagatay@gmail.com
// Description : Terminal chess game board definition and implementation.
//============================================================================

#ifndef TCHESS_BOARD_HPP
#define TCHESS_BOARD_HPP

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>
#include "tchess_piece.hpp"

#define CHESS_BOARD_SIZE 8

class Board {
public:
	Board() {
		//allocate the vector
		board.resize(CHESS_BOARD_SIZE);
		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				board[i].push_back(NULL);
			}
		}
	}
	void initialize() {
		Piece* x;
		turn = false; //white's turn in the beginning

		//initialize the board configuration
		// put white pieces
		x = new Rook(White);
		board[0][0] = x;
		x = new Knight(White);
		board[0][1] = x;
		x = new Bishop(White);
		board[0][2] = x;
		x = new Queen(White);
		board[0][3] = x;
		x = new King(White);
		board[0][4] = x;
		x = new Bishop(White);
		board[0][5] = x;
		x = new Knight(White);
		board[0][6] = x;
		x = new Rook(White);
		board[0][7] = x;
		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			x = new Pawn(White);
			board[1][i] = x;
		}

		//put spaces
		for (int i = 2; i < 6; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				board[i][j] = NULL;
			}
		}

		//put black pieces
		x = new Rook(Black);
		board[7][0] = x;
		x = new Knight(Black);
		board[7][1] = x;
		x = new Bishop(Black);
		board[7][2] = x;
		x = new Queen(Black);
		board[7][3] = x;
		x = new King(Black);
		board[7][4] = x;
		x = new Bishop(Black);
		board[7][5] = x;
		x = new Knight(Black);
		board[7][6] = x;
		x = new Rook(Black);
		board[7][7] = x;
		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			x = new Pawn(Black);
			board[6][i] = x;
		}
		w_pieces_number.resize(6);
		w_pieces_number[pawn] = 8;
		w_pieces_number[rook] = 2;
		w_pieces_number[bishop] = 2;
		w_pieces_number[knight] = 2;
		w_pieces_number[queen] = 1;
		w_pieces_number[king] = 1;

		b_pieces_number.resize(6);
		b_pieces_number[pawn] = 8;
		b_pieces_number[rook] = 2;
		b_pieces_number[bishop] = 2;
		b_pieces_number[knight] = 2;
		b_pieces_number[queen] = 1;
		b_pieces_number[king] = 1;
	}
	Board(Board *b) {
		//allocate the vector
		board.resize(CHESS_BOARD_SIZE);
		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				board[i].push_back(NULL);
			}
		}
		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				set_piece(i, j, b->get_piece(i, j));
			}
		}
		//set parent of the new object
		set_parent(b);
		//set turn of the new object
		turn = !b->get_turn();

		//set piece numbers
		w_pieces_number.resize(6);
		w_pieces_number[pawn] = b->get_piece_number(pawn, White);
		w_pieces_number[rook] = b->get_piece_number(rook, White);
		w_pieces_number[bishop] = b->get_piece_number(bishop, White);
		w_pieces_number[knight] = b->get_piece_number(knight, White);
		w_pieces_number[queen] = b->get_piece_number(queen, White);
		w_pieces_number[king] = b->get_piece_number(king, White);

		b_pieces_number.resize(6);
		b_pieces_number[pawn] = b->get_piece_number(pawn, Black);
		b_pieces_number[rook] = b->get_piece_number(rook, Black);
		b_pieces_number[bishop] = b->get_piece_number(bishop, Black);
		b_pieces_number[knight] = b->get_piece_number(knight, Black);
		b_pieces_number[queen] = b->get_piece_number(queen, Black);
		b_pieces_number[king] = b->get_piece_number(king, Black);
	}
	short int get_piece_number(PieceType type, PieceColor color) {
		if (color == White) {
			return w_pieces_number[type];
		} else {
			return b_pieces_number[type];
		}
	}
	void set_piece_number(PieceType type, PieceColor color, int value) {
		if (color == White) {
			w_pieces_number[type] += value;
		} else {
			b_pieces_number[type] += value;
		}
	}
	void print() {
		//		cout << "  01234567" << endl;
		cout << "  a b c d e f g h" << endl;
		for (int i = CHESS_BOARD_SIZE - 1; i >= 0; --i) {
			//			cout << i << " ";
			cout << i + 1 << " ";
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				if (board[i][j] != NULL) {
					board[i][j]->print();
				} else {
					wcout << L"- ";
				}
			}
			if (i == 6 && get_turn()) { // black's turn
				cout << "	B";
			} else if (i == 1 && !get_turn()) { //white's turn
				cout << "	W";
			}
			cout << endl;
		}
		cout << endl;
	}

	Piece* get_piece(short int x, short int y) {
		return board[x][y];
	}
	void set_piece(short int x, short int y, Piece* p) {
		board[x][y] = p;
	}
	bool get_turn() {
		return turn;
	}
	vector<vector<Piece*> > get_board() {
		return board;
	}
	Board* move_piece(short int src_x, short int src_y, short int dest_x,
			short int dest_y) {
		Board *new_board = new Board(this);

		Piece* src = new_board->get_piece(src_x, src_y);
		Piece* dest = new_board->get_piece(dest_x, dest_y);
		if (dest != NULL) { //in case of a yime
			new_board->set_piece_number(dest->get_type(), dest->get_color(), -1);
		}

		new_board->set_piece(dest_x, dest_y, src);
		new_board->set_piece(src_x, src_y, NULL);

		return new_board;
	}
	Board* just_move_piece(short int src_x, short int src_y, short int dest_x,
			short int dest_y) { //to set up a conf
		Board *new_board = new Board(this);
		new_board->set_piece(dest_x, dest_y, new_board->get_piece(src_x, src_y));
		new_board->set_piece(src_x, src_y, NULL);
		return new_board;
	}
	Board* move(short int src_x, short int src_y, short int dest_x,
			short int dest_y) {
		//Board *new_board = new Board(this);
		Piece* src = get_piece(src_x, src_y);
		Piece* dest = get_piece(dest_x, dest_y);

		if (src == NULL) {
			cout << "Source is null." << endl;
			return NULL;
		}

		if (src_x == dest_x && src_y == dest_y) {
			cout << "Source is equal to destination." << endl;
			return NULL;
		}

		//turn check
		if (!get_turn() && src->get_color() != White) { //white's turn black cannot move
			cout << "It's White's turn wait yours." << endl;
			return NULL;
		} else if (get_turn() && src->get_color() != Black) {
			cout << "It's Black's turn wait yours.." << endl;
			return NULL;
		}

		if (src->get_type() == pawn) {
			if (src->get_color() == White) {
				if ((src_x - dest_x) == -1) {// move forward one step
					if (src_y == dest_y && dest == NULL) {// if there is no horizontal move and there is no piece then this is valid.
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else if (abs(src_y - dest_y) == 1 && dest != NULL
							&& dest->get_color() == Black) { //if there is a enemy in the diameter is valid.
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else {
						//						cout << "Pawn cannot move.Err:1" << endl;
						return NULL;
					}
				} else {
					//					cout << "Pawn cannot move.Err:2" << endl;
					return NULL;
				}
			} else {//if black
				if ((src_x - dest_x) == 1) {// move forward one step
					if (src_y == dest_y && dest == NULL) {// if there is no horizontal move and there is no piece then this is valid.
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else if (abs(src_y - dest_y) == 1 && dest != NULL
							&& dest->get_color() == White) { //if there is a enemy in the diameter is valid.
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else {
						//						cout << "Pawn cannot move.Err:3" << endl;
						return NULL;
					}
				} else {
					//					cout << "Pawn cannot move.Err:4" << endl;
					return NULL;
				}
			}
		} else if (src->get_type() == rook) {
			//black and white is the same
			if (src_x == dest_x) {//if horizontal
				if (dest_y > src_y) { //move to right
					for (int i = src_y + 1; i < dest_y; ++i) {
						if (get_piece(src_x, i) != NULL) {//if there is a piece between the dest and src
							//							cout << "Rook cannot move.Err:3" << endl;
							return NULL;
						}
					}
				} else if (dest_y < src_y) { // move to left
					for (int i = src_y - 1; i > dest_y; --i) {
						if (get_piece(src_x, i) != NULL) {//if there is a piece between the dest and src
							//							cout << "Rook cannot move.Err:4" << endl;
							return NULL;
						}
					}
				}
				//then no piece in between
				//if the dest is enemy then eat it =D
				if (dest == NULL) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else if (dest->get_color() != src->get_color()) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else {//cannot eat the same color
					//					cout << "Rook cannot move.Err:5" << endl;
					return NULL;
				}
			} else if (src_y == dest_y) {//if vertical
				if (dest_x > src_x) { //move up
					for (int i = src_x + 1; i < dest_x; ++i) {
						if (get_piece(i, src_y) != NULL) {//if there is a piece between the dest and src
							//							cout << "Rook cannot move.Err:6" << endl;
							return NULL;
						}
					}
				} else if (dest_x < src_x) { //move down
					for (int i = src_x - 1; i > dest_x; --i) {
						if (get_piece(i, src_y) != NULL) {//if there is a piece between the dest and src
							//							cout << "Rook cannot move.Err:7" << endl;
							return NULL;
						}
					}
				}
				//then no piece in between
				//if the dest is enemy then eat it =D
				if (dest == NULL) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else if (dest->get_color() != src->get_color()) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else {//cannot eat the same color
					//					cout << "Rook cannot move.Err:8" << endl;
					return NULL;
				}
			} else {
				//				cout << "Rook cannot move. Err:3" << endl;
				return NULL;
			}
		} else if (src->get_type() == bishop) {
			//black or white it it the same
			if (abs(src_x - dest_x) == abs(src_y - dest_y)) { //difference should be the same
				if (dest_x > src_x) {
					if (dest_y > src_y) {//move right-top
						for (int i = 1; i < abs(dest_x - src_x); ++i) {
							if (get_piece(src_x + i, src_y + i) != NULL) {//there is a piece in between
								//								cout << "Bishop cannot move. Err:1" << endl;
								return NULL;
							}
						}
					} else if (dest_y < src_y) {// move right-bottom
						for (int i = 1; i < abs(dest_x - src_x); ++i) {
							if (get_piece(src_x + i, src_y - i) != NULL) {//there is a piece in between
								//								cout << "Bishop cannot move. Err:2" << endl;
								return NULL;
							}
						}
					} else {
						//						cout << "Bishop cannot move. Err:3" << endl;
						return NULL;
					}
					//then no piece in between
					//if the dest is enemy then eat it =D
					if (dest == NULL) {
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else if (dest->get_color() != src->get_color()) {
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else {//cannot eat the same color
						//						cout << "Bishop cannot move.Err:4" << endl;
						return NULL;
					}
				} else if (dest_x < src_x) {
					if (dest_y > src_y) {//move left-top
						for (int i = 1; i < abs(dest_x - src_x); ++i) {
							if (get_piece(src_x - i, src_y + i) != NULL) {//there is a piece in between
								//								cout << "Bishop cannot move. Err:5" << endl;
								return NULL;
							}
						}
					} else if (dest_y < src_y) {// move left-bottom
						for (int i = 1; i < abs(dest_x - src_x); ++i) {
							if (get_piece(src_x - i, src_y - i) != NULL) {//there is a piece in between
								//								cout << "Bishop cannot move. Err:6" << endl;
								return NULL;
							}
						}
					} else {
						//						cout << "Bishop cannot move. Err:7" << endl;
						return NULL;
					}
					//then no piece in between
					//if the dest is enemy then eat it =D
					if (dest == NULL) {
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else if (dest->get_color() != src->get_color()) {
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else {//cannot eat the same color
						//						cout << "Bishop cannot move.Err:8" << endl;
						return NULL;
					}
				} else {
					//					cout << "Bishop cannot move. Err:9" << endl;
					return NULL;
				}
			} else {
				//				cout << "Bishop cannot move. Err:10" << endl;
				return NULL;
			}
		} else if (src->get_type() == knight) {
			if (abs(dest_x - src_x) == 2 && abs(dest_y - src_y) == 1) {
				if (dest == NULL) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else if (dest->get_color() != src->get_color()) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else {// cannot eat the same color
					//					cout << "Knight cannot move. Err:9" << endl;
					return NULL;
				}
			} else if (abs(dest_x - src_x) == 1 && abs(dest_y - src_y) == 2) {
				if (dest == NULL) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else if (dest->get_color() != src->get_color()) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else {// cannot eat the same color
					//					cout << "Knight cannot move. Err:10" << endl;
					return NULL;
				}
			} else {// invalid move for knight
				//				cout << "Knight cannot move. Err:11" << endl;
				return NULL;
			}
		} else if (src->get_type() == queen) {
			if (src_x == dest_x) {//if horizontal
				if (dest_y > src_y) { //move to right
					for (int i = src_y + 1; i < dest_y; ++i) {
						if (get_piece(src_x, i) != NULL) {//if there is a piece between the dest and src
							//							cout << "Queen cannot move.Err:1" << endl;
							return NULL;
						}
					}
				} else if (dest_y < src_y) { // move to left
					for (int i = src_y - 1; i > dest_y; --i) {
						if (get_piece(src_x, i) != NULL) {//if there is a piece between the dest and src
							//							cout << "Queen cannot move.Err:2" << endl;
							return NULL;
						}
					}
				}
				//then no piece in between
				//if the dest is enemy then eat it =D
				if (dest == NULL) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else if (dest->get_color() != src->get_color()) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else {//cannot eat the same color
					//					cout << "Queen cannot move.Err:3" << endl;
					return NULL;
				}
			} else if (src_y == dest_y) {//if vertical
				if (dest_x > src_x) { //move up
					for (int i = src_x + 1; i < dest_x; ++i) {
						if (get_piece(i, src_y) != NULL) {//if there is a piece between the dest and src
							//							cout << "Queen cannot move.Err:4" << endl;
							return NULL;
						}
					}
				} else if (dest_x < src_x) { //move down
					for (int i = src_x - 1; i > dest_x; --i) {
						if (get_piece(i, src_y) != NULL) {//if there is a piece between the dest and src
							//							cout << "Queen cannot move.Err:5" << endl;
							return NULL;
						}
					}
				}
				//then no piece in between
				//if the dest is enemy then eat it =D
				if (dest == NULL) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else if (dest->get_color() != src->get_color()) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else {//cannot eat the same color
					//					cout << "Queen cannot move.Err:6" << endl;
					return NULL;
				}
			} //black or white it it the same
			else if (abs(src_x - dest_x) == abs(src_y - dest_y)) { //difference should be the same
				if (dest_x > src_x) {
					if (dest_y > src_y) {//move right-top
						for (int i = 1; i < abs(dest_x - src_x); ++i) {
							if (get_piece(src_x + i, src_y + i) != NULL) {//there is a piece in between
								//								cout << "Queen cannot move. Err:7" << endl;
								return NULL;
							}
						}
					} else if (dest_y < src_y) {// move right-bottom
						for (int i = 1; i < abs(dest_x - src_x); ++i) {
							if (get_piece(src_x + i, src_y - i) != NULL) {//there is a piece in between
								//								cout << "Queen cannot move. Err:8" << endl;
								return NULL;
							}
						}
					} else {
						//						cout << "Queen cannot move. Err:9" << endl;
						return NULL;
					}
					//then no piece in between
					//if the dest is enemy then eat it =D
					if (dest == NULL) {
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else if (dest->get_color() != src->get_color()) {
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else {//cannot eat the same color
						//						cout << "Queen cannot move.Err:10" << endl;
						return NULL;
					}
				} else if (dest_x < src_x) {
					if (dest_y > src_y) {//move left-top
						for (int i = 1; i < abs(dest_x - src_x); ++i) {
							if (get_piece(src_x - i, src_y + i) != NULL) {//there is a piece in between
								//								cout << "Queen cannot move. Err:11" << endl;
								return NULL;
							}
						}
					} else if (dest_y < src_y) {// move left-bottom
						for (int i = 1; i < abs(dest_x - src_x); ++i) {
							if (get_piece(src_x - i, src_y - i) != NULL) {//there is a piece in between
								//								cout << "Queen cannot move. Err:12" << endl;
								return NULL;
							}
						}
					} else {
						//						cout << "Queen cannot move. Err:13" << endl;
						return NULL;
					}
					//then no piece in between
					//if the dest is enemy then eat it =D
					if (dest == NULL) {
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else if (dest->get_color() != src->get_color()) {
						return move_piece(src_x, src_y, dest_x, dest_y);
					} else {//cannot eat the same color
						//						cout << "Queen cannot move.Err:14" << endl;
						return NULL;
					}
				} else {
					//					cout << "Queen cannot move. Err:15" << endl;
					return NULL;
				}
			} else {
				//				cout << "Queen cannot move. Err:16" << endl;
				return NULL;
			}
		} else if (src->get_type() == king) {
			if (abs(dest_x - src_x) == 1 && abs(dest_y - src_y) == 1) { //diagonal move
				if (dest == NULL || dest->get_color() != src->get_color()) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else {// cannot eat the same color
					//					cout << "King cannot move. Err:15" << endl;
					return NULL;
				}
			} else if (abs(dest_x - src_x) == 1 && dest_y - src_y == 0) { //vertical move
				if (dest == NULL || dest->get_color() != src->get_color()) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else {// cannot eat the same color
					//					cout << "King cannot move. Err:15" << endl;
					return NULL;
				}
			} else if (abs(dest_y - src_y) == 1 && dest_x - src_x == 0) {
				if (dest == NULL || dest->get_color() != src->get_color()) {
					return move_piece(src_x, src_y, dest_x, dest_y);
				} else {// cannot eat the same color
					//					cout << "King cannot move. Err:15" << endl;
					return NULL;
				}
			} else {// invalid move for king
				//				cout << "King cannot move. Err:16" << endl;
				return NULL;
			}
		} else {
			return NULL;
		}

		return NULL;
	}
	//	vector<Board*> list_all_moves(){
	//		return ;
	//	}
	Board* get_parent() {
		return parent;
	}
	void set_parent(Board* parent) {
		this->parent = parent;
	}
	int evaluate_board(PieceColor color) {
		int eval = 0;
		eval += (Pawn::eval_value * get_piece_number(pawn, color));
		eval += (Rook::eval_value * get_piece_number(rook, color));
		eval += (Knight::eval_value * get_piece_number(knight, color));
		eval += (Bishop::eval_value * get_piece_number(bishop, color));
		eval += (Queen::eval_value * get_piece_number(queen, color));
		eval += (King::eval_value * get_piece_number(king, color));
		return eval;
	}
	vector<Board*>* list_all_moves() {
		vector<Board*> *moves = new vector<Board*> ();
		Board* temp = NULL;
		PieceColor turn = get_turn() ? Black : White;

		for (int i = 0; i < CHESS_BOARD_SIZE; ++i) {
			for (int j = 0; j < CHESS_BOARD_SIZE; ++j) {
				if (get_piece(i, j) != NULL && get_piece(i, j)->get_color()
						== turn) {
					for (int k = 0; k < CHESS_BOARD_SIZE; ++k) {
						for (int l = 0; l < CHESS_BOARD_SIZE; ++l) {
							if (i == k && j == l) {
								continue;
							}
							if ((temp = move(i, j, k, l)) != NULL) {
								moves->push_back(temp);
							}
						}
					}
				}
			}
		}

		return moves;
	}
private:
	vector<vector<Piece*> > board;
	Board* parent;
	bool turn;
	vector<short int> w_pieces_number;
	vector<short int> b_pieces_number;
};

#endif