#include "ChessQueen.h"
#include "ChessUtility.h"
#include "ChessScene/BoardLayer.h"
#include <algorithm>
#include "GameState.h"

USING_NS_CC;

ChessQueen::ChessQueen() { }
ChessQueen::~ChessQueen() { }

bool ChessQueen::init()
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

ChessQueen* ChessQueen::create(const ChessPiece::PieceType type, const ChessPiece::Color color)
{
	const std::string filePath = ChessUtility::piecePath[color][type];
	ChessQueen* queen = ChessQueen::create();
	if (queen && queen->initWithSpriteFrameName(filePath)) {
		queen->setPieceColor(color);
		queen->setPieceType(type);
		return queen;
	}
	else {
		CC_SAFE_DELETE(queen);
	}
	return queen;
}

std::vector<Rowcol> ChessQueen::getMoveAreas(BoardLayer* board, bool throwException)
{
	std::vector<Rowcol> rowcols;

	bool possible[8];
	std::fill(possible, possible + 8, true);

	try {
		for (int i = 1; i < MAX_ROWCOLS; ++i) {
			for (int j = 0; j < 8; ++j) {
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
	}
	catch (GameState e) {
		if (throwException)
			throw e;
	}

	return rowcols;
}