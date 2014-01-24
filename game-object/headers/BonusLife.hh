#ifndef		__BONUSLIFE_HH__
#define	        __BONUSLIFE_HH__

#include	"ABonus.hh"

class		BonusLife : public ABonus
{
public:
  BonusLife(int, int, int, int, std::string &, ObjectType);
  BonusLife(TiXmlAttribute **attr);
  virtual	~BonusLife();

  virtual	void	effectObject(APlayer *);
};

#endif
