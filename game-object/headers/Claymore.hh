#ifndef		__CLAYMORE_HH__
#define	        __CLAYMORE_HH__

#include	"ABomb.hh"

class		Claymore : public ABomb
{
public:
  Claymore(int, int, int, int, std::string &, int puissance, int, APlayer *);
  Claymore(TiXmlAttribute **);
  virtual	int	update();
  virtual	void	draw();
  virtual	void	initialize();
  virtual	bool	isReachable() const;

  virtual	~Claymore();
  virtual	void	spreadExplosion(int range);
};

#endif
