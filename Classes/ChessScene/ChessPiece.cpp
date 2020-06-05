#include "ChessScene/ChessPiece.h"

USING_NS_CC;

ChessPiece::ChessPiece() { }
ChessPiece::~ChessPiece() { }

bool ChessPiece::init() {
	if (!Sprite::create()) return false;
	return true;
}