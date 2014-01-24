#ifndef		__OBJECT_H__
#define		__OBJECT_H__

#include	<SFML/Graphics.hpp>
#include	<iostream>
#include	"../../common/headers/enum.hh"

class		Object
{
private:
  sf::Sprite	*_sprite;
  sf::Image	*_image;
  ObjectType		_type;
  int		_posX;
  int		_posY;
  int		_posMapX;
  int		_posMapY;
  bool		_isBorder;
public:
  Object(ObjectType type, int x, int y,  int posMapX, int posMapY, bool border);
  ~Object();
  void		setX(int x);
  void		setY(int y);
  void		setType(ObjectType type);
  int		getX() const;
  int		getY() const;
  ObjectType	getType() const;
  void		setSprite(sf::Sprite *sprite);
  sf::Sprite	*getSprite() const;
  bool		getBorder() const;
  int		getPosMapX() const;
  int		getPosMapY() const;
  void		setPosMapX(int x);
  void		setPosMapY(int x);
};

#endif
