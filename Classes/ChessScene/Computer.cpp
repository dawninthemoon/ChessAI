#include "ChessScene/Computer.h"
#include "ChessScene/Pieces/Pieces.h"
#include "RowCol.h"
#include "ChessScene/BoardLayer.h"
#include "GameState.h"

Computer::Computer()  { 
	_cpuColor = ChessPiece::BLACK;
}
Computer::~Computer() { }

Rowcol Computer::decideMove(BoardLayer* board, ChessPiece*& selectedPiece) {
	Rowcol selectedNext = Rowcol::IMPOSSIBLE;
	int maxScore = -987654321;

	auto pieces = board->getPiecesByColor(_cpuColor);
	for (const auto& piece : pieces) {
		auto moves = piece->getMoveAreas(board);
		for (const auto& rc : moves) {
			int score = board->calculateScoreIfMoved(piece, rc);
			if (score > maxScore) {
				maxScore = score;
				selectedNext = rc;
				selectedPiece = piece;
			}
		}
	}

	return selectedNext;
}

int Computer::getColor() const {
	return _cpuColor;
}
