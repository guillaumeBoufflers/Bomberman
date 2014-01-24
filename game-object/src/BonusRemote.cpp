#include	"BonusRemote.hh"
#include	"GameScene.hh"

BonusRemote::BonusRemote(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusRemote::BonusRemote(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusRemote::~BonusRemote()
{

}

void            BonusRemote::effectObject(APlayer *player)
{
  std::vector<int>      tmp2;

  tmp2 = player->getStock()[REMOTEBOMB];
  if (tmp2[0] == -1)		
  	player->addToStock(REMOTEBOMB, -1, tmp2[1], tmp2[2] + 1);
  else
  	player->addToStock(REMOTEBOMB, 1, tmp2[1], tmp2[2] + 3);
  player->setScore(player->getScore() + SCORE_BONUS);
}
