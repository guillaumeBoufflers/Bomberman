#ifndef		__MAPVALIDITY_HH__
#define		__MAPVALIDITY_HH__

#include	<vector>
#include	<sstream>
#include	<iostream>
#include	<iomanip>
#include	<string>
#include	<fstream>
#include	<algorithm>
#include	"errorWindow.hh"

#define		MAXOBJ	22

namespace 	GameMap
{
  bool		isValidMap(const std::string &file, int nbPlayers);
}

#endif
