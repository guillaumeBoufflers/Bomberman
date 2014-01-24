#ifndef		__SAVE_HH__
#define		__SAVE_HH__

#include	<fstream>
#include	<iostream>
#include	<string>
#include	<vector>
#include	<Object.hh>
#include	<sys/types.h>
#include	<dirent.h>
#include	"../../common/headers/enum.hh"
#include	"errorWindow.hh"

std::string		intToString(int a);

class		Save
{
private:
  std::map<int, Object *>		_list;
  std::string				_name;
  int					_size;
  int					_players;
  int					_rate;
  bool					isExisting(std::string &name);
public:
  Save(std::map<int, Object *> list, std::string name, int size, int players, int rate);
  ~Save();
  void		run();
};

#endif
