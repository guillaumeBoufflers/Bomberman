#include	"Except.hh"

Except::Except()
{

}

Except::~Except()
{

}

Except::Except(int x, int y) :
  _x(x), _y(y)
{

}

void		Except::setX(int x)
{
  this->_x = x;
}

int		Except::getX() const
{
  return (this->_x);
}

void		Except::setY(int y)
{
  this->_y = y;
}

int		Except::getY() const
{
  return (this->_y);
}
