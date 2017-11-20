/*
 * king.h
 *
 *  Created on: Mar 30, 2017
 *      Author: andrewratz
 */

#ifndef KING_H_
#define KING_H_

#include <iostream>
#include <string>
#include <cmath>
#include <stdio.h>
#include "piece.h"

using namespace std;

class King: public Piece
{
    bool moved;
public:
    void MovedReset();
    
    void move();
    
    King(string color, string display):Piece(color, display){
        moved = false;
    }
    bool moveCheck(int a, int b, int c, int d, Piece* array[8][8]);
};

#endif /* KING_H_ */
