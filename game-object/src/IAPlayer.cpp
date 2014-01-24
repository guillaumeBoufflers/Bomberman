#include	"IAPlayer.hh"

IAPlayer::IAPlayer(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, int id, int life, int range, int start) : APlayer(x, y, scale, angle, mesh, type, id, life, range, start), _iacontroller(id)
{
  this->_model.set_default_model_color(gdl::Color(rand() % 255, rand()  % 255, rand()  % 255, 255));
}

IAPlayer::IAPlayer(TiXmlAttribute **attr) : APlayer(attr), _iacontroller(3) //  
{

}

IAPlayer::~IAPlayer()
{

}

void  IAPlayer::equipBestBomb()
{
  _typeBomb = BASICBOMB;
  if (_stockBomb[NUKEBOMB][2] > 0)
    _typeBomb = NUKEBOMB;
  if (_stockBomb[TOXICBOMB][2] > 0)
    _typeBomb = TOXICBOMB;
  if (_stockBomb[SPIKEBOMB][2] > 0)
    _typeBomb = SPIKEBOMB;
}

int		IAPlayer::update()
{
  this->checkStates();
  this->whatInCase();
  this->_act = _iacontroller.getDecision(this->getPosCaseX(), this->getPosCaseY(), this);
  this->_model.update(*Clock::getClock());
  switch (this->_act)
  {
      case BOT_GORIGHT:
        this->goRight();
        break ;
      case BOT_GOLEFT:
        this->goLeft();
        break ;
      case BOT_GOTOP:
        this->goUp();
        break ;
      case BOT_GOBOTTOM:
        this->goDown();
        break ;
      case BOT_POSEBOMB:
        this->equipBestBomb();
        this->putBomb();
        break ;
      default:
        break;
  }
  return (0);
}
