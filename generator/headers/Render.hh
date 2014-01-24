#ifndef		__RENDER_H__
#define		__RENDER_H__

#include	<cstdlib>
#include	<iostream>
#include	<vector>
#include	<map>
#include	"Object.hh"

#define		WINDOWSIZE	1000

class		Render
{
private:
  sf::RenderWindow			  *_app;
  std::map<int, Object *>		  _list;
  int					  *_size;
  int					  *_players;
  int					  *_rate;
  ObjectType				   _currentType;
  sf::Image				  *_image[34];
  int					  *_isActive;
public:
  Render(int *size, int *players, int *rate, int *isActive);
  ~Render();
  /****/
  sf::RenderWindow	*getWindow() const;
  int			getActivity() const;
  void			setCurrentType(ObjectType type);
  void			setList(std::map<int, Object *> list);
  std::map<int, Object *>	getList() const;
  void			print();
  void			putNewObj(int x, int y, ObjectType type);
  void			sfmlLaunch();
  static void		*run(void *data);
  void			setImg();
};

#endif
