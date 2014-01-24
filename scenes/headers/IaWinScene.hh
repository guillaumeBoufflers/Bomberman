#ifndef		__IAWINSCENE_HH__
#define		__IAWINSCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class		IaWinScene : public IScene
{
public:
  enum		IaWinSceneActions {
    IA_WIN_NOTHING,
    IA_WIN_SCORE,
    IA_WIN_NEXT
  };
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::list<IGDLObject *>		_objects;
  void					(IaWinScene::*_actions[3])();
public:
  IaWinScene(Bomberman *, KeyController *, CameraView *);
  ~IaWinScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			score();
  void			next();
};

#endif
