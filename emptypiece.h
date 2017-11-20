/*
 * emptypiece.h
 *
 *  Created on: Mar 30, 2017
 *      Author: andrewratz
 */

#ifndef EMPTYPIECE_H_
#define EMPTYPIECE_H_

#include <iostream>
#include <string>

#include <stdio.h>
#include "piece.h"

using namespace std;

class EmptyPiece: public Piece
{
public:
    
    EmptyPiece(string color, string display):Piece(color, display){}
    
    bool moveCheck(int a, int b, int c, int d, Piece* array[8][8]);
    
};

#endif /* EMPTYPIECE_H_ */
