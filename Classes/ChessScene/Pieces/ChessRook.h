#ifndef __CHESS_ROOK_H__
#define __CHESS_ROOK_H__

#include "ChessScene/Pieces/ChessPiece.h"

class ChessRook : public ChessPiece {
private:
	Rowcol dir[4];
public:
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board, bool throwException = false) override;
public:
	static ChessRook* create(const ChessPiece::PieceType type, const ChessPiece::Color color);
	ChessRook();
	virtual ~ChessRook();
	virtual bool init();
	CREATE_FUNC(ChessRook);
};

#endif