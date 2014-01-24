#ifndef		__COMMON_HH__
#define		__COMMON_HH__

 #include 	<QByteArray>
 #include 	<QFile>
 #include 	<QCryptographicHash>

#undef 		signals

#include 	<string>
#include 	<list>
#include	<map>
#include 	<iostream>
#include 	<ios>
#include	<GL/gl.h>
#include	<GL/glu.h>
#include 	<unistd.h>
#include 	<cstdlib>
#include	<sstream>
#include	<fstream>
#include 	"gtk/gtk.h"

#include 	"BombermanException.hpp"

#include	"Clock.hpp"
#include	"Color.hpp"
#include	"Game.hpp"
#include	"GameClock.hpp"
#include	"Image.hpp"
#include	"Input.hpp"
#include	"Model.hpp"
#include	"Window.hpp"
#include	"Text.hpp"

#define		W_WIDTH       1280
#define		W_HEIGHT      1024
#define		W_TITLE       "Game"
#define 	CASE_SIZE	  256
#define		MOVE_BY		  15
#define 	NB_SCENES	  17
#define		FPS		  60
#define		EXPLOSION_TIME	  1 * FPS
#define		TOXIC_TIME	  2 * FPS
//#define		CLOUD_TIME	  2 * EXPLOSION_TIME
#define		BOMB_TIME	  2 * FPS
#define		BIGBOMB_TIME	2 * BOMB_TIME
#define		BONUS_INVICIBILITY EXPLOSION_TIME + 2
#define		RECOVERY_TIME	5 * FPS
#define		SCORE_TOXIC	100
#define		SCORE_BONUS	1000
#define		SCORE_KILL	5000
#define		MAX_BOMB	9
#define		TIME_RAMBO	10 * FPS
#define		TIME_GHOST	10 * FPS
#define		DISTANCE_PLAYER_BEFORE_DUAL	14
#define		VERIF_BUILD	((a >= 4 && a <= 5) || ( a >= 8 && a <= 18) || (a == 22))
#define		CAN_POSE_BOMB	(GameScene::_map[this->getPosCaseY()][this->getPosCaseX()].back()->getGlobalType() == BOMB || GameScene::_map[this->getPosCaseY()][this->getPosCaseX()].back()->getType() == DESTRUCTIBLEWALL || GameScene::_map[this->getPosCaseY()][this->getPosCaseX()].back()->getType() == UNDESTRUCTIBLEWALL)

#endif
