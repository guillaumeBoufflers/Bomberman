#ifndef __QUADTREE_HH__
#define __QUADTREE_HH__

#include "Build.hh"

class QuadTree
{
  std::vector<QuadTree *>	quad;
  int				x;
  int				y;
  int				dispo;
  int				play;
  int				x_max;
  int				y_max;
  int				sizex;
  int				sizey;
  QuadTree			*par;
  int				pos;
public:
  QuadTree(int x, int y, int sizex, int sizey, QuadTree *prev, int pos);
  ~QuadTree();
  int getDispo() const;
  void makeDispo(std::map<int, Object *>&, int&);
  void placePlayers(int nb, std::map<int, Object *>&, int &size, std::list<Except *>&);
  void updatePlay();
  int getPlay();
  int getX() const;
  int getY() const;
  QuadTree *cornerTopLeft();
  QuadTree *cornerTopRight();
  QuadTree *cornerBottomLeft();
  QuadTree *cornerBottomRight();
};

#endif
