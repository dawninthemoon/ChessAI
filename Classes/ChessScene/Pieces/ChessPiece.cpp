#include "ChessScene/Pieces/ChessPiece.h"
#include "ChessScene/BoardLayer.h"

USING_NS_CC;

ChessPiece::ChessPiece() { }
ChessPiece::~ChessPiece() { }

bool ChessPiece::init() {
	if (!Sprite::create()) return false;
	return true;
}

Rowcol ChessPiece::canAddMove(BoardLayer* board, const Rowcol base, Rowcol additonal) {
	additonal.row *= (getPieceColor() == Color::WHITE) ? -1 : 1;
	Rowcol target = base + additonal;
	if (!board->isValidRowcol(target))
		return Rowcol::IMPOSSIBLE;
	return target;
}

ChessPiece::Color ChessPiece::getPieceColor() {
	return _pieceColor;
}

void ChessPiece::setPieceColor(ChessPiece::Color color) {
	_pieceColor = color;
}