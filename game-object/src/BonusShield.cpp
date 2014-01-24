#include	"BonusShield.hh"
#include	"GameScene.hh"

BonusShield::BonusShield(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusShield::BonusShield(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusShield::~BonusShield()
{

}

void            BonusShield::effectObject(APlayer *player)
{
  player->setIsDestructible(false);
  player->setScore(player->getScore() + SCORE_BONUS);
}
