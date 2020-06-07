#include "ChessScene/BoardLayer.h"
#include "ChessUtility.h"
#include "RowCol.h"
#include "ChessScene/Pieces/Pieces.h"
#include "GameState.h"

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

	for (int r = 0; r < MAX_ROWCOLS; ++r) {
		for (int c = 0; c < MAX_ROWCOLS; ++c) {
			_tempPieces[r][c] = Sprite::create();
			_tempPieces[r][c]->retain();
		}
	}

	initLayer();

	return true;
}

void BoardLayer::initLayer() {
	Size boardContentSize = initBoardSprite();
	initBoardSize(boardContentSize);
	initBoard();
}

void BoardLayer::initBoard() {
#pragma region Pawn
	const int pawnRow = 1;
	for (int pawnColumn = 0; pawnColumn < 8; ++pawnColumn) {
		Rowcol whiteRowcol = Rowcol(MAX_ROWCOLS - pawnRow - 1, pawnColumn);
		createPiece(whiteRowcol, ChessPiece::PAWN, ChessPiece::WHITE);
		
		Rowcol blackRowcol = Rowcol(pawnRow, pawnColumn);
		createPiece(blackRowcol, ChessPiece::PAWN, ChessPiece::BLACK);
	}
#pragma endregion

#pragma region Bishop
	Rowcol blackBishopRc1 = Rowcol(0, 2);
	Rowcol blackBishopRc2 = Rowcol(0, MAX_ROWCOLS - 3);

	Rowcol whiteBishopRc1 = Rowcol(MAX_ROWCOLS - 1, 2);
	Rowcol whiteBishopRc2 = Rowcol(MAX_ROWCOLS - 1, MAX_ROWCOLS - 3);

	createPiece(blackBishopRc1, ChessPiece::BISHOP, ChessPiece::BLACK);
	createPiece(blackBishopRc2, ChessPiece::BISHOP, ChessPiece::BLACK);

	createPiece(whiteBishopRc1, ChessPiece::BISHOP, ChessPiece::WHITE);
	createPiece(whiteBishopRc2, ChessPiece::BISHOP, ChessPiece::WHITE);
#pragma endregion

#pragma region Knight
	Rowcol blackKnightRc1 = Rowcol(0, 1);
	Rowcol blackKnightRc2 = Rowcol(0, MAX_ROWCOLS - 2);

	Rowcol whiteKnightRc1 = Rowcol(MAX_ROWCOLS - 1, 1);
	Rowcol whiteKnightRc2 = Rowcol(MAX_ROWCOLS - 1, MAX_ROWCOLS - 2);

	createPiece(blackKnightRc1, ChessPiece::KNIGHT, ChessPiece::BLACK);
	createPiece(blackKnightRc2, ChessPiece::KNIGHT, ChessPiece::BLACK);

	createPiece(whiteKnightRc1, ChessPiece::KNIGHT, ChessPiece::WHITE);
	createPiece(whiteKnightRc2, ChessPiece::KNIGHT, ChessPiece::WHITE);
#pragma endregion

#pragma region Rook
	Rowcol blackRookRc1 = Rowcol(0, 0);
	Rowcol blackRookRc2 = Rowcol(0, MAX_ROWCOLS - 1);

	Rowcol whiteRookRc1 = Rowcol(MAX_ROWCOLS - 1, 0);
	Rowcol whiteRookRc2 = Rowcol(MAX_ROWCOLS - 1, MAX_ROWCOLS - 1);

	createPiece(blackRookRc1, ChessPiece::ROOK, ChessPiece::BLACK);
	createPiece(blackRookRc2, ChessPiece::ROOK, ChessPiece::BLACK);

	createPiece(whiteRookRc1, ChessPiece::ROOK, ChessPiece::WHITE);
	createPiece(whiteRookRc2, ChessPiece::ROOK, ChessPiece::WHITE);
#pragma endregion

#pragma region Queen
	Rowcol blackQueenRc = Rowcol(0, 3);
	Rowcol whiteQueenRc = Rowcol(MAX_ROWCOLS - 1, 3);

	createPiece(blackQueenRc, ChessPiece::QUEEN, ChessPiece::BLACK);
	createPiece(whiteQueenRc, ChessPiece::QUEEN, ChessPiece::WHITE);
#pragma endregion

#pragma region King
	Rowcol blackKingRc = Rowcol(0, 4);
	Rowcol whiteKingRc = Rowcol(MAX_ROWCOLS - 1, 4);

	createPiece(blackKingRc, ChessPiece::KING, ChessPiece::BLACK);
	createPiece(whiteKingRc, ChessPiece::KING, ChessPiece::WHITE);
#pragma endregion
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

Rowcol BoardLayer::findKingRowcolByColor(ChessPiece::Color color)
{
	for (int i = 0; i < MAX_ROWCOLS; ++i) {
		for (int j = 0; j < MAX_ROWCOLS; ++j) {
			if (_board[i][j] != nullptr) {
				if (_board[i][j]->getPieceColor() == color &&
					_board[i][j]->getPieceType() == ChessPiece::KING) {
					return Rowcol(i, j);
				}
			}
		}
	}
}

void BoardLayer::createPiece(Rowcol rowcol, ChessPiece::PieceType type, ChessPiece::Color color) {
	Point pos = rowcolToPoint(rowcol);

	auto piece = ChessUtility::createPiece(type, color);
	ChessUtility::initSprite(piece, this, pos);

	_board[rowcol.row][rowcol.column] = piece;
}

int BoardLayer::calculateScoreIfMoved(ChessPiece* piece, ChessPiece::Color color, const Rowcol prev, const Rowcol next) {
	ChessPiece* prevTemp = _board[prev.row][prev.column];
	ChessPiece* nextTemp = _board[next.row][next.column];

	_board[prev.row][prev.column] = nullptr;
	_board[next.row][next.column] = piece;
	
	int score = 0;
	for (int r = 0; r < MAX_ROWCOLS; ++r) {
		for (int c = 0; c < MAX_ROWCOLS; ++c) {
			score += ChessUtility::getPieceValue(_board[r][c], color);
		}
	}

	_board[prev.row][prev.column] = prevTemp;
	_board[next.row][next.column] = nextTemp;
	
	return score;
}

void BoardLayer::moveChessPiece(ChessPiece* piece, const Rowcol prev, const Rowcol next) {
	_board[prev.row][prev.column] = nullptr;
	
	ChessPiece* toMove = getChessPiece(next);
	
	_board[next.row][next.column] = piece;
	piece->onMove(rowcolToPoint(next), toMove, this);

	ChessPiece::Color oppositeColor = piece->getOppositeColor();
	
	if (piece->checkIsCheckState(this, next)) {
		bool isCheckmate = true;
		Rowcol kingLocation = findKingRowcolByColor(oppositeColor);
		ChessPiece* king = _board[kingLocation.row][kingLocation.column];

		auto possibleWays = king->getMoveAreas(this, kingLocation);
		for (const auto& rc : possibleWays) {
			int r = rc.row, c = rc.column;

			if (!checkIsCheckStateForAll(kingLocation, Rowcol(r, c))) {
				isCheckmate = false;
			}

			if (!isCheckmate) break;
		}

		throw isCheckmate ? GameState::CHECKMATE : GameState::CHECK;
	}
}

bool BoardLayer::checkIsCheckStateForAll(Rowcol kingRowcol, Rowcol target)
{
	int r = target.row, c = target.column;
	auto king = getChessPiece(kingRowcol);
	auto moverColor = king->getPieceColor();
	
	ChessPiece* temp = _board[r][c];
	_board[r][c] = king;
	_board[kingRowcol.row][kingRowcol.column] = nullptr;

	for (int r = 0; r < MAX_ROWCOLS; ++r) {
		for (int c = 0; c < MAX_ROWCOLS; ++c) {
			ChessPiece* piece = _board[r][c];
			if (piece && (piece->getPieceColor() == moverColor)) {
				if (piece->checkIsCheckState(this, Rowcol(r, c))) {
					_board[r][c] = temp;
					_board[kingRowcol.row][kingRowcol.column] = king;
					return true;
				}
			}
		}
	}

	_board[r][c] = temp;
	_board[kingRowcol.row][kingRowcol.column] = king;

	return false;
}

void BoardLayer::showPossibleRowcols(Rowcol rowcol, const std::string& path) {
	auto sprite = _tempPieces[rowcol.row][rowcol.column];
	sprite->initWithSpriteFrameName(path);
	Point pos = rowcolToPoint(rowcol);
	ChessUtility::initSprite(sprite, this, pos);

	sprite->setOpacity(255.0f * 0.7f);
	auto action = Blink::create(0.5f, 1);
	sprite->runAction(RepeatForever::create(action));
}

void BoardLayer::removeAllPossibleRowcols() {
	for (int r = 0; r < MAX_ROWCOLS; ++r) {
		for (int c = 0; c < MAX_ROWCOLS; ++c) {
			Sprite* sprite = _tempPieces[r][c];
			sprite->stopAllActions();
			this->removeChild(sprite);
		}
	}
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