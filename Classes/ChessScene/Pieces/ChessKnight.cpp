#include "ChessScene/Pieces/ChessKnight.h"
#include "ChessUtility.h"
#include "ChessScene/BoardLayer.h"
#include "GameState.h"

USING_NS_CC;

ChessKnight::ChessKnight() { }
ChessKnight::~ChessKnight() { }

bool ChessKnight::init()
{
	if (!Sprite::create()) return false;
	
	dir[0] = Rowcol(2, -1);
	dir[1] = Rowcol(2, 1);
	dir[2] = Rowcol(1, -2);
	dir[3] = Rowcol(1, 2);
	dir[4] = Rowcol(-1, -2);
	dir[5] = Rowcol(-1, 2);
	dir[6] = Rowcol(-2, -1);
	dir[7] = Rowcol(-2, 1);

	return true;
}

ChessKnight* ChessKnight::create(const ChessPiece::PieceType type, const ChessPiece::Color color)
{
	const std::string filePath = ChessUtility::piecePath[color][type];
	ChessKnight* knight = ChessKnight::create();
	if (knight && knight->initWithSpriteFrameName(filePath)) {
		knight->setPieceColor(color);
		knight->setPieceType(type);
		return knight;
	}
	else {
		CC_SAFE_DELETE(knight);
	}
	return knight;
}

std::vector<Rowcol> ChessKnight::getMoveAreas(BoardLayer* board) {
	std::vector<Rowcol> rowcols;

	for (int i = 0; i < 8; i++) {
		Rowcol target = canAddMove(board, dir[i]);
		if (target != Rowcol::IMPOSSIBLE) {
			rowcols.push_back(target);
		}
	}

	return rowcols;
}