#ifndef __IAPATHFINDERNODE_HPP__
#define __IAPATHFINDERNODE_HPP__

#include <iostream>
#include <vector>
#include <cstdlib>

class IAPathFinderNode
{
public:
	IAPathFinderNode() { };
	IAPathFinderNode(int _x, int _y, int _gscore, int _fscore) : x(_x), y(_y), gscore(_gscore), fscore(_fscore) {};
	~IAPathFinderNode() {};
	int x;
	int y;
	int gscore;
	int fscore;
};

#endif
