#include	"Explosion.hh"
#include	"GameScene.hh"

Explosion::Explosion(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, APlayer *owner) : AObject(x, y, scale, angle, mesh, type, EXPLOSION /*NE PLUS TOUCHER !!!!!!!!!!!!!!*/), _nbFramesSinceSpawn(0), _owner(owner), _hasDestroyedWall(false)
{

}

Explosion::Explosion(TiXmlAttribute **attrib) : AObject(attrib)
{
  this->_nbFramesSinceSpawn = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_hasDestroyedWall = static_cast<bool>((*attrib)->IntValue());
  (*attrib) = (*attrib)->Next();
}

Explosion::~Explosion()
{

}

int		Explosion::update()
{
  //  this->_model.play("EXPLODE"); // << penser à ajouter l'anim
  if (this->_nbFramesSinceSpawn < EXPLOSION_TIME)
  {
    if (this->_nbFramesSinceSpawn == 0)
    {
     for (std::list<IPhysicalObject *>::iterator it = GameScene::_map[getPosCaseY()][getPosCaseX()].begin() ; it != GameScene::_map[getPosCaseY()][getPosCaseX()].end(); ++it)
      if ((*it)->isDestructible() && (*it) != this)
      {
        if ((*it)->getType() == DESTRUCTIBLEWALL)
          this->_hasDestroyedWall = true;
       GameScene::destructObjectGame(it);
       return (0);
     }
    }
    else if (this->_nbFramesSinceSpawn % 4 == 0)
    {
      for (std::list<IPhysicalObject *>::iterator it = GameScene::_map[getPosCaseY()][getPosCaseX()].begin() ; it != GameScene::_map[getPosCaseY()][getPosCaseX()].end(); ++it)
        if ((*it)->isDestructible() && (*it) != this)
        {
         GameScene::destructObjectGame(it);
         return (0);
       }

     }
   }
  else if (this->_nbFramesSinceSpawn == EXPLOSION_TIME) // << penser à régler par rapport à deux define (fps & durée before explosion)
  {
    if (this->_hasDestroyedWall)
    {
      if (rand() % (Bomberman::isArmageddon) == 0)
      {
        int   a = rand() % 14;
        a++;
        a += BONUS;
        ObjectType  tmp;
        try
        {
           tmp = static_cast<ObjectType>(a);
        }
        catch (const std::exception &e)
        {
          std::cerr << "Exception :" << e.what() << std::endl;
        }
        GameScene::_map[this->getPosCaseY()][this->getPosCaseX()].push_back(GameScene::factory->createAObject(this->getPosCaseX(), this->getPosCaseY(), 1, 0, GameScene::_meshTab[tmp], tmp));
      }
    }
    GameScene::destructObjectGame(GameScene::findInstance(this));
    return (1);
  }
  this->_nbFramesSinceSpawn++;
  return (0);
}

void    Explosion::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void    Explosion::initialize()
{
  //  gdl::Model::cut_animation(this->_model, "Default Take", 0, 9, "EXPLODE");
}

int		Explosion::getNbFramesSinceSpawn() const
{
  return (this->_nbFramesSinceSpawn);
}

void		Explosion::setNbFramesSinceSpawn(int val)
{
  this->_nbFramesSinceSpawn = val;
}

bool		Explosion::isDestructible() const
{
  return (true);
}

bool		Explosion::isMovable() const
{
  return (true);
}

bool		Explosion::isTakable() const
{
  return (false);
}

bool		Explosion::isReachable() const
{
  return (true);
}

bool		Explosion::isExpandable() const
{
  return (true);
}

void		Explosion::destroyObject()
{

}

void		Explosion::setPlayer(APlayer *player)
{
  this->_owner = player;
}

void		Explosion::effectObject(APlayer *player)
{
  if (!player->getIsRecovering() && player->isDestructible())
  {
     player->setDamage(100);
    if (player != this->_owner)
      this->_owner->setScore(this->_owner->getScore() + SCORE_KILL); 
  }
}

TiXmlElement	*Explosion::serialize()
{
  TiXmlElement	*ret;

  ret = AObject::serialize();
  ret->SetAttribute("nbFrames", this->_nbFramesSinceSpawn);
  ret->SetAttribute("destroyWall", this->_hasDestroyedWall);
  ret->SetAttribute("id_play", this->_owner->getId());
  return (ret);
}
