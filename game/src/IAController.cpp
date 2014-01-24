#include	"IAController.hh"
#include	"GameScene.hh"

std::list<std::vector<std::string> > IAController::iaScript;
std::map<std::string, ObjectType> IAController::objDef;
std::map<std::string, bool (IAController::*)(int, int)> IAController::compFuncs;
std::map<std::string, bool (IAController::*)(int, int)> IAController::boolVerifs;
std::map<std::string, IAActions> IAController::retDec;
std::map<std::string, int> IAController::validW;

IAController::IAController(int _difficulty) : frameSinceBirth(0), frameSinceTracking(0), trackingPlayer(0)
{
	const char *IAFiles[3] = { "ia/IAMineur.ia", "ia/IABase.ia", "ia/IAAggro.ia" };
	path = NULL;
	difficulty = _difficulty;
	if (!(difficulty >= 0 && difficulty < 3))
		difficulty = 1;
	if (objDef.empty())
	{
		objDef["BOMB_DIST"] = BOMB;
		objDef["BONUS_DIST"] = BONUS;
		objDef["ENEMY_DIST"] = PLAYER;
		objDef["WEAKWALL_DIST"] = DESTRUCTIBLEWALL;
	}
	if (compFuncs.empty())
	{
		compFuncs["=="] = &IAController::compEqual;
		compFuncs["<"] = &IAController::compLess;
	}
	if (iaScript.empty())
	{
		parseIAFile(IAFiles[_difficulty - 2]);
	}
	if (boolVerifs.empty())
	{
		boolVerifs["IS_INDANGER"] = &IAController::isIndanger;
	}
	if (retDec.empty())
	{
		retDec["POSE_BOMB"] = BOT_POSEBOMB;
	}
}

IAController::~IAController()
{

}

bool IAController::isIndanger(int xP, int yP)
{
	for (int x = -5 ; x <= 5 ; ++x)
		if (GameScene::isValidPos(x + xP, yP) && (*(GameScene::_map[yP][xP + x].back())).getGlobalType() == BOMB)
			return (true);
	for (int y = -5 ; y <= 5 ; ++y)
		if (GameScene::isValidPos(xP, y + yP) && (*(GameScene::_map[y + yP][xP].back())).getGlobalType() == BOMB)
			return (true);

	for (int x = -5 ; x <= 5 ; ++x)
		for (int y = -5 ; y <= 5 ; ++y)
			if (GameScene::isValidPos(x + xP, y + yP) && ((*(GameScene::_map[y + yP][x + xP].back())).getType() == NUKEBOMB || (*(GameScene::_map[y + yP][x + xP].back())).getType() == TOXICBOMB))
			{
				if (sqrt((x * x) + (y * y)) <= 5)
					return (true);
			}
	return (false);
}

std::string &IAController::trim(std::string &word)
{
	size_t found;

	if ((found = word.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ_><=0123456789\n")) != std::string::npos)
		word.erase(0, found);
	return (word);
}

int strToInt(std::string const &str) {
	int i(0);
	std::istringstream ss(str);

	ss >> i;
	return (i);
}

void IAController::findSafeSpot(int *xr, int *yr, int xP, int yP)
{
	IAPathFinderNode *t;

	for (int r = 0 ; r <= 7 ; ++r)
	{
		for (int y = -r ; y <= r ; ++y)
		{
			for (int x = -r ; x <= r ; ++x)
			{
				if ((x == r || x == -r || y == r || y == -r) && GameScene::isValidPos(x + xP, y + yP) 
					&& GameScene::_map[y + yP][x + xP].front()->isReachable() 
					&& GameScene::_map[y + yP][x + xP].back()->isReachable() 
					&& !isIndanger(x + xP, y + yP))
				{
					t = findPath(xP, yP, x + xP, y + yP);
					if (t)
					{
						*xr = x + xP;
						*yr = y + yP;
						path = t;
						return ;
					}
				}
			}
		}
	}
}

IAActions IAController::execIa(int xP, int yP, APlayer *player)
{
	int x;
	int y;
	IAPathFinderNode *t;

	for (std::list<std::vector<std::string> >::iterator it = iaScript.begin(); it != iaScript.end(); ++it)
	{
		for (std::vector<std::string>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2)
		{
			if (*it2 == "IF")
			{
				if ((*it).size() >= 4)
				{
					if ((this->*compFuncs[*(it2 + 2)])(findNearest(objDef[*(it2 + 1)], xP, yP, &x, &y, player, strToInt(*(it2 + 3))), strToInt(*(it2 + 3))))
					{
						++it; it2 = (*it).begin();
						if (*(it2) == "GO")
						{
							t = findPath(xP, yP, x, y);
							if (t)
								path = t;
							return (BOT_DONOTHING);
						}
						else
						{
							return (retDec[*it2]);
						}
					}
					else
						{ ++it; it2 = (*it).begin(); }
				}
				else if ((*it).size() >= 2)
				{
					if (boolVerifs[*(it2 + 1)]) {
					if ((this->*boolVerifs[*(it2 + 1)])(xP, yP))
					{
						++it; it2 = (*it).begin();
						if (*(it2) == "GO_AWAY")
						{
							findSafeSpot(&x, &y, xP, yP);
							return (BOT_DONOTHING);
						}
						else
						{
							std::cout << *it2 << std::endl;
							return (retDec[*it2]);
						}
						return (BOT_DONOTHING);
					}
					else
					{ ++it; it2 = (*it).begin(); }
					}
				}
			}
		}
	}
	return (BOT_DONOTHING);
}

void IAController::verifIA()
{
	for (std::list<std::vector<std::string> >::iterator it = iaScript.begin(); it != iaScript.end(); ++it)
	{
		for (std::vector<std::string>::iterator it2 = (*it).begin(); it2 != (*it).end(); )
		{
			if (*it2 == "IF") {
				++it;
				it2 = (*it).begin();
				if (it == iaScript.end())
				{
					std::cerr << "Error : if with no body" << std::endl;
					exit(0);
				}
			}
			else
				++it2;
		}
	}
}

bool isInCase(ObjectType type, int x, int y)
{
	for (std::list<IPhysicalObject *>::iterator it = GameScene::_map[y][x].begin() ; it != GameScene::_map[y][x].end(); ++it)
		if ((*it)->getGlobalType() == type)
			return (true);
	return (false);
}

int IAController::findNearest(ObjectType type, int x, int y, int *rx, int *ry, APlayer *player, int range)
{
	if (type != PLAYER)
		for (int r = 0 ; r <= range ; ++r)
		{
			for (int yy = -r ; yy <= r ; ++yy)
			{
				for (int xx = -r ; xx <= r ; ++xx)
				{
					if (xx == r || xx == -r || yy == r || yy == -r)
						if (GameScene::isValidPos(x + xx, y + yy) && isInCase(type, x + xx, y + yy))
						{
							if (findPath(x, y, x + xx, y + yy) != NULL) {
								*rx = x + xx;
								*ry = y + yy;
								if (abs(xx) == 1 && abs(yy) == 1)
									return (2);
								return (sqrt((xx * xx) + (yy * yy)));
							}
						}
				}
			}
		}
	else {
		int bestDist = -1;
		int res;

		for (std::vector<APlayer*>::iterator it = GameScene::_alivePlayers.begin() ; it != GameScene::_alivePlayers.end() ; ++it)
		{
			if (((res = sqrt(((x - (*it)->getPosCaseX()) * (x - (*it)->getPosCaseX())) + ((y - (*it)->getPosCaseY()) * (y - (*it)->getPosCaseY())))) < bestDist || bestDist == -1) && player != *it)
			{
				if (res <= range && findPath(x, y, (*it)->getPosCaseX(), (*it)->getPosCaseY()) != NULL) {
					bestDist = res;
					*rx = (*it)->getPosCaseX();
					*ry = (*it)->getPosCaseY();
				}
			}
		}
		return (bestDist);
	}
	return (-1);
}

bool IAController::isValidWord(std::string &w, int y)
{
	if (y == 4)
		return (true);

	validW["IF"] = 1;
	validW["GO"] = 1;
	validW["POSE_BOMB"] = 1;
	validW["GO_AWAY"] = 1;
	validW["IS_INDANGER"] = 2;
	validW["BOMB_DIST"] = 2;
	validW["BONUS_DIST"] = 2;
	validW["ENEMY_DIST"] = 2;
	validW["WEAKWALL_DIST"] = 2;
	validW["=="] = 3;
	validW["<"] = 3;

	if (validW[w] == y)
		return (true);
	return (false);
}

void IAController::parseIALine(std::string &line)
{
	size_t found;
	int y = 0;
	std::vector<std::string> *vec;

	if ((found = line.find("//")) != std::string::npos)
	{
		line.erase(found, line.size());
	}
	if ((found = line.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ_ \n\t><=0123456789")) != std::string::npos)
	{
		std::cerr << "Error : Invalid Char" << std::endl;
		return ;
	}
	if (line.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ_><=0123456789") == std::string::npos)
		return ;
	vec = new std::vector<std::string>;
	while ((found = trim(line).find_first_of(" \n\t")) != std::string::npos && line.size())
	{
		std::string w = line.substr(0, found);
		++y;
		if (!isValidWord(w, y)) {
			std::cout << "Error : " << w << " is Invalid" << std::endl;
			exit(0);
		}
		vec->push_back(line.substr(0, found));
		line.erase(0, found + 1);
	}
	iaScript.push_back(*(vec));
}

void IAController::parseIAFile(const char *filename)
{
	std::string buffer;
	std::ifstream file;
	file.open(filename, std::ios::in);
	if (!file.is_open())
	{
		std::cerr << "Fichier IA non trouvé" << std::endl;
		exit(0);
	}
	while (!file.fail() && file.good() && !file.eof())
	{
		getline(file, buffer);
		buffer += "\n";
		parseIALine(buffer);
	}
	file.close();
	verifIA();
}

IAActions IAController::goToNestNode(int x, int y, APlayer *player)
{
	int dx;
	int dy;

	if (!path)
		return (BOT_DONOTHING);
	dx = path->x - x;
	dy = path->y - y;
	if (dx > 0)
		return (BOT_GORIGHT);
	if (dx < 0)
		return (BOT_GOLEFT);
	if (dy > 0)
		return (BOT_GOBOTTOM);
	if (dy < 0)
		return (BOT_GOTOP);

	if (player->getPosX() - (x * CASE_SIZE) <= CASE_SIZE / 3) {
		return (BOT_GORIGHT); }
	if (player->getPosX() - (x * CASE_SIZE) >= CASE_SIZE - (CASE_SIZE / 3)) {
		return (BOT_GOLEFT); }
	if (player->getPosY() - (y * CASE_SIZE) <= CASE_SIZE / 3) {
		return (BOT_GOBOTTOM); }
	if (player->getPosY() - (y * CASE_SIZE) >= CASE_SIZE - (CASE_SIZE / 3)) {
		return (BOT_GOTOP); }

	return (BOT_DONOTHING);
}

bool IAController::isPathInvalid()
{
	if (!path)
		return (true);
	if (!(*(GameScene::_map[path->y][path->x].front())).isReachable() || !(*(GameScene::_map[path->y][path->x].back())).isReachable())
		return (true);
	if ((*(GameScene::_map[path->y][path->x].front())).getGlobalType() == EXPLOSION || (*(GameScene::_map[path->y][path->x].back())).getGlobalType() == EXPLOSION || (*(GameScene::_map[path->y][path->x].back())).getType() == CLAYMORE)
		return (true);
	return (false);
}

IAActions IAController::getDecision(int x, int y, APlayer *player)
{
	IAActions act = BOT_DONOTHING;

	++frameSinceBirth;
	if (path && path->x == x && path->y == y && ((act = goToNestNode(x, y, player)) == BOT_DONOTHING))
		path = NULL;
	else if (isPathInvalid())
		path = NULL;
	if (path == NULL && frameSinceBirth % 10 == 0)
	{
		if ((act = execIa(x, y, player)) != BOT_DONOTHING)
			return (act);
	}
	if ((act = goToNestNode(x, y, player)) != BOT_DONOTHING)
		return (act);
	return (act);
}

bool IAController::compEqual(int a, int b)
{
	if (a == -1)
		return (false);
	return (a == b);
}

bool IAController::compSup(int a, int b)
{
	if (a == -1)
		return (false);
	return (a > b);
}

bool IAController::compLess(int a, int b)
{
	if (a == -1)
		return (false);
	return (a < b);
}