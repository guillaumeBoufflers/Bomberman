#include	"Empty.hh"

Empty::Empty(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : AObject(x, y, scale, angle, mesh, type, OBJ)
{

}

Empty::Empty(TiXmlAttribute **attr) : AObject(attr)
{

}

Empty::~Empty()
{

}

int		Empty::update()
{
  return (0);
}

void		Empty::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void		Empty::initialize()
{

}

bool		Empty::isDestructible() const
{
  return (false);
}

bool		Empty::isMovable() const
{
  return (false);
}

bool		Empty::isTakable() const
{
  return (false);
}

bool		Empty::isReachable() const
{
  return (true);
}

bool		Empty::isExpandable() const
{
  return (true);
}

void		Empty::destroyObject()
{

}

void		Empty::effectObject(APlayer *)
{
}
