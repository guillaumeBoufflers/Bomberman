#ifndef		__AOBJECT_HH__
#define	        __AOBJECT_HH__

#include	"IObject.hh"
#include	"APhysicalObject.hh"

class		AObject : public IObject, public APhysicalObject
{
public:
  AObject(int, int, int, int, std::string &, ObjectType, ObjectType);
  AObject(TiXmlAttribute **);
  virtual	~AObject();

  virtual	int	update() = 0;
  virtual	void	draw() = 0;
  virtual	void	initialize() = 0;
  // interface IPhysicalObject
  virtual	bool	isDestructible() const = 0;
  virtual	bool	isMovable() const = 0;
  virtual	bool	isTakable() const = 0;
  virtual	bool	isReachable() const = 0;
  virtual	bool	isExpandable() const = 0;
  virtual	void	effectObject(APlayer *) = 0;
  //interface IPlayer
  virtual	void	destroyObject() = 0;
  virtual	TiXmlElement *serialize();

};

#endif
