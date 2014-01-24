#ifndef		__IAPLAYER_HH__
#define	        __IAPLAYER_HH__

#include	"IAController.hh"
#include	"APlayer.hh"

// class		IAController;
// class		APlayer;

class		IAPlayer : public APlayer
{
private:
	IAController _iacontroller;
	IAActions _act;
public:
  IAPlayer(int, int, int, int, std::string &, ObjectType, int, int, int, int);
  IAPlayer(TiXmlAttribute **attr);
  void  equipBestBomb();
  virtual	~IAPlayer();

  virtual	int	update();
};

#endif
