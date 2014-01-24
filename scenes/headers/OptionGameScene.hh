
#ifndef		__OPTIONGAMESCENE_HH__
#define		__OPTIONGAMESCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class	OptionGameScene : public IScene
{
public:
  enum	OptionGameSceneActions {
    OPTION_GAME_NOTHING,
    OPTION_GAME_BACK,
    OPTION_GAME_ARCADE,
    OPTION_GAME_AZERTY,
    OPTION_GAME_QWERTY,
    OPTION_GAME_ARMAGEDDON
  };
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::vector<IGDLObject *>		_objects;
  void					(OptionGameScene::*_actions[6])();
public:
  OptionGameScene(Bomberman *, KeyController *, CameraView *);
  ~OptionGameScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			back();
  void			arcade();
  void			azerty();
  void			qwerty();
  void			armageddon();
};

#endif
