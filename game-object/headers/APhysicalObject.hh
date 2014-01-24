#ifndef		__APHYSICALOBJECT_HH__
#define	        __APHYSICALOBJECT_HH__

#include	"IPhysicalObject.hh"

class		APhysicalObject : public IPhysicalObject
{
protected:
  float _x;
  float _y;
  int		_scale;
  int		_angle;
  std::string	_mesh;

  ObjectType	_type;
  ObjectType	_globalType;
  ObjectStatus	_status;
  gdl::Model	_model;
public:
  virtual	~APhysicalObject();
  APhysicalObject(int, int, int, int, std::string &, ObjectType, ObjectType);
  APhysicalObject(TiXmlAttribute **);
  virtual	void	initialize() = 0;
  virtual	int	update() = 0;
  virtual	void	draw() = 0;

  // #getter et setter

  virtual	void	setPosition(float x, float y);
  virtual	float	getPosX() const;
  virtual	float	getPosY() const;
  virtual	void	setPositionCase(int x, int y);
  virtual	int	getPosCaseX() const;
  virtual	int	getPosCaseY() const;
  virtual	void	setRotation(int angle);
  virtual	int	getRotation() const;
  virtual	void	setScale(int scale);
  virtual	int	getScale() const;
  virtual	void	setMesh(std::string &);
  virtual	std::string	getMesh() const;
  virtual	void	 setType(ObjectType);
  virtual	ObjectType	getType() const;
  virtual	void	setGlobalType(ObjectType) ;
  virtual	ObjectType	getGlobalType() const;
  virtual	void	setStatus(ObjectStatus);
  virtual	ObjectStatus	getStatus() const;

  //
  virtual	bool	canWalk(float, float);
  virtual bool  canWalkOutTo(float x, float y, int xA, int yA);


  virtual	bool	isDestructible() const = 0;
  virtual	bool	isMovable() const = 0;
  virtual	bool	isTakable() const = 0;
  virtual	bool	isReachable() const = 0;
  virtual	bool	isExpandable() const = 0;

  virtual	TiXmlElement *serialize();
  virtual	void	destroyObject() = 0;
private:
};

#endif
