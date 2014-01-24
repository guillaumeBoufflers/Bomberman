#ifndef 				__GAMESCENE_HH__
#define					__GAMESCENE_HH__

#include				<algorithm>

#include 				"IScene.hh"
#include				"GDLObjectFactory.hh"
#include 				"Bomberman.hh"
#include        "Serialize.hh"

#include 				"common.hh"
#include 				"KeyController.hh"

#include 				"GDLButton.hh"
#include 				"GDLText.hh"
#include				"GDLRectangle.hh"

#include 				"CameraView.hh"


#include				"HumanPlayer.hh"
#include				"IObject.hh"
#include				"Empty.hh"
#include				"Wall.hh"
#include				"Score.hh"
#include				"utils.hh"

class					  APlayer;
class 					Bomberman;
class					GDLRectangle;

class 					GameScene : public IScene
{
public:
  enum 				GameSceneActions
    {
      GAME_SCENE_NOTHING,
    };
  static std::vector<std::vector<std::list<IPhysicalObject *> > >	_map;
  static std::vector<APlayer*>						_alivePlayers;
  static std::vector<APlayer *>    _deadPlayers;
  static std::vector<std::string>					_meshTab;
  static IGDLObjectFactory	*factory;
  static bool	p1Alive;
  static bool	p2Alive;
  static std::vector<int>						_listBombP1;
  static std::vector<int>						_listBombP2;
  static bool								_updateVector;
  static int								currentWeapon1;
  static int								currentWeapon2;
  static std::list<IPhysicalObject *>::iterator	findInstance(IPhysicalObject *obj);
  static std::list<IPhysicalObject *>::iterator findSpecInstance(IPhysicalObject *obj);
  static void	destructObjectGame(std::list<IPhysicalObject *>::iterator it);
  static bool	isValidPos(int x, int y);
private:
  GDLText			*_score;
  Bomberman			*_bomberman;
  KeyController			*_keyController;
  CameraView 			*_camera;
  std::vector<IGDLObject *>		_objects;
  std::vector<int>			_listBomb1;
  std::vector<int>			_listBomb2;
  std::vector<std::string>		_tabSprite;
  std::string				_finalScore1;
  std::string				_finalScore2;
  std::string				_allInfo1;
  std::string				_allInfo2;
  GDLText				*_info1;
  GDLText				*_info2;
  GDLText				*_text1;
  GDLText				*_text2;
  GDLRectangle				*_current1;
  GDLRectangle				*_current2;
  GDLRectangle				*_p1;
public:
  GameScene(Bomberman *, KeyController *, CameraView *);
  ~GameScene();

  virtual void 		initialize();
  virtual void 		initializeCamera();
  void			initializeGame(const std::string &, std::map<std::string, int>);
  void			createPlayers(int, int, int, int, int, int);
  void        loadGame(const std::string &map);
  virtual void 		update();
  virtual void 		draw();

  /* ====================================
   *              ACTIONS
   * ====================================
   */
private:
  void	drawMap();
  void	initializeMeshTab();
  void	chooseWhatToBuild(int, int , int, std::list<IPhysicalObject*> &, std::vector<std::vector<int> > &);
  void	updateScore();
  void			buildMap(const std::string &, std::vector<std::vector <int> > &);
  void  initializeScore();
  void	updateInfo();
  int   calcDist(int x, int y, int x1, int y1);
};

#endif
