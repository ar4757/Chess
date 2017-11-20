/*
 * rook.h
 *
 *  Created on: Mar 30, 2017
 *      Author: andrewratz
 */

#ifndef ROOK_H_
#define ROOK_H_

#include <iostream>
#include <string>

#include <stdio.h>
#include "piece.h"

using namespace std;

class Rook: public Piece
{
    bool moved1;//moved1 and 2 are used to determine if and whick rook has moved
    bool moved2;//moved1 is for rooks starting on a, 2 for h
public:
    void MovedReset();
    
    void move1();
    
    void move2();
    
    bool checkMoved1();
    
    bool checkMoved2();
    
    Rook(string color, string display):Piece(color, display){
        moved1 = false;
        moved2 = false;
    }
    
    bool moveCheck(int a, int b, int c, int d, Piece* array[8][8]);
};

#endif /* ROOK_H_ */
