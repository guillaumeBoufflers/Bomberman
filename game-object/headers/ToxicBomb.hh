#ifndef		__TOXICBOMB_H__
#define	        __TOXICBOMB_H__

#include	"ABomb.hh"

class		ToxicBomb : public ABomb
{
public:
  ToxicBomb(int, int, int, int, std::string &, int puissance, int, APlayer *);
  ToxicBomb(TiXmlAttribute **);
  virtual	int	update();
  virtual	void	draw();
  virtual	void	initialize();

  virtual	~ToxicBomb();
  virtual	void	spreadExplosion(int range);
};

#endif
