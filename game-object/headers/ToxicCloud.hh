#ifndef		__TOXICCLOUD_HH__
#define		__TOXICCLOUD_HH__

#include	"AObject.hh"

class		APlayer;

class		ToxicCloud : public AObject
{
private:
  int         _nbFramesSinceSpawn;
  APlayer	*_owner;
public:
  ToxicCloud(int, int, int, int, std::string &, ObjectType, APlayer *);
  ToxicCloud(TiXmlAttribute **);
  virtual	~ToxicCloud();

  virtual	int	update();
  virtual	void	draw();
  virtual	void	initialize();

  int		getNbFramesSinceSpawn() const;
  void		setNbFramesSinceSpawn(int);
  void		setPlayer(APlayer *);
  // interface IPhysicalObject
  virtual	bool	isDestructible() const;
  virtual	bool	isMovable() const;
  virtual	bool	isTakable() const;
  virtual	bool	isReachable() const;
  virtual	bool	isExpandable() const;
  virtual	void	destroyObject();
  virtual	void	effectObject(APlayer *);
  virtual	TiXmlElement *serialize();
};

#endif
