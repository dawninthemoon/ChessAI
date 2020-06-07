#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "ChessScene/Pieces/ChessPiece.h"

enum class GameState {
	CHECK_WHITE,
	CHECKMATE_WHITE,
	CHECK_BLACK,
	CHECKMATE_BLACK,
	DEFEAT_WHITE,
	DEFEAT_BLACK
};

inline GameState getCheckState(ChessPiece::Color color) {
	return (color == ChessPiece::Color::WHITE) ? GameState::CHECK_BLACK : GameState::CHECK_WHITE;
}

inline GameState getCheckmateState(ChessPiece::Color color) {
	return (color == ChessPiece::Color::WHITE) ? GameState::CHECK_BLACK : GameState::CHECK_WHITE;
}

#endif