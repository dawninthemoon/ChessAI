#ifndef __COMPUTER_H__
#define __COMPUTER_H__

struct Rowcol;
class BoardLayer;
class ChessPiece;

class Computer {
private:
	const int MAX_TIMEOUT = 10000;
	int _cpuColor;
public:
	Computer();
	virtual ~Computer();
public:
	Rowcol decideMove(BoardLayer* board, Rowcol& selectedPrev, ChessPiece*& selectedPiece);
	int getColor() const;
};

#endif