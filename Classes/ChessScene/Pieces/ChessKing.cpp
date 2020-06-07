#include "ChessKing.h"
#include "ChessUtility.h"
#include "ChessScene/BoardLayer.h"
#include "GameState.h"

USING_NS_CC;

ChessKing::ChessKing() { }
ChessKing::~ChessKing() { }

bool ChessKing::init()
{
	if (!Sprite::create()) return false;

	dir[0] = Rowcol(1, -1);
	dir[1] = Rowcol(1, 1);
	dir[2] = Rowcol(-1, -1);
	dir[3] = Rowcol(-1, 1);
	dir[4] = Rowcol(-1, 0);
	dir[5] = Rowcol(1, 0);
	dir[6] = Rowcol(0, -1);
	dir[7] = Rowcol(0, 1);

	return true;
}

ChessKing* ChessKing::create(const ChessPiece::PieceType type, const ChessPiece::Color color)
{
	const std::string filePath = ChessUtility::piecePath[color][type];
	ChessKing* king = ChessKing::create();
	if (king && king->initWithSpriteFrameName(filePath)) {
		king->setPieceColor(color);
		king->setPieceType(type);
		return king;
	}
	else {
		CC_SAFE_DELETE(king);
	}
	return king;
}

Rowcol ChessKing::canAddMove(BoardLayer* board, Rowcol additonal)
{
	try {
		Rowcol target = ChessPiece::canAddMove(board, additonal);
		if (target == Rowcol::IMPOSSIBLE)
			return target;
		if (board->isKingisStalemated(this, target))
			return Rowcol::IMPOSSIBLE;
		return target;
	}
	catch (GameState e) {
		throw e;
	}
}

Rowcol ChessKing::canAddMoveExceptCheck(BoardLayer* board, Rowcol additonal)
{
	try {
		Rowcol target = ChessPiece::canAddMove(board, additonal);
		if (target == Rowcol::IMPOSSIBLE)
			return target;
		return target;
	}
	catch (GameState e) {
		throw e;
	}
}

bool ChessKing::checkIsCheckState(BoardLayer* board)
{
	try {
		getMoveAreasExceptCheck(board);
	}
	catch (GameState e) {
		return true;
	}
	return false;
}

std::vector<Rowcol> ChessKing::getMoveAreas(BoardLayer* board, bool throwException)
{
	std::vector<Rowcol> rowcols;
	
	try {
		for (int i = 0; i < 8; ++i) {
			Rowcol target = canAddMove(board, dir[i]);
			if (target != Rowcol::IMPOSSIBLE) {
				rowcols.push_back(target);
			}
		}
	}
	catch (GameState e) {
		if (throwException)
			throw e;
	}

	return rowcols;
}

std::vector<Rowcol> ChessKing::getMoveAreasExceptCheck(BoardLayer* board)
{
	std::vector<Rowcol> rowcols;

	try {
		for (int i = 0; i < 8; ++i) {
			Rowcol target = canAddMoveExceptCheck(board, dir[i]);
			if (target != Rowcol::IMPOSSIBLE) {
				rowcols.push_back(target);
			}
		}
	}
	catch (GameState e) {
		throw e;
	}

	return rowcols;
}