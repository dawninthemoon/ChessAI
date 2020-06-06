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
	if (pawn && pawn->initWithFile(filePath)) {
		pawn->setPieceColor(color);
		return pawn;
	}
	else {
		CC_SAFE_DELETE(pawn);
	}
	return pawn;
}

Rowcol ChessPawn::canAddDiagonalMove(BoardLayer* board, const Rowcol base, Rowcol additonal) {
	additonal.row *= (getPieceColor() == Color::WHITE) ? -1 : 1;
	Rowcol target = base + additonal;

	auto piece = board->getChessPiece(target);
	return (piece != nullptr) ? target : Rowcol::IMPOSSIBLE;
}

std::vector<Rowcol> ChessPawn::getMoveAreas(BoardLayer* board, const Rowcol& current) {
	std::vector<Rowcol> moveVector;

	Rowcol target = canAddMove(board, current, Rowcol(1, 0));
	if (target != Rowcol::IMPOSSIBLE) {
		moveVector.push_back(target);
	}

	if (_isFirstMove && (target = canAddMove(board, current, Rowcol(2, 0))) != Rowcol::IMPOSSIBLE) {
		moveVector.push_back(target);
	}

	target = canAddDiagonalMove(board, current, Rowcol(1, -1));
	if (target != Rowcol::IMPOSSIBLE) {
		moveVector.push_back(target);
	}

	target = canAddDiagonalMove(board, current, Rowcol(1, 1));
	if (target != Rowcol::IMPOSSIBLE) {
		moveVector.push_back(target);
	}

	return moveVector;
}