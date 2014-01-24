#include	"BonusSpike.hh"
#include	"GameScene.hh"

BonusSpike::BonusSpike(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusSpike::BonusSpike(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusSpike::~BonusSpike()
{

}

void            BonusSpike::effectObject(APlayer *player)
{
  std::vector<int>      tmp2;

  tmp2 = player->getStock()[SPIKEBOMB];
  if (tmp2[0] == -1)		
  	player->addToStock(SPIKEBOMB, -1, tmp2[1], tmp2[2] + 1);
  else
  	player->addToStock(SPIKEBOMB, 1, tmp2[1], tmp2[2] + 3);
  player->setScore(player->getScore() + SCORE_BONUS);
}
