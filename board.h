/*
 * board.h
 *
 *  Created on: Mar 30, 2017
 *      Author: andrewratz
 */

#ifndef BOARD_H_
#define BOARD_H_

#include <iostream>
#include <string>

#include <stdio.h>

#include "bishop.h"
#include "piece.h"
#include "emptypiece.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include <vector>
#include <utility>

using namespace std;

//Initializes all of the pieces
//White
Rook wrook = Rook("white", "R");
Knight wknight = Knight("white", "N");
Bishop wbishop = Bishop("white", "B");
Queen wqueen = Queen("white", "Q");
King wking = King("white", "K");
Pawn wpawn1 = Pawn("white", "P");
Pawn wpawn2 = Pawn("white", "P");
Pawn wpawn3 = Pawn("white", "P");
Pawn wpawn4 = Pawn("white", "P");
Pawn wpawn5 = Pawn("white", "P");
Pawn wpawn6 = Pawn("white", "P");
Pawn wpawn7 = Pawn("white", "P");
Pawn wpawn8 = Pawn("white", "P");

//Empty
EmptyPiece empty = EmptyPiece("gray", "~");

//Black
Rook brook = Rook("black", "R");
Knight bknight = Knight("black", "N");
Bishop bbishop = Bishop("black", "B");
Queen bqueen = Queen("black", "Q");
King bking = King("black", "K");
Pawn bpawn1 = Pawn("black", "P");
Pawn bpawn2 = Pawn("black", "P");
Pawn bpawn3 = Pawn("black", "P");
Pawn bpawn4 = Pawn("black", "P");
Pawn bpawn5 = Pawn("black", "P");
Pawn bpawn6 = Pawn("black", "P");
Pawn bpawn7 = Pawn("black", "P");
Pawn bpawn8 = Pawn("black", "P");

//Puts them into the default board
Piece* initialize[8][8] = {
    &wrook, &wknight, &wbishop, &wqueen, &wking, &wbishop, &wknight, &wrook,
    &wpawn1, &wpawn2, &wpawn3, &wpawn4, &wpawn5, &wpawn6, &wpawn7, &wpawn8,
    &empty, &empty, &empty, &empty, &empty, &empty, &empty, &empty,
    &empty, &empty, &empty, &empty, &empty, &empty, &empty, &empty,
    &empty, &empty, &empty, &empty, &empty, &empty, &empty, &empty,
    &empty, &empty, &empty, &empty, &empty, &empty, &empty, &empty,
    &bpawn1, &bpawn2, &bpawn3, &bpawn4, &bpawn5, &bpawn6, &bpawn7, &bpawn8,
    &brook, &bknight, &bbishop, &bqueen, &bking, &bbishop, &bknight, &brook
};

//Creates the board that will hold the pieces while the game is being played
Piece* board[8][8];

vector< pair<string,string> > captured;



#endif /* BOARD_H_ */
