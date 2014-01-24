#ifndef		__ROCKET_HH__
#define	        __ROCKET_HH__

#include	"ABomb.hh"
#include	"IPlayer.hh"

class		Rocket : public ABomb
{
	Dir		_dir;
	int 	_xBeg;
  	int   	_yBeg;
public:
  Rocket(int, int, int, int, std::string &, int puissance, int, APlayer *);
  Rocket(TiXmlAttribute **);
  virtual	int	update();
  virtual	void	draw();
  virtual	void	initialize();
  virtual	bool	isReachable()const;
  
  int		moveUp();
  int		moveDown();
  int		moveRight();
  int		moveLeft();

  int 		getXBeg() const;
  int 		getYBeg() const;

  virtual TiXmlElement	*serialize();
  virtual	~Rocket();
  virtual	void	spreadExplosion(int range);
};

#endif
