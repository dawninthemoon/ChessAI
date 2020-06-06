#include "ChessScene/TimerLayer.h"

USING_NS_CC;

TimerLayer::TimerLayer() { }
TimerLayer::~TimerLayer() { }

bool TimerLayer::init() {
	if (!Layer::init()) return false;

	initLayer();

	return true;
}

void TimerLayer::initLayer() {

}