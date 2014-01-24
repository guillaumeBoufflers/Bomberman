
#ifndef __SCORE_HH__
#define __SCORE_HH__

#include <sstream>
#include "Serialize.hh"

class Score
{
  static Score		*_instance;
  std::list<int> _score;
  std::vector<std::string> _player;
public:
  Score();
  ~Score();
  static  Score	*getInstance();
  static  void	deleteInstance();
  void setFich();
  std::vector<std::string> getScore();
  void		setScore(int, int);
};

#endif
