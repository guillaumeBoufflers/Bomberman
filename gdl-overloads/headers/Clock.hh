#ifndef					__GAME_CLOCK_HH__
#define					__GAME_CLOCK_HH__

#include				<list>
#include 				"common.hh"

class					Clock
{
private:
  gdl::GameClock 		*_gameClock;
  Clock(gdl::GameClock *gameClock);

public:
  static Clock	*getInstance(gdl::GameClock *gameClock = NULL);
  
  static gdl::GameClock *getClock();
  gdl::GameClock *getClockPtr();

  ~Clock();
};

#endif
