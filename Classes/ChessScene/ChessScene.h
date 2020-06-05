#ifndef __CHESS_SCENE_H__
#define __CHESS_SCENE_H__

#include "cocos2d.h"

class UILayer;
class BoardLayer;
class TimerLayer;

class ChessScene : public cocos2d::Scene
{
private:
	UILayer* _uiLayer;
	BoardLayer* _boardLayer;
	TimerLayer* _timerLayer;
private:
	bool initLayers();
	bool initTouchListeners();
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
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