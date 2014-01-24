
#ifndef		__LOADINGSCENE_HH__
#define		__LOADINGSCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class		LoadingScene : public IScene
{
public:
  enum		LoadingSceneActions
    {
      LOADING_NOTHING
    };

private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::list<IGDLObject *>		_objects;
  void					(LoadingScene::*_actions[1])();
public:
  LoadingScene(Bomberman *, KeyController *, CameraView *);
  ~LoadingScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
};

#endif
