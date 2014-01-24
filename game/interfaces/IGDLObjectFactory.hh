#ifndef			__IGDLOBJECTFACTORY_HH__
#define			__IGDLOBJECTFACTORY_HH__

#include		<string>
#include		"IGDLObject.hh"
#include		"HumanPlayer.hh"
#include		"IAPlayer.hh"
#include		"Explosion.hh"
#include		"ToxicCloud.hh"
#include		"BasicBomb.hh"
#include		"SpikeBomb.hh"
#include		"Claymore.hh"
#include		"NukeBomb.hh"
#include		"ToxicBomb.hh"
#include		"RemoteBomb.hh"
#include 		"Rocket.hh"
#include		"Wall.hh"
#include		"ABonus.hh"
#include		"BonusRange.hh"
#include		"BonusSpeed.hh"
#include		"BonusStock.hh"
#include		"BonusNuke.hh"
#include		"BonusClaymore.hh"
#include		"BonusRocket.hh"
#include		"BonusToxic.hh"
#include		"BonusSpike.hh"
#include		"BonusRemote.hh"
#include		"BonusLife.hh"
#include		"BonusShield.hh"
#include		"BonusHealth.hh"
#include		"BonusRandom.hh"
#include		"BonusGhost.hh"

#include		"Empty.hh"

class				IGDLObjectFactory
{
public:
  virtual			~IGDLObjectFactory(){}
  virtual IPhysicalObject	*createABomb(int, int, int, int, std::string &, ObjectType, int, int, APlayer *) = 0;
  virtual APlayer		*createAPlayer(int, int, int, int, std::string &, ObjectType, int, int, int, int) = 0;
  virtual IPhysicalObject	*createAObject(int, int, int, int, std::string &, ObjectType) = 0;
  virtual IPhysicalObject	*createObjSpec(int, int, int, int, std::string &, ObjectType, APlayer *) = 0;
  virtual APlayer		*createXmlAPlay(ObjectType, TiXmlAttribute **) = 0;
  virtual IPhysicalObject	*createXmlIPhys(ObjectType, TiXmlAttribute **) = 0;
};

#endif
