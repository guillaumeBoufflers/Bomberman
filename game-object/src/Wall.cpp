#include	"Wall.hh"
#include  "GameScene.hh"

Wall::Wall(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : AObject(x, y, scale, angle, mesh, type, OBJ)
{
  this->_globalType = type; // NE PLUS TOUCHER
}

Wall::Wall(TiXmlAttribute **attr) : AObject(attr)
{

}

Wall::~Wall()
{

}

int		Wall::update()
{
  return (0);
}

void		Wall::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void		Wall::initialize()
{

}

bool		Wall::isDestructible() const
{
  if (this->getType() == UNDESTRUCTIBLEWALL)
    return (false);
  else
    return (true);
}

bool		Wall::isMovable() const
{
  return (false);
}

bool		Wall::isTakable() const
{
  return (false);
}

bool		Wall::isReachable() const
{
  return (false);
}

bool		Wall::isExpandable() const
{
  return (false);
}

void		Wall::destroyObject()
{ 

}

void		Wall::effectObject(APlayer *player)
{
  if (!player->isAGhost())
  {
  player->setDamage(100);
  player->setLife(0);
  }
}