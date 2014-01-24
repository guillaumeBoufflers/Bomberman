#ifndef		__PLAYERTWOWINSCENE_HH__
#define		__PLAYERTWOWINSCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class		PlayerTwoWinScene : public IScene
{
public:
  enum		PlayerTwoWinSceneActions {
    PLAYER_TWO_WIN_NOTHING,
    PLAYER_TWO_WIN_SCORE,
    PLAYER_TWO_WIN_NEXT
  };
private:
    Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::list<IGDLObject *>		_objects;
  void					(PlayerTwoWinScene::*_actions[3])();
public:
  PlayerTwoWinScene(Bomberman *, KeyController *, CameraView *);
  ~PlayerTwoWinScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			score();
  void			next();
};

#endif
