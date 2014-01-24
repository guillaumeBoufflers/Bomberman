#include	"BonusNuke.hh"
#include	"GameScene.hh"

BonusNuke::BonusNuke(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusNuke::BonusNuke(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusNuke::~BonusNuke()
{

}

void            BonusNuke::effectObject(APlayer *player)
{
  std::vector<int>      tmp2;

  tmp2 = player->getStock()[NUKEBOMB];
  if (tmp2[0] == -1)		
  	player->addToStock(NUKEBOMB, -1, tmp2[1], tmp2[2] + 1);
  else
  	player->addToStock(NUKEBOMB, 1, tmp2[1], tmp2[2] + 3);
  player->setScore(player->getScore() + SCORE_BONUS);
}
