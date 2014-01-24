#ifndef		__BONUSSTOCK_HH__
#define	        __BONUSSTOCK_HH__

#include	"ABonus.hh"

class		BonusStock : public ABonus
{
public:
  BonusStock(int, int, int, int, std::string &, ObjectType);
  BonusStock(TiXmlAttribute **attr);
  virtual	~BonusStock();

  virtual	void	effectObject(APlayer *);
};

#endif
