#ifndef __CHESS_KNGITH_H__
#define __CHESS_KNIGHT_H__

#include "ChessScene/Pieces/ChessPiece.h"

class ChessKnight : public ChessPiece {
private:
	Rowcol dir[8];
public:
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board) override;
public:
	static ChessKnight* create(const ChessPiece::PieceType type, const ChessPiece::Color color);
	ChessKnight();
	virtual ~ChessKnight();
	virtual bool init();
	CREATE_FUNC(ChessKnight);
};

#endif