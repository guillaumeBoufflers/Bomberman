#ifndef		__BONUSRANDOM_HH__
#define	        __BONUSRANDOM_HH__

#include	"ABonus.hh"

class		BonusRandom : public ABonus
{
public:
  BonusRandom(int, int, int, int, std::string &, ObjectType);
  BonusRandom(TiXmlAttribute **attr);
  virtual	~BonusRandom();

  virtual	void	effectObject(APlayer *);
};

#endif
