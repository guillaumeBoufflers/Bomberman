#include	"Object.hh"

Object::Object(ObjectType type, int x, int y, int posMapX, int posMapY, bool border)
{
  this->_type = type;
  this->_posX = x;
  this->_posY = y;
  this->_posMapX = posMapX;
  this->_posMapY = posMapY;
  this->_isBorder = border;
}

Object::~Object()
{

}

void		Object::setX(int x)
{
  this->_posX = x;
}

void		Object::setY(int y)
{
  this->_posY = y;
}

void		Object::setType(ObjectType type)
{
  this->_type = type;
}

int		Object::getX() const
{
  return (this->_posX);
}

int		Object::getY() const
{
  return (this->_posY);
}

ObjectType	Object::getType() const
{
  return (this->_type);
}

void		Object::setSprite(sf::Sprite *sprite)
{
  this->_sprite = sprite;
}

sf::Sprite	*Object::getSprite() const
{
  return (this->_sprite);
}

bool		Object::getBorder() const
{
  return (this->_isBorder);
}

int		Object::getPosMapX() const
{
  return (this->_posMapX);
}

int		Object::getPosMapY() const
{
  return (this->_posMapY);
}

void		Object::setPosMapX(int x)
{
  this->_posMapX = x;
}

void		Object::setPosMapY(int y)
{
  this->_posMapY = y;
}
