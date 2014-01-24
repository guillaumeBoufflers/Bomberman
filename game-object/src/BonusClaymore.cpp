#include	"BonusClaymore.hh"
#include	"GameScene.hh"

BonusClaymore::BonusClaymore(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusClaymore::BonusClaymore(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusClaymore::~BonusClaymore()
{

}

void            BonusClaymore::effectObject(APlayer *player)
{
  std::vector<int>      tmp2;

  tmp2 = player->getStock()[CLAYMORE];
  if (tmp2[0] == -1)		
  	player->addToStock(CLAYMORE, -1, tmp2[1], tmp2[2] + 1);
  else
  	player->addToStock(CLAYMORE, 1, tmp2[1], tmp2[2] + 3);
  player->setScore(player->getScore() + SCORE_BONUS);
}
