#ifndef __BOARD_LAYER_H__
#define __BOARD_LAYER_H__

#include "cocos2d.h"
#include <string>
#include "ChessScene/Pieces/ChessPiece.h"

struct Rowcol;

constexpr int MAX_ROWCOLS = 8;
constexpr int PIXEL_MARGIN = 16;
constexpr int PIXEL_INTERVAL = 36;

class BoardLayer : public cocos2d::Layer {
private:
	ChessPiece* _board[MAX_ROWCOLS][MAX_ROWCOLS];
	cocos2d::Point _startPoint;
	cocos2d::Point _endPoint;
	float _pixelMargin;
	float _pixelInterval;
private:
	cocos2d::Size initBoardSprite();
public:
	void initLayer();
	void initBoard();
	void initBoardSize(cocos2d::Size baseSize);

	ChessPiece* getChessPiece(const Rowcol& rowcol);
	ChessPiece* getChessPiece(const int& row, const int& column);

	void moveChessPiece(ChessPiece* piece, const Rowcol prev, const Rowcol next);
	void createPiece(Rowcol rowcol, ChessPiece::PieceType type, ChessPiece::Color color);

	bool isValidPos(const cocos2d::Point& pos);
	bool isValidRowcol(const int& row, const int& column);
	bool isValidRowcol(const Rowcol& rowcol);
	
	Rowcol pointToRowcol(cocos2d::Point pos);
	cocos2d::Point rowcolToPoint(Rowcol rowcol);
public:
	BoardLayer();
	virtual ~BoardLayer();
	virtual bool init();
	CREATE_FUNC(BoardLayer);
};

#endif