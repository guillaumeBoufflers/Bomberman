#ifndef		__BONUSRANGE_HH__
#define	        __BONUSRANGE_HH__

#include	"ABonus.hh"

class		BonusRange : public ABonus
{
public:
  BonusRange(int, int, int, int, std::string &, ObjectType);
  BonusRange(TiXmlAttribute **attr);
  virtual	~BonusRange();

  virtual	void	effectObject(APlayer *);
};

#endif
