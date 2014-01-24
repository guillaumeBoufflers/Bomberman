#ifndef		__BONUSSHIELD_HH__
#define	        __BONUSSHIELD_HH__

#include	"ABonus.hh"

class		BonusShield : public ABonus
{
public:
  BonusShield(int, int, int, int, std::string &, ObjectType);
  BonusShield(TiXmlAttribute **attr);
  virtual	~BonusShield();

  virtual	void	effectObject(APlayer *);
};

#endif
