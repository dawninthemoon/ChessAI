#ifndef __CHESS_KING_H__
#define __CHESS_KING_H__

#include "ChessScene/Pieces/ChessPiece.h"

class ChessKing : public ChessPiece {
private:
	Rowcol dir[8];
public:
	virtual Rowcol canAddMove(BoardLayer* board, Rowcol additonal) override;
	Rowcol canAddMoveExceptCheck(BoardLayer* board, Rowcol additonal);
	virtual bool checkIsCheckState(BoardLayer* board) override;
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board, bool throwException = false) override;
	std::vector<Rowcol> getMoveAreasExceptCheck(BoardLayer* board);
public:
	static ChessKing* create(const ChessPiece::PieceType type, const ChessPiece::Color color);
	ChessKing();
	virtual ~ChessKing();
	virtual bool init();
	CREATE_FUNC(ChessKing);
};

#endif