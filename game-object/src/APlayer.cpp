#include	"APlayer.hh"
#include	"GameScene.hh"

APlayer::APlayer(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, int id, int life, int range, int startBomb) : APhysicalObject(x, y, scale, angle, mesh, type, PLAYER), _rotx(0.0), _roty(0.0), _rotz(0.0),  _id(id), _life(life), _health(100), _recoveryTime(RECOVERY_TIME), _score(0),_range(range), _speed(0.0), _isDestructible(false), _canShootBomb(true), _isRecovering(false), _canPutBomb(true), _isAGhost(false), _hasDetonate(false), _timeGhost(0), _timeInvincible(0), _typeBomb(BASICBOMB), _dir(DOWN), _timeChangingWeapon(0)
{
  this->addToStock(BASICBOMB, -1, MAX_BOMB, startBomb);
  this->addToStock(SPIKEBOMB, 0, MAX_BOMB, 0);
  this->addToStock(CLAYMORE, 0, MAX_BOMB, 0);
  this->addToStock(NUKEBOMB, 0, MAX_BOMB, 0);
  this->addToStock(ROCKET, 0, MAX_BOMB, 0);
  this->addToStock(TOXICBOMB, 0, MAX_BOMB, 0);
  this->addToStock(REMOTEBOMB, 0, MAX_BOMB, 0);

  this->_tabBomb.push_back(BASICBOMB);
  this->_tabBomb.push_back(SPIKEBOMB);
  this->_tabBomb.push_back(CLAYMORE);
  this->_tabBomb.push_back(NUKEBOMB);
  this->_tabBomb.push_back(ROCKET);
  this->_tabBomb.push_back(TOXICBOMB);
  this->_tabBomb.push_back(REMOTEBOMB);
}

APlayer::APlayer(TiXmlAttribute **attrib) : APhysicalObject(attrib)
{
  (*attrib)->QueryIntValue(&this->_id);
  (*attrib) = (*attrib)->Next();
  (*attrib)->QueryIntValue(&this->_life);
  (*attrib) = (*attrib)->Next();
  this->_rotx = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_roty = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_rotz = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  (*attrib)->QueryIntValue(&this->_health);
  (*attrib) = (*attrib)->Next();
  (*attrib)->QueryIntValue(&this->_recoveryTime);
  (*attrib) = (*attrib)->Next();

  (*attrib)->QueryIntValue(&this->_score);
  (*attrib) = (*attrib)->Next();

  this->_range = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_speed = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_isDestructible = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_canShootBomb = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_isRecovering = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_canPutBomb = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();

  this->_isAGhost = static_cast<bool>((*attrib)->IntValue());
  (*attrib) = (*attrib)->Next();
  this->_hasDetonate = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_timeGhost = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_timeInvincible = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();
  this->_timeChangingWeapon = (*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();

  this->_typeBomb = static_cast<ObjectType>((*attrib)->IntValue());
  (*attrib) = (*attrib)->Next();
  this->_dir = (Dir)(*attrib)->IntValue();
  (*attrib) = (*attrib)->Next();

  this->_tabBomb.push_back(BASICBOMB);
  this->_tabBomb.push_back(SPIKEBOMB);
  this->_tabBomb.push_back(CLAYMORE);
  this->_tabBomb.push_back(NUKEBOMB);
  this->_tabBomb.push_back(ROCKET);
  this->_tabBomb.push_back(TOXICBOMB);
  this->_tabBomb.push_back(REMOTEBOMB);
}

APlayer::~APlayer()
{

}

void		APlayer::initialize()
{
  gdl::Model::cut_animation(this->_model, "Take 001", 0, 0, "START");
  gdl::Model::cut_animation(this->_model, "Take 001", 36, 53, "RUN");
  gdl::Model::cut_animation(this->_model, "Take 001", 60, 120, "END");
}

float		APlayer::getRotX() const
{
	return (this->_rotx);
}

void		APlayer::setRotX(float val)
{
	this->_rotx = val;
}

float		APlayer::getRotY() const
{
	return (this->_roty);
}

void		APlayer::setRotY(float val)
{
	this->_roty = val;
}

float		APlayer::getRotZ() const
{
	return (this->_rotz);
}

void		APlayer::setRotZ(float val)
{
	this->_rotz = val;
}

int		APlayer::getId() const
{
	return (this->_id);
}

void		APlayer::setId(int val)
{
	this->_id = val;
}

int		APlayer::getLife() const
{
	return (this->_life);
}

void		APlayer::setLife(int val)
{
	this->_life = val;
}

int		APlayer::getHealth() const
{
	return (this->_health);
}

void		APlayer::setHealth(int val)
{
	this->_health = val;
}

int		APlayer::getRecoveryTime() const
{
	return (this->_recoveryTime);
}

void		APlayer::setRecoveryTime(int val)
{
	this->_recoveryTime = val;
}

int		APlayer::getScore() const
{
	return (this->_score);
}

void		APlayer::setScore(int val)
{
	this->_score = val;
}

float		APlayer::getSpeed() const
{
	return (this->_speed);
}

void		APlayer::setSpeed(float val)
{
	this->_speed = val;
  if (this->_speed > 5)
    this->_speed = 5;
}

float		APlayer::getRange() const
{
	return (this->_range);
}

void		APlayer::setRange(float val)
{
	this->_range = val;
}

void		APlayer::setIsDestructible(bool val)
{
	this->_isDestructible = val;
}

bool    APlayer::isAGhost() const
{
  return (this->_isAGhost);
}

void    APlayer::setIsAGhost(bool val)
{
  this->_isAGhost = val;
}

bool    APlayer::hasDetonateBomb() const
{
  return (this->_hasDetonate);
}

void    APlayer::setDetonateBomb(bool val)
{
  this->_hasDetonate = val;
}

bool		APlayer::getCanShootBomb() const
{
	return (this->_canShootBomb);
}

void		APlayer::setCanShootBomb(bool val)
{
	this->_canShootBomb = val;
}

bool		APlayer::getIsRecovering() const
{
	return (this->_isRecovering);
}

void		APlayer::setIsRecovering(bool val)
{
	this->_isRecovering = val;
}

bool		APlayer::getCanPutBomb() const
{
	return (this->_canPutBomb);
}

void		APlayer::setCanPutBomb(bool val)
{
	this->_canPutBomb = val;
}

ObjectType	APlayer::getTypeBomb() const
{
	return (this->_typeBomb);
}

void		APlayer::setTypeBomb(ObjectType val)
{
	this->_typeBomb = val;
}

Dir		APlayer::getDir() const
{
	return (this->_dir);
}

void		APlayer::setDir(Dir val)
{
	this->_dir = val;
}

void		APlayer::checkDeath()
{
    if (!this->_isRecovering)
      {
        if (this->_health <= 0)
     {
      this->_isRecovering = true;
      this->_canPutBomb = false;
      this->_health = 0;
      this->_life -= 1;
      this->_isAGhost = false;
      if (this->_life <= 0)
        {
          SoundController::playFxSound("die.ogg");
      this->_status = DEAD;
      if (this->getId() == 0)
        GameScene::p1Alive = false;
      else if (this->getId() == 1)
        GameScene::p2Alive = false;
      return ;
        }
    }
    }
}

void		APlayer::addToStock(ObjectType type, int limit, int max, int nbr)
{
  std::vector<int>	tmp;

  tmp.push_back(limit);
  tmp.push_back(max);
  if (nbr > max)
      nbr = max; 
  tmp.push_back(nbr);
  this->_stockBomb[type] = tmp;
  GameScene::_updateVector = true;
  if (this->_id == 0)
    GameScene::_listBombP1[type - BOMB - 1] = nbr;
  else if (this->_id == 1)
    GameScene::_listBombP2[type - BOMB - 1] = nbr;

}

void		APlayer::reloadStock(ObjectType obj)
{
  if (this->_stockBomb[obj][2] < this->_stockBomb[obj][1])
    this->_stockBomb[obj][2] += 1;
}

bool		APlayer::checkStock()
{
	if (this->_stockBomb[this->_typeBomb][2] >= 1)
		return (true);
	return (false);
}

void		APlayer::goLeft()
{
  if ((this->canWalk(this->getPosX() - (MOVE_BY + this->_speed), this->getPosY()) || (((*(GameScene::_map[this->getPosCaseY()][this->getPosCaseX()].back())).getGlobalType() == BOMB) && this->canWalkOutTo(this->getPosX() - (MOVE_BY + this->_speed), this->getPosY(), this->getPosCaseX(), this->getPosCaseY()))) 
    || (this->_isAGhost && GameScene::isValidPos((this->getPosX() - (MOVE_BY + this->_speed) + (CASE_SIZE / 2)) / CASE_SIZE, (this->getPosY() + (CASE_SIZE / 2)) / CASE_SIZE)))
    {
      this->_model.play("RUN");
      if (this->_dir != LEFT)
	{
	  if (this->_dir  == RIGHT)
	    this->_roty = (static_cast<int>(_roty) + 180) % 360;
	  else if (this->_dir  == DOWN)
	    this->_roty = (static_cast<int>(_roty) - 90) % 360;
	  else
	    this->_roty = (static_cast<int>(_roty) + 90) % 360;
	  this->_dir = LEFT;
	}
      this->_x -= (MOVE_BY + this->_speed);
    }
  else
    this->doNothing();
}

void		APlayer::goUp()
{
  if ((this->canWalk(this->getPosX(), this->getPosY() - (MOVE_BY + this->_speed))
    || (((*(GameScene::_map[this->getPosCaseY()][this->getPosCaseX()].back())).getGlobalType() == BOMB)
          && this->canWalkOutTo(this->getPosX(), this->getPosY() - (MOVE_BY + this->_speed), this->getPosCaseX(), this->getPosCaseY()))) 
    || (this->_isAGhost && GameScene::isValidPos((this->getPosX() + (CASE_SIZE / 2)) / CASE_SIZE, (this->getPosY() - (MOVE_BY + this->_speed) + (CASE_SIZE / 2)) / CASE_SIZE)))
    {
      this->_model.play("RUN");
      if (this->_dir != UP)
	{
	  if (this->_dir  == DOWN)
	    this->_roty = (static_cast<int>(_roty) + 180) % 360;
	  else if (this->_dir  == LEFT)
	    this->_roty = (static_cast<int>(_roty) - 90) % 360;
	  else
	    this->_roty = (static_cast<int>(_roty) + 90) % 360;
	  this->_dir = UP;
	}
      this->_y -= (MOVE_BY + this->_speed); // <<<< BY MAITRE_C    += -     NICE LOGIC
    }
  else
    this->doNothing();
}

void		APlayer::goDown()
{
  if ((this->canWalk(this->getPosX(), this->getPosY() + (MOVE_BY + this->_speed))
    || (((*(GameScene::_map[this->getPosCaseY()][this->getPosCaseX()].back())).getGlobalType() == BOMB)
          && this->canWalkOutTo(this->getPosX(), this->getPosY() + (MOVE_BY + this->_speed), this->getPosCaseX(), this->getPosCaseY()))) 
    || (this->_isAGhost && GameScene::isValidPos((this->getPosX() + (CASE_SIZE / 2)) / CASE_SIZE, (this->getPosY() + (MOVE_BY + this->_speed) + (CASE_SIZE / 2)) / CASE_SIZE)))
    {
      this->_model.play("RUN");
      if (this->_dir != DOWN)
	{
	  if (this->_dir  == UP)
	    this->_roty = (static_cast<int>(_roty) + 180) % 360;
	  else if (this->_dir  == RIGHT)
	    this->_roty = (static_cast<int>(_roty) - 90) % 360;
	  else
	    this->_roty = (static_cast<int>(_roty) + 90) % 360;
	  this->_dir = DOWN;
	}
      this->_y += (MOVE_BY + this->_speed);
    }
  else
    this->doNothing();
}

void		APlayer::goRight()
{
  if ((this->canWalk(this->getPosX() + (MOVE_BY + this->_speed), this->getPosY())
    || (((*(GameScene::_map[this->getPosCaseY()][this->getPosCaseX()].back())).getGlobalType() == BOMB)
          && this->canWalkOutTo(this->getPosX() + (MOVE_BY + this->_speed), this->getPosY(), this->getPosCaseX(), this->getPosCaseY()))) 
    || (this->_isAGhost && GameScene::isValidPos((this->getPosX() + (MOVE_BY + this->_speed) + (CASE_SIZE / 2)) / CASE_SIZE, (this->getPosY() + (CASE_SIZE / 2)) / CASE_SIZE)))
    {
      this->_model.play("RUN");
      if (this->_dir != RIGHT)
	{
	  if (this->_dir  == LEFT)
	    this->_roty = (static_cast<int>(_roty) + 180) % 360;
	  else if (this->_dir  == UP)
	    this->_roty = (static_cast<int>(_roty) - 90) % 360;
	  else
	    this->_roty = (static_cast<int>(_roty) + 90) % 360;
	  this->_dir = RIGHT;
	}
      this->_x += (MOVE_BY + this->_speed);
    }
  else
    this->doNothing();
}

void		APlayer::doNothing()
{
	this->_model.play("START");
}

void		APlayer::selectBomb(const std::string &action)
{
  int  tmp;
  ObjectType  final;

  if (action == "prev")
  {
    if (this->_typeBomb == BASICBOMB)
      tmp = REMOTEBOMB;
    else
      tmp = this->_typeBomb - 1;
    try
    {
      final = static_cast<ObjectType>(tmp);      
    }
    catch (const std::exception &e)
        {
      throw BombermanException("cast fail\n");
        }
    this->_typeBomb = final;
  }
  else
  {
    if (this->_typeBomb == REMOTEBOMB)
      tmp = BASICBOMB;
    else
      tmp = this->_typeBomb + 1;
    try
    {
     final = static_cast<ObjectType>(tmp);      
    }
    catch (const std::exception &e)
        {
      throw BombermanException("cast fail\n");
        }
    this->_typeBomb = final;    
  }
  if (this->getId() == 0)
    GameScene::currentWeapon1 = tmp - BOMB - 1;
  else if (this->getId() == 1)
    GameScene::currentWeapon2 = tmp - BOMB - 1;
}

void		APlayer::putBomb()
{
  if (this->checkStock() && this->_canPutBomb)
  {
    if (CAN_POSE_BOMB)
    {
      return ;      
    }
    this->_stockBomb[this->_typeBomb][2] -= 1;
    GameScene::_updateVector = true;
    if (this->getId() == 0)
      GameScene::_listBombP1[this->_typeBomb - BOMB - 1] = this->_stockBomb[this->_typeBomb][2];
    else if (this->getId() == 1)
      GameScene::_listBombP2[this->_typeBomb - BOMB - 1] = this->_stockBomb[this->_typeBomb][2];
    GameScene::_map[getPosCaseY()][getPosCaseX()].push_back(GameScene::factory->createABomb(getPosCaseX(), getPosCaseY(), 1, 0, GameScene::_meshTab[this->_typeBomb], this->_typeBomb, this->_range + 1,  this->_stockBomb[this->_typeBomb][0], this));
  }
}

void		APlayer::shootBomb()
{

}

std::map<ObjectType, std::vector<int> >		APlayer::getStock() const
{
	return (this->_stockBomb);
}

void		APlayer::whatInCase()
{
  int		x = this->getPosCaseX();
  int		y = this->getPosCaseY();

 if (GameScene::_map[y][x].size() != 1)
 {
  for (std::list<IPhysicalObject *>::iterator it = GameScene::_map[y][x].begin(); it != GameScene::_map[y][x].end(); ++it)
  {
    IObject *tmp;
    tmp = dynamic_cast<IObject*>(*it);
    if (tmp == NULL)
      throw BombermanException("cast fail\n");
   tmp->effectObject(this);
   if ((*it)->getGlobalType() == BONUS)
   {
     GameScene::destructObjectGame(it);
      return ;
   }
 }
}
}

void    APlayer::checkStates()
{
  if (this->_isRecovering)
  {
    this->_recoveryTime -= 1;
    if (this->_recoveryTime <= 0)
    {
     this->_canPutBomb = true;
     this->_isRecovering = false;
     this->_recoveryTime = RECOVERY_TIME;
     this->_health = 100;
   }
 }
  if (this->_isAGhost)
  {
    this->_timeGhost++;
    if (this->_timeGhost == TIME_GHOST)
    {
      this->_isAGhost = false;
        this->_timeGhost = 0;
    }
  }
  if (!this->_isDestructible)
  {
   this->_timeInvincible++;
    if (this->_timeInvincible == TIME_RAMBO)
    {
      this->_isDestructible = true;
      this->_timeInvincible = 0;
    }
  }
}

std::vector<int> APlayer::getNumberBomb() const
{
  std::vector<int>      tmp;

  for (std::map<ObjectType, std::vector<int> >::const_iterator it = this->_stockBomb.begin(); it != this->_stockBomb.end(); ++it)
      tmp.push_back(it->second[2]);
    return (tmp);
}

void		APlayer::draw()
{
  if (this->_isAGhost && this->_timeGhost % 2 == 0)
    return ;
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_roty, 0.0f, 1.0f, 0.0f);
  this->_model.draw();
}

void		APlayer::setDamage(int dmg)
{
  this->_health -= dmg;
  this->checkDeath();
}

void    APlayer::detonateRemote()
{
  this->_hasDetonate = true;
}

bool		APlayer::isDestructible() const
{
	return (this->_isDestructible);
}

bool		APlayer::isMovable() const
{
	return (true);
}

bool		APlayer::isTakable() const
{
	return (false);
}

bool		APlayer::isReachable() const
{
	return (true);
}

bool		APlayer::isExpandable() const
{
	return (true);
}

TiXmlElement	*APlayer::serialize()
{
  TiXmlElement	*ret;
  TiXmlElement	*newr;

  ret = APhysicalObject::serialize();
  ret->SetAttribute("id", this->_id);
  ret->SetAttribute("life", this->_life);
  ret->SetAttribute("rotx", this->_rotx);
  ret->SetAttribute("roty", this->_roty);
  ret->SetAttribute("rotz", this->_rotz);
  ret->SetAttribute("health", this->_health);
  ret->SetAttribute("recoveryTime", this->_recoveryTime);

  ret->SetAttribute("score", this->_score);

  ret->SetAttribute("range", this->_range);
  ret->SetAttribute("speed", this->_speed);
  ret->SetAttribute("isDestructible", this->_isDestructible);
  ret->SetAttribute("canShootBomb", this->_canShootBomb);
  ret->SetAttribute("isRecovering", this->_isRecovering);
  ret->SetAttribute("canPutBomb", this->_canPutBomb);

  ret->SetAttribute("iaghost", this->_isAGhost);
  ret->SetAttribute("hasdeto", this->_hasDetonate);
  ret->SetAttribute("timeGhost", this->_timeGhost);
  ret->SetAttribute("timeInvincible", this->_timeInvincible);
  ret->SetAttribute("timeChangingWeapon", this->_timeChangingWeapon);
  

  ret->SetAttribute("typeBomb", this->_typeBomb);
  ret->SetAttribute("dir", this->_dir);
  for (ObjectType bomb = static_cast<ObjectType>(BOMB + 1); bomb != END; bomb = static_cast<ObjectType>(bomb + 1))
    {
      newr = new TiXmlElement("BOMB");
      newr->SetAttribute("type", bomb);
      newr->SetAttribute("a", this->_stockBomb[bomb][0]);
      newr->SetAttribute("b", this->_stockBomb[bomb][1]);
      newr->SetAttribute("c", this->_stockBomb[bomb][2]);
      ret->LinkEndChild(newr);
    }
  return (ret);
}

void		APlayer::destroyObject()
{

}

