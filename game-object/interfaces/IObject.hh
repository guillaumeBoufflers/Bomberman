#ifndef		__IOBJECT_HH__
#define	        __IOBJECT_HH__

#include	<string>

class		APlayer;

class		IObject
{
public:
  virtual	~IObject(){};

  virtual	void	effectObject(APlayer *) = 0;
};

#endif
