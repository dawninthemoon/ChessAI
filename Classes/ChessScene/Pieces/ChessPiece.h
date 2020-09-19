#ifndef __CHESSS_PIECE_H__
#define __CHESSS_PIECE_H__

#include "cocos2d.h"
#include "RowCol.h"
#include <string>
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
		KING,
		TYPE_COUNT
	};
	enum Color {
		WHITE,
		BLACK,
		COLOR_COUNT
	};
public:
	virtual std::vector<Rowcol> getMoveAreas(BoardLayer* board) = 0;
	virtual Rowcol canAddMove(BoardLayer* board, const Rowcol additional);
	virtual bool checkIsCheckState(BoardLayer* board);
	ChessPiece::Color getPieceColor() const;
	ChessPiece::Color getOppositeColor() const;
	void setPieceColor(Color color);
	PieceType getPieceType() const;
	void setPieceType(PieceType type);
	virtual void onMove(const cocos2d::Point point, ChessPiece* toRemove, cocos2d::Node* parent);
	void setRowcol(Rowcol rowcol);
	Rowcol getRowcol() const;
private:
	Color _pieceColor;
	PieceType _pieceType;
	Rowcol _rowcol;
};

#endif