#include "ChessScene/Pieces/ChessBishop.h"
#include "ChessUtility.h"
#include "ChessScene/BoardLayer.h"
#include "GameState.h"

USING_NS_CC;

ChessBishop::ChessBishop() { }
ChessBishop::~ChessBishop() { }

bool ChessBishop::init()
{
	if (!Sprite::create()) return false;

	dir[0] = Rowcol(1, -1);
	dir[1] = Rowcol(1, 1);
	dir[2] = Rowcol(-1, -1);
	dir[3] = Rowcol(-1, 1);

	return true;
}

ChessBishop* ChessBishop::create(const ChessPiece::PieceType type, const ChessPiece::Color color)
{
	const std::string filePath = ChessUtility::piecePath[color][type];
	ChessBishop* bishop = ChessBishop::create();
	if (bishop && bishop->initWithSpriteFrameName(filePath)) {
		bishop->setPieceColor(color);
		bishop->setPieceType(type);
		return bishop;
	}
	else {
		CC_SAFE_DELETE(bishop);
	}
	return bishop;
}

std::vector<Rowcol> ChessBishop::getMoveAreas(BoardLayer* board) {
	std::vector<Rowcol> rowcols;

	bool possible[4];
	std::fill(possible, possible + 4, true);

	for (int i = 1; i < MAX_ROWCOLS; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (!possible[j]) continue;
			Rowcol target = canAddMove(board, dir[j] * i);
			if (target != Rowcol::IMPOSSIBLE) {
				rowcols.push_back(target);
				if (board->getChessPiece(target))
					possible[j] = false;
			}
			else {
				possible[j] = false;
			}
		}
	}

	return rowcols;
}