#ifndef 					__GAME_OVER_HH__
#define						__GAME_OVER_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class 						Bomberman;

class 						GameOverScene : public IScene
{
public:
	enum 					GameOverSceneActions {
		GAME_OVER_NOTHING,
		GAME_OVER_BACK,
	};
private:
	Bomberman				*_bomberman;
	KeyController				*_keyController;
	CameraView				*_camera;
	std::vector<IGDLObject *>			_objects;
	void					(GameOverScene::*_actions[2])();

public:
	GameOverScene(Bomberman *, KeyController *, CameraView *);
	~GameOverScene();

	virtual void 			initActionPtrs();
	virtual void 			initialize();
	virtual void 			initializeCamera();
	virtual void 			update();
	virtual void 			draw();
	void				back();
};

#endif
