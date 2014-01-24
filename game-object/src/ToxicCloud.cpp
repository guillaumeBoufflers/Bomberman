#include	"ToxicCloud.hh"
#include	"GameScene.hh"

ToxicCloud::ToxicCloud(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, APlayer *owner) : AObject(x, y, scale, angle, mesh, type, EXPLOSION), _nbFramesSinceSpawn(0), _owner(owner)
{

}

ToxicCloud::ToxicCloud(TiXmlAttribute **attrib) : AObject(attrib)
{
  (*attrib)->QueryIntValue(&this->_nbFramesSinceSpawn);
  (*attrib) = (*attrib)->Next();
}

ToxicCloud::~ToxicCloud()
{

}

int		ToxicCloud::update()
{
  if (this->_nbFramesSinceSpawn == 0)
  {
    for (std::list<IPhysicalObject *>::iterator it = GameScene::_map[getPosCaseY()][getPosCaseX()].begin() ; it != GameScene::_map[getPosCaseY()][getPosCaseX()].end(); ++it)
      if ((*it)->getType() == TOXICCLOUD && (*it) != this)
      {
       GameScene::destructObjectGame(it);
       return (0);
     }
  }
  this->_nbFramesSinceSpawn++;
  if (this->_nbFramesSinceSpawn == TOXIC_TIME) // << penser à régler par rapport à deux define (fps & durée before explosion)
    {
      GameScene::destructObjectGame(GameScene::findInstance(this));
      return (1);
    }
  return (0);
}

void    ToxicCloud::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void    ToxicCloud::initialize()
{
  //  gdl::Model::cut_animation(this->_model, "Default Take", 0, 9, "EXPLODE");
}

int		ToxicCloud::getNbFramesSinceSpawn() const
{
  return (this->_nbFramesSinceSpawn);
}

void		ToxicCloud::setNbFramesSinceSpawn(int val)
{
  this->_nbFramesSinceSpawn = val;
}

bool		ToxicCloud::isDestructible() const
{
  return (true);
}

bool		ToxicCloud::isMovable() const
{
  return (true);
}

bool		ToxicCloud::isTakable() const
{
  return (false);
}

bool		ToxicCloud::isReachable() const
{
  return (true);
}

bool		ToxicCloud::isExpandable() const
{
  return (true);
}

void		ToxicCloud::destroyObject()
{

}

void		ToxicCloud::setPlayer(APlayer *player)
{
  this->_owner = player;
}

void		ToxicCloud::effectObject(APlayer *player)
{
  if (this->_nbFramesSinceSpawn % 4 == 0 && !player->getIsRecovering() && player->isDestructible())
  {
  player->setDamage(1);
  if (player != this->_owner)
    this->_owner->setScore(this->_owner->getScore() + SCORE_TOXIC);
  }
}

TiXmlElement	*ToxicCloud::serialize()
{
  TiXmlElement	*ret;

  ret = AObject::serialize();
  ret->SetAttribute("nbFrames", this->_nbFramesSinceSpawn);
  ret->SetAttribute("id_play", this->_owner->getId());
  return (ret);
}
