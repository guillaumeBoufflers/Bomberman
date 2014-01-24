#include	"BonusRandom.hh"
#include	"GameScene.hh"

BonusRandom::BonusRandom(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusRandom::BonusRandom(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusRandom::~BonusRandom()
{

}

void            BonusRandom::effectObject(APlayer *player)
{
  player->setRange(player->getRange() + 1);
  player->setScore(player->getScore() + SCORE_BONUS);
}
