#ifndef		__IPHYSICALOBJECT_HH__
#define	        __IPHYSICALOBJECT_HH__

#include	"common.hh"
#include	"IGDLObject.hh"
#include	"tinyxml.h"
#include	"enum.hh"

enum		ObjectStatus
{
  ALIVE,
  HURT,
  POISONED,
  DETONATING,
  DEAD
};

class		IGDLObject;

class		IPhysicalObject : public IGDLObject
{
public:
  virtual	~IPhysicalObject(){};
  virtual	int	update() = 0;
  virtual	void	draw() = 0;
  virtual	void	initialize() = 0;

  // #getter et setter

  virtual	void	setPosition(float, float ) = 0;
  virtual	float	getPosX() const = 0;
  virtual	float	getPosY() const = 0;
  virtual	void	setPositionCase(int x, int y) = 0;
  virtual	int	getPosCaseX() const = 0;
  virtual	int	getPosCaseY() const = 0;
  virtual	void	setRotation(int angle) = 0;
  virtual	int	getRotation() const = 0;
  virtual	void	setScale(int scale) = 0;
  virtual	int	getScale() const = 0;
  virtual	void	setMesh(std::string &) = 0;
  virtual	std::string	getMesh() const = 0;
  virtual	void	setType(ObjectType) = 0;
  virtual	ObjectType	getType() const = 0;
  virtual	void	setGlobalType(ObjectType) = 0;
  virtual	ObjectType	getGlobalType() const = 0;
  virtual	void	setStatus(ObjectStatus) = 0;
  virtual	ObjectStatus	getStatus() const = 0;

  //
  virtual	bool	canWalk(float x, float y) = 0;
  virtual bool  canWalkOutTo(float x, float y, int xA, int yA) = 0;

  virtual	bool	isDestructible() const = 0;
  virtual	bool	isMovable() const = 0;
  virtual	bool	isTakable() const = 0;
  virtual	bool	isReachable() const = 0;
  virtual	bool	isExpandable() const = 0;

  virtual	TiXmlElement	*serialize() = 0;
  virtual	void	destroyObject() = 0;
};

#endif
