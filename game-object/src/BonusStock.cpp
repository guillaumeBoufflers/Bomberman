#include	"BonusStock.hh"
#include	"GameScene.hh"

BonusStock::BonusStock(int x, int y, int scale, int angle, std::string &mesh, ObjectType type) : ABonus(x, y, scale, angle, mesh, type)
{

}

BonusStock::BonusStock(TiXmlAttribute **attr) : ABonus(attr)
{

}

BonusStock::~BonusStock()
{

}

void            BonusStock::effectObject(APlayer *player)
{
  std::map<ObjectType, std::vector<int> >       tmp;
  std::vector<int>      tmp2;

  tmp = player->getStock();
  for (std::map<ObjectType, std::vector<int> >::const_iterator it = tmp.begin(); it != tmp.end(); ++it)
    {
      tmp2 = it->second;
      if (tmp2[0] == -1)
	player->addToStock(it->first, -1, tmp2[1], tmp2[2] + 1);
      else
	player->addToStock(it->first, 1, tmp2[1], tmp2[2] + 2);
      tmp2.clear();
    }
  player->setScore(player->getScore() + SCORE_BONUS);
}
