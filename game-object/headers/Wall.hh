#ifndef		__WALL_HH__
#define	        __WALL_HH__

#include	"AObject.hh"

class		Wall : public AObject
{
public:
  Wall(int, int, int, int, std::string &, ObjectType);
  Wall(TiXmlAttribute **attr);
  virtual	~Wall();

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
  virtual	void	effectObject(APlayer *);
};

#endif
