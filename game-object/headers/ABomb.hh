#ifndef		__ABOMB_HH__
#define	        __ABOMB_HH__

#include	"AObject.hh"
#include	"Explosion.hh"

class		ABomb : public AObject
{
protected:
  int         _timeLeftBeforeExplosion;
  int         _puissance;
  int	      _dispo;
  APlayer	*_owner;
public:
  ABomb(int, int, int, int, std::string &, ObjectType, int, int, APlayer *);
  ABomb(TiXmlAttribute **);
  virtual	~ABomb();

  virtual	int	update() = 0;
  virtual	void	draw() = 0;
  virtual	void	initialize() = 0;

  // #getter et setter
  int		getTimeBeforeExplosion() const;
  void		setTimeBeforeExplosion(int);
  int		getPuissance() const;
  void		setPuissance(int);
  int		getDispo() const;
  void		setDispo(int);
  void		setPlayer(APlayer *);
  // interface IPhysicalObject
  virtual	bool	isDestructible() const;
  virtual	bool	isMovable() const;
  virtual	bool	isTakable() const;
  virtual	bool	isReachable() const;
  virtual	bool	isExpandable() const;
  virtual	void	effectObject(APlayer *);
  // interface IObject
  virtual	void	destroyObject();

  //methode pure
  virtual	void	explode();
  virtual	void	spreadExplosion(int range) = 0;

  virtual	void	reloadPlayer();
  virtual	TiXmlElement *serialize();
};

#endif
