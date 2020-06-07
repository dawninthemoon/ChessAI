#include "ChessPawn.h"
#include "ChessScene/BoardLayer.h"
#include "ChessUtility.h"
#include "GameState.h"

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

Rowcol ChessPawn::canAddDiagonalMove(BoardLayer* board, Rowcol additional) {
	additional.row *= (getPieceColor() == Color::WHITE) ? -1 : 1;
	Rowcol target = getRowcol() + additional;

	auto piece = board->getChessPiece(target);
	if ((piece != nullptr) &&
		(piece->getPieceColor() != getPieceColor()) &&
		(piece->getPieceType() == ChessPiece::KING)) {
		throw getCheckState(getPieceColor());
	}

	return (piece != nullptr) ? target : Rowcol::IMPOSSIBLE;
}

void ChessPawn::onMove(const cocos2d::Point point, ChessPiece* toRemove, cocos2d::Node* parent)
{
	ChessPiece::onMove(point, toRemove, parent);
	_isFirstMove = false;
}

std::vector<Rowcol> ChessPawn::getMoveAreas(BoardLayer* board, bool throwException) {
	std::vector<Rowcol> rowcols;

	Rowcol target = canAddMove(board, Rowcol(1, 0));
	if (target != Rowcol::IMPOSSIBLE) {
		rowcols.push_back(target);
	}

	if (_isFirstMove && (target = canAddMove(board, Rowcol(2, 0))) != Rowcol::IMPOSSIBLE) {
		rowcols.push_back(target);
	}

	try {
		target = canAddDiagonalMove(board, Rowcol(1, -1));
		if (target != Rowcol::IMPOSSIBLE) {
			rowcols.push_back(target);
		}

		target = canAddDiagonalMove(board, Rowcol(1, 1));
		if (target != Rowcol::IMPOSSIBLE) {
			rowcols.push_back(target);
		}
	}
	catch (GameState e) {
		if (throwException)
			throw e;
	}

	return rowcols;
}

Rowcol ChessPawn::canAddMove(BoardLayer* board, Rowcol additional) {
	additional.row *= (getPieceColor() == Color::WHITE) ? -1 : 1;
	Rowcol target = getRowcol() + additional;

	if (!board->isValidRowcol(target))
		return Rowcol::IMPOSSIBLE;
	if (board->getChessPiece(target))
		target = Rowcol::IMPOSSIBLE;
	
	return target;
}
