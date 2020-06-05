#ifndef __CHESSS_PIECE_H__
#define __CHESSS_PIECE_H__

#include "cocos2d.h"

class ChessPiece : public cocos2d::Sprite {

public:
	ChessPiece();
	virtual ~ChessPiece();
	virtual bool init();
	CREATE_FUNC(ChessPiece);
};

#endif