#include "ChessUtility.h"
#include "ChessScene/Pieces/Pieces.h"

USING_NS_CC;

cocos2d::Size ChessUtility::standardSize = cocos2d::Size(360.0f, 640.0f);

std::string** ChessUtility::generatePiecePath() {
	std::string** str = new std::string*[2];
	str[0] = new std::string[6]{
		"etc/pieces/spr_piece_pawn_white.png",
		"etc/pieces/spr_piece_bishop_white.png",
		"etc/pieces/spr_piece_knight_white.png",
		"etc/pieces/spr_piece_rook_white.png",
		"etc/pieces/spr_piece_queen_white.png",
		"etc/pieces/spr_piece_king_white.png"
	};
	str[1] = new std::string[6]{
		"etc/pieces/spr_piece_pawn_black.png",
		"etc/pieces/spr_piece_bishop_black.png",
		"etc/pieces/spr_piece_knight_black.png",
		"etc/pieces/spr_piece_rook_black.png",
		"etc/pieces/spr_piece_queen_black.png",
		"etc/pieces/spr_piece_king_black.png"
	};

	return str;
}
std::string** ChessUtility::piecePath = generatePiecePath();

float ChessUtility::getSpriteScale() {
	Size winSize = Director::getInstance()->getVisibleSize();

	float scale =
		(winSize.width > winSize.height) ?
		winSize.height / ChessUtility::standardSize.height :
		winSize.width / ChessUtility::standardSize.width;

	return scale;
}

Sprite* ChessUtility::createSprite(const std::string name, Node* parent, Point pos, Point anchor) {
	Sprite* sprite = Sprite::create(name);
	initSprite(sprite, parent, pos, anchor);
	return sprite;
}

Sprite* ChessUtility::createWithSpriteFrame(const std::string name, Node* parent, Point pos, Point anchor) {
	Sprite* sprite = Sprite::createWithSpriteFrameName(name);
	initSprite(sprite, parent, pos, anchor);
	return sprite;
}

void ChessUtility::initSprite(cocos2d::Sprite* sprite, cocos2d::Node* parent, cocos2d::Point pos, cocos2d::Point anchor) {
	sprite->getTexture()->setAliasTexParameters();

	sprite->setAnchorPoint(anchor);
	sprite->setScale(getSpriteScale());
	sprite->setPosition(pos);

	parent->addChild(sprite);
}

ChessPiece* ChessUtility::createPiece(ChessPiece::PieceType type, ChessPiece::Color color)
{
	ChessPiece* piece = nullptr;
	switch (type) {
	case ChessPiece::PAWN:
		piece = ChessPawn::create(type, color);
		break;
	case ChessPiece::BISHOP:
		piece = ChessBishop::create(type, color);
		break;
	case ChessPiece::KNIGHT:
		piece = ChessKnight::create(type, color);
		break;
	case ChessPiece::ROOK:
		piece = ChessRook::create(type, color);
		break;
	case ChessPiece::QUEEN:
		piece = ChessQueen::create(type, color);
		break;
	case ChessPiece::KING:
		piece = ChessKing::create(type, color);
		break;
	default:
		break;
	}
	return piece;
}

int ChessUtility::getPieceValue(ChessPiece* piece, ChessPiece::Color color) {
	if (piece == nullptr) return 0;

	static int values[ChessPiece::TYPE_COUNT] = {
		1,
		3,
		3,
		5,
		9,
		100000
	};

	int multiplyer = (piece->getPieceColor() == color) ? 1 : -1;
	return values[piece->getPieceType()] * multiplyer;
}
