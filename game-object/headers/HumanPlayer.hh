#ifndef		__HUMANPLAYER_HH__
#define	        __HUMANPLAYER_HH__

#include	"APlayer.hh"
#include	"KeyController.hh"

class		HumanPlayer : public APlayer
{
KeyController	*_keyController;
std::vector<gdl::Keys::Key>	_ctrlP;
gdl::Model	_helmet;
public:
  HumanPlayer(int, int, int, int, std::string &, ObjectType, int, int, int, int);
  HumanPlayer(TiXmlAttribute **attr);
  virtual	~HumanPlayer();

  virtual	int	update();
  virtual	void draw();
  void		assignKeys(std::vector<gdl::Keys::Key> &, gdl::Keys::Key, gdl::Keys::Key, gdl::Keys::Key, gdl::Keys::Key, gdl::Keys::Key, gdl::Keys::Key, gdl::Keys::Key, gdl::Keys::Key);
};

#endif
