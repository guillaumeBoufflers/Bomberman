#include	"ToxicBomb.hh"
#include	"GameScene.hh"
#include	"GDLObjectFactory.hh"

ToxicBomb::ToxicBomb(int x, int y, int scale, int angle, std::string &mesh, int puissance, int dispo, APlayer *owner) : ABomb(x, y, scale, angle, mesh, TOXICBOMB, puissance, dispo, owner)
{
  this->_timeLeftBeforeExplosion = BIGBOMB_TIME;
}

ToxicBomb::ToxicBomb(TiXmlAttribute **attr) : ABomb(attr)
{

}

ToxicBomb::~ToxicBomb()
{

}

void	ToxicBomb::spreadExplosion(int range)
{
  for (int y = getPosCaseY() - (2 * range) ; y < getPosCaseY() + (2 * range) ; ++y)
    {
      for (int x = getPosCaseX() - (2 * range) ; x < getPosCaseX() + (2 * range) ; ++x)
	{
	  if (GameScene::isValidPos(x, y))
	    if ((sqrt(pow(abs(getPosCaseX()) - x, 2) + pow(abs(getPosCaseY()) - y, 2)) < range))// && ((*(GameScene::_map[y][x].begin()))->isDestructible() == true || (*(GameScene::_map[y][x].begin()))->isExpandable() == true))
	      GameScene::_map[y][x].push_back(GameScene::factory->createObjSpec(x, y, 1, 0, GameScene::_meshTab[TOXICCLOUD], TOXICCLOUD, this->_owner));
	}
    }
}

int		ToxicBomb::update()
{
  this->_timeLeftBeforeExplosion--;
  if (_timeLeftBeforeExplosion <= 0)
  {
    SoundController::playFxSound("nuke.ogg");
    this->explode();
    GameScene::destructObjectGame(GameScene::findInstance(this));
    return (1);
  }
  return (0);
}

void		ToxicBomb::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void		ToxicBomb::initialize()
{

}
