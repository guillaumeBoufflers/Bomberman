#ifndef		__BONUSGHOST_HH__
#define	        __BONUSGHOST_HH__

#include	"ABonus.hh"

class		BonusGhost : public ABonus
{
public:
  BonusGhost(int, int, int, int, std::string &, ObjectType);
  BonusGhost(TiXmlAttribute **attr);
  virtual	~BonusGhost();

  virtual	void	effectObject(APlayer *);
};

#endif
