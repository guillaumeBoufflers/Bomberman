#include	"Claymore.hh"
#include	"GameScene.hh"
#include	"GDLObjectFactory.hh"

Claymore::Claymore(int x, int y, int scale, int angle, std::string &mesh, int puissance, int dispo, APlayer *owner) : ABomb(x, y, scale, angle, mesh, CLAYMORE, puissance, dispo, owner)
{

}

Claymore::Claymore(TiXmlAttribute **attr) : ABomb(attr)
{

}

Claymore::~Claymore()
{

}

void	Claymore::spreadExplosion(int range)
{
  std::string mesh = "medias/models/explosion.fbx"; // nice collision bitch
  for (int y = getPosCaseY() ; GameScene::isValidPos(getPosCaseX(), y) && y < getPosCaseY() + range ; ++y)
    {
      if ((*(GameScene::_map[y][getPosCaseX()].begin()))->isDestructible() == false && (*(GameScene::_map[y][getPosCaseX()].begin()))->isExpandable() == false)
	y = -2;
      else
	{
	  GameScene::_map[y][getPosCaseX()].push_back(GameScene::factory->createObjSpec(getPosCaseX(), y, 1, 0, mesh, EXPLOSION, this->_owner));
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
	  GameScene::_map[y][getPosCaseX()].push_back(GameScene::factory->createObjSpec(getPosCaseX(), y, 1, 0, mesh, EXPLOSION, this->_owner));
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
	  GameScene::_map[getPosCaseY()][x].push_back(GameScene::factory->createObjSpec(x, getPosCaseY(), 1, 0, mesh, EXPLOSION, this->_owner));
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
	  GameScene::_map[getPosCaseY()][x].push_back(GameScene::factory->createObjSpec(x, getPosCaseY(), 1, 0, mesh, EXPLOSION, this->_owner));
	  if ((*(GameScene::_map[getPosCaseY()][x].begin()))->isDestructible() == true)
	    {
	      x = -2;
	    }
	}
    }
}

bool    Claymore::isReachable() const
{
  return (true);
}

int		Claymore::update()
{
  if (this->_timeLeftBeforeExplosion > 0)
    this->_timeLeftBeforeExplosion -= 2;
  if (this->getStatus() == DETONATING)
    {
      SoundController::playFxSound("explosion.ogg");
      GameScene::destructObjectGame(GameScene::findInstance(this));
      return (1);
    }
  return (0);
}

void		Claymore::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void		Claymore::initialize()
{

}
