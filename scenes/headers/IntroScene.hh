
#ifndef		__INTROSCENE_HH__
#define		__INTROSCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class		IntroScene : public IScene
{
public:
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  GDLBackground				*_objects;
  void					(IntroScene::*_actions[1])();
  int					_update;
  int					_nbScene;
  std::vector<std::string>		_images;
public:
  IntroScene(Bomberman *, KeyController *, CameraView *);
  ~IntroScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
};

#endif
