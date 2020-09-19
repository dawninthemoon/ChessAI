#ifndef __CHESS_KING_H__
#define __CHESS_KING_H__

#include "ChessScene/Pieces/ChessPiece.h"

class ChessKing : public ChessPiece {
private:
	Rowcol dir[8];
public:
	virtual Rowcol canAddMove(BoardLayer* board, Rowcol additonal) override;
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board) override;
public:
	static ChessKing* create(const ChessPiece::PieceType type, const ChessPiece::Color color);
	ChessKing();
	virtual ~ChessKing();
	virtual bool init();
	CREATE_FUNC(ChessKing);
};

#endif