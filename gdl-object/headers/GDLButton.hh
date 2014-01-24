#ifndef		__GDL_BUTTON_HH
#define		__GDL_BUTTON_HH

#include 	"common.hh"
#include 	"Bomberman.hh"
#include	"IGDLObject.hh"

class		GDLButton : public IGDLObject
{
public:
	enum 	ButtonState {
		GDL_BUTTON_BASE,
		GDL_BUTTON_HOVER,
		GDL_BUTTON_CLICKED
	};
	enum	Type {
		GDL_BUTTON_RECT,
		GDL_BUTTON_TRIUP,
		GDL_BUTTON_TRIDOWN
	};
private:
	KeyController				*_keyController;
	GDLButton::ButtonState			_state;
	float 					_x;
	float					_y;
	float 					_width;
	float					_height;
	std::string		 		_baseSpritePath;
	std::string				_hoverSpritePath;
	const std::string			_clickedSpritePath;
	GDLButton::Type				_type;
	 int					_actionDefault;
	int 					_actionPressed;
	int					_reverse;
	void				(GDLButton::*_typ[3])();
	std::vector<gdl::Image>		_image;
public:
  GDLButton(KeyController *, const std::string &, const std::string &, const std::string &,Type, int, int, int, int, int, int, int);

  
  virtual ~GDLButton();
  virtual void		initialize();
  virtual int		update();
  virtual void		draw();
  void			drawButton(gdl::Image texture);
  void			drawRec();
  void			drawTri();
  void			drawTriInv();
  void			setHover(const std::string & hover);
  void			setSurvol(const std::string & survol);
};

#endif
