#ifndef		__BONUSTOXIC_HH__
#define	        __BONUSTOXIC_HH__

#include	"ABonus.hh"

class		BonusToxic : public ABonus
{
public:
  BonusToxic(int, int, int, int, std::string &, ObjectType);
  BonusToxic(TiXmlAttribute **attr);
  virtual	~BonusToxic();

  virtual	void	effectObject(APlayer *);
};

#endif
