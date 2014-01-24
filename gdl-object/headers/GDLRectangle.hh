#ifndef		__GDLRECTANGLE_HH__
#define		__GDLRECTANGLE_HH__

#include 	"common.hh"
#include 	"Bomberman.hh"
#include	"IGDLObject.hh"

#include 				"CameraView.hh"

class		GDLRectangle : public IGDLObject
{
private:
	float 					_x;
	float					_y;
	float					_z;
	float 					_width;
	float					_height;
	float					_xCamera;
	float					_yCamera;
	std::string		 		_SpritePath;	
	int					_reverse;
	gdl::Image				_image;
	CameraView					*_camera;
	int					_dir;
	int					_side;
public:
  GDLRectangle(float, float, float, float, float, std::string, int, CameraView *);
  GDLRectangle(float , float , float , float , float , std::string , int, CameraView *, int);
  virtual ~GDLRectangle();
  virtual void		initialize();
  virtual int		update();
  virtual void		draw();
  void			drawRec();
  void			setX(float);
  void			setY(float);
  void			setSprite(const std::string &);
  void			setCoordX(float);
};

#endif
