
#ifndef	__SCORESCENE_HH__
#define	__SCORESCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

#include					"Score.hh"

class	ScoreScene : public IScene
{
public:
  enum			ScoreSceneActions {
    SCORE_NOTHING,
    SCORE_MENU
  };
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::vector<IGDLObject *>		_objects;
  std::string				_score;
  void					(ScoreScene::*_actions[2])();
  std::vector<std::string>		_allScore;
  GDLText				*_scoreText;
public:
  ScoreScene(Bomberman *, KeyController *, CameraView *);
  ~ScoreScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			menu();
};

#endif
