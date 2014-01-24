#ifndef		__BONUSHEALTH_HH__
#define	        __BONUSHEALTH_HH__

#include	"ABonus.hh"

class		BonusHealth : public ABonus
{
public:
  BonusHealth(int, int, int, int, std::string &, ObjectType);
  BonusHealth(TiXmlAttribute **attr);
  virtual	~BonusHealth();

  virtual	void	effectObject(APlayer *);
};

#endif
