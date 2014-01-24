#ifndef		__ISCENE_HH__
#define		__ISCENE_HH__

#include 	"common.hh"
#include 	"CameraView.hh"
#include	"BonusStock.hh"

class		IScene
{
public:
  virtual void	initialize() = 0;
  virtual void 	initializeCamera() = 0;
  virtual void	update() = 0;
  virtual void	draw() = 0;
  virtual ~IScene(){};
};

#endif
