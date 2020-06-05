#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class UILayer : public cocos2d::Layer {
public:
	void initLayer();
public:
	UILayer();
	virtual ~UILayer();
	virtual bool init();
	CREATE_FUNC(UILayer);
};