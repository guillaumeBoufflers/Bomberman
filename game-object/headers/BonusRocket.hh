#ifndef		__BONUSROCKET_HH_
#define	        __BONUSROCKET_HH_

#include	"ABonus.hh"

class		BonusRocket : public ABonus
{
public:
  BonusRocket(int, int, int, int, std::string &, ObjectType);
  BonusRocket(TiXmlAttribute **attr);
  virtual	~BonusRocket();

  virtual	void	effectObject(APlayer *);
};

#endif
