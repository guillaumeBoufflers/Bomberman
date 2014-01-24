#include	"GDLObjectFactory.hh"

IGDLObjectFactory	*GDLObjectFactory::_instance = NULL;

GDLObjectFactory::GDLObjectFactory()
{
  this->tab[EXPLOSION - (OBJSPEC + 1)] = &GDLObjectFactory::create<Explosion>;
  this->tab[TOXICCLOUD - (OBJSPEC + 1)] = &GDLObjectFactory::create<ToxicCloud>;

  this->tabBomb[BASICBOMB - (BOMB + 1)] = &GDLObjectFactory::create<BasicBomb>;
  this->tabBomb[SPIKEBOMB - (BOMB + 1)] = &GDLObjectFactory::create<SpikeBomb>;
  this->tabBomb[CLAYMORE - (BOMB + 1)] = &GDLObjectFactory::create<Claymore>;
  this->tabBomb[NUKEBOMB - (BOMB + 1)] = &GDLObjectFactory::create<NukeBomb>;
  this->tabBomb[TOXICBOMB - (BOMB + 1)] = &GDLObjectFactory::create<ToxicBomb>;
  this->tabBomb[REMOTEBOMB - (BOMB + 1)] = &GDLObjectFactory::create<RemoteBomb>;
  this->tabBomb[ROCKET - (BOMB + 1)] = &GDLObjectFactory::create<Rocket>;

  this->tabPlay[HUMANPLAYER - (PLAYER + 1)] = &GDLObjectFactory::create<HumanPlayer>;
  this->tabPlay[IAPLAYER - (PLAYER + 1)] = &GDLObjectFactory::create<IAPlayer>;
  this->tabObj[BONUSSPEED - (OBJ + 1)] = &GDLObjectFactory::create<BonusSpeed>;
  this->tabObj[BONUSSTOCK - (OBJ + 1)] = &GDLObjectFactory::create<BonusStock>;
  this->tabObj[BONUSRANGE - (OBJ + 1)] = &GDLObjectFactory::create<BonusRange>;
  this->tabObj[BONUSNUKE - (OBJ + 1)] = &GDLObjectFactory::create<BonusNuke>;
  this->tabObj[BONUSCLAYMORE - (OBJ + 1)] = &GDLObjectFactory::create<BonusClaymore>;
  this->tabObj[BONUSROCKET - (OBJ + 1)] = &GDLObjectFactory::create<BonusRocket>;
  this->tabObj[BONUSTOXIC - (OBJ + 1)] = &GDLObjectFactory::create<BonusToxic>;
  this->tabObj[BONUSSPIKE - (OBJ + 1)] = &GDLObjectFactory::create<BonusSpike>;
  this->tabObj[BONUSREMOTE - (OBJ + 1)] = &GDLObjectFactory::create<BonusRemote>;
  this->tabObj[BONUSLIFE - (OBJ + 1)] = &GDLObjectFactory::create<BonusLife>;
  this->tabObj[BONUSSHIELD - (OBJ + 1)] = &GDLObjectFactory::create<BonusShield>;
  this->tabObj[BONUSGHOST - (OBJ + 1)] = &GDLObjectFactory::create<BonusGhost>;
  this->tabObj[BONUSHEALTH - (OBJ + 1)] = &GDLObjectFactory::create<BonusHealth>;
  this->tabObj[BONUSRANDOM - (OBJ + 1)] = &GDLObjectFactory::create<BonusRandom>;
  this->tabObj[BONUS - (OBJ + 1)] = &GDLObjectFactory::create<BonusRange>;
  this->tabObj[DESTRUCTIBLEWALL - (OBJ + 1)] = &GDLObjectFactory::create<Wall>;
  this->tabObj[UNDESTRUCTIBLEWALL - (OBJ + 1)] = &GDLObjectFactory::create<Wall>;
  this->tabObj[EMPTY - (OBJ + 1)] = &GDLObjectFactory::create<Empty>;

  this->tabXmlAPlay[HUMANPLAYER - (PLAYER + 1)] = &GDLObjectFactory::create<HumanPlayer>;
  this->tabXmlAPlay[IAPLAYER - (PLAYER + 1)] = &GDLObjectFactory::create<IAPlayer>;

  this->tabXmlIPhys[EXPLOSION] = &GDLObjectFactory::create<Explosion>;
  this->tabXmlIPhys[TOXICCLOUD] = &GDLObjectFactory::create<Explosion>;
  this->tabXmlIPhys[BASICBOMB] = &GDLObjectFactory::create<BasicBomb>;
  this->tabXmlIPhys[SPIKEBOMB] = &GDLObjectFactory::create<SpikeBomb>;
  this->tabXmlIPhys[CLAYMORE] = &GDLObjectFactory::create<Claymore>;
  this->tabXmlIPhys[NUKEBOMB] = &GDLObjectFactory::create<NukeBomb>;
  this->tabXmlIPhys[TOXICBOMB] = &GDLObjectFactory::create<ToxicBomb>;
  this->tabXmlIPhys[REMOTEBOMB] = &GDLObjectFactory::create<RemoteBomb>;
  this->tabXmlIPhys[ROCKET] = &GDLObjectFactory::create<Rocket>;

  this->tabXmlIPhys[BONUSSTOCK] = &GDLObjectFactory::create<BonusStock>;
  this->tabXmlIPhys[BONUSSPEED] = &GDLObjectFactory::create<BonusSpeed>;
  this->tabXmlIPhys[BONUSRANGE] = &GDLObjectFactory::create<BonusRange>;
  this->tabXmlIPhys[BONUSCLAYMORE] = &GDLObjectFactory::create<BonusClaymore>;
  this->tabXmlIPhys[BONUSROCKET] = &GDLObjectFactory::create<BonusRocket>;
  this->tabXmlIPhys[BONUSTOXIC] = &GDLObjectFactory::create<BonusToxic>;
  this->tabXmlIPhys[BONUSSPIKE] = &GDLObjectFactory::create<BonusSpike>;
  this->tabXmlIPhys[BONUSREMOTE] = &GDLObjectFactory::create<BonusRemote>;
  this->tabXmlIPhys[BONUSLIFE] = &GDLObjectFactory::create<BonusLife>;
  this->tabXmlIPhys[BONUSSHIELD] = &GDLObjectFactory::create<BonusShield>;
  this->tabXmlIPhys[BONUSGHOST] = &GDLObjectFactory::create<BonusGhost>;
  this->tabXmlIPhys[BONUSHEALTH]  = &GDLObjectFactory::create<BonusHealth>;
  this->tabXmlIPhys[BONUSRANDOM ] = &GDLObjectFactory::create<BonusRandom>;
  this->tabXmlIPhys[BONUSNUKE] = &GDLObjectFactory::create<BonusNuke>;
  this->tabXmlIPhys[DESTRUCTIBLEWALL] = &GDLObjectFactory::create<Wall>;
  this->tabXmlIPhys[UNDESTRUCTIBLEWALL] = &GDLObjectFactory::create<Wall>;
  this->tabXmlIPhys[EMPTY] = &GDLObjectFactory::create<Empty>;
}

GDLObjectFactory::~GDLObjectFactory()
{

}

IGDLObjectFactory	*GDLObjectFactory::getInstance()
{
  if (_instance == NULL)
    _instance = new GDLObjectFactory();
  return (_instance);
}

void			GDLObjectFactory::deleteInstance()
{
  if (_instance != NULL)
    delete _instance;
  _instance = NULL;
}

IPhysicalObject		*GDLObjectFactory::createObjSpec(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, APlayer *player)
{
  return ((this->*tab[type - (OBJSPEC + 1)])(x, y, scale, angle, mesh, type, player));
}

IPhysicalObject		*GDLObjectFactory::createABomb(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, int puissance,  int dispo, APlayer *player)
{
  return ((this->*tabBomb[type - (BOMB + 1)])(x, y, scale, angle, mesh, puissance, dispo, player));
}

APlayer			*GDLObjectFactory::createAPlayer(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, int id, int life, int range, int start)
{
  return ((this->*tabPlay[type - (PLAYER + 1)])(x, y, scale, angle, mesh, type, id, life, range, start));
}

IPhysicalObject		*GDLObjectFactory::createAObject(int x, int y, int scale, int angle, std::string &mesh, ObjectType type)
{
  return ((this->*tabObj[type - (OBJ + 1)])(x, y, scale, angle, mesh, type));
}

IPhysicalObject		*GDLObjectFactory::createXmlIPhys(ObjectType type, TiXmlAttribute **attr)
{
  return ((this->*tabXmlIPhys[type])(attr));
}

APlayer			*GDLObjectFactory::createXmlAPlay(ObjectType type, TiXmlAttribute **attr)
{
  return ((this->*tabXmlAPlay[type - (PLAYER  + 1)])(attr));
}
