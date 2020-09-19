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
	Rowcol target = ChessPiece::canAddMove(board, additonal);
	if (target == Rowcol::IMPOSSIBLE)
		return target;
	return target;
}

std::vector<Rowcol> ChessKing::getMoveAreas(BoardLayer* board) {
	std::vector<Rowcol> rowcols;
	
	for (int i = 0; i < 8; ++i) {
		Rowcol target = canAddMove(board, dir[i]);
		if (target != Rowcol::IMPOSSIBLE) {
			rowcols.push_back(target);
		}
	}

	return rowcols;
}