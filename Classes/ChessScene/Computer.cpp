#include "ChessScene/Computer.h"
#include "ChessScene/Pieces/Pieces.h"
#include "RowCol.h"
#include "ChessScene/BoardLayer.h"
#include "GameState.h"
#include <algorithm>

Computer::Computer()  { 
	_cpuColor = ChessPiece::BLACK;
}
Computer::~Computer() { }

Rowcol Computer::decideMove(BoardLayer* board, ChessPiece*& selectedPiece) {
	Rowcol selectedNext = Rowcol::IMPOSSIBLE;
	int maxScore = std::numeric_limits<int>::min();

	int bestMove = std::numeric_limits<int>::min();
	auto pieces = board->getPiecesByColor(_cpuColor);
	int depth = 2;

	for (const auto& piece : pieces) {
		auto areas = piece->getMoveAreas(board);
		Rowcol prevRowcol = piece->getRowcol();
		for (const auto& rc : areas) {
			auto temp = board->getChessPiece(rc);

			board->setChessPiece(piece, rc);
			board->setChessPiece(nullptr, prevRowcol);

			int value 
				= minimax(
					board,
					piece->getOppositeColor(),
					std::numeric_limits<int>::min(),
					std::numeric_limits<int>::max(),
					depth);

			board->setChessPiece(piece, prevRowcol);
			board->setChessPiece(temp, rc);

			if (value >= bestMove) {
				bestMove = value;
				selectedPiece = board->getChessPiece(prevRowcol);
				selectedNext = rc;
			}
		}
	}

	return selectedNext;
}

int Computer::minimax(BoardLayer* board, ChessPiece::Color color, int alpha, int beta, int depth) {
	if (depth == 0) {
		using PColor = ChessPiece::Color;
		PColor oppositeColor = (color == PColor::BLACK) ? PColor::WHITE : PColor::BLACK;
		return -board->evaluateBoard(oppositeColor);
	}

	auto pieces = board->getPiecesByColor(color);
	int bestMove = 0;
	if (color == ChessPiece::Color::BLACK)
		bestMove = std::numeric_limits<int>::min() + 1;
	else
		bestMove = std::numeric_limits<int>::max() - 1;

	for (const auto& piece : pieces) {
		auto oppositeColor = piece->getOppositeColor();
		auto areas = piece->getMoveAreas(board);
		Rowcol prevRowcol = piece->getRowcol();

		for (const auto& rc : areas) {
			auto temp = board->getChessPiece(rc);

			board->setChessPiece(piece, rc);
			board->setChessPiece(nullptr, prevRowcol);

			int value = minimax(board, oppositeColor, alpha, beta, depth - 1);
			if (color == ChessPiece::Color::BLACK)
				bestMove = std::max(bestMove, value);
			else
				bestMove = std::min(bestMove, value);

			board->setChessPiece(piece, prevRowcol);
			board->setChessPiece(temp, rc);
			
			if (color == ChessPiece::Color::BLACK) {
				alpha = std::max(alpha, bestMove);
				if (beta <= alpha) return bestMove;
			}
			else {
				beta = std::min(beta, bestMove);
				if (beta <= alpha) return bestMove;
			}
		}
	}

	return bestMove;
}

int Computer::getColor() const {
	return _cpuColor;
}
