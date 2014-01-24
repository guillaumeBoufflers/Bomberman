#ifndef		__APLAYER_HH__
#define	        __APLAYER_HH__

#include	<map>
#include	"IPlayer.hh"
#include	"APhysicalObject.hh"
#include	"BasicBomb.hh"
#include  "ABomb.hh"
#include	"SpikeBomb.hh"
#include	"Clock.hh"

class		APlayer : public IPlayer, public APhysicalObject
{
protected:
  float		_rotx;
  float		_roty;
  float		_rotz;
  int		_id;
  int		_life;
  int		_health;
  int		_recoveryTime;
  int		_score;
  float		_range;
  float		_speed;

  bool		_isDestructible;
  bool		_canShootBomb;
  bool		_isRecovering;
  bool		_canPutBomb;
  bool    _isAGhost;
  bool    _hasDetonate;

  int     _timeGhost;
  int     _timeInvincible;

  ObjectType	_typeBomb;

  Dir		_dir;

  std::map<ObjectType, std::vector<int> >	_stockBomb;
  std::list<ABomb *>                      _remoteBomb;
  std::vector<ObjectType>                 _tabBomb;

  int                                     _timeChangingWeapon;

public:
  APlayer(int, int, int, int, std::string &, ObjectType, int, int, int, int);
  APlayer(TiXmlAttribute **);
  virtual	~APlayer();

  virtual	void	initialize();
  virtual	int	update() = 0;
  virtual	void	draw();

  // interface IAPlayer

  // setter et getter

  virtual	float	getRotX() const;
  virtual	void	setRotX(float);
  virtual	float	getRotY() const;
  virtual	void	setRotY(float);
  virtual	float	getRotZ() const;
  virtual	void	setRotZ(float);
  virtual	int	getId() const;
  virtual	void	setId(int);
  virtual	int	getLife() const;
  virtual	void	setLife(int);
  virtual	int	getHealth() const;
  virtual	void	setHealth(int);
  virtual	int	getRecoveryTime() const;
  virtual	void	setRecoveryTime(int);
  virtual	int	getScore() const;
  virtual	void	setScore(int);
  virtual	float	getRange() const;
  virtual	void	setRange(float);
  virtual	float	getSpeed() const;
  virtual	void	setSpeed(float);
  virtual	void	setIsDestructible(bool);
  virtual bool  isAGhost() const;
  virtual void  setIsAGhost(bool);
  virtual bool  hasDetonateBomb() const;
  virtual void  setDetonateBomb(bool);
  virtual	bool	getCanShootBomb() const;
  virtual	void	setCanShootBomb(bool);
  virtual	bool	getIsRecovering() const;
  virtual	void	setIsRecovering(bool);
  virtual	bool	getCanPutBomb() const;
  virtual	void	setCanPutBomb(bool);
  virtual	ObjectType getTypeBomb() const;
  virtual	void	setTypeBomb(ObjectType);
  virtual	Dir	getDir() const;
  virtual	void	setDir(Dir);

  // interface IPlayer
  virtual	void	setDamage(int);
  virtual	std::map<ObjectType, std::vector<int> >	getStock() const;

  virtual void  checkStates();
  virtual	void	goLeft();
  virtual	void	goRight();
  virtual	void	goUp();
  virtual	void	goDown();
  virtual	void	doNothing();
  virtual	void	selectBomb(const std::string &);
  virtual	void	putBomb();
  virtual	void	shootBomb();
  virtual	void	addToStock(ObjectType, int, int, int);
  virtual	bool	checkStock();
  virtual	void	whatInCase();
  virtual	void	reloadStock(ObjectType);
  virtual	void	checkDeath();
  virtual void  detonateRemote();
  virtual std::vector<int> getNumberBomb() const;

  // interface IPhysicalObject
  virtual	bool	isDestructible() const;
  virtual	bool	isMovable() const;
  virtual	bool	isTakable() const;
  virtual	bool	isReachable() const;
  virtual	bool	isExpandable() const;
  virtual	TiXmlElement *serialize();
private:

  virtual	void	destroyObject();

};

#endif
