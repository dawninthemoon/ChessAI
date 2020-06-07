#include "ChessKing.h"
#include "ChessUtility.h"
#include "ChessScene/BoardLayer.h"

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

Rowcol ChessKing::canAddMove(BoardLayer* board, const Rowcol base, Rowcol additonal)
{
	try {
		Rowcol target = ChessPiece::canAddMove(board, base, additonal);
		if (target == Rowcol::IMPOSSIBLE)
			return target;
		if (board->checkIsCheckStateForAll(base, target))
			return Rowcol::IMPOSSIBLE;
		return target;
	}
	catch (int e) {
		throw e;
	}
}

Rowcol ChessKing::canAddMoveExceptCheck(BoardLayer * board, const Rowcol base, Rowcol additonal)
{
	try {
		Rowcol target = ChessPiece::canAddMove(board, base, additonal);
		if (target == Rowcol::IMPOSSIBLE)
			return target;
		return target;
	}
	catch (int e) {
		throw e;
	}
}

bool ChessKing::checkIsCheckState(BoardLayer * board, Rowcol current)
{
	try {
		getMoveAreasExceptCheck(board, current);
	}
	catch (int e) {
		return true;
	}
	return false;
}

std::vector<Rowcol> ChessKing::getMoveAreas(BoardLayer* board, const Rowcol & current)
{
	std::vector<Rowcol> rowcols;
	
	try {
		for (int i = 0; i < 8; ++i) {
			Rowcol target = canAddMove(board, current, dir[i]);
			if (target != Rowcol::IMPOSSIBLE) {
				rowcols.push_back(target);
			}
		}
	}
	catch (int e) {
		throw e;
	}

	return rowcols;
}

std::vector<Rowcol> ChessKing::getMoveAreasExceptCheck(BoardLayer* board, const Rowcol & current)
{
	std::vector<Rowcol> rowcols;

	try {
		for (int i = 0; i < 8; ++i) {
			Rowcol target = canAddMoveExceptCheck(board, current, dir[i]);
			if (target != Rowcol::IMPOSSIBLE) {
				rowcols.push_back(target);
			}
		}
	}
	catch (int e) {
		throw e;
	}

	return rowcols;
}