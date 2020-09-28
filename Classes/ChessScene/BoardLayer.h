#ifndef __BOARD_LAYER_H__
#define __BOARD_LAYER_H__

#include "cocos2d.h"
#include <string>
#include "ChessScene/Pieces/ChessPiece.h"

struct Rowcol;
class ChessKing;

constexpr int MAX_ROWCOLS = 8;
constexpr int PIXEL_MARGIN = 8;
constexpr int PIXEL_INTERVAL = 64;

class BoardLayer : public cocos2d::Layer {
private:
	// temporary
	cocos2d::Sprite* _tempPieces[MAX_ROWCOLS][MAX_ROWCOLS];
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

	std::vector<ChessPiece*> getPiecesByColor(ChessPiece::Color color);

	void setChessPiece(ChessPiece* piece, const Rowcol rowcol);
	void setChessPiece(ChessPiece* piece, const int row, const int column);
	ChessPiece* getChessPiece(const Rowcol rowcol) const;
	ChessPiece* getChessPiece(const int row, const int column) const;

	int evaluateBoard(ChessPiece::Color color);
	void moveChessPiece(ChessPiece* piece, const Rowcol next);
	
	bool isInCheck(ChessPiece::Color myColor);
	bool isCheckmate(ChessPiece::Color oppositeColor);

	void createPiece(Rowcol rowcol, ChessPiece::PieceType type, ChessPiece::Color color);

	bool isValidPos(const cocos2d::Point& pos);
	bool isValidRowcol(const int row, const int column) const;
	bool isValidRowcol(const Rowcol rowcol) const;

	void showPossibleRowcols(Rowcol rowcol, const std::string& path);
	void removeAllPossibleRowcols();

	Rowcol pointToRowcol(cocos2d::Point pos);
	cocos2d::Point rowcolToPoint(Rowcol rowcol);
public:
	BoardLayer();
	virtual ~BoardLayer();
	virtual bool init();
	CREATE_FUNC(BoardLayer);
};

#endif