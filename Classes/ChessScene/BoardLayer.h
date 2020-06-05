#ifndef __BOARD_LAYER_H__
#define __BOARD_LAYER_H__

#include "cocos2d.h"
#include <string>

class ChessPiece;
struct RowCol;

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
public:
	void initLayer();
	cocos2d::Size initBoard();
	void initBoardSize(cocos2d::Size baseSize);

	inline bool isValidPos(cocos2d::Point pos);
	RowCol pointToRowcol(cocos2d::Point pos);
public:
	BoardLayer();
	virtual ~BoardLayer();
	virtual bool init();
	CREATE_FUNC(BoardLayer);
};

#endif