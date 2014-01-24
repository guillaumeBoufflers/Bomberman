#include	"BonusHealth.hh"
#include	"GameScene.hh"

BonusHealth::BonusHealth(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusHealth::BonusHealth(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusHealth::~BonusHealth()
{

}

void            BonusHealth::effectObject(APlayer *player)
{
  player->setHealth(100);
  player->setScore(player->getScore() + SCORE_BONUS);
}
