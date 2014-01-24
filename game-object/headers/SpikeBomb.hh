#ifndef		__SPIKEBOMB_HH__
#define	        __SPIKEBOMB_HH__

#include	"ABomb.hh"

class		SpikeBomb : public ABomb
{
public:
  SpikeBomb(int, int, int, int, std::string &, int puissance, int, APlayer *);
  SpikeBomb(TiXmlAttribute **);
  virtual	int	update();
  virtual	void	draw();
  virtual	void	initialize();

  virtual	~SpikeBomb();
  virtual	void	spreadExplosion(int range);
};

#endif
