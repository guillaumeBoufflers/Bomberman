#ifndef		__NUKEBOMB_HH__
#define	        __NUKEBOMB_HH__

#include	"ABomb.hh"

class		NukeBomb : public ABomb
{
public:
  NukeBomb(int, int, int, int, std::string &, int puissance, int, APlayer *);
  NukeBomb(TiXmlAttribute **);
  virtual	int	update();
  virtual	void	draw();
  virtual	void	initialize();

  virtual	~NukeBomb();
  virtual	void	spreadExplosion(int range);
};

#endif
