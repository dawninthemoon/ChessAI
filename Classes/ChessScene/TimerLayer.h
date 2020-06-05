#ifndef __TIMER_LAYER_H__
#define __TIMER_LAYER_H__

#include "cocos2d.h"

class TimerLayer : public cocos2d::Layer {
public:
	void initLayer();
public:
	TimerLayer();
	virtual ~TimerLayer();
	virtual bool init();
	CREATE_FUNC(TimerLayer);
};

#endif