#include "ChessUtility.h"

USING_NS_CC;

cocos2d::Size ChessUtility::standardSize = cocos2d::Size(360.0f, 640.0f);

float ChessUtility::getSpriteScale() {
	Size winSize = Director::getInstance()->getVisibleSize();

	float scale =
		(winSize.width > winSize.height) ?
		winSize.height / ChessUtility::standardSize.height :
		winSize.width / ChessUtility::standardSize.width;

	return scale;
}