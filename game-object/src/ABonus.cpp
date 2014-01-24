#include	"ABonus.hh"
#include	"GameScene.hh"

ABonus::ABonus(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : AObject(x, y, scale, angle, mesh, type, BONUS), _destructible(false), _timeBeforeDestructible(BONUS_INVICIBILITY)
{

}

ABonus::ABonus(TiXmlAttribute **attrib) : AObject(attrib)
{
  this->_destructible = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_timeBeforeDestructible = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
}

ABonus::~ABonus()
{

}

int		ABonus::update()
{
  if (this->_destructible == false)
    {
      this->_timeBeforeDestructible--;
      if (this->_timeBeforeDestructible == 0)
	     this->_destructible = true;
    }
  this->_angle++;
  return (0);
}

void		ABonus::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(-30, 1, 0, 0);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void		ABonus::initialize()
{

}

bool		ABonus::isDestructible() const
{
  return (this->_destructible);
}

bool		ABonus::isMovable() const
{
  return (false);
}

bool		ABonus::isTakable() const
{
  return (true);
}

bool		ABonus::isReachable() const
{
  return (true);
}

bool		ABonus::isExpandable() const
{
  return (true);
}

void		ABonus::destroyObject()
{
  
}

TiXmlElement	*ABonus::serialize()
{
  TiXmlElement	*ret;

  ret = AObject::serialize();
  ret->SetAttribute("destructible", this->_destructible);
  ret->SetAttribute("timeBeforeExpo", this->_timeBeforeDestructible);
  return (ret);
}
