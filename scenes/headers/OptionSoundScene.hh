
#ifndef		__OPTION_SCENE_HH__
#define		__OPTION_SCENE_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class	OptionSoundScene : public IScene
{
public:
  enum	OptionSoundSceneActions {
    OPTION_SOUND_NOTHING,
    OPTION_SOUND_ON_FX,
    OPTION_SOUND_OFF_FX,
    OPTION_SOUND_ON_MUSIC,
    OPTION_SOUND_OFF_MUSIC,
    OPTION_SOUND_BACK
  };
private:
  Bomberman				*_bomberman;
  KeyController				*_keyController;
  CameraView				*_camera;
  std::vector<IGDLObject *>		_objects;
  void					(OptionSoundScene::*_actions[6])();
public:
  OptionSoundScene(Bomberman *, KeyController *, CameraView *);
  ~OptionSoundScene();
  virtual void		initActionPtrs();
  virtual void 		initialize();
  virtual void 		initializeCamera();
  virtual void 		update();
  virtual void 		draw();
  void			soundOnFx();
  void			soundOffFx();
  void			soundOnMusic();
  void			soundOffMusic();
  void			back();
};

#endif
