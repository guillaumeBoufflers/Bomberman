#include "IAPathFinderNode.hh"
#include "IAPathfinder.hh"
#include "GameScene.hh"

bool isNeighbor(IAPathFinderNode &one, IAPathFinderNode &two)
{
	if (abs(one.x - two.x) == 1 && abs(one.y - two.y) == 0)
		return (true);
	if (abs(one.x - two.x) == 0 && abs(one.y - two.y) == 1)
		return (true);
	return (false);
}

bool isDangerCase(int xP, int yP)
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

int heuristicScore(IAPathFinderNode &start, IAPathFinderNode &end)
{
	int s = abs(end.x - start.x) + abs(end.y - start.y);
	s += 80 * isDangerCase(end.x, end.y);
	return (s);
}

// IAPathFinderNode *findPath(int startx, int starty, int endx, int endy)
// {
// 	int tx, ty;
// 	int dx = 0;
// 	int dy = 0;

// 	if (startx < endx)
// 		dx = 1;
// 	else if (startx > endx)
// 		dx = -1;
// 	if (starty < endy)
// 		dy = 1;
// 	else if (starty > endy)
// 		dy = -1;
// 	tx = startx + dx;
// 	ty = starty;

// 	while (GameScene::isValidPos(tx, ty) 
// 			&& GameScene::_map[ty][tx].front()->isReachable() 
// 			&& GameScene::_map[ty][tx].back()->isReachable() 
// 			&& GameScene::_map[ty][tx].back()->getType() != CLAYMORE
// 			&& GameScene::_map[ty][tx].back()->getGlobalType() != EXPLOSION
// 			&& tx != endx)
// 		tx += dx;
// 	ty += dy;
// 	while (GameScene::isValidPos(tx, ty) 
// 			&& GameScene::_map[ty][tx].front()->isReachable() 
// 			&& GameScene::_map[ty][tx].back()->isReachable() 
// 			&& GameScene::_map[ty][tx].back()->getType() != CLAYMORE
// 			&& GameScene::_map[ty][tx].back()->getGlobalType() != EXPLOSION
// 			&& ty != endy)
// 		ty += dy;
// 	if (tx == endx && ty == endy)
// 	{
// 		if (dx)
// 			return (new IAPathFinderNode(startx + dx, starty, 0, 0));
// 		else
// 			return (new IAPathFinderNode(startx, starty + dy, 0, 0));
// 	}


// 	tx = startx + dx;
// 	ty = starty;
// 	ty += dy;
// 	while (GameScene::isValidPos(tx, ty) 
// 			&& GameScene::_map[ty][tx].front()->isReachable() 
// 			&& GameScene::_map[ty][tx].back()->isReachable() 
// 			&& GameScene::_map[ty][tx].back()->getType() != CLAYMORE
// 			&& GameScene::_map[ty][tx].back()->getGlobalType() != EXPLOSION
// 			&& ty != endy)
// 		ty += dy;
// 	while (GameScene::isValidPos(tx, ty) 
// 			&& GameScene::_map[ty][tx].front()->isReachable() 
// 			&& GameScene::_map[ty][tx].back()->isReachable() 
// 			&& GameScene::_map[ty][tx].back()->getType() != CLAYMORE
// 			&& GameScene::_map[ty][tx].back()->getGlobalType() != EXPLOSION
// 			&& tx != endx)
// 		tx += dx;
// 	if (tx == endx && ty == endy)
// 	{
// 		if (dx)
// 			return (new IAPathFinderNode(startx + dx, starty, 0, 0));
// 		else
// 			return (new IAPathFinderNode(startx, starty + dy, 0, 0));
// 	}

// 	return (NULL);
// }

IAPathFinderNode *findPath(int startx, int starty, int endx, int endy)
{
	std::vector<IAPathFinderNode> alreadyEval;
	std::vector<IAPathFinderNode> toCheck;
	std::vector<IAPathFinderNode> cameFrom;
	std::vector<IAPathFinderNode> path;
	IAPathFinderNode removed;
	IAPathFinderNode tentative;
	IAPathFinderNode endPos(endx, endy, 0, 0);
	int lowestFscore;
	int chosenNode = 0;
	bool proceed;
	bool goNextTo = false;

	if (!GameScene::_map[endy][endx].front()->isReachable() || !GameScene::_map[endy][endx].back()->isReachable())
		goNextTo = true;
	toCheck.push_back(*(new IAPathFinderNode(startx, starty, 0, heuristicScore(*(new IAPathFinderNode(startx, starty, 0, 0)), endPos))));
	while (!toCheck.empty())
	{
		//get lowest heuristic score node
		lowestFscore = -1;
		for (unsigned int i = 0 ; i < toCheck.size() ; ++i)
		{
			if ((toCheck[i].fscore <= lowestFscore) || lowestFscore == -1)
			{
				lowestFscore = toCheck[i].fscore;
				chosenNode = i;
			}
		}
		removed = toCheck[chosenNode];
		//end
		if ((removed.x == endx && removed.y == endy) || (goNextTo && isNeighbor(removed, endPos)))
		{
			path.push_back(removed);
			for (int i = cameFrom.size() - 1 ; i >= 0 ; i--)
			{
				if (isNeighbor(cameFrom[i], (path)[0]) && cameFrom[i].gscore == (path)[0].gscore - 1)
					path.insert(path.begin(), cameFrom[i]);
			}
			if (isDangerCase((path)[0].x, (path)[0].y) && !isDangerCase(startx, starty))
				return (NULL);
			return (new IAPathFinderNode(path[0].x, path[0].y, 0, 0));
		}
		alreadyEval.push_back(removed);
		toCheck.erase(toCheck.begin() + chosenNode);
		//add neighbors
		for (int y = -1 ; y <= 1 ; ++y)
			for (int x = -1 ; x <= 1 ; ++x)
				if (((abs(x) == 1) ^ (abs(y) == 1))
					&& GameScene::isValidPos(x + removed.x, y + removed.y) 
					&& GameScene::_map[y + removed.y][x + removed.x].front()->isReachable() 
					&& GameScene::_map[y + removed.y][x + removed.x].back()->isReachable() 
					&& GameScene::_map[y + removed.y][x + removed.x].back()->getType() != CLAYMORE
					&& GameScene::_map[y + removed.y][x + removed.x].back()->getGlobalType() != EXPLOSION
/*					&& GameScene::_map[y + removed.y][x + removed.x].front()->getGlobalType() != EXPLOSION*/)
					{
						tentative = IAPathFinderNode((x + removed.x), (y + removed.y),
							(removed.gscore + 1),
							0);
						proceed = true;
						for (unsigned int i = 0 ; i < alreadyEval.size() && proceed ; ++i)
						{
							if (tentative.x == alreadyEval[i].x
								&& tentative.y == alreadyEval[i].y
								&& tentative.gscore >= alreadyEval[i].gscore)
								proceed = false;
						}
						if (proceed)
						{
							proceed = true;
							for (unsigned int i = 0 ; i < toCheck.size() && proceed ; ++i)
							{
								if (tentative.x == toCheck[i].x
									&& tentative.y == toCheck[i].y
									&& tentative.gscore >= toCheck[i].gscore)
									proceed = false;
							}
							if (proceed)
							{
								tentative.fscore = (tentative.gscore + heuristicScore(tentative, endPos));
								toCheck.push_back(tentative);
								cameFrom.push_back(tentative);
							}
						}
					}
				}
				return (NULL);
			}

void affPath(std::vector<IAPathFinderNode> *path)
{
	for (unsigned int i = 0 ; i < path->size() ; ++i)
	{
		std::cout << i << " ] " << (*path)[i].x << " " << (*path)[i].y << std::endl;
	}
}
