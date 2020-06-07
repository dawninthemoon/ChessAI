#ifndef __CHESS_KING_H__
#define __CHESS_KING_H__

#include "ChessScene/Pieces/ChessPiece.h"

class ChessKing : public ChessPiece {
private:
	Rowcol dir[8];
public:
	virtual Rowcol canAddMove(BoardLayer* board, const Rowcol base, Rowcol additonal) override;
	Rowcol canAddMoveExceptCheck(BoardLayer* board, const Rowcol base, Rowcol additonal);
	virtual bool checkIsCheckState(BoardLayer* board, Rowcol current) override;
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board, const Rowcol& current) override;
	std::vector<Rowcol> getMoveAreasExceptCheck(BoardLayer* board, const Rowcol& current);
public:
	static ChessKing* create(const ChessPiece::PieceType type, const ChessPiece::Color color);
	ChessKing();
	virtual ~ChessKing();
	virtual bool init();
	CREATE_FUNC(ChessKing);
};

#endif