#include "ChessScene/ChessScene.h"
#include "ChessScene/UILayer.h"
#include "ChessScene/BoardLayer.h"
#include "ChessScene/TimerLayer.h"
#include "SimpleAudioEngine.h"
#include "ChessUtility.h"
#include "GameState.h"
#include "ChessScene/Pieces/Pieces.h"
#include "ChessScene/Computer.h"

USING_NS_CC;

Scene* ChessScene::createScene()
{
	return ChessScene::create();
}

bool ChessScene::init()
{
	if (!Scene::init()) return false;

	initData();
	do {
		CC_BREAK_IF(!initSpriteFrames());
		CC_BREAK_IF(!initLayers());
		CC_BREAK_IF(!initTouchListeners());
	} while (false);

	return true;
}

void ChessScene::initData() {
	_isGameEnd = false;
	_waiting = false;
	_currentTurn = ChessPiece::WHITE;
	_selectedPiece = nullptr;
	_selectedRowcol = Rowcol::IMPOSSIBLE;
	_computer = new Computer();
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

bool ChessScene::initSpriteFrames() {
	auto cache = SpriteFrameCache::getInstance();
	Rect pieceRect = Rect(0, 0, 64, 64);

	for (int i = 0; i < ChessPiece::COLOR_COUNT; ++i) {
		for (int j = 0; j < ChessPiece::TYPE_COUNT; ++j) {
			auto path = ChessUtility::piecePath[i][j];
			auto sprite = SpriteFrame::create(path, pieceRect);
			cache->addSpriteFrame(sprite, path);
			if (!sprite) return false;
		}
	}
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
	if (_isGameEnd || _waiting) return;

	Point touchPosition = touch->getLocation();
	Rowcol rowcol = _boardLayer->pointToRowcol(touchPosition);
	
	auto prev = this->getChildByTag(1);
	this->removeChild(prev);

	if (_checkLabel) {
		this->removeChild(_checkLabel);
		_checkLabel->release();
	}

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
		_boardLayer->removeAllPossibleRowcols();
		_selectedRowcol = Rowcol::IMPOSSIBLE;
		_selectedPiece = nullptr;
		_possibleRowcols.clear();
	}
}

void ChessScene::showPossibleRowcols(const Rowcol& rowcol) {
	_selectedRowcol = rowcol;

	_selectedPiece = _boardLayer->getChessPiece(rowcol);
	ChessPiece::Color color = _selectedPiece->getPieceColor();

	if (_currentTurn != color) return;
	
	_possibleRowcols = _selectedPiece->getMoveAreas(_boardLayer);

	ChessPiece::PieceType type = _selectedPiece->getPieceType();
	std::string path = ChessUtility::piecePath[color][type];
	
	for (const auto& rc : _possibleRowcols) {
		_boardLayer->showPossibleRowcols(rc, path);
	}
}

bool ChessScene::tryMovePiece(const Rowcol& next) {
	bool bRet = false;

	_boardLayer->removeAllPossibleRowcols();

	for (const auto& rc : _possibleRowcols) {
		if (next == rc) {
			bRet = true;
			movePiece(next);
			break;
		}
	}

	_selectedRowcol = Rowcol::IMPOSSIBLE;
	_selectedPiece = nullptr;

	return bRet;
}

void ChessScene::movePiece(const Rowcol& next)
{
	ChessPiece::Color color = _selectedPiece->getPieceColor();
	_boardLayer->moveChessPiece(_selectedPiece, next);
	
	ChessPiece::Color oppositeColor = _selectedPiece->getOppositeColor();
	
	if (_boardLayer->isInCheck(oppositeColor)) {
		if (_boardLayer->isCheckmate(color))
			onCheckmate(color);
		else
			setCheck(true);
	}
	else
		setCheck(false);
}

void ChessScene::setCheck(bool check) {
	auto color = _selectedPiece->getPieceColor();
	auto oppositeColor = _selectedPiece->getOppositeColor();
	_currentTurn = oppositeColor;

	if (check) {
		std::string str = (color == ChessPiece::Color::BLACK) ? "BLACK" : "WHITE";
		str += " CHECK";

		if (_checkLabel) {
			this->removeChild(_checkLabel);
			_checkLabel->release();
		}
		_checkLabel = Label::create(str, "Arial", 24);
		_checkLabel->setColor(Color3B::RED);
		auto visibleSize = Director::getInstance()->getVisibleSize();
		_checkLabel->setPosition(visibleSize * 0.5f);
		_checkLabel->setScale(ChessUtility::getSpriteScale());
	
		this->addChild(_checkLabel);
	}

	if (_currentTurn == _computer->getColor()) {
		_waiting = true;
		this->runAction(
			Sequence::create(
				DelayTime::create(0.5f),
				CallFunc::create([&]() { 
					_waiting = false;
					Rowcol next = _computer->decideMove(_boardLayer, _selectedPiece);
					movePiece(next); 
				}
			),
			nullptr)
		);
	}
}

void ChessScene::onCheckmate(ChessPiece::Color color) {
	_isGameEnd = true;

	std::string str = (color == ChessPiece::Color::BLACK) ? "BLACK" : "WHITE";
	str += " CHECKMATE";

	if (_checkLabel) {
		this->removeChild(_checkLabel);
		_checkLabel->release();
	}
	_checkLabel = Label::create(str, "Arial", 24);
	_checkLabel->setColor(Color3B::RED);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_checkLabel->setPosition(visibleSize * 0.5f);
	_checkLabel->setScale(ChessUtility::getSpriteScale());

	this->addChild(_checkLabel);
}