#include "ChessRook.h"
#include "ChessUtility.h"
#include "ChessScene/BoardLayer.h"
#include "GameState.h"

USING_NS_CC;

ChessRook::ChessRook() { }
ChessRook::~ChessRook() { }

bool ChessRook::init()
{
	if (!Sprite::create()) return false;

	dir[0] = Rowcol(-1, 0);
	dir[1] = Rowcol(1, 0);
	dir[2] = Rowcol(0, -1);
	dir[3] = Rowcol(0, 1);

	return true;
}

ChessRook* ChessRook::create(const ChessPiece::PieceType type, const ChessPiece::Color color)
{
	const std::string filePath = ChessUtility::piecePath[color][type];
	ChessRook* rook = ChessRook::create();
	if (rook && rook->initWithSpriteFrameName(filePath)) {
		rook->setPieceColor(color);
		rook->setPieceType(type);
		return rook;
	}
	else {
		CC_SAFE_DELETE(rook);
	}
	return rook;
}

std::vector<Rowcol> ChessRook::getMoveAreas(BoardLayer* board, bool throwException)
{
	std::vector<Rowcol> rowcols;

	bool possible[4];
	std::fill(possible, possible + 4, true);

	try {
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
	}
	catch (GameState e) {
		if (throwException)
			throw e;
	}

	return rowcols;
}