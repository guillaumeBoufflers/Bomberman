#ifndef		__ABONUS_HH__
#define	        __ABONUS_HH__

#include	"AObject.hh"

class		ABonus : public AObject
{
public:
  ABonus(int, int, int, int, std::string &, ObjectType);
  ABonus(TiXmlAttribute **attr);
  virtual	~ABonus();

  virtual	int	update();
  virtual	void	draw();
  virtual	void	initialize();

  // interface IPhysicalObject
  virtual	bool	isDestructible() const;
  virtual	bool	isMovable() const;
  virtual	bool	isTakable() const;
  virtual	bool	isReachable() const;
  virtual	bool	isExpandable() const;
  virtual	void	destroyObject();
  virtual	void	effectObject(APlayer *) = 0;
  virtual	TiXmlElement *serialize();
protected:
  bool		_destructible;
  int		_timeBeforeDestructible;
};

#endif
