/*
 * queen.h
 *
 *  Created on: Mar 30, 2017
 *      Author: andrewratz
 */

#ifndef QUEEN_H_
#define QUEEN_H_

#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include "piece.h"

using namespace std;

class Queen: public Piece
{
public:
    
    Queen(string color, string display):Piece(color, display){}
    bool moveCheck(int a, int b, int c, int d, Piece* array[8][8]);
};

#endif /* QUEEN_H_ */
