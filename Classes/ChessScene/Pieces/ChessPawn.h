#ifndef __CHESS_PAWN_H__
#define __CHESS_PAWN_H__

#include "ChessScene/Pieces/ChessPiece.h"

class ChessPawn : public ChessPiece {
private:
	bool _isFirstMove;
public:
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board, const Rowcol& current) override;
	Rowcol canAddDiagonalMove(BoardLayer* board, const Rowcol base, Rowcol additonal);
public:
	static ChessPawn* create(const ChessPiece::PieceType type, const ChessPiece::Color color);
	ChessPawn();
	virtual ~ChessPawn();
	virtual bool init();
	CREATE_FUNC(ChessPawn);
};

#endif