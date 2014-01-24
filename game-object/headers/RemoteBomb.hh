#ifndef		__REMOTEBOMB_HH__
#define	        __REMOTEBOMB_HH__

#include	"ABomb.hh"

class		RemoteBomb : public ABomb
{
public:
  RemoteBomb(int, int, int, int, std::string &, int puissance, int, APlayer *);
  RemoteBomb(TiXmlAttribute **);
  virtual	int	update();
  virtual	void	draw();
  virtual	void	initialize();

  virtual	~RemoteBomb();
  virtual	void	spreadExplosion(int range);
};

#endif
