#ifndef		__EMPTY_HH__
#define	  __EMPTY_HH__

#include	"AObject.hh"

class		Empty : public AObject
{
public:
  Empty(int, int, int, int, std::string &, ObjectType);
  Empty(TiXmlAttribute **attr);
  virtual	~Empty();

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
