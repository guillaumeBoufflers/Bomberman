#ifndef		__BONUSCLAYMORE_HH_
#define	        __BONUSCLAYMORE_HH_

#include	"ABonus.hh"

class		BonusClaymore : public ABonus
{
public:
  BonusClaymore
 (int, int, int, int, std::string &, ObjectType);
  BonusClaymore
 (TiXmlAttribute **attr);
  virtual	~BonusClaymore
 ();

  virtual	void	effectObject(APlayer *);
};

#endif
