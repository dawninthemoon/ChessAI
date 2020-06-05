#include "ChessScene/BoardLayer.h"
#include "ChessUtility.h"
#include "RowCol.h"

USING_NS_CC;

BoardLayer::BoardLayer()
	: _pixelMargin(PIXEL_MARGIN), _pixelInterval(PIXEL_INTERVAL)
{ }
BoardLayer::~BoardLayer() { }

bool BoardLayer::init() {
	if (!Layer::init()) return false;

	initLayer();

	return true;
}

void BoardLayer::initLayer() {
	Size boardContentSize = initBoard();
	initBoardSize(boardContentSize);
}

Size BoardLayer::initBoard() {
	Size winSize = Director::getInstance()->getVisibleSize();
	float scale = ChessUtility::getSpriteScale();

	Sprite* boardSprite = Sprite::create("etc/chessBoard.png");
	boardSprite->getTexture()->setAliasTexParameters();

	boardSprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	boardSprite->setScale(scale);
	boardSprite->setPosition(winSize / 2.0f);

	this->addChild(boardSprite);

	Sprite* spr = Sprite::create("etc/pieces/spr_piece_bishop_white.png");
	spr->getTexture()->setAliasTexParameters();
	
	spr->setAnchorPoint(Vec2(0.5f, 0.5f));
	spr->setScale(scale);
	spr->setPosition(winSize / 2.0f);
	this->addChild(spr);

	Size contentSize = boardSprite->getContentSize();
	return contentSize;
}

void BoardLayer::initBoardSize(Size baseSize) {
	float scale = ChessUtility::getSpriteScale();
	Size adjustedSize = baseSize * scale;
	Size winSize = Director::getInstance()->getVisibleSize();

	_startPoint = Point(
		winSize.width / 2.0f - adjustedSize.width / 2.0f,
		winSize.height / 2.0f - adjustedSize.height / 2.0f
	);

	_endPoint = Point(
		winSize.width / 2.0f + adjustedSize.width / 2.0f,
		winSize.height / 2.0f + adjustedSize.height / 2.0f
	);

	_pixelMargin *= scale;
	_pixelInterval *= scale;
}

bool BoardLayer::isValidPos(Point pos) {
	return
		(pos.x >= _startPoint.x + _pixelMargin) &&
		(pos.x <= _endPoint.x - _pixelMargin) &&
		(pos.y >= _startPoint.y + _pixelMargin) &&
		(pos.y <= _endPoint.y - _pixelMargin);
}

RowCol BoardLayer::pointToRowcol(cocos2d::Point pos) {
	RowCol ret = RowCol::IMPOSSIBLE;

	if (isValidPos(pos)) {
		pos.x = pos.x - _pixelMargin - _startPoint.x;
		pos.y = pos.y - _pixelMargin - _startPoint.y;

		int col = static_cast<int>(pos.x) / _pixelInterval;
		int row = static_cast<int>(pos.y) / _pixelInterval;

		ret = RowCol(7 - row, col);
	}

	return ret;
}