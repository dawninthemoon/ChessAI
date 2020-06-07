#include "ChessPawn.h"
#include "ChessScene/BoardLayer.h"
#include "ChessUtility.h"

USING_NS_CC;

ChessPawn::ChessPawn() { }
ChessPawn::~ChessPawn() { }
bool ChessPawn::init() {
	if (!Sprite::create()) return false;
	_isFirstMove = true;
	return true;
}

ChessPawn* ChessPawn::create(const ChessPiece::PieceType type, const ChessPiece::Color color) {
	const std::string filePath = ChessUtility::piecePath[color][type];
	ChessPawn* pawn = ChessPawn::create();
	if (pawn && pawn->initWithSpriteFrameName(filePath)) {
		pawn->setPieceColor(color);
		pawn->setPieceType(type);
		return pawn;
	}
	else {
		CC_SAFE_DELETE(pawn);
	}
	return pawn;
}

Rowcol ChessPawn::canAddDiagonalMove(BoardLayer* board, const Rowcol base, Rowcol additional) {
	additional.row *= (getPieceColor() == Color::WHITE) ? -1 : 1;
	Rowcol target = base + additional;

	auto piece = board->getChessPiece(target);
	return (piece != nullptr) ? target : Rowcol::IMPOSSIBLE;
}

void ChessPawn::onMove(const cocos2d::Point point, ChessPiece* toRemove, cocos2d::Node* parent)
{
	ChessPiece::onMove(point, toRemove, parent);
	_isFirstMove = false;
}

std::vector<Rowcol> ChessPawn::getMoveAreas(BoardLayer* board, const Rowcol& current) {
	std::vector<Rowcol> rowcols;

	Rowcol target = canAddMove(board, current, Rowcol(1, 0));
	if (target != Rowcol::IMPOSSIBLE) {
		rowcols.push_back(target);
	}

	if (_isFirstMove && (target = canAddMove(board, current, Rowcol(2, 0))) != Rowcol::IMPOSSIBLE) {
		rowcols.push_back(target);
	}

	try {
		target = canAddDiagonalMove(board, current, Rowcol(1, -1));
		if (target != Rowcol::IMPOSSIBLE) {
			rowcols.push_back(target);
		}

		target = canAddDiagonalMove(board, current, Rowcol(1, 1));
		if (target != Rowcol::IMPOSSIBLE) {
			rowcols.push_back(target);
		}
	}
	catch (int e) {
		throw e;
	}

	return rowcols;
}

Rowcol ChessPawn::canAddMove(BoardLayer* board, const Rowcol base, Rowcol additional) {
	Rowcol target = ChessPiece::canAddMove(board, base, additional);
	if (target == Rowcol::IMPOSSIBLE)
		return target;

	if (board->getChessPiece(target))
		target = Rowcol::IMPOSSIBLE;
	return target;
}
