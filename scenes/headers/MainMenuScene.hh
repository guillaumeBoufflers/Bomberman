#ifndef 					__MAIN_MENU_HH__
#define						__MAIN_MENU_HH__

#include 					"common.hh"

#include 					"IScene.hh"
#include 					"Bomberman.hh"
#include 					"KeyController.hh"
#include 					"CameraView.hh"

#include 					"GDLBackground.hh"
#include 					"GDLButton.hh"
#include 					"GDLText.hh"

class 						Bomberman;

class 						MainMenuScene : public IScene
{
public:
	enum 					MainMenuSceneActions {
		MAIN_MENU_NOTHING,
		MAIN_MENU_PLAY,
		MAIN_MENU_OPTIONS,
		MAIN_MENU_CREDITS,
		MAIN_MENU_SCORE,
		MAIN_MENU_QUIT
	};

private:
	Bomberman				*_bomberman;
	KeyController				*_keyController;
	CameraView				*_camera;
	std::list<IGDLObject *>			_objects;
	void					(MainMenuScene::*_actions[6])();

public:
	MainMenuScene(Bomberman *, KeyController *, CameraView *);
	~MainMenuScene();

	virtual void 			initActionPtrs();
	virtual void 			initialize();
	virtual void 			initializeCamera();
	virtual void 			update();
	virtual void 			draw();

	/* ====================================
	 *              ACTIONS
	 * ====================================
	 */
	void 					play();
	void 					options();
	void 					quit();
	void					credits();
	void					score();
};

#endif
