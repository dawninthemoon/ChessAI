#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "RowCol.h"
#include "ChessScene/Pieces/ChessPiece.h"

class BoardLayer;

class Computer {
private:
	ChessPiece::Color _cpuColor;
public:
	Computer();
	virtual ~Computer();
public:
	Rowcol decideMove(BoardLayer* board, ChessPiece*& selectedPiece);
	int minimax(BoardLayer* board, ChessPiece::Color color, int alpha, int beta, int depth);
	int getColor() const;
};

#endif