/*
 * chess.cpp
 *
 *  Created on: Mar 30, 2017
 *      Author: Andrew Ratz
 * 		Secondary Authors: Brian Barker, Ruojia Xu, Susanna Yau
 */



//Changelog - Bishop/Queen movement, Promotions, AI (it's a start)
#include <iostream>
#include <string>
#include <cstdlib>

#include <stdio.h>
#include "board.h"

//////////////////////////////////////////Implementation of board.h

void setup(void) {
	/*Resets the values that check whether a piece has moved yet or not (applies to pawns because they can move to spaces on their first move,
	and rooks because they are used in castling*/
	wpawn1.MovedReset();
	wpawn2.MovedReset();
	wpawn3.MovedReset();
	wpawn4.MovedReset();
	wpawn5.MovedReset();
	wpawn6.MovedReset();
	wpawn7.MovedReset();
	wpawn8.MovedReset();
	bpawn1.MovedReset();
	bpawn2.MovedReset();
	bpawn3.MovedReset();
	bpawn4.MovedReset();
	bpawn5.MovedReset();
	bpawn6.MovedReset();
	bpawn7.MovedReset();
	bpawn8.MovedReset();
	wking.MovedReset();
	bking.MovedReset();
	wrook.MovedReset();
	brook.MovedReset();
	//Resets the board to its default state
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			board[i][j] = initialize[i][j];
		}
	}
}

//Adds captured pieces to the captured pieces list (only adds pieces you capture, if in cpu mode)
void addCaptured(string color,string display){
	captured.push_back(make_pair(color,display));
}

//Outputs the captured pieces list
void displayCaptured(void){
	for ( vector < pair<string,string> >::const_iterator it = captured.begin() ; it != captured.end(); it++){
        cout << it->first << " " << it->second << endl;
    }
}

/*Takes in the coordinates of each position around the king (8 positions + the king's current position), if all testmates return true
then the king is in checkmate and the game ends*/
bool testmate(int e, int f, int modf_e, int modf_f, Piece *king, string color) {
	//e and f are the king's current coordinates, modf_e and modf_f are the modified coordinates it would potentially move to
		//If the king is along a border of the board, return true because the king can't move off the board
		if (modf_e < 0 || modf_f < 0 || modf_e > 7 || modf_f > 7) {
			return true;
		}
		//If the king would be moviong in bounds
		if (modf_e >= 0 && modf_f >= 0 && modf_e <= 7 && modf_f <= 7) {
		//If the move is a valid move that the king can make (not more than 1 square in any direction)
		if (king->moveCheck(e, f, modf_e, modf_f, board) == true) {
		//Checking if any enemy pieces can attack the king due to moving piece
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Piece *enemypiece = board[i][j];
				//If selected piece is not an enemy piece, restart the loop
				if ((enemypiece->getColor() == color) || enemypiece->getColor() == "gray") {
					continue;
				}
				//If enemy piece is selected
				else {
					//If not a pawn, just check if the piece can move to the king's proposed location
					if (enemypiece->getDisplay() != "P") {
						if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
							return true;
						}
						//This section checks for if a friendly piece gets captured, would that make the king go into check in that position
						//Bishop
						if (board[modf_f][modf_e]->getDisplay() == "B") {
							if (board[modf_f][modf_e]->getColor() == "white") {
									board[modf_f][modf_e] = new Bishop("black", "B");
									if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
										delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &wbishop;
										return true;
									}
									delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &wbishop;
								}
							if (board[modf_f][modf_e]->getColor() == "black") {
									board[modf_f][modf_e] = new Bishop("white", "B");
										if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
											delete board[modf_f][modf_e];
											board[modf_f][modf_e] = &bbishop;
											return true;
									}
									delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &bbishop;
								}
							}
						//Rook
						if (board[modf_f][modf_e]->getDisplay() == "R") {
							if (board[modf_f][modf_e]->getColor() == "white") {
									board[modf_f][modf_e] = new Rook("black", "R");
									if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
										delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &wrook;
										return true;
									}
									delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &wrook;
								}
							if (board[modf_f][modf_e]->getColor() == "black") {
									board[modf_f][modf_e] = new Rook("white", "R");
										if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
											delete board[modf_f][modf_e];
											board[modf_f][modf_e] = &brook;
											return true;
									}
									delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &brook;

								}
							}
						//Knight
						if (board[modf_f][modf_e]->getDisplay() == "N") {
							if (board[modf_f][modf_e]->getColor() == "white") {
									board[modf_f][modf_e] = new Knight("black", "N");
									if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
										delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &wknight;
										return true;
									}
									delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &wknight;
								}
							if (board[modf_f][modf_e]->getColor() == "black") {
									board[modf_f][modf_e] = new Knight("white", "N");
										if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
											delete board[modf_f][modf_e];
											board[modf_f][modf_e] = &bknight;
											return true;
									}
									delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &bknight;
								}
							}
						//Queen
						if (board[modf_f][modf_e]->getDisplay() == "Q") {
							if (board[modf_f][modf_e]->getColor() == "white") {
									board[modf_f][modf_e] = new Queen("black", "Q");
									if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
									delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &wqueen;
										return true;
									}
									delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &wqueen;
								}
							if (board[modf_f][modf_e]->getColor() == "black") {
									board[modf_f][modf_e] = new Queen("white", "Q");
										if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
											delete board[modf_f][modf_e];
											board[modf_f][modf_e] = &bqueen;
											return true;
									}
									delete board[modf_f][modf_e];
									board[modf_f][modf_e] = &bqueen;
								}
							}
						}
					//If enemy piece is a pawn, check if it can diagonally attack the pawn
					if (enemypiece->getDisplay() == "P") {
						if (enemypiece->getColor() == "white" && (modf_f-i) == 1 && abs(modf_e-j) == 0) {
							return false;
						}
						if (enemypiece->getColor() == "black" && (modf_f-i) == 1 && abs(modf_e-j) == 0) {
							return false;
						}
						else {
							if (enemypiece->moveCheck(j, i, modf_e, modf_f, board) == true) {
								return true;
						}
					}
				}
				}
			}
		}
	}
	else {
		return true;
	}
	}
	return false;
}

//Checks if check can be resolved by having a friendly piece other than the king save the king
bool fixablecheck(string color, int e, int f) {
	Piece *attacker;
	Piece *defender;
	//Locates the attacker
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			//Find piece that is attacking king
			if (board[j][i]->getColor() == color || board[j][i]->getColor() == "gray") {
				continue;
			}
			else {
				attacker = board[j][i];
				//Located the defender
					for (int k = 0; k < 8; k++) {
						for (int l = 0; l < 8; l++) {
							if (board[l][k]->getColor() == color) {
								defender = board[l][k];
								//If defender can attack the attacker, return true, meaning that the check is fixable
								if (defender->moveCheck(l, k, i, j, board) == true) {
									if (defender->getDisplay() != "K") {
										return true;
									}
								}
							}
						}
					}
				}
			}
		}
	//Otherwise, the check is not fixable
	return false;
}

//Pushes out a notification when checkmate has occurred
void notifyofcheckmate(string color) {
	//Locates the king of the specified color
	int e;
	int f;
	Piece *king;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[j][i]->getDisplay() == "K" && board[j][i]->getColor() == color) {
				king = board[j][i];
				e = i;
				f = j;
				break;
			}
			else {
				continue;
			}
		}
	}
	//Now that king is located, check which spots it could, in an ideal situation, move to
	bool check[9] = {false, false, false, false, false, false, false, false, false};
	//Recall that testmate checks for check in a proposed location
	check[0] = testmate(e, f, e+1, f+1, king, color);
	check[1] = testmate(e, f, e+1, f, king, color);
	check[2] = testmate(e, f, e+1, f-1, king, color);
	check[3] = testmate(e, f, e, f+1, king, color);
	check[4] = testmate(e, f, e, f, king, color);
	check[5] = testmate(e, f, e, f-1, king, color);
	check[6] = testmate(e, f, e-1, f+1, king, color);
	check[7] = testmate(e, f, e-1, f, king, color);
	check[8] = testmate(e, f, e-1, f-1, king, color);
	//If king is in check everywhere but its current position
	if (check[0] == true && check[1] == true && check[2] == true && check[3] == true && check[4] == false && check[5] == true && check[6] == true && check[7] == true && check[8] == true) {
		//Check if king is only piece on player's side
		int colorpieces = 0;
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				if (board[x][y]->getColor() == color) {
					colorpieces++;
				}
			}
		}
		//If king is only piece left and king is in check everywhere but its current position, return stalemate
		if (colorpieces == 1) {
			cout << "Stalemate" << endl;
			exit(0);
		}
	}
	bool checkmate = false;;
	//If king is in check everywhere it could move including its current position
	if (check[0] == true && check[1] == true && check[2] == true && check[3] == true && check[4] == true && check[5] == true && check[6] == true && check[7] == true && check[8] == true) {
		//Then it's checkmate
		checkmate = true;
	}
	//But if a check is fixable
	if (fixablecheck(color, e, f) == true) {
		//Then it's not checkmate
		checkmate = false;
		return;
	}
	//Inform the player that it is checkmate if checkmate is true
	if (checkmate == true) {
		if (color == "white") {
			cout << "Checkmate - Black Wins" << endl;
		}
		if (color == "black") {
			cout << "Checkmate - White Wins" << endl;
		}
		//Terminate the program
		exit(0);
	}
}

//Pushes out a notification when a king is in check
void notifyofcheck(string color) {
	bool check;
	int e;
	int f;
	//Locates the king
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[j][i]->getDisplay() == "K" && board[j][i]->getColor() == color) {
				e = i;
				f = j;
				break;
			}
			else {
				continue;
			}
		}
	}
	//Checking if any enemy pieces can attack the king due to moving piece
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece *enemypiece = board[i][j];
			if ((enemypiece->getColor() == color) || enemypiece->getColor() == "gray") {
				continue;
			}
			else {
				//If enemy piece can attack king, then check is true
				check = enemypiece->moveCheck(j, i, e, f, board);
				if (check == true) {
				//Determines whether king is in checkmate or stalemate
				notifyofcheckmate(color);
				//Informs player that a king is in check
					if (color == "white") {
						cout << "White's King is in check" << endl;
					}
					if (color == "black") {
						cout << "Black's King is in check" << endl;
					}
				}
			}
		}
	}
}

//Checks if any enemy pieces can attack a specified space
bool checkForCheck(string color, int c, int d) {
	bool check;
	//Locates enemy piece
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece *enemypiece = board[i][j];
			if ((enemypiece->getColor() == color) || enemypiece->getColor() == "gray") {
				continue;
			}
			else {
				//If piece can move to the space, return true
				if (enemypiece->getDisplay() != "P") {
					check = enemypiece->moveCheck(j, i, c, d, board);
					if (check == true) {
						return true;
					}
				}
				//If a pawn, check if pawn can attack the space, or move there normally
				if (enemypiece->getDisplay() == "P") {
					if (enemypiece->getColor() == "white" && (d-i) == 1 && abs(c-j) == 1) {
						check = true;
					}
					if (enemypiece->getColor() == "black" && (i-d) == 1 && abs(c-j) == 1) {
						check = true;
					}
					else {
						check = enemypiece->moveCheck(j, i, c, d, board);
					}
				}
				//Returns true if check is true
				if (check == true) {
					return true;
				}
			}
		}
	}
	return false;
}

//Prints the help menu
void helpMenu(void){
    cout << "\nWhat do you need help with?" << endl;
    cout << "1. Rules of chess\n2. Chess pieces" << endl;
    int inputChoice = 0;
    cin >> inputChoice;
    if (inputChoice == 1){
        cout << "\nBasic rules:" << endl;
        cout << "- The goal of the game is to checkmate (threaten the opponent's king with inevitable capture)." << endl;
        cout << "- White moves first, then the players alternate until a king is checkmated, a player resigns, or a draw is declared." << endl;
        cout << "- No one can skip a turn; making a move is required." << endl;
        cout << "- Each type of chess piece has a different pattern of movement, and a piece moves to a vacant square except when capturing an opponent's piece." << endl;
        cout << "- A piece is captured when an attacking enemy piece replaces it on its square, except in the case of en passant. The king cannot be captured, but can be placed in check, which is when a king is under threat of capture on the opponent's next turn.\n" << endl;
    	cout << "Type 'print' when done reading to resume play." << endl;
    }
    else if (inputChoice == 2){
        cout << "\nWhich chess piece do you want to know about?" << endl;
        cout << "1. King\n2. Queen\n3. Rook\n4. Bishop\n5. Knight\n6. Pawn" << endl;
        int pieceChoice = 0;
        cin >> pieceChoice;
        if (pieceChoice == 1){
            cout << "King:\nMovement - Can move one square in any direction unless the square is already occupied by a friendly piece or the move would place the king in check.*" << endl;
            cout << "*The king may make a special move called castling, in which the king moves two squares toward one of its rooks and then the rook is placed on the square over which the king crossed.\n" << endl;
        }
        else if (pieceChoice == 2){
            cout << "Queen:\nMovement - Can move any number of unoccupied squares in a straight line vertically, horizontally, or diagonally.\n" << endl;
        }
        else if (pieceChoice == 3){
            cout << "Rook:\nMovement - Can move horizontally or vertically through any number of unoccupied squares.\n" << endl;
        }
        else if (pieceChoice == 4){
            cout << "Bishop:\nMovement - Can move diagonally through any number of unoccupied squares.\n" << endl;
        }
        else if (pieceChoice == 5){
            cout << "Knight:\nMovement - Can move in an L-shape, in other words, it can move to a square that is two squares away horizontally and one square vertically, or two squares vertically and one square horizontally.\n" << endl;
        }
        else if (pieceChoice == 6){
            cout << "Pawn:\nMovement - Can not move backwards. Normally moves by advancing a single square, but the first time a pawn is moved, it can move two unoccupied squares instead of one." << endl;
            cout << "Capturing - Catptures diagonally forward one square to the left or right.*" << endl;
            cout << "*The pawn may make a special capture called en passant, which occurs after a pawn advances two squares using its initial two-step move option, and the square passed over is attacked by an enemy pawn." << endl;
            cout << "Promotion - A pawn that advances all the way to the opposite side of the board is replaced by another piece of that player's choice: queen, rook, bishop, or knight of the same color.\n" << endl;
        }
        else{
            cout << "Invalid choice" << endl;
        }
    cout << "Type 'print' when done reading to resume play." << endl;
    }
    else{
        cout << "Invalid choice" << endl;
    }
}

//Prints out the board
void printboard(void) {
	//Horizontal divider handles horizontal black bars
	int horizontal_divider_count = 0;
	int a, b;
	Piece *piece;
	//Toggle hands the alternating colors of the board
	int toggle = 0;
	//The horizontal grid that shows letter coordinates
	string lgrid[8] = {" a  ", " b  ", " c  ", " d  ", " e  ", " f  ", " g  ", " h  "};
	int ngrid = 8;
	//Outputs the letter grid at the top of the board
	cout << "  " << lgrid[0] << lgrid[1] << lgrid[2] << lgrid[3] << lgrid[4] << lgrid[5] << lgrid[6] << lgrid[7];
	//Prints each position one at a time
	for (a = 7; a > -1; a--) {
		cout << endl;
		//Outputs a number at the start of each row (forms the left hand side number grid)
		cout << ngrid << " ";
		//Vertical divider handles vertical black bars
		int vertical_divider_count = 0;
		for (b = 0; b < 8; b++) {
			//Selects a piece
			piece = board[a][b];
			//If toggle is even
			if (toggle % 2 == 0) {
				//If a white piece, output white text
				if (piece->getColor() == "white") {
					cout << "\e[0;37;41m " << piece->getDisplay() << " \e[0;0;0m";
				}
				//If a black piece, output black text
				else if (piece->getColor() == "black") {
					cout << "\e[0;30;41m " << piece->getDisplay() << " \e[0;0;0m";
				}
				//Otherwise, output gray text
				else {
					cout << "\e[0;90;41m " << piece->getDisplay() << " \e[0;0;0m";
				}
				//Note that the color is 41 when toggle is even
			}
			//If toggle is odd
			else {
				//If a white piece, output white text
				if (piece->getColor() == "white") {
					cout << "\e[0;37;101m " << piece->getDisplay() << " \e[0;0;0m";
				}
				//If a black piece, output black text
				else if (piece->getColor() == "black") {
					cout << "\e[0;30;101m " << piece->getDisplay() << " \e[0;0;0m";
				}
				//Otherwise, output gray text
				else {
					cout << "\e[0;90;101m " << piece->getDisplay() << " \e[0;0;0m";
				}
				//Note that the color is 101 when toggle is odd
			}
			//Handles the black spacing between columns
			if (vertical_divider_count < 7) {
				cout << "\e[0;40m" << " " << "\e[0;0;0m";
				vertical_divider_count++;
			}
			//Increments the color toggle
			toggle++;
		}
		//Outputs the right hand side number grid
		cout << " " << ngrid;
		ngrid--;
		cout << endl;
		//Handles the black spacing between rows
		if (horizontal_divider_count < 7) {
			cout << "  \e[0;40m" << "                               " << "\e[0;0;0m";
			horizontal_divider_count++;
		}
		//Increments the color toggle
		toggle++;
	}
	//Outputs the bottom letter grid
	cout << "  " << lgrid[0] << lgrid[1] << lgrid[2] << lgrid[3] << lgrid[4] << lgrid[5] << lgrid[6] << lgrid[7];
	cout << endl << endl;
}

//Checks if moving any piece (king or otherwise) would put the king in check
bool movewouldcausecheck(int a, int b, int c, int d) {
	Piece *movingpiece = board[b][a];
	bool check;
	//Moving piece is a king
	if (movingpiece->getDisplay() == "K") {
	//Checking if any enemy pieces can attack the proposed square
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece *enemypiece = board[i][j];
			if ((movingpiece->getColor() == enemypiece->getColor()) || enemypiece->getColor() == "gray") {
				continue;
			}
			//If selected piece is an enemy piece
			else {
				//If not a pawn, check if the piece can move to the given spot
				if (enemypiece->getDisplay() != "P") {
					check = enemypiece->moveCheck(j, i, c, d, board);
				}
				//If a pawn, check if the piece can attack or move to the spot
				if (enemypiece->getDisplay() == "P") {
					if (enemypiece->getColor() == "white" && (d-i) == 1 && abs(c-j) == 0) {
						check = true;
					}
					if (enemypiece->getColor() == "black" && (i-d) == 1 && abs(c-j) == 0) {
						check = true;
					}
					else {
						check = enemypiece->moveCheck(j, i, c, d, board);
					}
				}
				if (check == true) {
					return true;
				}
			}
		}
	}
	return false;
	}
	//Moving piece is not a king
	//Finds the king
	else {
		int e;
		int f;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[j][i]->getDisplay() == "K" && board[j][i]->getColor() == movingpiece->getColor()) {
					e = i;
					f = j;
					break;
				}
				else {
					continue;
				}
			}
		}
	//Checking if any enemy pieces can attack the king due to moving piece
	//Temporarily move the proposed piece where it is intended to move to
	Piece *temp = board[d][c];
	board[d][c] = board[b][a];
	board[b][a] = &empty;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Piece *enemypiece = board[i][j];
			if ((movingpiece->getColor() == enemypiece->getColor()) || enemypiece->getColor() == "gray") {
				continue;
			}
			//If piece is an enemy piece
			else {
				check = enemypiece->moveCheck(j, i, e, f, board);
				if (check == true) {
					//If piece would put the king in check, put it back (executemove/pickmove will handle it)
					board[d][c] = temp;
					board[b][a] = movingpiece;
					//Return true that the move will put the king in check
					return true;
				}
			}
		}
	}
	//If piece can move there and would not put the king in check, put it back
	board[d][c] = temp;
	board[b][a] = movingpiece;
	//Return false - the move will not put the king in check
	return false;
	}
}

//Execute the proposed move, if valid
bool executeMove(string coordinates, int *turn) {
	//Turns the 4 character string of coordinates into coordinates an array can interpret
	string start = coordinates.substr(0,2);
	string x1 = start.substr(0,1);
	string y1 = start.substr(1,1);
	string finish = coordinates.substr(2,2);
	string x2 = finish.substr(0,1);
	string y2 = finish.substr(1,1);
	//Turns the letters and numbers into array coordinates (because array starts at 0)
	int a = x1[0]-'a';
	int b = y1[0]-'1';
	int c = x2[0]-'a';
	int d = y2[0]-'1';
	Piece *piece = board[b][a];
	bool valid;
	//If white's turn
	if (*turn % 2 == 1) {
		//Make sure piece is white
		if (piece->getColor() == "white") {
			valid = piece->moveCheck(a, b, c, d, board);
		}
		else {
			valid = false;
		}
	}
	//If black's turn
	if (*turn % 2 == 0) {
		//Make sure piece is black
		if (piece->getColor() == "black") {
			valid = piece->moveCheck(a, b, c, d, board);
		}
		else {
			valid = false;
		}
	}
	//If chosen piece is of the player's color
	if (valid == true) {
		//If not a king, check if the piece's move would put the king into check
		if (board[d][c]->getDisplay() != "K") {
			if (movewouldcausecheck(a, b, c, d) == true) {
				cout << "Move would put your King into check" << endl;
				return false;
			}
		//If proposed location is not empty
		if (board[d][c]->getColor() != "gray") {
            string display = board[d][c]->getDisplay();
            string color=piece->getColor();
          //switching color of captured piece, as white piece would capture black and vice versa
            if(color=="white"){
               color="black";
            }
            else if(color=="black"){
            color="white";
            }
        //Adds the captured piece to the captured pieces list
        addCaptured(color,display);
        }	
        //Move the piece, and make the previous location empty
		board[d][c] = board[b][a];
		board[b][a] = &empty;
		//If a pawn makes it to the end of the board
		if ((d == 7 || d == 1) && board[d][c]->getDisplay() == "P") {
			//Print out the move before promoting, to show that the pawn made it to the end of the board
			printboard();
			//Tell the player it's promotion time, and prompts them to choose a promotion
			cout << "Promotion time! What would you like to promote to?" << endl << "Enter: 'queen', 'knight', 'rook', or 'bishop'" << endl;
			string input;
			//Makes sure user enters a valid input
			while (1){ // a while loop that always loops; except when a break; statement occurs
			    getline (cin, input);  //ask the user to input what he wants the app to do
			    //Promotes pawn to queen of correct color
			    if (input == "queen") {
			    	if (board[d][c]->getColor() == "white") {
			    		board[d][c] = &wqueen;
			    		break;
			    	}
			    	else {
			    		board[d][c] = &bqueen;
			    		break;
			    	}
			    }
			    //Promotes pawn to knight of correct color
			    if (input == "knight") {
			    	if (board[d][c]->getColor() == "white") {
			    		board[d][c] = &wknight;
			    		break;
			    	}
			    	else {
			    		board[d][c] = &bknight;
			    		break;
			    	}
			    }
			    //Promotes pawn to rook of correct color
			    if (input == "rook") {
			    	if (board[d][c]->getColor() == "white") {
			    		board[d][c] = &wrook;
			    		break;
			    	}
			    	else {
			    		board[d][c] = &brook;
			    		break;
			    	}
			    }
			    //Promotes pawn to bishop of correct color
			    if (input == "bishop") {
			    	if (board[d][c]->getColor() == "white") {
			    		board[d][c] = &wbishop;
			    		break;
			    	}
			    	else {
			    		board[d][c] = &bbishop;
			    		break;
			    	}
			    }
			}
		}
		//Increments the turn counter after the move is executed
		*turn = *turn + 1;
		return true;
	}
	}
	else {
		return false;
	}
return false;
}

//When in cpu mode, tells the user where the AI moved to (helps in remembering where they moved)
void printAIMove(int e, int f, int new_e, int new_f) {
	string letter;
	string new_letter;
	//Converts the first and third coordinates into letters, like how they are when a human would input them
	switch (e) {
		case 0: letter = "a";
			break;
		case 1: letter = "b";
			break;
		case 2: letter = "c";
			break;
		case 3: letter = "d";
			break;
		case 4: letter = "e";
			break;
		case 5: letter = "f";
			break;
		case 6: letter = "g";
			break;
		case 7: letter = "h";
			break;
	}
	//Since array starts at 0, add 1
	f = f+1;
	switch (new_e) {
		case 0: new_letter = "a";
			break;
		case 1: new_letter = "b";
			break;
		case 2: new_letter = "c";
			break;
		case 3: new_letter = "d";
			break;
		case 4: new_letter = "e";
			break;
		case 5: new_letter = "f";
			break;
		case 6: new_letter = "g";
			break;
		case 7: new_letter = "h";
			break;
	}
	//Since array starts at 0, add 1
	new_f = new_f + 1;
	//Output the cpu's move in text form
	cout << "Black moved from " << letter << f << " to " << new_letter << new_f << endl << endl;
	return;
}

//The AI player's (cpu) version of executeMove
void pickMove() {
	//Finds the King (in case in check)
	int e;
	int f;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[j][i]->getDisplay() == "K" && board[j][i]->getColor() == "black") {
					e = i;
					f = j;
					break;
				}
				else {
					continue;
				}
			}
		}
	Piece *king = board[f][e];
	Piece *temp;
	//If King is in check
	if (checkForCheck("black", e, f) == true) {
		bool check[9] = {false, false, false, false, false, false, false, false, false};
		check[0] = testmate(e, f, e+1, f+1, king, "black");
		check[1] = testmate(e, f, e+1, f, king, "black");
		check[2] = testmate(e, f, e+1, f-1, king, "black");
		check[3] = testmate(e, f, e, f+1, king, "black");
		check[4] = testmate(e, f, e, f, king, "black");
		check[5] = testmate(e, f, e, f-1, king, "black");
		check[6] = testmate(e, f, e-1, f+1, king, "black");
		check[7] = testmate(e, f, e-1, f, king, "black");
		check[8] = testmate(e, f, e-1, f-1, king, "black");
		//RNG based on the time
		srand(time(NULL));
		//If cpu's king is in checkmate, output that white wins and end the program
		if (check[0] == true && check[1] == true && check[2] == true && check[3] == true && check[4] == true && check[5] == true && check[6] == true && check[7] == true && check[8] == true) {
		 cout << "Checkmate - White Wins" << endl;
		 exit(0);
		}
		//Prevents the AI from getting stuck when no pieces can move (for example, if a pawn and king are left on the cpu's side and the king blocked the pawn from moving)
		int y = 0;
		while(y < 1000) {
			//Generates the random number
			int i = rand() % 9;
			//If the selected move is one of the move that puts the king in check, restart the loop, trying again
			if (check[i] == true) {
				y++;
				continue;
			}
			//If the move wouldn't put the king in check
			else {
			//Moves the king to the safe location, ensuring the location doesn't in some way put the king into check
			switch(i) {
    			case 0 : 
    				temp = board[f+1][e+1];
    				board[f+1][e+1] = board[f][e];
    				board[f][e] = &empty;
    				if (checkForCheck("black", e+1, f+1) == true) {
    					board[f+1][e+1] = temp;
    					board[f][e] = &bking;
    					continue;
    				}
    				printAIMove(e, f, e+1, f+1);
    				return;
            	case 1 : 
            		temp = board[f][e+1];
    				board[f][e+1] = board[f][e];
    				board[f][e] = &empty;
       				if (checkForCheck("black", e+1, f) == true) {
    					board[f][e+1] = temp;
    					board[f][e] = &bking;
    					continue;
    				}
    				printAIMove(e, f, e+1, f);
    				return;
            	case 2 : 
            		temp = board[f-1][e+1];
    				board[f-1][e+1] = board[f][e];
    				board[f][e] = &empty;
       				if (checkForCheck("black", e+1, f-1) == true) {
    					board[f-1][e+1] = temp;
    					board[f][e] = &bking;
    					continue;
    				}
    				printAIMove(e, f, e+1, f-1);
    				return;
            	case 3 : 
            		temp = board[f+1][e];
    				board[f+1][e] = board[f][e];
    				board[f][e] = &empty;
    				if (checkForCheck("black", e, f+1) == true) {
    					board[f+1][e] = temp;
    					board[f][e] = &bking;
    					continue;
    				}
    				printAIMove(e, f, e, f+1);
            		return;
            	case 4 : 
            		temp = board[f][e];
    				board[f][e] = board[f][e];
    				board[f][e] = &empty;
       				if (checkForCheck("black", e, f) == true) {
    					board[f][e] = temp;
    					board[f][e] = &bking;
    					continue;
    				}
    				printAIMove(e, f, e, f);
            		return;
            	case 5 : 
            		temp = board[f-1][e];
    				board[f-1][e] = board[f][e];
    				board[f][e] = &empty;
       				if (checkForCheck("black", e, f-1) == true) {
    					board[f-1][e] = temp;
    					board[f][e] = &bking;
    					continue;
    				}
    				printAIMove(e, f, e, f-1);
            		return;
            	case 6 : 
            		temp = board[f+1][e-1];
    				board[f+1][e-1] = board[f][e];
    				board[f][e] = &empty;
       				if (checkForCheck("black", e-1, f+1) == true) {
    					board[f+1][e-1] = temp;
    					board[f][e] = &bking;
    					continue;
    				}
    				printAIMove(e, f, e-1, f+1);
            		return;
            	case 7 : 
            		temp = board[f][e-1];
    				board[f][e-1] = board[f][e];
    				board[f][e] = &empty;
       				if (checkForCheck("black", e-1, f) == true) {
    					board[f][e-1] = temp;
    					board[f][e] = &bking;
    					continue;
    				}
    				printAIMove(e, f, e-1, f);
            		return;
            	case 8 : 
            		temp = board[f-1][e-1];
    				board[f-1][e-1] = board[f][e];
    				board[f][e] = &empty;
       				if (checkForCheck("black", e-1, f-1) == true) {
    					board[f-1][e-1] = temp;
    					board[f][e] = &bking;
    					continue;
    				}
    				printAIMove(e, f, e-1, f-1);
            		return;
			}
		}
	}
	//If king is in check and couldn't move anywhere after numerous attempts, output that it is checkmate (prevents buggy infinite loop)
	cout << "Checkmate - White Wins" << endl;
	exit(0);
	}
	//If King is not in check
	//Locate a piece to move
	int i = 0;
	while(i < 8) {
		for (i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
			Piece *piece = board[j][i];
			if ((piece->getColor() == "white") || piece->getColor() == "gray") {
				continue;
			}
			else {
				//Attacks enemy piece if possible - has priority over normal movement
				//Locates enemy piece
				for (int k = 0; k < 8; k++) {
					for (int l = 0; l < 8; l++) {
						Piece *whitepiece = board[l][k];
						if (whitepiece->getColor() == "white" && whitepiece->getDisplay() != "K") {
							//If black piece can attack white piece (cpu attacks human piece)
							bool valid = piece->moveCheck(i, j, k, l, board);
							if (valid == true) {
								//And wouldn't put its own king in check
								if (movewouldcausecheck(i, j, k, l) == false) {
								temp = board[l][k];
								board[l][k] = board[j][i];
								board[j][i] = &empty;
								//If somehow the king gets put into check by this move, try a different piece
								if (piece->getDisplay() != "K") {
								//e and f are the king's coordinates
								if (checkForCheck("black", e, f) == true) {
									board[l][k] = temp;
									board[j][i] = piece;
									continue;
								}
								}
								//If somehow the king gets put into check by this move, try a different piece
								if (piece->getDisplay() == "K") {
								//If moving the king, i and j are the king's coordinates
								if (checkForCheck("black", i, j) == true) {
									board[l][k] = temp;
									board[j][i] = piece;
									continue;
								}
								}
								//Output the AI's move
								printAIMove(i, j, k, l);
								//AI automatically promotes to queen, because it almost always makes the most sense
								if ((l == 7 || l == 0) && board[l][k]->getDisplay() == "P") {
									printboard();
									cout << "Promotion to Queen!" << endl;
									board[l][k] = &bqueen;
								}
								return;
							}
						}
							else {
								continue;
							}
						}
						else {
							continue;
						}
					}
				}
			}
		}
		}
	}
	//If no pieces can attack the enemy
	//RNG based on the time
	srand(time(NULL));
	int z = 0;
	//Prevents infinite loop
	while(z < 1000) {
		//Generates coordinates between 0 and 7
		i = rand() % 8;
		int j = rand() % 8;
		//Chooses the piece at these random coordinates
		//If piece is not a black piece, try again
		Piece *piece = board[j][i];
		if ((piece->getColor() == "white") || piece->getColor() == "gray") {
			z++;
			continue;
		}
		//If piece is a black piece
		else {
			for (int m = 0; m < 8; m++) {
				for (int n = 0; n < 8; n++) {
					//Try to move the piece down the board, towards white's base
					bool valid = piece->moveCheck(i, j, m, n, board);
					if (valid == true) {
						//Won't put itself into check on purpose
						if (movewouldcausecheck(i, j, m, n) == false) {
							temp = board[n][m];
							board[n][m] = board[j][i];
							board[j][i] = &empty;
							if (piece->getDisplay() != "K") {
								if (checkForCheck("black", e, f) == true) {
									board[n][m] = temp;
									board[j][i] = piece;
									continue;
								}
							}
							if (piece->getDisplay() == "K") {
								if (checkForCheck("black", i, j) == true) {
									board[n][m] = temp;
									board[j][i] = piece;
									continue;
								}
							}
							//Notifies the player of the AI's move
							printAIMove(i, j, m, n);
							//Automatically promotes to queen
							if (n == 0 && board[n][m]->getDisplay() == "P") {
								printboard();
								cout << "Promotion to Queen!" << endl;
								board[n][m] = &bqueen;
							}
						return;	
						}
					}
				}
			}
		}
	}
	//Outputs stalemate if an infinite loop occurs
	cout << "Stalemate" << endl;
	exit(0);
}

//////////////////////////////////////////Implementation of emptypiece.h

bool EmptyPiece::moveCheck(int a, int b, int c, int d, Piece* array[8][8]){
    	return false;
    }

//////////////////////////////////////////Implementation of piece.h
Piece::Piece(string color, string display) {
		this->color = color;
		this->display = display;
}

string Piece::getColor() {
	return color;
}

string Piece::getDisplay() {
	return display;
}

//////////////////////////////////////////Implementation of pawn.h

void Pawn::MovedReset() {
    moved = false;
    return;
}

//Pawn movement
bool Pawn::moveCheck(int a, int b, int c, int d, Piece* array[8][8]){
    	int distance;
    	if (array[b][a]->getColor() == "white") {
    	distance = d - b;
    	//Checks if attacking - looks for 1 space upward movement if white, and moving left or right by 1
    	if (distance == 1 && abs(c-a) == 1) {
    		if (array[d][c]->getDisplay() != "~" && array[d][c]->getColor() == "black") {
    			moved = true;
    			return true;
    		}
    		else {
    			return false;
    		}
    	}
    	//Checks if movement path is upwards
    	if (a == c && d > b) {
    		if (moved == false) {
    			if (distance > 2)  {
    				return false;
    			}
    			if (distance == 2) {
    				if (array[d][c]->getDisplay() == "~" && array[d-1][c]->getDisplay() == "~") {
    					moved = true;
    					return true;
    				}
    			}
    			if (distance == 1) {
    				if (array[d][c]->getDisplay() == "~") {
    					moved = true;
    					return true;
    				}
    			}
    			else {
    				return false;
    			}
    		}
    		else {
    			if (distance == 1) {
    				if (array[d][c]->getDisplay() == "~") {
    					return true;
    				}
    			}
    			else {
    				return false;
    			}
    		}
    	}
    	else {
    		return false;
    	}
    	}
    	if (array[b][a]->getColor() == "black") {
    	distance = b - d;
    	//Checks if attacking - looks for 1 space downward movement if black, and moving left or right by 1
    	if (distance == 1 && abs(c-a) == 1) {
    		if (array[d][c]->getDisplay() != "~" && array[d][c]->getColor() == "white") {
    			moved = true;
    			return true;
    		}
    		else {
    			return false;
    		}
    	}
    	//Checks if movement path is downwards
    	if (a == c && b > d) {
    		if (moved == false) {
    			if (distance > 2)  {
    				return false;
    			}
    			if (distance == 2) {
    				if (array[d][c]->getDisplay() == "~" && array[d+1][c]->getDisplay() == "~") {
    					moved = true;
    					return true;
    				}
    			}
    			if (distance == 1) {
    				if (array[d][c]->getDisplay() == "~") {
    					moved = true;
    					return true;
    				}
    			}
    			else {
    				return false;
    			}
    		}
    		else {
    			if (distance == 1) {
    				if (array[d][c]->getDisplay() == "~") {
    					return true;
    				}
    			}
    			else {
    				return false;
    			}
    		}
    	}
    	else {
    		return false;
    	}
    	}
    	else {
    		return false;
    	}
    return false;
    }

//////////////////////////////////////////Implementation of bishop.h

//Bishop movement
bool Bishop::moveCheck(int a, int b, int c, int d, Piece* array[8][8]){
	//Checks if destination is same color as piece
	if (array[d][c]->getColor() == array[b][a]->getColor()) {
		return false;
	}
	//Checks if movement path is diagonal
	int distance1 = abs(d - b);
	int distance2 = abs(c - a);
	if (distance1 == distance2) {
		//Checks if pathway is clear, depending on the direction the bishop is going
		if (a > c && b < d) {
			for (int j = d-1, i = c+1; j > b; j--, i++) {
				if (array[j][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
		if (a < c && b > d) {
			for (int j = b-1, i = a+1; j > d; j--, i++) {
				if (array[j][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
		if (a < c && b < d) {
			for (int j = d-1, i = c-1; j > b; j--, i--) {
				if (array[j][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
		if (a > c && b > d) {
			for (int j = d+1, i = c+1; j < b; j++, i++) {
				if (array[j][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
	}
	else {
		return false;
	}
	return false;
}

//////////////////////////////////////////Implementation of knight.h

//Knight movement
bool Knight::moveCheck(int a, int b, int c, int d, Piece* array[8][8]){
	//Checks if destination is same color as piece
	if (array[d][c]->getColor() == array[b][a]->getColor()) {
		return false;
	}
	//Checks if movement path is 2 one direction and 1 the other
	int distance1 = abs(d - b);
	int distance2 = abs(c - a);
	if ((distance1 == 2 && distance2 == 1) || (distance1 == 1 && distance2 == 2)) {
		return true;
	}
	else {
		return false;
	}
}

//////////////////////////////////////////Implementation of rook.h

//Castling
bool Rook::checkMoved1(){
	return moved1;
}

//Castling
bool Rook::checkMoved2(){
	return moved2;
}

//Castling
void Rook::move1(){
	moved1 = true;
}

//Castling
void Rook::move2(){
	moved2 = true;
}

//Castling - resets the field that holds whether or not the rooks have moved
void Rook::MovedReset() {
    moved1 = false;
    moved2 = false;
    return;
}

//Rook movement
bool Rook::moveCheck(int a, int b, int c, int d, Piece* array[8][8]){
	//Checks if destination is same color as piece
	if (array[d][c]->getColor() == array[b][a]->getColor()) {
		return false;
	}
	//Checks if movement path is a line
	//Vertical
	if (a == c) {
		if (b > d) {
			for (int j = d+1; j < b; j++) {
				if (array[j][a]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			//Castling
			if (a == 'a'-'a')//determines which rook is being moved, then rets the appropriate variable to true
				moved1 = true;
			else if (a == 'h'-'a')
				moved2 = true;
			return true;
			}
		if (b < d) {
			for (int j = d-1; j > b; j--) {
				if (array[j][a]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
		//Castling
		if (a == 'a'-'a')
			moved1 = true;
		else if (a == 'h'-'a')
			moved2 = true;
		return true;
		}
	}
	//Horizontal
	if (b == d) {
		if (a > c) {
			for (int i = c+1; i < a; i++) {
				if (array[b][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			//Castling
			if (a == 'a'-'a')
				moved1 = true;
			else if (a == 'h'-'a')
				moved2 = true;
			return true;
			}
		if (a < c) {
			for (int i = c-1; i > a; i--) {
				if (array[b][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
		//Castling
		if (a == 'a'-'a')
			moved1 = true;
		else if (a == 'h'-'a')
			moved2 = true;
		return true;
		}
	}
	//Neither
	else {
		return false;
	}
return false;
}

//////////////////////////////////////////Implementation of queen.h

//Queen movement - just uses movement from rook and bishop
bool Queen::moveCheck(int a, int b, int c, int d, Piece* array[8][8]){
	//Checks if destination is same color as piece
	if (array[d][c]->getColor() == array[b][a]->getColor()) {
		return false;
	}
	//Checks if movement path is a line
	//Vertical
	if (a == c) {
		if (b > d) {
			for (int j = d+1; j < b; j++) {
				if (array[j][a]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
		if (b < d) {
			for (int j = d-1; j > b; j--) {
				if (array[j][a]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
		return true;
		}
	}
	//Horizontal
	if (b == d) {
		if (a > c) {
			for (int i = c+1; i < a; i++) {
				if (array[b][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
		if (a < c) {
			for (int i = c-1; i > a; i--) {
				if (array[b][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
		return true;
		}
	}
	//Checks if movement path is diagonal
	int distance1 = abs(d - b);
	int distance2 = abs(c - a);
	if (distance1 == distance2) {
		//Checks if pathway is clear
		if (a > c && b < d) {
			for (int j = d-1, i = c+1; j > b; j--, i++) {
				if (array[j][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
		//Problem - fixed!
		if (a < c && b > d) {
			for (int j = b-1, i = a+1; j > d; j--, i++) {
				if (array[j][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
		if (a < c && b < d) {
			for (int j = d-1, i = c-1; j > b; j--, i--) {
				if (array[j][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
		if (a > c && b > d) {
			for (int j = d+1, i = c+1; j < b; j++, i++) {
				if (array[j][i]->getDisplay() == "~") {
					continue;
				}
				else {
					return false;
				}
			}
			return true;
			}
	}
	//None
	else {
		return false;
	}
return false;
}

//////////////////////////////////////////Implementation of king.h

//Castling
void King::move(){
	moved = true;
}

//Castling - stores whether the king has moved from its starting position
void King::MovedReset() {
    moved = false;
    return;
}

//King movement
bool King::moveCheck(int a, int b, int c, int d, Piece* array[8][8]){
	//Checks if destination is same color as piece
	if (array[d][c]->getColor() == array[b][a]->getColor()) {
		return false;
	}
	
	if (!moved){//Castling
		if (array[b][a]->getColor() == "white"){
			if (c == 'g'-'a' && d == 0 && !dynamic_cast<Rook*>(array[0]['h'-'a'])->checkMoved2() && array[0]['g'-'a']->getDisplay() == "~" && array[0]['f'-'a']->getDisplay() == "~"){
				if (!checkForCheck("white", 'g'-'a', 0) && !checkForCheck("white", 'f'-'a', 0) && !checkForCheck("white", 'e'-'a', 0)){
					board[0]['f'-'a'] = board[0]['h'-'a'];
					board[0]['h'-'a'] = &empty;
					moved = true;
					return true;
				}
			} else if (c == 'c'-'a' && d == 0 && !dynamic_cast<Rook*>(array[0]['a'-'a'])->checkMoved1() && array[0]['c'-'a']->getDisplay() == "~" && array[0]['d'-'a']->getDisplay() == "~"){
				if (!checkForCheck("white", 'c'-'a', 0) && !checkForCheck("white", 'd'-'a', 0) && !checkForCheck("white", 'e'-'a', 0)){
					board[0]['d'-'a'] = board[0]['h'-'a'];
					board[0]['a'-'a'] = &empty;
					moved = true;
					return true;
				}
			}
		} else {
			if (c == 'g'-'a' && d == 7 && !dynamic_cast<Rook*>(array[7]['h'-'a'])->checkMoved2() && array[7]['g'-'a']->getDisplay() == "~" && array[7]['f'-'a']->getDisplay() == "~"){
				if (!checkForCheck("black", 'g'-'a', 7) && !checkForCheck("black", 'f'-'a', 7) && !checkForCheck("black", 'e'-'a', 7)){
					board[7]['f'-'a'] = board[7]['h'-'a'];
					board[7]['h'-'a'] = &empty;
					moved = true;
					return true;
				}
			} else if (c == 'c'-'a' && d == 7 && !dynamic_cast<Rook*>(array[7]['a'-'a'])->checkMoved1() && array[7]['c'-'a']->getDisplay() == "~" && array[7]['d'-'a']->getDisplay() == "~"){
				if (!checkForCheck("black", 'c'-'a', 7) && !checkForCheck("black", 'd'-'a', 7) && !checkForCheck("black", 'e'-'a', 7)){
					board[7]['d'-'a'] = board[7]['h'-'a'];
					board[7]['a'-'a'] = &empty;
					moved = true;
					return true;
				}
			}
		}	
	}
	
	//Normal movement
	int distance1 = abs(d - b);
	int distance2 = abs(c - a);
	//Checks if movement path is vertical
	if (distance1 == 1) {
			if (distance2 == 0) {
				moved = true;
				return true;
			}
		}
	if (distance2 == 1) {
			if (distance1 == 0) {
				moved = true;
				return true;
			}
		}
	if (distance1 == 1 && distance2 == 1) {
		return true;
	}
	else {
		return false;
	}
}

//Failsafe if the AI somehow manages to take player's king in a check situation (bug)
bool kingistaken() {
	int kings = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->getDisplay() == "K") {
				kings++;
			}
		}
	}
	if (kings < 2) {
		return true;
	}
	else {
		return false;
	}	
}

//Checks for stalemate
bool checkstalemate(string color) {
	int e;
	int f;
	Piece *king;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[j][i]->getDisplay() == "K" && board[j][i]->getColor() == color) {
				king = board[j][i];
				e = i;
				f = j;
				break;
			}
			else {
				continue;
			}
		}
	}
	//Now that king is located, check which spots it could, in an ideal situation, move to
	bool check[9] = {false, false, false, false, false, false, false, false, false};
	check[0] = testmate(e, f, e+1, f+1, king, color);
	check[1] = testmate(e, f, e+1, f, king, color);
	check[2] = testmate(e, f, e+1, f-1, king, color);
	check[3] = testmate(e, f, e, f+1, king, color);
	check[4] = testmate(e, f, e, f, king, color);
	check[5] = testmate(e, f, e, f-1, king, color);
	check[6] = testmate(e, f, e-1, f+1, king, color);
	check[7] = testmate(e, f, e-1, f, king, color);
	check[8] = testmate(e, f, e-1, f-1, king, color);
	//If in check everywhere but the current position
	if (check[0] == true && check[1] == true && check[2] == true && check[3] == true && check[4] == false && check[5] == true && check[6] == true && check[7] == true && check[8] == true) {
		cout << "Stalemate" << endl;
		exit(0);
	}
	//Counts how many pieces are left in total (both sides)
	int pieces = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->getDisplay() != "~") {
				pieces++;
			}
		}
	}
	//If there's only two pieces left (would mean only kings)
	if (pieces == 2) {
		//Return true (stalemate)
		return true;
	}
	else {
		return false;
	}
}

//////////////////////////////////////////////////////////////////

using namespace std;

int main (void) {
//On startup
cout << "Commands:" << endl << "'restart' to play another game" << endl << "'print' to display the board (does so automatically normally)" << endl << "'help' to receive help" << endl << "'captured' to display captured pieces" << endl << "'exit' to quit" << endl << endl;
cout << "To perform a move, type a 4 letter string from starting destination" << endl << "to ending destination. For example: 'a2a4'" << endl << endl;
cout << "To begin, type 'cpu' to play the computer, or 'human' to play with a friend" << endl;
string input;
//Initializes the board on launch
setup();
string challenger;
while (1) {
	//Lets user choose what type of opponent to play against
	getline (cin, challenger);
	if (challenger.substr(0,3) == "cpu" || challenger.substr(0,5) == "human") {
		cout << endl;
		break;
	}
	else {
		cout << "Invalid Choice" << endl;
	}
}
//Displays the board on startup
printboard();
//Sets it to turn #1
int turn = 1;
//Begins the loop that the user will be in for the rest of the game
while (1){
	//Notifies players of whether any king is in check at the beginning of each turn
    notifyofcheck("white");
    notifyofcheck("black");
    //Outputs the turn #
    cout << "Turn " << turn << ", ";
    //Informs which player's turn it is
    if (turn % 2 == 1) {
    	cout << "White's Turn" << endl;
    }
    else {
    	cout << "Black's Turn" << endl;
    }
    //If human vs human or it's human's turn in a cpu game
    if (challenger == "human" || (challenger == "cpu" && turn % 2 == 1)) {
	getline (cin, input);  //ask the user to input what he wants the app to do
    //Restarts the game
    if (input.substr(0, 7) == "restart") {
    	setup();
    	turn = 1;
    	printboard();
    }
    //Prints the board if the user can't see it (due to too many invalid moves, for example)
    if (input.substr(0, 5) == "print") {
        printboard();
    }
    //Displays the captured pieces list
    if (input.substr(0, 8) == "captured") {
        displayCaptured();
    }
    //Displays the help menu
    if (input.substr(0, 4) == "help") {
        helpMenu();
    }
    //Terminates the program
    if (input.substr(0, 4) == "exit") {
        exit(0);
        break;
    }
    //Passes in the user's desired move coordinates
    if (input.substr(0, 1) >= "a" && input.substr(0, 1) <= "h" && input.substr(1, 1) >= "1" && input.substr(1, 1) <= "8" && input.substr(2, 1) >= "a" && input.substr(2, 1) <= "h" && input.substr(3, 1) >= "1" && input.substr(3, 1) <= "8")   { // this statement makes sure both squares are on the chess board when executing //a move
         if (executeMove(input, &turn) == true) {
        	 printboard();
         }
         else {
        	 cout << "Invalid Move" << endl;
         }
    }
	}
	//If AI's turn
	else {
		//Picks a move
		pickMove();
		turn++;
		printboard();
	}
	//Failsafe if AI manages to capture user's king (bug)
	if (kingistaken() == true) {
		cout << "You lose!" << endl;
		exit(0);
	}
	//Outputs stalemate if necessary
	if (checkstalemate("white") == true || checkstalemate("black") == true) {
		cout << "Stalemate" << endl;
		exit(0);
	}
}
}