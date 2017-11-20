/*
 * piece.h
 *
 *  Created on: Mar 30, 2017
 *      Author: andrewratz
 */

#ifndef PIECE_H_
#define PIECE_H_
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

class Piece
{
private:
    //Color of the Piece
    string color;
    string display;
    //Coordinates of the Piece
    string x;
    string y;
    
public:
    Piece() {}
    virtual ~Piece() {}
    Piece(string color, string display);
    string getColor();
    string getDisplay();
    virtual bool moveCheck(int a, int b, int c, int d, Piece* array[8][8]) = 0;
};


#endif /* PIECE_H_ */
