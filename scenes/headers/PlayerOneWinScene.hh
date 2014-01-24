
#ifndef		__PLAYERONEWINSCENE_HH__
#define		__PLAYERONEWINSCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class		PlayerOneWinScene : public IScene
{
public:
  enum		PlayerOneWinSceneActions {
    PLAYER_ONE_WIN_NOTHING,
    PLAYER_ONE_WIN_SCORE,
    PLAYER_ONE_WIN_NEXT
  };
private:
    Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::list<IGDLObject *>		_objects;
  void					(PlayerOneWinScene::*_actions[3])();
public:
  PlayerOneWinScene(Bomberman *, KeyController *, CameraView *);
  ~PlayerOneWinScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			score();
  void			next();
};

#endif
