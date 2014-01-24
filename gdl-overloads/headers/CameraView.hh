
#ifndef		__CAMERA_VIEW_HH__
#define		__CAMERA_VIEW_HH__

#include 	"common.hh"

class		CameraView
{
public:
  CameraView();
  ~CameraView();
  void		initialize2d();
  void		initialize3d();
  bool    isDualMode();
  void    setDualMode(bool dual);
  void    setPosAndRot(float x1, float y1, float z1, float x2, float y2, float z2);
  void    setPosAndRot(float x, float y, float z);
  float	  getX() const;
  float	  getY() const;
  float	  getZ() const;
protected:
  bool      twoCams;
  float		_x;
  float		_y;
  float		_z;
};

#endif
