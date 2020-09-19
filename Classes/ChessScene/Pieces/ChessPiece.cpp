#include "ChessScene/Pieces/ChessPiece.h"
#include "ChessScene/BoardLayer.h"
#include "GameState.h"

USING_NS_CC;

ChessPiece::ChessPiece() { }
ChessPiece::~ChessPiece() { }

bool ChessPiece::init() {
	if (!Sprite::create()) return false;
	return true;
}

Rowcol ChessPiece::canAddMove(BoardLayer* board, Rowcol additional) {
	additional.row *= (getPieceColor() == Color::WHITE) ? -1 : 1;
	Rowcol target = _rowcol + additional;

	if (!board->isValidRowcol(target))
		return Rowcol::IMPOSSIBLE;

	ChessPiece* piece = board->getChessPiece(target);
	if (piece != nullptr) {
		if (piece->getPieceColor() == getPieceColor())
			return Rowcol::IMPOSSIBLE;
	}

	return target;
}

bool ChessPiece::checkIsCheckState(BoardLayer* board) {
	auto areas = getMoveAreas(board);
	for (const auto& rc : areas) {
		auto piece = board->getChessPiece(rc);
		if ((piece != nullptr) && (piece->getPieceType() == ChessPiece::KING)) {
			return true;
		}
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

void ChessPiece::onMove(const Point target, ChessPiece* toRemove, cocos2d::Node* parent) {
	MoveTo* moveTo = MoveTo::create(0.3f, target);
	CallFunc* callFunc = CallFunc::create([=]() {
		if (toRemove != nullptr) {
			parent->removeChild(toRemove);
		}
	});
	Sequence* sequence = Sequence::create(moveTo, callFunc, nullptr);
	this->runAction(sequence);
}

void ChessPiece::setRowcol(Rowcol rowcol) {
	_rowcol = rowcol;
}

Rowcol ChessPiece::getRowcol() const {
	return _rowcol;
}
