/*
 * whiteknight.h
 *
 *  Created on: Mar 30, 2017
 *      Author: andrewratz
 */

#ifndef KNIGHT_H_
#define KNIGHT_H_

#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include "piece.h"

using namespace std;

class Knight: public Piece
{
public:
    
    Knight(string color, string display):Piece(color, display){}
    bool moveCheck(int a, int b, int c, int d, Piece* array[8][8]);
    
};

#endif /* KNIGHT_H_ */
