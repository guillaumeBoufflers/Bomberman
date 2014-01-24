#include	"BonusRocket.hh"
#include	"GameScene.hh"

BonusRocket::BonusRocket(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusRocket::BonusRocket(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusRocket::~BonusRocket()
{

}

void            BonusRocket::effectObject(APlayer *player)
{
  std::vector<int>      tmp2;

  tmp2 = player->getStock()[ROCKET];
  if (tmp2[0] == -1)		
  	player->addToStock(ROCKET, -1, tmp2[1], tmp2[2] + 1);
  else
  	player->addToStock(ROCKET, 1, tmp2[1], tmp2[2] + 3);
  player->setScore(player->getScore() + SCORE_BONUS);
}
