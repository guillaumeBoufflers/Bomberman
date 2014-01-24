
#ifndef	__GAMEOPTIONSCENE_HH__
#define	__GAMEOPTIONSCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"
#include          "isValidMap.hh"

class	GameOptionScene : public IScene
{
public:
  enum			GameOptionSceneActions {
    GAME_OPTION_NOTHING,
    GAME_OPTION_PLAY,
    GAME_OPTION_BACK,
    GAME_ONE_PLAYER,
    GAME_TWO_PLAYER,
    GAME_UP_IA,
    GAME_DOWN_IA,
    GAME_EASY,
    GAME_MEDIUM,
    GAME_HARD,
    GAME_MAP,
    GAME_LOAD
  };
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  bool                _validMap;
  std::vector<IGDLObject *>   _objects;
  std::stringstream     _nb;
  std::string         _map;
  void					(GameOptionScene::*_actions[12])();
public:
  GameOptionScene(Bomberman *, KeyController *, CameraView *);
  ~GameOptionScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			play();
  void			back();
  void			onePlayer();
  void			twoPlayer();
  void			upIa();
  void			downIa();
  void			upNbBomb();
  void			downNbBomb();
  void			upRangeBomb();
  void			downRangeBomb();
  void			upLife();
  void			downLife();
  void			easy();
  void			medium();
  void			hard();
  void			map();
  void			load();
};

#endif
