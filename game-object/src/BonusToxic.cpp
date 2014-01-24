#include	"BonusToxic.hh"
#include	"GameScene.hh"

BonusToxic::BonusToxic(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusToxic::BonusToxic(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusToxic::~BonusToxic()
{

}

void            BonusToxic::effectObject(APlayer *player)
{
  std::vector<int>      tmp2;

  tmp2 = player->getStock()[TOXICBOMB];
  if (tmp2[0] == -1)		
  	player->addToStock(TOXICBOMB, -1, tmp2[1], tmp2[2] + 1);
  else
  	player->addToStock(TOXICBOMB, 1, tmp2[1], tmp2[2] + 3);
  player->setScore(player->getScore() + SCORE_BONUS);
}
