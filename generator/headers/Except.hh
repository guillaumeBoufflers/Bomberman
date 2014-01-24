#ifndef		__EXCEPT_HH__
#define		__EXCEPT_HH__

class		Except
{
private:
  int		_x;
  int		_y;
public:
  Except();
  Except(int, int);
  ~Except();
  void		setX(int x);
  int		getX() const;
  void		setY(int y);
  int		getY() const;
};

#endif
