#include "ChessScene/ChessScene.h"
#include "ChessScene/UILayer.h"
#include "ChessScene/BoardLayer.h"
#include "ChessScene/TimerLayer.h"
#include "SimpleAudioEngine.h"
#include "Rowcol.h"
#include "ChessUtility.h"

USING_NS_CC;

Scene* ChessScene::createScene()
{
	return ChessScene::create();
}

bool ChessScene::init()
{
	if (!Scene::init()) return false;

	do {
		CC_BREAK_IF(!initLayers());
		CC_BREAK_IF(!initTouchListeners());
	} while (false);

	return true;
}

bool ChessScene::initLayers() {
	_boardLayer = BoardLayer::create();
	if (!_boardLayer) return false;
	this->addChild(_boardLayer, LayerZOrder::BoardLayerOrder);

	_timerLayer = TimerLayer::create();
	if (!_timerLayer) return false;
	this->addChild(_timerLayer, LayerZOrder::TimerLayerOrder);

	_uiLayer = UILayer::create();
	if (!_uiLayer) return false;
	this->addChild(_uiLayer, LayerZOrder::UILayerOrder);

	return true;
}

bool ChessScene::initTouchListeners() {
	auto listener = EventListenerTouchOneByOne::create();
	if (!listener) return false;
	listener->setSwallowTouches(true);
	
	listener->onTouchBegan = CC_CALLBACK_2(ChessScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ChessScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChessScene::onTouchEnded, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool ChessScene::onTouchBegan(Touch* touch, Event* event) {
	return true;
}

void ChessScene::onTouchMoved(Touch* touch, Event* event) {

}

void ChessScene::onTouchEnded(Touch* touch, Event* event) {
	try {
		Point touchPosition = touch->getLocation();

		RowCol rowcol = _boardLayer->pointToRowcol(touchPosition);
		log("(%d, %d)", rowcol.row, rowcol.column);
	}
	catch (int e) {

	}
}