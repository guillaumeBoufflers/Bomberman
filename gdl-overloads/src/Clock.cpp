#include	"Clock.hh"

Clock::Clock(gdl::GameClock *gameClock) : _gameClock(gameClock)
{

}

Clock::~Clock()
{

}

Clock 				*Clock::getInstance(gdl::GameClock *gameClock) {
	static Clock 	*instance = NULL;

	if (!instance)
		instance = new Clock(gameClock);
	return (instance);
}

gdl::GameClock 		*Clock::getClock() {
	Clock 			*c = Clock::getInstance();
	return (c->getClockPtr());
}

gdl::GameClock 		*Clock::getClockPtr() {
	return (this->_gameClock);
}
