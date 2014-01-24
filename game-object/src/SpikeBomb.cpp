#include	"SpikeBomb.hh"
#include	"GameScene.hh"
#include	"GDLObjectFactory.hh"

SpikeBomb::SpikeBomb(int x, int y, int scale, int angle, std::string &mesh, int puissance, int dispo, APlayer *owner) : ABomb(x, y, scale, angle, mesh, SPIKEBOMB, puissance, dispo, owner)
{

}

SpikeBomb::SpikeBomb(TiXmlAttribute **attr) : ABomb(attr)
{

}

SpikeBomb::~SpikeBomb()
{

}

void	SpikeBomb::spreadExplosion(int range)
{
  std::string mesh = "medias/models/explosion.fbx";

  for (int y = getPosCaseY() ; GameScene::isValidPos(getPosCaseX(), y) && y < getPosCaseY() + range ; ++y)
    GameScene::_map[y][getPosCaseX()].push_back(GameScene::factory->createObjSpec(getPosCaseX(), y, 1, 0, mesh, EXPLOSION, this->_owner));
  for (int y = getPosCaseY() - 1 ; GameScene::isValidPos(getPosCaseX(), y) && y > getPosCaseY() - range ; --y)
    GameScene::_map[y][getPosCaseX()].push_back(GameScene::factory->createObjSpec(getPosCaseX(), y, 1, 0, mesh, EXPLOSION, this->_owner));
  for (int x = getPosCaseX() + 1 ; GameScene::isValidPos(x, getPosCaseY()) && x < getPosCaseX() + range ; ++x)
    GameScene::_map[getPosCaseY()][x].push_back(GameScene::factory->createObjSpec(x, getPosCaseY(), 1, 0, mesh, EXPLOSION, this->_owner));
  for (int x = getPosCaseX() - 1 ; GameScene::isValidPos(x, getPosCaseY()) && x > getPosCaseX() - range ; --x)
      GameScene::_map[getPosCaseY()][x].push_back(GameScene::factory->createObjSpec(x, getPosCaseY(), 1, 0, mesh, EXPLOSION, this->_owner));
}

int		SpikeBomb::update()
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

void		SpikeBomb::draw()
{
  glPushMatrix();
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_angle, 0, 1, 0);
  this->_model.draw();
}

void		SpikeBomb::initialize()
{

}
