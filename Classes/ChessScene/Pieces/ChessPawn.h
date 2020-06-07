#ifndef __CHESS_PAWN_H__
#define __CHESS_PAWN_H__

#include "ChessScene/Pieces/ChessPiece.h"

class ChessPawn : public ChessPiece {
private:
	bool _isFirstMove;
public:
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board, bool throwException = false) override;
	virtual Rowcol canAddMove(BoardLayer* board, Rowcol additional) override;
	Rowcol canAddDiagonalMove(BoardLayer* board, Rowcol additional);
	virtual void onMove(const cocos2d::Point point, ChessPiece* toRemove, cocos2d::Node* parent) override;
public:
	static ChessPawn* create(const ChessPiece::PieceType type, const ChessPiece::Color color);
	ChessPawn();
	virtual ~ChessPawn();
	virtual bool init();
	CREATE_FUNC(ChessPawn);
};

#endif