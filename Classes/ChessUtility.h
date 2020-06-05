#ifndef __CHESS_UTILITY_H__
#define __CHESS_UTILITY_H__

#include "cocos2d.h"

class ChessUtility {
private:
	static cocos2d::Size standardSize;
public:
	static float getSpriteScale();
};


#endif