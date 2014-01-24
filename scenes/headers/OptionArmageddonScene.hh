
#ifndef		__OPTIONARMAGEDDONSCENE_HH__
#define		__OPTIONARMAGEDDONSCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class	OptionArmageddonScene : public IScene
{
public:
  enum	OptionArmageddonSceneActions {
    OPTION_ARMAGEDDON_NOTHING,
    OPTION_ARMAGEDDON_BACK,
    OPTION_ARMAGEDDON_ARCADE,
    OPTION_ARMAGEDDON_CLASSIC,
    OPTION_ARMAGEDDON_AZERTY,
    OPTION_ARMAGEDDON_QWERTY,
    OPTION_UP_BOMB,
    OPTION_DOWN_BOMB,
    OPTION_UP_RANGE,
    OPTION_DOWN_RANGE,
    OPTION_UP_LIFE,
    OPTION_DOWN_LIFE
  };
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::stringstream			_nbBomb;
  std::stringstream			_nbLife;
  std::stringstream			_nbRange;
  std::vector<IGDLObject *>		_objects;
  void					(OptionArmageddonScene::*_actions[12])();
public:
  OptionArmageddonScene(Bomberman *, KeyController *, CameraView *);
  ~OptionArmageddonScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			back();
  void			classic();
  void			arcade();
  void			azerty();
  void			qwerty();
  void			upNbBomb();
  void			downNbBomb();
  void			upRangeBomb();
  void			downRangeBomb();
  void			upLife();
  void			downLife();
};

#endif
