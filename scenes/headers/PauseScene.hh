
#ifndef		__PAUSESCENE_HH__
#define		__PAUSESCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class		PauseScene : public IScene
{
public:
  enum		CreditsSceneActions {
    PAUSE_NOTHING,
    PAUSE_MENU,
    PAUSE_SAVE,
    PAUSE_RESUME
  };
private:
    Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::list<IGDLObject *>		_objects;
  void					(PauseScene::*_actions[4])();
public:
  PauseScene(Bomberman *, KeyController *, CameraView *);
  ~PauseScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			menu();
  void			resume();
  void			save();
};

#endif
