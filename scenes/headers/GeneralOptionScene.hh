
#ifndef	__GENERAL_OPTION_HH__
#define	__GENERAL_OPTION_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class	GeneralOptionScene : public IScene
{
public:
  enum	GeneralOptionSceneActions {
    GENERAL_OPTION_NOTHING,
    GENERAL_OPTION_BACK,
    GENERAL_OPTION_GAME,
    GENERAL_OPTION_SOUND
  };
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::vector<IGDLObject *>		_objects;
  void					(GeneralOptionScene::*_actions[4])();
public:
  GeneralOptionScene(Bomberman *, KeyController *, CameraView *);
  ~GeneralOptionScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			back();
  void			game();
  void			sound();
};

#endif
