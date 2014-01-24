#ifndef		__GDLBACKGROUNDOBJECT_H__
#define		__GDLBACKGROUNDOBJECT_H__

#include 	"common.hh"
#include	"IGDLObject.hh"

class		GDLBackground : public IGDLObject
{
private:
	gdl::Image			_background;
	 int				_reverse;
public:
  GDLBackground(const std::string &, int );

	virtual void		initialize();
	virtual int			update();
	virtual void		draw();
	virtual ~GDLBackground();
  void			setBackground(const std::string &);
};

#endif
