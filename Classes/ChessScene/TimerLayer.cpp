#include "ChessScene/TimerLayer.h"

USING_NS_CC;

TimerLayer::TimerLayer() { }
TimerLayer::~TimerLayer() { }

bool TimerLayer::init() {
	if (!Layer::create()) return false;

	return true;
}

void TimerLayer::initLayer() {

}