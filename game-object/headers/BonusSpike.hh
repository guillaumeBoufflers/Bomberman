#ifndef		__BONUSSPIKE_HH__
#define	        __BONUSSPIKE_HH__

#include	"ABonus.hh"

class		BonusSpike : public ABonus
{
public:
  BonusSpike(int, int, int, int, std::string &, ObjectType);
  BonusSpike(TiXmlAttribute **attr);
  virtual	~BonusSpike();

  virtual	void	effectObject(APlayer *);
};

#endif
