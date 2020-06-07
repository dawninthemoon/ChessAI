#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "RowCol.h"

class BoardLayer;
class ChessPiece;

class Computer {
private:
	int _cpuColor;
public:
	Computer();
	virtual ~Computer();
public:
	Rowcol decideMove(BoardLayer* board, Rowcol& selectedPrev, ChessPiece*& selectedPiece);
	int getColor() const;
};

#endif