#include	"BonusGhost.hh"
#include	"GameScene.hh"

BonusGhost::BonusGhost(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusGhost::BonusGhost(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusGhost::~BonusGhost()
{

}

void            BonusGhost::effectObject(APlayer *player)
{
  player->setIsAGhost(true);
  player->setScore(player->getScore() + SCORE_BONUS);
}
