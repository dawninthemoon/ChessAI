#ifndef __CHESS_QUEEN_H__
#define __CHESS_QUEEN_H__

#include "ChessScene/Pieces/ChessPiece.h"

class ChessQueen : public ChessPiece {
private:
	Rowcol dir[8];
public:
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board) override;
public:
	static ChessQueen* create(const ChessPiece::PieceType type, const ChessPiece::Color color);
	ChessQueen();
	virtual ~ChessQueen();
	virtual bool init() override;
	CREATE_FUNC(ChessQueen);
};

#endif