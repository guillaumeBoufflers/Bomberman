
#ifndef		__CREDITSSCENE_HH__
#define		__CREDITSSCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class		CreditsScene : public IScene
{
public:
  enum		CreditsSceneActions {
    CREDITS_NOTHING,
    CREDITS_BACK
  };
private:
    Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::list<IGDLObject *>		_objects;
  void					(CreditsScene::*_actions[2])();
public:
  CreditsScene(Bomberman *, KeyController *, CameraView *);
  ~CreditsScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			back();
};

#endif
