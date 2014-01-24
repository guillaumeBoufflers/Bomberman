#include	"BonusRange.hh"
#include	"GameScene.hh"

BonusRange::BonusRange(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusRange::BonusRange(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusRange::~BonusRange()
{

}

void            BonusRange::effectObject(APlayer *player)
{
  player->setRange(player->getRange() + 1);
  player->setScore(player->getScore() + SCORE_BONUS);
}
