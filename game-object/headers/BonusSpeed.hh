#ifndef		__BONUSSPEED_HH__
#define	        __BONUSSPEED_HH__

#include	"ABonus.hh"

class		BonusSpeed : public ABonus
{
public:
  BonusSpeed(int, int, int, int, std::string &, ObjectType);
  BonusSpeed(TiXmlAttribute **);
  virtual	~BonusSpeed();

  virtual	void	effectObject(APlayer *);
};

#endif
