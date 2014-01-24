#ifndef		__IACONTROLLER_HH__
#define		__IACONTROLLER_HH__

#include <iterator>
#include <cmath>
#include <iostream>
#include <fstream>
#include "IAPathFinderNode.hh"
#include "IAPathfinder.hh"
#include "APlayer.hh"

enum IAActions {
	BOT_GOTOP,
	BOT_GORIGHT,
	BOT_GOBOTTOM,
	BOT_GOLEFT,
	BOT_POSEBOMB,
	BOT_DONOTHING
};

class		IAController
{
private:
	int frameSinceBirth;
	int frameSinceTracking;
	int difficulty;
	bool trackingPlayer;
	static std::list<std::vector<std::string> > iaScript;
	static std::map<std::string, ObjectType> objDef;
	static std::map<std::string, bool (IAController::*)(int, int)> compFuncs;
	static std::map<std::string, bool (IAController::*)(int, int)> boolVerifs;
	static std::map<std::string, IAActions> retDec;
	static std::map<std::string, int> validW;
	IAPathFinderNode *path;
	void parseIALine(std::string &line);
	void parseIAFile(const char *filename);
	bool compEqual(int a, int b);
	bool compSup(int a, int b);
	bool compLess(int a, int b);
	bool isValidWord(std::string &w, int y);
	bool isPathInvalid();
	std::string &trim(std::string &word);
	int findNearest(ObjectType type, int x, int y, int *rx, int *ry, APlayer *player, int range);
	void verifIA();
	bool isIndanger(int x, int y);
	bool enemyInRange(int x, int y);
	IAActions goToNestNode(int x, int y, APlayer *player);
	void findSafeSpot(int *xr, int *yr, int xp, int yp);

public:
  IAController(int difficulty);
  ~IAController();
  IAActions getDecision(int x, int y, APlayer *player);
  IAActions execIa(int x, int y, APlayer *player);

};

#endif
