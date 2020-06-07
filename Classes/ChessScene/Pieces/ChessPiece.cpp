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

	ChessPiece* piece = board->getChessPiece(target);
	if (piece != nullptr) {

		if (piece->getPieceColor() == getPieceColor())
			return Rowcol::IMPOSSIBLE;
		if (piece->getPieceType() == ChessPiece::KING)
			throw 1;
	}

	return target;
}

bool ChessPiece::checkIsCheckState(BoardLayer * board, Rowcol current)
{
	try {
		getMoveAreas(board, current);
	}
	catch (int e) {
		return true;
	}
	return false;
}

ChessPiece::Color ChessPiece::getPieceColor() const {
	return _pieceColor;
}

ChessPiece::Color ChessPiece::getOppositeColor() const
{
	ChessPiece::Color color = getPieceColor();
	ChessPiece::Color oppositeColor = static_cast<ChessPiece::Color>(ChessPiece::COLOR_COUNT - color - 1);
	return oppositeColor;
}

void ChessPiece::setPieceColor(ChessPiece::Color color) {
	_pieceColor = color;
}

ChessPiece::PieceType ChessPiece::getPieceType() const {
	return _pieceType;
}
void ChessPiece::setPieceType(ChessPiece::PieceType type) {
	_pieceType = type;
}

void ChessPiece::onMove(const Point target, ChessPiece* toRemove, cocos2d::Node* parent)
{
	MoveTo* moveTo = MoveTo::create(0.3f, target);
	CallFunc* callFunc = CallFunc::create([=]() {
		if (toRemove != nullptr) {
			parent->removeChild(toRemove);
		}
	});
	Sequence* sequence = Sequence::create(moveTo, callFunc, nullptr);
	this->runAction(sequence);
}
