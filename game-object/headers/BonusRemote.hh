#ifndef		__BONUSREMOTE_HH__
#define	        __BONUSREMOTE_HH__

#include	"ABonus.hh"

class		BonusRemote : public ABonus
{
public:
  BonusRemote(int, int, int, int, std::string &, ObjectType);
  BonusRemote(TiXmlAttribute **attr);
  virtual	~BonusRemote();

  virtual	void	effectObject(APlayer *);
};

#endif
