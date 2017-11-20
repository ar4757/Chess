/*
 * bishop.h
 *
 *  Created on: Mar 30, 2017
 *      Author: andrewratz
 */

#ifndef BISHOP_H_
#define BISHOP_H_

#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include "piece.h"

using namespace std;

class Bishop: public Piece
{
public:
    
    Bishop(string color, string display):Piece(color, display){}
    bool moveCheck(int a, int b, int c, int d, Piece* array[8][8]);
};

#endif /* BISHOP_H_ */
