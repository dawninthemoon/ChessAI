#ifndef __CHESS_BISHOP_H__
#define __CHESS_BISHOP_H__

#include "ChessScene/Pieces/ChessPiece.h"

class ChessBishop : public ChessPiece {
private:
	Rowcol dir[4];
public:
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board) override;
public:
	static ChessBishop* create(const ChessPiece::PieceType type, const ChessPiece::Color color);
	ChessBishop();
	virtual ~ChessBishop();
	virtual bool init();
	CREATE_FUNC(ChessBishop);
};

#endif