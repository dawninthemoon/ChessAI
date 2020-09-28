#ifndef __CHESS_SCENE_H__
#define __CHESS_SCENE_H__

#include "cocos2d.h"
#include "RowCol.h"
#include "ChessScene/Pieces/ChessPiece.h"

class UILayer;
class BoardLayer;
class TimerLayer;
class ChessPiece;
class Computer;

class ChessScene : public cocos2d::Scene
{
private:
	bool _isGameEnd;
	bool _waiting;
	int _currentTurn;
	UILayer* _uiLayer;
	BoardLayer* _boardLayer;
	TimerLayer* _timerLayer;
	Rowcol _selectedRowcol;
	ChessPiece* _selectedPiece;
	cocos2d::Label* _checkLabel;
	std::vector<Rowcol> _possibleRowcols;
	Computer* _computer;
private:
	void initData();
	bool initLayers();
	bool initSpriteFrames();
	bool initTouchListeners();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	
	void setCheck(bool check);
	void onCheckmate(ChessPiece::Color color);

	void showPossibleRowcols(const Rowcol& rowcol);
	bool tryMovePiece(const Rowcol& next);
	void movePiece(const Rowcol& next);
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
    CREATE_FUNC(ChessScene);
private:
	enum LayerZOrder {
		BoardLayerOrder,
		TimerLayerOrder,
		UILayerOrder
	};
};

#endif // __CHESS_SCENE_H__
