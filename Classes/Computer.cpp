#include "ChessScene/Computer.h"
#include "ChessScene/Pieces/Pieces.h"
#include "RowCol.h"
#include "ChessScene/BoardLayer.h"

Computer::Computer()  { 
	_cpuColor = ChessPiece::BLACK;
}
Computer::~Computer() { }

Rowcol Computer::decideMove(BoardLayer* board, Rowcol& selectedPrev, ChessPiece*& selectedPiece) {
	Rowcol selectedNext = Rowcol::IMPOSSIBLE;
	int maxScore = -987654321;

	for (int r = 0; r < MAX_ROWCOLS; ++r) {
		for (int c = 0; c < MAX_ROWCOLS; ++c) {
			ChessPiece* piece = board->getChessPiece(r, c);
			if (piece == nullptr || piece->getPieceColor() != _cpuColor) continue;
			Rowcol current = Rowcol(r, c);
			auto moves = piece->getMoveAreas(board, current);
			for (const auto& rc : moves) {
				int score = board->calculateScoreIfMoved(
									piece,
									piece->getPieceColor(),
									current,
									rc);
				
				if (score > maxScore) {
					maxScore = score;
					selectedPrev = current;
					selectedNext = rc;
					selectedPiece = piece;
				}
			}
		}
	}

	return selectedNext;
}

int Computer::getColor() const {
	return _cpuColor;
}
