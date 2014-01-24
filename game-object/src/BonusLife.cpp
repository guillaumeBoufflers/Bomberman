#include	"BonusLife.hh"
#include	"GameScene.hh"

BonusLife::BonusLife(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusLife::BonusLife(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusLife::~BonusLife()
{

}

void            BonusLife::effectObject(APlayer *player)
{
  player->setLife(player->getLife() + 1);
  player->setScore(player->getScore() + SCORE_BONUS);
}
