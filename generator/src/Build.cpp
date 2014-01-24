#include		"Build.hh"
#include		"QuadTree.hh"

Build::Build(int *size, int *players, int *rate, int *subWall, int *subUWall, int *subBonus)
{
  srand(time(NULL));
  this->_size = size;
  this->_players = players;
  this->_rate = rate;
  this->_subWall = subWall;
  this->_subUWall = subUWall;
  this->_subBonus = subBonus;
  this->_bonusList[0] = BONUSRANGE;
  this->_bonusList[1] = BONUSSTOCK;
  this->_bonusList[2] = BONUSSPEED;
  this->_bonusList[3] = BONUSRANDOM;
  this->_bonusList[4] = BONUSROCKET;
  this->_bonusList[5] = BONUSNUKE;
  this->_bonusList[6] = BONUSTOXIC;
  this->_bonusList[7] = BONUSSPIKE;
  this->_bonusList[8] = BONUSREMOTE;
  this->_bonusList[9] = BONUSLIFE;
  this->_bonusList[10] = BONUSSHIELD;
  this->_bonusList[11] = BONUSGHOST;
  this->_bonusList[12] = BONUSHEALTH;
  this->_bonusList[13] = BONUSRANDOM;
}

Build::~Build()
{

}

std::map<int, Object *>	Build::getList() const
{
  return (this->_list);
}

void			Build::pushLine(int rate, int y, int yMap, int *pos)
{
  int			x = 0;
  int			xMap = 0;

  while (xMap < (*this->_size))
    {
      if (yMap == 0 || xMap == 0 || yMap == ((*this->_size) - 1) || xMap == ((*this->_size) - 1))
	this->_list[*pos] = new Object(UNDESTRUCTIBLEWALL, x, y, xMap, yMap, true);
      else
	this->_list[*pos] = new Object(EMPTY, x, y, xMap, yMap, false);
      x += rate;
      xMap++;
      (*pos)++;
    }
}

void			Build::init()
{
  int			rate = WINDOWSIZE / (*this->_size);
  int			y = 0;
  int			yMap = 0;
  int			pos = 0;

  if (this->_list.size() != 0)
    this->_list.clear();
  while (yMap < (*this->_size))
    {
      this->pushLine(rate, y, yMap, &pos);
      y += rate;
      yMap++;
    }
}

bool			Build::isAnException(int x, int y) const
{
  for (std::list<Except *>::const_iterator it = this->_security.begin(); it != this->_security.end(); ++it)  
    if (x == (*it)->getX() && y == (*it)->getY())
      return (true);
  return (false);
}

void			Build::getValidPos(int *pos)
{
  Object		*obj;
  
  (*pos) = rand() % this->_list.size();
  obj = this->_list[(*pos)];
  while ((obj->getType() != EMPTY) || isAnException(obj->getPosMapX(), obj->getPosMapY()) == true || obj->getBorder() == true)
    {
      (*pos) = rand() % this->_list.size();
      obj = this->_list[(*pos)];
    }
}

void			Build::addOnMap(int pos, ObjectType type)
{
  Object		*obj;
  
  obj = this->_list[pos];
  obj->setType(type);
}

void			Build::handleDistrib(int it, ObjectType type)
{
  int			pos = 0;
  int			iter;

  iter = 0;
  while (iter < it)
    {
      this->getValidPos(&pos);
      this->addOnMap(pos, type);
      iter++;
    }
}

void			Build::handleDistrib(int it)
{
  int			pos = 0;
  int			iter;

  iter = 0;
  while (iter < it)
    {
      this->getValidPos(&pos);
      this->addOnMap(pos, getRandomBonus());
      iter++;
    }
}

void			Build::pushExcept(int x, int y)
{
  Except		*except;

  except = new Except();
  except->setX(x);
  except->setY(y);
  this->_security.push_back(except);
}

void			Build::setPlayer()
{
  QuadTree		yolo(1, 1, *this->_size - 1, *this->_size - 1, NULL, 0);

  yolo.makeDispo(this->_list, *this->_size);
  yolo.placePlayers(*this->_players, this->_list, *this->_size, this->_security);
}

ObjectType		Build::getRandomBonus()
{
  int			nb = rand() % 13;

  return (this->_bonusList[nb]);
}

void			Build::random()
{
  this->_nbObj = (((*this->_rate) * pow((*this->_size), 2)) / 100) - ((2 * (*this->_size)) + (2 * (*this->_size) - 2)) - (*this->_players);
  this->_nbUWall = ((*this->_subUWall) / 10.0) * this->_nbObj;
  this->_nbWall = ((*this->_subWall) / 10.0) * this->_nbObj;
  this->_nbBonus = ((*this->_subBonus) / 10.0) * this->_nbObj;
  this->handleDistrib(this->_nbUWall, UNDESTRUCTIBLEWALL);
  this->handleDistrib(this->_nbWall, DESTRUCTIBLEWALL);
  this->handleDistrib(this->_nbBonus);
}
