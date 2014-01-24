#include	"BasicBomb.hh"
#include	"GameScene.hh"
#include	"GDLObjectFactory.hh"

BasicBomb::BasicBomb(int x, int y, int scale, int angle, std::string &mesh, int puissance, int dispo, APlayer *owner) : ABomb(x, y, scale, angle, mesh, BASICBOMB, puissance, dispo, owner)
{

}

BasicBomb::BasicBomb(TiXmlAttribute **attr) : ABomb(attr)
{

}

BasicBomb::~BasicBomb()
{

}

void	BasicBomb::spreadExplosion(int range)
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

int		BasicBomb::update()
{
  this->_timeLeftBeforeExplosion--;
  if (_timeLeftBeforeExplosion <= 0)
  {
    SoundController::playFxSound("explosion.ogg");
    this->explode();
    GameScene::destructObjectGame(GameScene::findInstance(this));
    return (1);
  }
  return (0);
}

void		BasicBomb::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void		BasicBomb::initialize()
{

}
