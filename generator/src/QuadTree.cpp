
#include "QuadTree.hh"

QuadTree			*(QuadTree::*tab[4])();

QuadTree::QuadTree(int x, int y, int sizex, int sizey, QuadTree *prev, int pos):
  x(x), y(y), sizex(sizex), sizey(sizey), par(prev), pos(pos)
{
  this->play = 0;
  if (tab[0] == NULL)
    {
      tab[0] = &QuadTree::cornerTopLeft;
      tab[1] = &QuadTree::cornerTopRight;
      tab[2] = &QuadTree::cornerBottomRight;
      tab[3] = &QuadTree::cornerBottomLeft;
    }
  this->dispo = 0;
  this->x_max = this->x + (this->sizex - 1);
  this->y_max = this->y + (this->sizey - 1);
  if ((this->sizex) * (this->sizey) > 1)
    {
      this->quad.push_back(new QuadTree(this->x, 
      					this->y,
      					this->sizex - this->sizex / 2,
      					this->sizey - this->sizey / 2,
      					this, (pos != 0)?(pos):(1)));
      if (this->y + this->sizey / 2 + this->sizey % 2 <= this->y_max)
	if (this->x + this->sizex / 2 + this->sizex % 2 <= this->x_max)
	  this->quad.push_back(new QuadTree((this->x + this->sizex / 2 + this->sizex % 2),
					    (this->y + this->sizey / 2 + this->sizey % 2),
					    this->sizex - (this->sizex / 2 + this->sizex % 2),
					    this->sizey - (this->sizey / 2 + this->sizey % 2),
					    this, (pos != 0)?(pos):(3)));

      if (this->y + this->sizey / 2 + this->sizey % 2 <= this->y_max)
	{
	  this->quad.push_back(new QuadTree(this->x, 
					    (this->y + this->sizey / 2 + this->sizey % 2),
					    this->sizex - this->sizex / 2,
					    this->sizey - (this->sizey / 2 + this->sizey % 2),
					    this, (pos != 0)?(pos):(4)));
	}
      if (this->x + this->sizex / 2 + this->sizex % 2 <= this->x_max)
	{
	  this->quad.push_back(new QuadTree((this->x + this->sizex / 2 + this->sizex % 2),
					    this->y,
					    this->sizex - (this->sizex / 2 + this->sizex % 2),
					    this->sizey - this->sizey / 2,
					    this, (pos != 0)?(pos):(2)));
	}
    }
  else
    dispo = 1;
}

QuadTree::~QuadTree()
{
  
}

int QuadTree::getDispo() const
{
  return (this->dispo);
}

void QuadTree::makeDispo(std::map<int, Object *>& _map, int& size)
{
  if (this->quad.empty())
    {
      if (_map[(this->x -1) * size + this->y - 1]->getType() != EMPTY)
	dispo = 0;
    }
  else
    {
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	(*it)->makeDispo(_map, size);
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	this->dispo = (*it)->getDispo() + this->dispo;
    }
}

void QuadTree::placePlayers(int nb, std::map<int, Object *>&map, int &_size, std::list<Except *>&list)
{
  if (this->par == NULL)
    while (nb > 0)
      {
	for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end() && nb > 0; it++)
	  {
	    if ((*it)->getDispo() > 0)
	      {
		(*it)->placePlayers(1, map, _size, list);
		nb--;
	      } 
	  }
      }
  else
    {
      QuadTree *tmp;
      tmp = (this->*tab[this->pos - 1])();
      tmp->updatePlay();
      map[(tmp->getX() - 1) * _size + tmp->getY() - 1]->setType(PLAYER);
      ;
      list.push_back(new Except(tmp->getX() - 1, tmp->getY()));
      list.push_back(new Except(tmp->getX(), tmp->getY() - 1));
      list.push_back(new Except(tmp->getX() - 2, tmp->getY() - 1));
      list.push_back(new Except(tmp->getX() - 1, tmp->getY() - 2));
    }
}

void QuadTree::updatePlay()
{
  this->play = this->play + 1;
  this->dispo = this->dispo - 1;
  if (this->par != NULL)
    this->par->updatePlay();
}

int QuadTree::getX() const
{
  return (this->x);
}

int QuadTree::getY() const
{
  return (this->y);
}

int QuadTree::getPlay()
{
  return (this->play);
}

QuadTree *QuadTree::cornerTopLeft()
{
  QuadTree *tmp;
  int play;
  QuadTree *ret = NULL;

  if (this->quad.empty())
    return (this);
  else
    {
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	{
	  if (it == this->quad.begin())
	    play = (*it)->getPlay();
	  else
	    {
	      if ((*it)->getPlay() < play)
		play = (*it)->getPlay();
	    }
	}
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	{
	  if ((*it)->getPlay() == play)
	    {
	      if (ret == NULL && (*it)->cornerTopLeft()&& (*it)->cornerTopLeft()->getDispo() > 0)
		{
		  ret = (*it)->cornerTopLeft();
		  play = (*it)->getPlay();
		}
	      else
		{
		  tmp = (*it)->cornerTopLeft();	
		  if ((tmp && tmp->getDispo() > 0) && (*it)->getPlay() < play)
		    {
		      ret = tmp;
		      play = (*it)->getPlay();
		    }
		  else if ((tmp && tmp->getDispo() > 0) && tmp->getX() <= ret->getX() && tmp->getY() <= ret->getY() && (*it)->getPlay() <= play)
		    {
		      ret = tmp;
		      play = (*it)->getPlay();
		    }
		}
	    }
	}
    }
  return (ret);
}

QuadTree *QuadTree::cornerTopRight()
{
  QuadTree *tmp;
  QuadTree *ret = NULL;
  int play;

  if (this->quad.empty())
    return (this);
  else
    {
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	{
	  if (it == this->quad.begin())
	    play = (*it)->getPlay();
	  else
	    {
	      if ((*it)->getPlay() < play)
		play = (*it)->getPlay();
	    }
	}
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	{
	  if ((*it)->getPlay() == play)
	    {
	      if (ret == NULL && (*it)->cornerTopRight() && (*it)->cornerTopRight()->getDispo() > 0)
		{
		  ret = (*it)->cornerTopRight();
		  play = (*it)->getPlay();
		}
	      else
		{
		  tmp = (*it)->cornerTopRight();
		  if ((tmp && tmp->getDispo() > 0) && (*it)->getPlay() < play)
		    {
		      ret = tmp;
		      play = (*it)->getPlay();
		    }
		  else if ((tmp && tmp->getDispo() > 0) && tmp->getX() >= ret->getX() && tmp->getY() <= ret->getY() && (*it)->getPlay() <= play)
		    {
		      ret = tmp;
		      play = (*it)->getPlay();
		    }
		}
	    }
	}
      return (ret);
    }
}

QuadTree *QuadTree::cornerBottomLeft()
{
  QuadTree *tmp;
  QuadTree *ret = NULL;
  int play;

  if (this->quad.empty())
    return (this);
  else
    {
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	{
	  if (it == this->quad.begin())
	    play = (*it)->getPlay();
	  else
	    {
	      if ((*it)->getPlay() < play)
		play = (*it)->getPlay();
	    }
	}
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	{
	  if ((*it)->getPlay() == play)
	    {
	      if (ret == NULL && (*it)->cornerBottomLeft() && (*it)->cornerBottomLeft()->getDispo() > 0)
		{
		  ret = (*it)->cornerBottomLeft();
		  play = (*it)->getPlay();
		}
	      else
		{
		  tmp = (*it)->cornerBottomLeft();
		  if ((tmp && tmp->getDispo() > 0) && (*it)->getPlay() < play)
		    {
		      ret = tmp;
		      play = (*it)->getPlay();
		    }
		  else if ((tmp && tmp->getDispo() > 0) && tmp->getX() <= ret->getX() && tmp->getY() >= ret->getY() && (*it)->getPlay() <= play)
		    {
		      ret = tmp;
		      play = (*it)->getPlay();
		    }
		}
	    }
	}
    }
  return (ret);
}

QuadTree *QuadTree::cornerBottomRight()
{
  QuadTree *tmp;
  QuadTree *ret = NULL;
  int play;

  if (this->quad.empty())
    return (this);
  else
    {
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	{
	  if (it == this->quad.begin())
	    play = (*it)->getPlay();
	  else
	    {
	      if ((*it)->getPlay() < play)
		play = (*it)->getPlay();
	    }
	}
      for (std::vector<QuadTree *>::iterator it = this->quad.begin(); it != quad.end(); it++)
	{
	  if ((*it)->getPlay() == play)
	    {
	      if (ret == NULL && (*it)->cornerBottomRight() && (*it)->cornerBottomRight()->getDispo() > 0)
		{
		  ret = (*it)->cornerBottomRight();
		  play = (*it)->getPlay();
		}
	      else
		{
		  tmp = (*it)->cornerBottomRight();
		  if ((tmp && tmp->getDispo() > 0) && (*it)->getPlay() < play)
		    {
		      ret = tmp;
		      play = (*it)->getPlay();
		    }
		  else if ((tmp && tmp->getDispo() > 0) && tmp->getX() >= ret->getX() && tmp->getY() >= ret->getY() && (*it)->getPlay() <= play)
		    {
		      ret = tmp;
		      play = (*it)->getPlay();
		    }
		}
	    }
	}
    }
  return (ret);
}
