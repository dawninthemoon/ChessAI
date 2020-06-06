#include "ChessScene/BoardLayer.h"
#include "ChessUtility.h"
#include "RowCol.h"
#include "ChessScene/Pieces/Pieces.h"

USING_NS_CC;

BoardLayer::BoardLayer()
	: _pixelMargin(PIXEL_MARGIN), _pixelInterval(PIXEL_INTERVAL)
{ 
	for (int i = 0; i < MAX_ROWCOLS; ++i) {
		for (int j = 0; j < MAX_ROWCOLS; ++j) {
			_board[i][j] = nullptr;
		}
	}
}
BoardLayer::~BoardLayer() { }

bool BoardLayer::init() {
	if (!Layer::init()) return false;

	initLayer();

	return true;
}

void BoardLayer::initLayer() {
	Size boardContentSize = initBoardSprite();
	initBoardSize(boardContentSize);
	initBoard();
}

void BoardLayer::initBoard() {
	const int pawnRow = 2;
	for (int pawnColumn = 0; pawnColumn < 8; ++pawnColumn) {
		Rowcol whiteRowcol = Rowcol(MAX_ROWCOLS - pawnRow, pawnColumn);
		createPiece(whiteRowcol, ChessPiece::PAWN, ChessPiece::WHITE);
		
		Rowcol blackRowcol = Rowcol(pawnRow, pawnColumn);
		createPiece(blackRowcol, ChessPiece::PAWN, ChessPiece::BLACK);
	}
}

Size BoardLayer::initBoardSprite() {
	Size winSize = Director::getInstance()->getVisibleSize();

	const std::string boardFileName = "etc/spr_chessBoard.png";
	auto boardSprite = ChessUtility::createSprite(boardFileName, this, winSize * 0.5f);

	Size contentSize = boardSprite->getContentSize();
	return contentSize;
}

void BoardLayer::initBoardSize(Size baseSize) {
	float scale = ChessUtility::getSpriteScale();
	Size adjustedSize = baseSize * scale;
	Size winSize = Director::getInstance()->getVisibleSize();

	_startPoint = Point(
		winSize.width / 2.0f - adjustedSize.width / 2.0f,
		winSize.height / 2.0f + adjustedSize.height / 2.0f
	);

	_endPoint = Point(
		winSize.width / 2.0f + adjustedSize.width / 2.0f,
		winSize.height / 2.0f - adjustedSize.height / 2.0f
	);

	_pixelMargin *= scale;
	_pixelInterval *= scale;
}

bool BoardLayer::isValidRowcol(const int& row, const int& column) {
	return
		(row >= 0) &&
		(row < MAX_ROWCOLS) &&
		(column >= 0) &&
		(column < MAX_ROWCOLS);
}

bool BoardLayer::isValidRowcol(const Rowcol& rowcol) {
	return isValidRowcol(rowcol.row, rowcol.column);
}

bool BoardLayer::isValidPos(const Point& pos) {
	return
		(pos.x >= _startPoint.x + _pixelMargin) &&
		(pos.x <= _endPoint.x - _pixelMargin) &&
		(pos.y <= _startPoint.y - _pixelMargin) &&
		(pos.y >= _endPoint.y + _pixelMargin);
}


ChessPiece* BoardLayer::getChessPiece(const Rowcol& rowcol) {
	int r = rowcol.row;
	int c = rowcol.column;
	ChessPiece* piece = getChessPiece(r, c);
	return piece;
}

ChessPiece* BoardLayer::getChessPiece(const int& row, const int& column) {
	if (!isValidRowcol(row, column)) return nullptr;
	ChessPiece* piece = _board[row][column];
	return piece;
}

void BoardLayer::createPiece(Rowcol rowcol, ChessPiece::PieceType type, ChessPiece::Color color) {
	Point pos = rowcolToPoint(rowcol);

	ChessPawn* pawn = ChessPawn::create(type, color);
	ChessUtility::initSprite(pawn, this, pos);

	_board[rowcol.row][rowcol.column] = pawn;
}

void BoardLayer::moveChessPiece(ChessPiece* piece, const Rowcol prev, const Rowcol next) {
	_board[prev.row][prev.column] = nullptr;
	_board[next.row][next.column] = piece;

	Point nextPos = rowcolToPoint(next);
	piece->setPosition(nextPos);
}

Rowcol BoardLayer::pointToRowcol(cocos2d::Point pos) {
	Rowcol ret = Rowcol::IMPOSSIBLE;

	if (isValidPos(pos)) {
		pos.x = pos.x - _startPoint.x - _pixelMargin;
		pos.y = _startPoint.y - _pixelMargin - pos.y;

		int col = static_cast<int>(pos.x) / _pixelInterval;
		int row = static_cast<int>(pos.y) / _pixelInterval;

		ret = Rowcol(row, col);
	}

	return ret;
}

Point BoardLayer::rowcolToPoint(Rowcol rowcol) {
	float impossible = 9876543.0f;
	Point ret = Point(impossible, impossible);

	if (isValidRowcol(rowcol)) {
		ret = _startPoint;

		ret.x += (_pixelMargin + _pixelInterval * rowcol.column);
		ret.y -= (_pixelMargin + _pixelInterval * rowcol.row);

		ret.x += _pixelInterval * 0.5f;
		ret.y -= _pixelInterval * 0.5f;
	}

	return ret;
}