#ifndef		__BUILD_H__
#define		__BUILD_H__

#include	<iostream>
#include	<vector>
#include	<string>
#include	<map>
#include	<unistd.h>
#include	<list>
#include	<map>
#include	"Object.hh"
#include	"Except.hh"

std::string		intToString(int a);

#define		WINDOWSIZE	1000

class		Build
{
private:
  std::map<int, Object *>		_list;
  int		*_size;
  int		*_players;
  int		*_rate;
  int		*_subWall;
  int		*_subUWall;
  int		*_subBonus;
  int   	_nbObj;
  double	_nbUWall;
  double	_nbWall;
  double	_nbBonus;
  std::map<int, ObjectType>		_bonusList;
  std::list<Except *>			_security;
  void			getValidPos(int *pos);
  void			pushLine(int rate, int y, int yMap, int *pos);
  void			getValidPos(int *x, int *y);
  void			addOnMap(int pos, ObjectType type);
  void			handleDistrib(int it, ObjectType type);
  void			handleDistrib(int it);
  ObjectType		getRandomBonus();
  void			pushExcept(int x, int y);
  bool		        isAnException(int x, int y) const;
public:
  Build(int *size, int *players, int *rate, int *subWall, int *subUWall, int *subBonus);
  ~Build();
  std::map<int, Object *>	getList() const;
  void		init();
  void		random();
  void		setPlayer();
};

#endif
