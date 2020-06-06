#ifndef __CHESS_UTILITY_H__
#define __CHESS_UTILITY_H__

#include "cocos2d.h"
#include <string>

class ChessUtility {
private:
	static cocos2d::Size visibleSize;
	static cocos2d::Size standardSize;

	static std::string** generatePiecePath();
public:
	static float getSpriteScale();
	static cocos2d::Sprite* createSprite(const std::string name, cocos2d::Node* parent, cocos2d::Point pos, cocos2d::Point anchor = cocos2d::Point(0.5f, 0.5f));
	static void initSprite(cocos2d::Sprite* sprite, cocos2d::Node* parent, cocos2d::Point pos, cocos2d::Point anchor = cocos2d::Point(0.5f, 0.5f));

	static std::string** piecePath;
};

#endif