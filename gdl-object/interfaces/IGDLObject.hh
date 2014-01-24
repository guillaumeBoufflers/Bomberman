#ifndef		__IGDLOBJECT_HH__
#define		__IGDLOBJECT_HH__

class		IGDLObject
{
public:
  virtual void	initialize() = 0;
  virtual int	update() = 0;
  virtual void	draw() = 0;
  virtual ~IGDLObject(){};
};

#endif
