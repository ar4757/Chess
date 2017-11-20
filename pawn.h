/*
 * pawn.h
 *
 *  Created on: Mar 30, 2017
 *      Author: andrewratz
 */

#ifndef PAWN_H_
#define PAWN_H_

#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include "piece.h"

using namespace std;

class Pawn: public Piece
{
private:
    bool moved;
public:
    
    Pawn(string color, string display):Piece(color, display)
    {
        moved = false;
    }
    void MovedReset();
    bool moveCheck(int a, int b, int c, int d, Piece* array[8][8]);
};

#endif /* PAWN_H_ */
