#include	"Rocket.hh"
#include	"GameScene.hh"
#include	"GDLObjectFactory.hh"

Rocket::Rocket(int x, int y, int scale, int angle, std::string &mesh, int puissance, int dispo, APlayer *owner) : ABomb(x, y, scale, angle, mesh, ROCKET, puissance, dispo, owner)
{
  
}

Rocket::Rocket(TiXmlAttribute **attrib) : ABomb(attrib)
{
  //  int toto;

  this->_dir = static_cast<Dir>((*attrib)->IntValue());
  (*attrib) = (*attrib)->Next();
  (*attrib)->QueryIntValue(&this->_xBeg);
  (*attrib) = (*attrib)->Next();
  (*attrib)->QueryIntValue(&this->_yBeg);
  (*attrib) = (*attrib)->Next();
  this->_x = this->_xBeg * CASE_SIZE;
  this->_y = this->_yBeg * CASE_SIZE;
}

Rocket::~Rocket()
{

}

void	Rocket::spreadExplosion(int range)
{
  for (int y = getPosCaseY() ; GameScene::isValidPos(getPosCaseX(), y) && y < getPosCaseY() + range ; ++y)
    {
      if ((*(GameScene::_map[y][getPosCaseX()].begin()))->isDestructible() == false && (*(GameScene::_map[y][getPosCaseX()].begin()))->isExpandable() == false)
	y = -2;
      else
	   {
	  GameScene::_map[y][getPosCaseX()].push_back(GameScene::factory->createObjSpec(getPosCaseX(), y, 1, 0, GameScene::_meshTab[EXPLOSION], EXPLOSION, this->_owner));
	  if ((*(GameScene::_map[y][getPosCaseX()].begin()))->isDestructible() == true)
	    {
	      y = -2;
	    }
	   }
    }
  for (int y = getPosCaseY() - 1 ; GameScene::isValidPos(getPosCaseX(), y) && y > getPosCaseY() - range ; --y)
    {

      if ((*(GameScene::_map[y][getPosCaseX()].begin()))->isDestructible() == false && (*(GameScene::_map[y][getPosCaseX()].begin()))->isExpandable() == false)
	y = -2;
      else
	{
	  GameScene::_map[y][getPosCaseX()].push_back(GameScene::factory->createObjSpec(getPosCaseX(), y, 1, 0, GameScene::_meshTab[EXPLOSION], EXPLOSION, this->_owner));
	  if ((*(GameScene::_map[y][getPosCaseX()].begin()))->isDestructible() == true)
	    {
	      y = -2;
	    }
	}
    }
  for (int x = getPosCaseX() + 1 ; GameScene::isValidPos(x, getPosCaseY()) && x < getPosCaseX() + range ; ++x)
    {

      if ((*(GameScene::_map[getPosCaseY()][x].begin()))->isDestructible() == false && (*(GameScene::_map[getPosCaseY()][x].begin()))->isExpandable() == false)
	x = -2;
      else
	{
	  GameScene::_map[getPosCaseY()][x].push_back(GameScene::factory->createObjSpec(x, getPosCaseY(), 1, 0,  GameScene::_meshTab[EXPLOSION], EXPLOSION, this->_owner));
	  if ((*(GameScene::_map[getPosCaseY()][x].begin()))->isDestructible() == true)
	    {
	      x = -2;
	    }
	}
    }
  for (int x = getPosCaseX() - 1 ; GameScene::isValidPos(x, getPosCaseY()) && x > getPosCaseX() - range ; --x)
    {
      if ((*(GameScene::_map[getPosCaseY()][x].begin()))->isDestructible() == false && (*(GameScene::_map[getPosCaseY()][x].begin()))->isExpandable() == false)
	x = -2;
      else
	{
	  GameScene::_map[getPosCaseY()][x].push_back(GameScene::factory->createObjSpec(x, getPosCaseY(), 1, 0, GameScene::_meshTab[EXPLOSION], EXPLOSION, this->_owner));
	  if ((*(GameScene::_map[getPosCaseY()][x].begin()))->isDestructible() == true)
	    {
	      x = -2;
	    }
	}
    }
}

int  Rocket::moveDown()
{
  if (this->canWalk(this->getPosX(), this->getPosY() + (MOVE_BY)))
  {
    this->_y += (MOVE_BY);
    return (0);
  }
  else
  {
    SoundController::playFxSound("explosion.ogg");
    this->explode();
    GameScene::destructObjectGame(GameScene::findSpecInstance(this));
    return (1);
  }
}

int  Rocket::moveUp()
{
  if (this->canWalk(this->getPosX(), this->getPosY() - (MOVE_BY)))
  {
    this->_y -= (MOVE_BY);
    return (0);
  }
  else
  {
    SoundController::playFxSound("explosion.ogg");
    this->explode();
    GameScene::destructObjectGame(GameScene::findSpecInstance(this));
    return (1);
  }
}

int  Rocket::moveRight()
{
  if (this->canWalk(this->getPosX() + (MOVE_BY), this->getPosY()))
  {
    this->_x += (MOVE_BY);
    return (0);
  }
  else
  {
    SoundController::playFxSound("explosion.ogg");
    this->explode();
    GameScene::destructObjectGame(GameScene::findSpecInstance(this));
     return (1);
  }
  return (0);
}

int  Rocket::moveLeft()
{
   if (this->canWalk(this->getPosX() - (MOVE_BY), this->getPosY()))
    { 
      this->_x -= (MOVE_BY);
      return (0);
    }
    else
    {
      SoundController::playFxSound("explosion.ogg");
      this->explode();
      GameScene::destructObjectGame(GameScene::findSpecInstance(this));
      return (1);
    }
    return (0);
}

int		Rocket::update()
{
  int     a = 0;

  if (_timeLeftBeforeExplosion == BOMB_TIME)
  {
    this->_dir = this->_owner->getDir();
    this->_xBeg = this->getPosCaseX();
    this->_yBeg = this->getPosCaseY();
    this->_angle = static_cast<int>(this->_owner->getRotY() + 180) % 360;
  }

  this->_timeLeftBeforeExplosion--;
  switch (_dir)
  {
    case DOWN:
      a = this->moveDown();
      break ;
    case UP:
      a = this->moveUp();
      break ;
    case LEFT:
      a = this->moveLeft();
      break ;
    case RIGHT:
      a = this->moveRight();
      break ;
    default:
      break;
  }
  return (a);
}

int     Rocket::getXBeg() const
{
  return (this->_xBeg);
}

int     Rocket::getYBeg() const
{
  return (this->_yBeg);
}

bool    Rocket::isReachable() const
{
  return (true);
}

void		Rocket::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void		Rocket::initialize()
{

}

TiXmlElement	*Rocket::serialize()
{
  TiXmlElement	*ret;

  ret = APhysicalObject::serialize();
  ret->SetAttribute("puissance", this->_puissance);
  ret->SetAttribute("dispo", this->_dispo);
  ret->SetAttribute("timeLeft", this->_timeLeftBeforeExplosion);
  ret->SetAttribute("dir", this->_dir);
  ret->SetAttribute("_xBeg", this->_xBeg);
  ret->SetAttribute("_yBeg", this->_yBeg);
  ret->SetAttribute("id_player", this->_owner->getId());
  return (ret);
}
