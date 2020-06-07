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
	_currentTurn = ChessPiece::WHITE;
	_selectedPiece = nullptr;
	_selectedRowcol = Rowcol::IMPOSSIBLE;
	for (int i = 0; i < ChessPiece::COLOR_COUNT; ++i)
		_isCheck[i] = false;
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
	Rect pieceRect = Rect(0, 0, 32, 32);

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
	if (_isGameEnd) return;

	Point touchPosition = touch->getLocation();
	Rowcol rowcol = _boardLayer->pointToRowcol(touchPosition);
	
	auto prev = this->getChildByTag(1);
	this->removeChild(prev);

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
	try {
		ChessPiece::Color color = _selectedPiece->getPieceColor();
		_boardLayer->moveChessPiece(_selectedPiece, next);
		if (_isCheck[color])
			throw (color == ChessPiece::WHITE) ? GameState::DEFEAT_BLACK : GameState::DEFEAT_WHITE;
		setCheck(false);
	}
	catch (GameState e) {
		switch (e) {
		case GameState::CHECK_WHITE:
			setCheck(true);
			break;
		case GameState::CHECK_BLACK:
			setCheck(true);
			break;
		case GameState::CHECKMATE_WHITE:
		case GameState::CHECKMATE_BLACK:
		case GameState::DEFEAT_WHITE:
		case GameState::DEFEAT_BLACK:
			onCheckmate(e);
			break;
		default:
			break;
		}
	}
}

void ChessScene::setCheck(bool check) {
	auto oppositeColor = _selectedPiece->getOppositeColor();
	_isCheck[oppositeColor] = check;
	_currentTurn = oppositeColor;

	if (_currentTurn == _computer->getColor()) {
		this->runAction(
			Sequence::create(
				DelayTime::create(0.5f),
				CallFunc::create([&]() { 
					Rowcol next = _computer->decideMove(_boardLayer, _selectedPiece);
					movePiece(next); 
				}),
				nullptr));
	}
}

void ChessScene::onCheckmate(GameState state) {
	_isGameEnd = true;

	// temp
	std::string str = (state == GameState::CHECKMATE_BLACK || state == GameState::DEFEAT_BLACK) ? "BLACK CHECKMATE" : "WHITE CHECKMATE";
	auto label = Label::create(str, "Arial", 24);
	label->setColor(Color3B::RED);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	label->setPosition(visibleSize * 0.5f);
	label->setScale(ChessUtility::getSpriteScale());

	this->addChild(label);
}