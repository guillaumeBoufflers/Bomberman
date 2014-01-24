#include	"BonusSpeed.hh"
#include	"GameScene.hh"

BonusSpeed::BonusSpeed(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusSpeed::BonusSpeed(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusSpeed::~BonusSpeed()
{

}

void            BonusSpeed::effectObject(APlayer *player)
{
  player->setSpeed(player->getSpeed() + 1.0);
  player->setScore(player->getScore() + SCORE_BONUS);
}
