#include	"ABomb.hh"
#include	"GameScene.hh"

ABomb::ABomb(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, int puissance, int dispo, APlayer *owner) : AObject(x, y, scale, angle, mesh, type, BOMB), _timeLeftBeforeExplosion(BOMB_TIME), _puissance(puissance),  _dispo(dispo), _owner(owner)
{
  //  this->_globalType = BOMB;
}

ABomb::ABomb(TiXmlAttribute **attrib) : AObject(attrib)
{
  (*attrib)->QueryIntValue(&this->_puissance);
  (*attrib) = (*attrib)->Next();
  (*attrib)->QueryIntValue(&this->_dispo);
  (*attrib) = (*attrib)->Next();
  (*attrib)->QueryIntValue(&this->_timeLeftBeforeExplosion);
  (*attrib) = (*attrib)->Next();
}

ABomb::~ABomb()
{
  
}

int		ABomb::getTimeBeforeExplosion() const
{
  return (this->_timeLeftBeforeExplosion);
}

void		ABomb::setTimeBeforeExplosion(int val)
{
  this->_timeLeftBeforeExplosion = val;
}

int		ABomb::getPuissance() const
{
  return (this->_puissance);
}

void		ABomb::setPuissance(int val)
{
  this->_puissance = val;
}

int		ABomb::getDispo() const
{
  return (this->_dispo);
}

void		ABomb::setDispo(int val)
{
  this->_dispo = val;
}


void		ABomb::reloadPlayer()
{
  if (this->_dispo == -1)
  {
    this->_owner->reloadStock(this->_type);
    if (this->_owner->getId() == 0)
    {
      GameScene::_listBombP1[this->_type - BOMB - 1] += 1;
      GameScene::_updateVector = true;
    } 
    else if (this->_owner->getId() == 1)
    {
      GameScene::_listBombP2[this->_type - BOMB - 1] += 1;
      GameScene::_updateVector = true;
    }
  }
}

void		ABomb::destroyObject()
{
  if (this->_status == ALIVE)
    {
      this->explode();
    }
  //si la bombe n'a pas explosé, on l'a fait explser
  //on fait exploser la bombe
  //on joue l'animation
}

bool		ABomb::isDestructible() const
{
  return (true);
}

bool		ABomb::isMovable() const
{
  return (true);
}

bool		ABomb::isTakable() const
{
  return (false);
}

bool		ABomb::isReachable() const
{
  if (this->getType() == CLAYMORE || this->getType() == ROCKET)
    return (true);
  return (false);
}

bool		ABomb::isExpandable() const
{
  return (true);
}

void		ABomb::setPlayer(APlayer *player)
{
  this->_owner = player;
}

TiXmlElement	*ABomb::serialize()
{
  TiXmlElement	*ret;

  ret = APhysicalObject::serialize();
  ret->SetAttribute("puissance", this->_puissance);
  ret->SetAttribute("dispo", this->_dispo);
  ret->SetAttribute("timeLeft", this->_timeLeftBeforeExplosion);
  ret->SetAttribute("id_player", this->_owner->getId());
  return (ret);
}

void		ABomb::effectObject(APlayer *)
{
  if (this->getType() == CLAYMORE && this->_timeLeftBeforeExplosion == 0)
    this->explode();
}

void		ABomb::explode()
{
  this->setStatus(DETONATING);
  this->spreadExplosion(this->_puissance);
  this->reloadPlayer();
}
