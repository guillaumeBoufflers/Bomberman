
#ifndef			__DRAWSCENE_HH__
#define			__DRAWSCENE_HH__


#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class		DrawScene : public IScene
{
public:
  enum		DrawSceneActions {
    DRAW_NOTHING,
    DRAW_SCORE,
    DRAW_NEXT
  };
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::list<IGDLObject *>		_objects;
  void					(DrawScene::*_actions[3])();
public:
  DrawScene(Bomberman *, KeyController *, CameraView *);
  ~DrawScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			score();
  void			next();
};

#endif
