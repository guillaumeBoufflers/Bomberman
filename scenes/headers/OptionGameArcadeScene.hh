
#ifndef		__OPTIONGAMEARCADE_HH__
#define		__OPTIONGAMEARCADE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class	OptionGameArcadeScene : public IScene
{
public:
  enum	OptionGameArcadeSceneActions {
    OPTION_GAME_ARCADE_NOTHING,
    OPTION_GAME_ARCADE_BACK,
    OPTION_GAME_CLASSIC,
    OPTION_GAME_ARMAGEDDON,
    OPTION_UP_BOMB,
    OPTION_DOWN_BOMB,
    OPTION_UP_RANGE,
    OPTION_DOWN_RANGE,
    OPTION_UP_LIFE,
    OPTION_DOWN_LIFE,
    OPTION_AZERTY,
    OPTION_QWERTY
  };
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::vector<IGDLObject *>		_objects;
  std::stringstream			_nbBomb;
  std::stringstream			_nbLife;
  std::stringstream			_nbRange;
  void					(OptionGameArcadeScene::*_actions[12])();
public:
  OptionGameArcadeScene(Bomberman *, KeyController *, CameraView *);
  ~OptionGameArcadeScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			back();
  void			classic();
  void			armageddon();
  void			upNbBomb();
  void			downNbBomb();
  void			upRangeBomb();
  void			downRangeBomb();
  void			upLife();
  void			downLife();
  void			azerty();
  void			qwerty();
};

#endif
