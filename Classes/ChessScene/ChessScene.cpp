#include "ChessScene/ChessScene.h"
#include "ChessScene/UILayer.h"
#include "ChessScene/BoardLayer.h"
#include "ChessScene/TimerLayer.h"
#include "SimpleAudioEngine.h"
#include "ChessUtility.h"
#include "ChessScene/Pieces/Pieces.h"

USING_NS_CC;

Scene* ChessScene::createScene()
{
	return ChessScene::create();
}

bool ChessScene::init()
{
	if (!Scene::init()) return false;

	_selectedRowcol = Rowcol::IMPOSSIBLE;
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
	Point touchPosition = touch->getLocation();
	Rowcol rowcol = _boardLayer->pointToRowcol(touchPosition);

	if (_boardLayer->isValidRowcol(rowcol)) {
		if (_selectedRowcol != Rowcol::IMPOSSIBLE) {
			if (!tryMovePiece(rowcol) && _boardLayer->getChessPiece(rowcol)) {
				showPossibleRowcols(rowcol);
			}
		}
		else if (_boardLayer->getChessPiece(rowcol)) {
			showPossibleRowcols(rowcol);
		}
	}
	else {
		_selectedRowcol = Rowcol::IMPOSSIBLE;
		_possibleRowcols.clear();
	}
}

void ChessScene::showPossibleRowcols(const Rowcol& rowcol) {
	_selectedRowcol = rowcol;

	ChessPiece* selectedPiece = _boardLayer->getChessPiece(rowcol);
	_possibleRowcols = selectedPiece->getMoveAreas(_boardLayer, rowcol);
	
	for (const auto& rc : _possibleRowcols) {
		Point pos = _boardLayer->rowcolToPoint(rc);
	}
}

bool ChessScene::tryMovePiece(const Rowcol& next) {
	bool bRet = false;
	for (const auto& rc : _possibleRowcols) {
		if (next == rc) {
			bRet = true;
			ChessPiece* selectedPiece = _boardLayer->getChessPiece(_selectedRowcol);
			_boardLayer->moveChessPiece(selectedPiece, _selectedRowcol, next);
			
			_selectedRowcol = Rowcol::IMPOSSIBLE;
			break;
		}
	}
	return bRet;
}