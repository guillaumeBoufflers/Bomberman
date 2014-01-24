#ifndef		__BASICBOMB_HH__
#define	        __BASICBOMB_HH__

#include	"ABomb.hh"

class		BasicBomb : public ABomb
{
public:
  BasicBomb(int, int, int, int, std::string &, int puissance, int, APlayer *);
  BasicBomb(TiXmlAttribute **);
  virtual	int	update();
  virtual	void	draw();
  virtual	void	initialize();

  virtual	~BasicBomb();
  virtual	void	spreadExplosion(int range);
};

#endif
