#ifndef __CHESSS_PIECE_H__
#define __CHESSS_PIECE_H__

#include "cocos2d.h"
#include "RowCol.h"
#include <vector>

class BoardLayer;

class ChessPiece : public cocos2d::Sprite {
public:
	ChessPiece();
	virtual ~ChessPiece();
	virtual bool init();
	enum PieceType {
		PAWN,
		BISHOP,
		KNIGHT,
		ROOK,
		QUEEN,
		KING
	};
	enum Color {
		WHITE,
		BLACK
	};
public:
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board, const Rowcol& current) = 0;
	virtual Rowcol canAddMove(BoardLayer* board, const Rowcol base, Rowcol additonal);
	Color getPieceColor();
	void setPieceColor(Color color);
protected:
	Color _pieceColor;
};

#endif