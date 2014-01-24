#ifndef		__BONUSNUKE_HH__
#define	        __BONUSNUKE_HH__

#include	"ABonus.hh"

class		BonusNuke : public ABonus
{
public:
  BonusNuke(int, int, int, int, std::string &, ObjectType);
  BonusNuke(TiXmlAttribute **attr);
  virtual	~BonusNuke();

  virtual	void	effectObject(APlayer *);
};

#endif
