#ifndef					__BOMBERMAN_HH__
#define					__BOMBERMAN_HH__

#include 				"common.hh"
#include 				"KeyController.hh"
#include 				"SoundController.hh"
#include 				"Clock.hh"

#include 				"IScene.hh"
#include 				"MainMenuScene.hh"
#include				"GameScene.hh"
#include				"GameOptionScene.hh"
#include				"GeneralOptionScene.hh"
#include				"CreditsScene.hh"
#include				"OptionSoundScene.hh"
#include				"OptionGameScene.hh"
#include				"OptionGameArcadeScene.hh"
#include				"OptionArmageddonScene.hh"
#include				"PlayerOneWinScene.hh"
#include				"PlayerTwoWinScene.hh"
#include				"IaWinScene.hh"
#include				"ScoreScene.hh"
#include				"PauseScene.hh"
#include				"DrawScene.hh"
#include				"IntroScene.hh"

class					GameScene;

class					Bomberman : public gdl::Game
{
public:
	enum 	Scenes {
		INTRODUCTION,
		MENU,
		GAME_OPTIONS,
		GENERAL_OPTIONS,
		GAME,
		CREDITS,
		SCORES,
		OPTION_SOUND,
		OPTION_GAME,
		OPTION_GAME_ARCADE,
		OPTION_GAME_ARMAGEDDON,
		PLAYER_ONE,
		PLAYER_TWO,
		IA,
		DRAW,
		PAUSE,
		INTRO
	};
	std::map<std::string, int>		_infoGame;
	static bool			isAzerty;
	static int			isArmageddon;
private:
	Bomberman::Scenes	_scene;
	KeyController		*_keyController;
	CameraView 			*_camera;

	IScene 				*_scenes[NB_SCENES];

public:
  Bomberman();
  ~Bomberman();


  void					initialize();
  void					update();
  void					draw();
  void					unload();
  void          		setScene(Bomberman::Scenes);
  void          		closeWindow();
  void					startNewGame(const std::string &);
  void					loadGame();
};

#endif
