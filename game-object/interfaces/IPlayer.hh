#ifndef		__IPLAYER_HH__
#define	        __IPLAYER_HH__

#include	<string>
#include	"IPhysicalObject.hh"

enum Dir
    {
      UP,
      DOWN,
      LEFT,
      RIGHT
    };

class		IPlayer
{
public:
  virtual	~IPlayer(){};

  //setter et getter

  virtual	float	getRotX() const = 0;
  virtual	void	setRotX(float) = 0;
  virtual	float	getRotY() const = 0;
  virtual	void	setRotY(float) = 0;
  virtual	float	getRotZ() const = 0;
  virtual	void	setRotZ(float) = 0;
  virtual	int	getId() const = 0;
  virtual	void	setId(int) = 0;
  virtual	int	getLife() const = 0;
  virtual	void	setLife(int) = 0;
  virtual	int	getHealth() const = 0;
  virtual	void	setHealth(int) = 0;
  virtual	int	getRecoveryTime() const = 0;
  virtual	void	setRecoveryTime(int) = 0;
  virtual	int	getScore() const = 0;
  virtual	void	setScore(int) = 0;
  virtual	float	getSpeed() const = 0;
  virtual	void	setSpeed(float) = 0;
  virtual	float	getRange() const = 0;
  virtual	void	setRange(float) = 0;
  virtual	void	setIsDestructible(bool) = 0;
  virtual bool  isAGhost() const = 0;
  virtual void  setIsAGhost(bool) = 0;
  virtual bool  hasDetonateBomb() const = 0;
  virtual void  setDetonateBomb(bool) = 0;
  virtual	bool	getCanShootBomb() const = 0;
  virtual	void	setCanShootBomb(bool) = 0;
  virtual	bool	getIsRecovering() const = 0;
  virtual	void	setIsRecovering(bool) = 0;
  virtual	bool	getCanPutBomb() const = 0;
  virtual	void	setCanPutBomb(bool) = 0;
  virtual	ObjectType getTypeBomb() const = 0;
  virtual	void	setTypeBomb(ObjectType) = 0;
  virtual	Dir	getDir() const = 0;
  virtual	void	setDir(Dir) = 0;

  virtual	void	goLeft() = 0;
  virtual	void	goRight() = 0;
  virtual	void	goUp() = 0;
  virtual	void	goDown() = 0;
  virtual	void	doNothing() = 0;
  virtual	void	selectBomb(const std::string &) = 0;
  virtual	void	putBomb() = 0;
  virtual	void	shootBomb() = 0;
  virtual void  checkStates() = 0;
  virtual	void	setDamage(int) = 0;
  virtual	std::map<ObjectType, std::vector<int> >	getStock() const = 0;
  virtual	void	addToStock(ObjectType, int, int, int) = 0;
  virtual	bool	checkStock() = 0;
  virtual	void	whatInCase() = 0;
  virtual	void	reloadStock(ObjectType) = 0;
  virtual void  checkDeath() = 0;
  virtual void  detonateRemote() = 0;
  virtual std::vector<int> getNumberBomb() const = 0;
};

#endif
