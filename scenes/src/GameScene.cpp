#include 					"GameScene.hh"

std::vector<std::vector<std::list<IPhysicalObject *> > >  GameScene::_map;
std::vector<APlayer*>                                     GameScene::_alivePlayers;
std::vector<APlayer*>                                     GameScene::_deadPlayers;

std::vector<std::string>				                          GameScene::_meshTab;
IGDLObjectFactory					                                *GameScene::factory;
bool							                                        GameScene::p1Alive;
bool							                                        GameScene::p2Alive;
bool							                                        GameScene::_updateVector;
int							                                          GameScene::currentWeapon1;
int							                                          GameScene::currentWeapon2;
std::vector<int>					                                GameScene::_listBombP1;
std::vector<int>					                                GameScene::_listBombP2;


GameScene::GameScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera)
{
  int	i = 0;
  this->factory = GDLObjectFactory::getInstance();
  this->initializeMeshTab();  
  this->_updateVector = false;
  while (i < 7)
    {
      if (i == 0)
	{
	  _listBombP1.push_back(this->_bomberman->_infoGame["nbBombs"]);
	  _listBombP2.push_back(this->_bomberman->_infoGame["nbBombs"]);
	}
      else
	{
	  _listBombP1.push_back(0);
	  _listBombP2.push_back(0);
	}
      i++;
    }
  this->_tabSprite.push_back("/generator/sprites/basic_bomb_text.png");
  this->_tabSprite.push_back("/generator/sprites/biological_text.png");
  this->_tabSprite.push_back("/generator/sprites/mine_text.png");
  this->_tabSprite.push_back("/generator/sprites/missile_text.png");
  this->_tabSprite.push_back("/generator/sprites/radioactive_text.png");
  this->_tabSprite.push_back("/generator/sprites/piquante_text.png");
  this->_tabSprite.push_back("/generator/sprites/remote_bomb.png");
  this->currentWeapon1 = 0;
  this->currentWeapon2 = 0;
}

void        GameScene::loadGame(const std::string &map)
{
  Serialize   *tmp = new Serialize();

  (void)map;
  tmp->deserialize(this->_map, this->_alivePlayers, this->_deadPlayers, map.c_str());
}

GameScene::~GameScene()
{
  int		a = 0;
  for (unsigned int y = 0 ; y < this->_map.size() ; ++y)
    {
      for (unsigned int x = 0 ; x < this->_map[y].size() ; ++x)
	{
	  for (std::list<IPhysicalObject *>::iterator it = this->_map[y][x].begin(); it != this->_map[y][x].end(); ++it)
	    {
	      delete(*it);
	      it = this->_map[y][x].erase(it);
	    }
	  this->_map[y].clear();
	}
      this->_map.clear();
    }
  for (std::vector<APlayer *>::iterator it = _alivePlayers.begin(); it != _alivePlayers.end() && a == 0 ; ++it)
    {
      delete(*it);
      it = _alivePlayers.erase(it);
      if (it == _alivePlayers.end())
	a = 1;
    }
  _alivePlayers.clear();
  for (std::vector<APlayer *>::iterator it = _deadPlayers.begin(); it != _deadPlayers.end() && a == 0; ++it)
    {
      delete(*it);
      it = _deadPlayers.erase(it);
      if (it == _deadPlayers.end())
	a = 1;
    }
  _deadPlayers.clear();
}

void	GameScene::initializeMeshTab()
{
  std::string		tmp;

  this->_meshTab.push_back(tmp = "");
  this->_meshTab.push_back(tmp = "medias/models/explosion.fbx");
  this->_meshTab.push_back(tmp = "medias/models/explosion_toxique.fbx");
  this->_meshTab.push_back(tmp = "");
  this->_meshTab.push_back(tmp = "medias/models/brick.fbx");
  this->_meshTab.push_back(tmp = "medias/models/solid_brick.fbx");
  this->_meshTab.push_back(tmp = "medias/models/empty.fbx");
  this->_meshTab.push_back(tmp = "");
  this->_meshTab.push_back(tmp = "medias/models/bonus_speed.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_plus_bomb.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_range.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_mine.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_rocket.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_nuke.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_toxic.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_traverse.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_remote.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_medic.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_shield.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_ghost.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_medic.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bonus_random.fbx");
  this->_meshTab.push_back(tmp = "");
  this->_meshTab.push_back(tmp = "medias/models/marvin.fbx");
  this->_meshTab.push_back(tmp = "medias/models/marvin.fbx");
  this->_meshTab.push_back(tmp = "");
  this->_meshTab.push_back(tmp = "medias/models/bomb.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bomb_toxic.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bomb_mine.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bomb_rocket.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bomb_nucl.fbx");
  this->_meshTab.push_back(tmp = "medias/models/bomb_spike.fbx"); 
  this->_meshTab.push_back(tmp = "medias/models/bomb_telec.fbx");
  this->_meshTab.push_back(tmp = "");
}

void    GameScene::initializeCamera() {
  if (this->_camera)
    this->_camera->initialize3d();
}

void    GameScene::initializeGame(const std::string &map, std::map<std::string, int> info)
{
  int		a = 0;

  std::vector<std::vector<int> >	posPlayer;
  this->buildMap(map, posPlayer);
  this->createPlayers(info["nbPlayers"], info["nbIa"], info["nbLife"], info["difficult"], info["rangeBombs"], info["nbBombs"]);
  for (std::vector<APlayer *>::iterator it = _alivePlayers.begin(); it != _alivePlayers.end(); ++it)
    {
      if (posPlayer[a][0] && posPlayer[a][1])
	{
	  (*it)->setPositionCase(posPlayer[a][0], posPlayer[a][1]);
	  a++;
	}
    }
}

void		GameScene::initializeScore()
{
  if (p1Alive == true && p2Alive == true)
  {
    this->_objects.push_back(new GDLRectangle(-1580, -80, 0, 80, 80, "/medias/buttons/casque1.png", 1, this->_camera, 0));

    this->_objects.push_back(new GDLRectangle(-1600, 0, 0, 40, 40, "/generator/sprites/life_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1320, 0, 0, 40, 40, "/generator/sprites/croix_rouge_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1450, 0, 0, 40, 40, "/generator/sprites/basic_bomb_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1450, 50, 0, 40, 40, "/generator/sprites/biological_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1600, 50, 0, 40, 40, "/generator/sprites/mine_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1320, 50, 0, 40, 40, "/generator/sprites/missile_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1600, 100, 0, 40, 40, "/generator/sprites/radioactive_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1450, 100, 0, 40, 40, "/generator/sprites/remote_bomb.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1320, 100, 0, 40, 40, "/generator/sprites/piquante_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1490, 190, 0, 80, 80, "/generator/sprites/basic_bomb_text.png", 1, this->_camera, 0));

    this->_objects.push_back(new GDLRectangle(-280, -80, 0, 80, 80, "/medias/buttons/casque2.png", 1, this->_camera, 1));
    this->_objects.push_back(new GDLRectangle(-300, 0, 0, 40, 40, "/generator/sprites/life_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-20, 0, 0, 40, 40, "/generator/sprites/croix_rouge_text.png", 1, this->_camera)); 
    this->_objects.push_back(new GDLRectangle(-150, 0, 0, 40, 40, "/generator/sprites/basic_bomb_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-150, 50, 0, 40, 40, "/generator/sprites/biological_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-300, 50, 0, 40, 40, "/generator/sprites/mine_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-20, 50, 0, 40, 40, "/generator/sprites/missile_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-300, 100, 0, 40, 40, "/generator/sprites/radioactive_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-150, 100, 0, 40, 40, "/generator/sprites/remote_bomb.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-20, 100, 0, 40, 40, "/generator/sprites/piquante_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-190, 190, 0, 80, 80, "/generator/sprites/basic_bomb_text.png", 1, this->_camera, 1));


    this->_finalScore1 = "       :" + BUtils::intToString(_alivePlayers[0]->getScore());
    this->_finalScore2 = "       :" + BUtils::intToString(_alivePlayers[1]->getScore());
    this->_allInfo1 = BUtils::intToString(_alivePlayers[0]->getLife()) + "          " + BUtils::intToString(_listBombP1[0]) +   "         " + BUtils::intToString(_alivePlayers[0]->getHealth()) + 
    "\n" + BUtils::intToString(_listBombP1[2]) +  "          " + BUtils::intToString(_listBombP1[1]) +   "         " + BUtils::intToString(_listBombP1[3]) +
    "\n" + BUtils::intToString(_listBombP1[4]) +   "          " + BUtils::intToString(_listBombP1[6]) +    "         " + BUtils::intToString(_listBombP1[5]);

    this->_allInfo2 = BUtils::intToString(_alivePlayers[1]->getLife()) + "          " + BUtils::intToString(_listBombP2[0]) +   "         " + BUtils::intToString(_alivePlayers[1]->getHealth()) + 
    "\n" + BUtils::intToString(_listBombP2[2]) +  "          " + BUtils::intToString(_listBombP2[1]) +   "         " + BUtils::intToString(_listBombP2[3]) +
    "\n" + BUtils::intToString(_listBombP2[4]) +   "          " + BUtils::intToString(_listBombP2[6]) +    "         " + BUtils::intToString(_listBombP2[5]);      

    //p2
    this->_objects.push_back(new GDLText(this->_allInfo2, 0, 950, 74, 30, 255, 255, 255));
    this->_objects.push_back(new GDLText(this->_finalScore2, 0, 900, 10, 40, 255, 255, 255));
    //p1
    this->_objects.push_back(new GDLText(this->_allInfo1, 0, 50, 74, 30, 255, 255, 255));
    this->_objects.push_back(new GDLText(this->_finalScore1, 0, 10, 10, 40, 255, 255, 255));
  }
  else
  {
    this->_objects.push_back(new GDLRectangle(-1580, -80, 0, 80, 80, "/medias/buttons/casque1.png", 1, this->_camera));

    this->_objects.push_back(new GDLRectangle(-1600, 0, 0, 40, 40, "/generator/sprites/life_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1320, 0, 0, 40, 40, "/generator/sprites/croix_rouge_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1450, 0, 0, 40, 40, "/generator/sprites/basic_bomb_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1450, 50, 0, 40, 40, "/generator/sprites/biological_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1600, 50, 0, 40, 40, "/generator/sprites/mine_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1320, 50, 0, 40, 40, "/generator/sprites/missile_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1600, 100, 0, 40, 40, "/generator/sprites/radioactive_text.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1450, 100, 0, 40, 40, "/generator/sprites/remote_bomb.png", 1, this->_camera));
    this->_objects.push_back(new GDLRectangle(-1320, 100, 0, 40, 40, "/generator/sprites/piquante_text.png", 1, this->_camera));

    this->_objects.push_back(new GDLRectangle(-1490, 190, 0, 80, 80, "/generator/sprites/basic_bomb_text.png", 1, this->_camera));

    this->_finalScore1 = "       :" + BUtils::intToString(_alivePlayers[0]->getScore());
    this->_allInfo1 = BUtils::intToString(_alivePlayers[0]->getLife()) + "          " + BUtils::intToString(_listBombP1[0]) +   "         " + BUtils::intToString(_alivePlayers[0]->getHealth()) + 
    "\n" + BUtils::intToString(_listBombP1[2]) +  "          " + BUtils::intToString(_listBombP1[1]) +   "         " + BUtils::intToString(_listBombP1[3]) +
    "\n" + BUtils::intToString(_listBombP1[4]) +   "          " + BUtils::intToString(_listBombP1[6]) +    "         " + BUtils::intToString(_listBombP1[5]);
    this->_objects.push_back(new GDLText(this->_allInfo1, 0, 50, 75, 33, 255, 255, 255));
    this->_objects.push_back(new GDLText(this->_finalScore1, 0, 5, 10, 40, 255, 255, 255));
  }
}

void		GameScene::initialize()
{
	for (std::vector<APlayer *>::iterator it = _alivePlayers.begin(); it != _alivePlayers.end(); ++it)
		(*it)->initialize();
	this->initializeScore();
	for (std::vector<IGDLObject *>:: iterator it = _objects.begin(); it != _objects.end(); ++it)
		(*it)->initialize();
}


void		GameScene::chooseWhatToBuild(int a, int x, int y, std::list<IPhysicalObject *> &listObj, std::vector<std::vector<int> > &posPlayer)
{
  ObjectType	tmp;

  tmp = static_cast<ObjectType>(a);
  if (VERIF_BUILD)
    {
      if (a >= 4 && a <= 5)
	listObj.push_back(factory->createAObject(x, y, 1, 0, this->_meshTab[tmp], tmp));
      else if (a >= 8 && a <= 18)
	listObj.push_back(factory->createAObject(x, y, 1, 0, this->_meshTab[tmp], tmp));
      else
	{
	  std::vector<int>	tmp1;
	  tmp1.push_back(x);
	  tmp1.push_back(y);
	  posPlayer.push_back(tmp1);
	}
    }
  listObj.push_back(factory->createAObject(x, y, 1, 0, this->_meshTab[EMPTY], EMPTY));
}

void		GameScene::buildMap(const std::string &file, std::vector<std::vector<int> >&posPlayer)
{
  std::ifstream fichier(file.c_str(), std::ifstream::in);
  std::string data;
  std::vector<std::string> objs;
  std::list<IPhysicalObject *> tmp1;
  std::vector<std::list<IPhysicalObject *> > tmp;
  int		tmp2;
  int		x = 0;
  int		y = 0;

  if(fichier)
    {
      while (getline(fichier, data))
	{
	  data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
	  objs = BUtils::split(' ', data);
	  x = 0;
	  for (std::vector<std::string>::iterator it = objs.begin() ; it != objs.end() ; ++it)
	    {
	      tmp2 = BUtils::stringToInt((*it));
	      this->chooseWhatToBuild(tmp2, x, y,  tmp1, posPlayer);
	      tmp.push_back(tmp1);
	      tmp1.clear();
	      x++;
	    }
	  this->_map.push_back(tmp);
	  tmp.clear();
	  y++;
	}
      fichier.close();
    }
}

void		GameScene::createPlayers(int human, int ia, int life, int difficulty, int range, int start)
{
  p1Alive = false;
  p2Alive = false;
  for (int x = 0; x < human ; x++)
    this->_alivePlayers.push_back(factory->createAPlayer(0, 0, 1, 0, this->_meshTab[HUMANPLAYER], HUMANPLAYER, x, life, range, start));
  for (int x = 0; x < ia ; x++)
    this->_alivePlayers.push_back(factory->createAPlayer(1, x, 1, 0, this->_meshTab[IAPLAYER], IAPLAYER, difficulty, life, range, start));
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		GameScene::updateInfo()
{
  try
    {
      if (p1Alive == true && p2Alive == true)
	{
	  this->_finalScore1 = "       :" + BUtils::intToString(_alivePlayers[0]->getScore());
	  this->_finalScore2 = "       :" + BUtils::intToString(_alivePlayers[1]->getScore());

	  if (this->_updateVector == true)
	    {
	      this->_allInfo1 = BUtils::intToString(_alivePlayers[0]->getLife()) + "          " + BUtils::intToString(_listBombP1[0]) +   "         " + BUtils::intToString(_alivePlayers[0]->getHealth()) + 
		"\n" + BUtils::intToString(_listBombP1[2]) +  "          " + BUtils::intToString(_listBombP1[1]) +   "         " + BUtils::intToString(_listBombP1[3]) +
		"\n" + BUtils::intToString(_listBombP1[4]) +   "          " + BUtils::intToString(_listBombP1[6]) +    "         " + BUtils::intToString(_listBombP1[5]);


	      this->_allInfo2 = BUtils::intToString(_alivePlayers[1]->getLife()) + "          " + BUtils::intToString(_listBombP2[0]) +   "         " + BUtils::intToString(_alivePlayers[1]->getHealth()) + 
		"\n" + BUtils::intToString(_listBombP2[2]) +  "          " + BUtils::intToString(_listBombP2[1]) +   "         " + BUtils::intToString(_listBombP2[3]) +
		"\n" + BUtils::intToString(_listBombP2[4]) +   "          " + BUtils::intToString(_listBombP2[6]) +    "         " + BUtils::intToString(_listBombP2[5]);      
	      this->_updateVector = false;
	    }
	  this->_current1 = dynamic_cast<GDLRectangle *>(this->_objects[10]);
	  this->_p1 = dynamic_cast<GDLRectangle *>(this->_objects[0]);
	  this->_text1 = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 1]);
	  this->_info1 = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 2]);	  
	  this->_current2 = dynamic_cast<GDLRectangle *>(this->_objects[21]);
	  this->_text2 = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 3]);	  
	  this->_info2 = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 4]);
	  if (_current1 == 0 || _p1 == 0 || _text1 == 0 || _info1 == 0 || _current2 == 0 || _text2 == 0 || _info2 == 0)
	    throw BombermanException("dynamic cast fail");
	  this->_current1->setSprite(this->_tabSprite[currentWeapon1]);
	  this->_text1->setText(this->_finalScore1);
	  this->_info1->setText(this->_allInfo1);
	  this->_current2->setSprite(this->_tabSprite[currentWeapon2]);
	  this->_text2->setText(this->_finalScore2);
	  this->_info2->setText(this->_allInfo2);
	  if (this->_camera->isDualMode() == false)
	    {
	      this->_current1->setCoordX(-1490);
	      this->_p1->setCoordX(-1580);
	    }
	  else
	    {
	      this->_p1->setCoordX(-280);	
	      this->_current1->setCoordX(-190);
	    }

	}
      else if (p1Alive == true)
	{
	  this->_finalScore1 = "       :" + BUtils::intToString(_alivePlayers[0]->getScore());
	  if (this->_updateVector == true)
	    {

	      this->_allInfo1 = BUtils::intToString(_alivePlayers[0]->getLife()) + "          " + BUtils::intToString(_listBombP1[0]) +   "         " + BUtils::intToString(_alivePlayers[0]->getHealth()) + 
		"\n" + BUtils::intToString(_listBombP1[2]) +  "          " + BUtils::intToString(_listBombP1[1]) +   "         " + BUtils::intToString(_listBombP1[3]) +
		"\n" + BUtils::intToString(_listBombP1[4]) +   "          " + BUtils::intToString(_listBombP1[6]) +    "         " + BUtils::intToString(_listBombP1[5]);
	      this->_updateVector = false;
	    }
	  this->_current1 = dynamic_cast<GDLRectangle *>(this->_objects[10]);
	  this->_p1 = dynamic_cast<GDLRectangle *>(this->_objects[0]);
	  this->_text1 = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 1]);	  
	  this->_info1 = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 2]);	  
	  if (this->_current1 == 0 || this->_p1 == 0 || this->_text1 == 0 || this->_info1 == 0)
	    throw BombermanException("dynamic cast fail");
	  this->_current1->setSprite(this->_tabSprite[currentWeapon1]);
	  this->_text1->setText(this->_finalScore1);
	  this->_info1->setText(this->_allInfo1);
	  if (this->_camera->isDualMode() == false)
	    {
	      this->_current1->setCoordX(-1490);
	      this->_p1->setCoordX(-1580);
	    }
	}
      else
	{
	  if (p2Alive == true)
	    {
	      if (this->_updateVector == true)
		{
		  this->_allInfo2 = BUtils::intToString(_alivePlayers[1]->getLife()) + "          " + BUtils::intToString(_listBombP2[0]) +   "         " + BUtils::intToString(_alivePlayers[1]->getHealth()) + 
		    "\n" + BUtils::intToString(_listBombP2[2]) +  "          " + BUtils::intToString(_listBombP2[1]) +   "         " + BUtils::intToString(_listBombP2[3]) +
		    "\n" + BUtils::intToString(_listBombP2[4]) +   "          " + BUtils::intToString(_listBombP2[6]) +    "         " + BUtils::intToString(_listBombP2[5]);
		  this->_updateVector = false;
		}
	      this->_finalScore2 = "       :" + BUtils::intToString(_alivePlayers[1]->getScore());
	      this->_current2 = dynamic_cast<GDLRectangle *>(this->_objects[21]);
	      this->_text2 = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 3]);
	      this->_info2 = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 4]);
	      if (this->_current2 == 0 || this->_text2 == 0 || this->_info2 == 0)
		throw BombermanException("dynamic cast fail");
	      this->_current2->setSprite(this->_tabSprite[currentWeapon2]);
	      this->_text2->setText(this->_finalScore2);
	      this->_info2->setText(this->_allInfo2);
	    }
	}
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		GameScene::update()
{
  if (this->_keyController->isKeyDown(gdl::Keys::Escape))
    {
      if (this->_camera)
	{
	  this->_camera->initialize2d();
	  this->_bomberman->setScene(Bomberman::PAUSE);
	}
    }
  SoundController::getInstance()->update();
  for (unsigned int y = 0 ; y < this->_map.size() ; ++y)
    {
      for (unsigned int x = 0 ; x < this->_map[y].size() ; ++x)
	{
	  if (this->_map[y][x].size() != 1)
	    {
	      for (std::list<IPhysicalObject *>::iterator it = this->_map[y][x].begin(); it != this->_map[y][x].end(); ++it)
		{
		  if ((*it)->update()) // <<<<<<<<<<<<<<<< return 1 = je me suis destroy
		    break; //OUI HEIN MERCI GHAIS, QUAND ON DELETE DEPUIS LOBJET LE IT NEST PLUS BON DONC JE RET 1 COMME CA ON SAIT
		}
	    }
	}
    }
  if (this->_alivePlayers.size() == 1 || (!this->p1Alive && !this->p2Alive))
    {
      this->_camera->initialize2d();
      sleep(2);
      if (!p1Alive && !p2Alive)
	{
	  if (this->_bomberman->_infoGame["nbIa"] == 0)
	    this->_bomberman->setScene(Bomberman::DRAW);
	  else
	    this->_bomberman->setScene(Bomberman::IA);
	}
      else if (p1Alive)
	{
	  Score::getInstance()->setScore(_alivePlayers[0]->getScore(), 1);
	  Score::getInstance()->setFich();
	  this->_bomberman->setScene(Bomberman::PLAYER_ONE);
	}
      else
	{
	  Score::getInstance()->setScore(_alivePlayers[0]->getScore(), 2);
	  Score::getInstance()->setFich();
	  this->_bomberman->setScene(Bomberman::PLAYER_TWO);
	}
    }
  else
    {
      int a = 0;
      for (std::vector<APlayer *>::iterator it = _alivePlayers.begin(); it != _alivePlayers.end() && a == 0; ++it)
	{
	  if ((*it)->getStatus() == DEAD)
	    {
	      this->_deadPlayers.push_back(*it);
	      it = _alivePlayers.erase(it);
	      if (it == _alivePlayers.end())
		a = 1;
	    }
	  else
	    (*it)->update();
	}
      this->updateInfo();
      for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
	(*it)->update();
    }
}

void	GameScene::updateScore()
{

}

int		GameScene::calcDist(int x, int y, int x1, int y1)
{
  return (sqrt(pow(x - x1, 2) + pow(y - y1, 2)));
}

void    GameScene::drawMap()
{
  int xp1;
  int yp1;
  int xp2;
  int yp2;

  if (p1Alive)
  {
    xp1 = _alivePlayers[0]->getPosCaseX();
    yp1 = _alivePlayers[0]->getPosCaseY();
    if (p2Alive) {
     xp2 = _alivePlayers[1]->getPosCaseX();
     yp2 = _alivePlayers[1]->getPosCaseY();
   }
   else {
     xp2 = xp1;
     yp2 = yp1;
   }
 }
  else// (p2Alive)
  {
    xp1 = xp2 = _alivePlayers[0]->getPosCaseX();
    yp1 = yp2 = _alivePlayers[0]->getPosCaseY();
  }

  for (std::vector<APlayer *>::iterator it = _alivePlayers.begin(); it != _alivePlayers.end(); ++it)
    (*it)->draw();

  if (!_camera->isDualMode()) //condition testee une fois par frame, ne pas mettre dans le for
    for (unsigned int y = 0 ; y < this->_map.size() ; ++y)
    {
      for (unsigned int x = 0 ; x < this->_map[y].size() ; ++x)
      {
       for (std::list<IPhysicalObject *>::iterator it = this->_map[y][x].begin(); it != this->_map[y][x].end(); ++it)
         if (calcDist(x, y, xp1, yp1 - 5) < 15 || calcDist(x, y, xp2, yp2 - 5) < 15)
           (*it)->draw();
       }
     }
  else
    for (unsigned int y = 0 ; y < this->_map.size() ; ++y)
    {
      for (unsigned int x = 0 ; x < this->_map[y].size() ; ++x)
      {
       for (std::list<IPhysicalObject *>::iterator it = this->_map[y][x].begin(); it != this->_map[y][x].end(); ++it)
         if (calcDist(x * 2, y, xp1 * 2, (yp1 - 5)) < 15 || calcDist(x * 2, y, xp2 * 2, (yp2 - 5)) < 15)
           (*it)->draw();
       }
     }


 }

 void		GameScene::draw()
 {

  glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
  if (p1Alive && p2Alive && calcDist(_alivePlayers[0]->getPosCaseX(), _alivePlayers[0]->getPosCaseY(), _alivePlayers[1]->getPosCaseX(), _alivePlayers[1]->getPosCaseY()) >= DISTANCE_PLAYER_BEFORE_DUAL)
    this->_camera->setDualMode(1);
  else
    this->_camera->setDualMode(0);
  if (!this->_camera->isDualMode() && p1Alive && p2Alive) {
    this->_camera->setPosAndRot(_alivePlayers[0]->getPosX(), 0, _alivePlayers[0]->getPosY(), _alivePlayers[1]->getPosX(), 0, _alivePlayers[1]->getPosY());
  }
  else
    this->_camera->setPosAndRot(_alivePlayers.front()->getPosX(), 0, _alivePlayers.front()->getPosY());

  if (_camera->isDualMode())
  {
    this->_camera->setPosAndRot(_alivePlayers[0]->getPosX(), 0, _alivePlayers[0]->getPosY());
    glViewport(0, 0, W_WIDTH / 2, W_HEIGHT);
    this->drawMap();
    for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
     (*it)->draw();
   this->_camera->setPosAndRot(_alivePlayers[1]->getPosX(), 0, _alivePlayers[1]->getPosY());
   glViewport(W_WIDTH / 2, 0, W_WIDTH / 2, W_HEIGHT);
   this->drawMap();
   for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
     (*it)->draw();
 }
 else
 {
  glViewport(0, 0, W_WIDTH, W_HEIGHT);
  this->drawMap();
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
   (*it)->draw();
}
}

bool    GameScene::isValidPos(int x, int y)
{
  if (x >= 0 && y >= 0 && x < (int)_map[y].size() && y < (int)_map.size())
    return (true);
  return (false);
}

void            GameScene::destructObjectGame(std::list<IPhysicalObject *>::iterator it)
{
  int		x, y;

  x = (*it)->getPosCaseX();
  y = (*it)->getPosCaseY();
  (*it)->destroyObject();
  delete(*it);
  _map[y][x].erase(it);
}

std::list<IPhysicalObject *>::iterator	GameScene::findInstance(IPhysicalObject *obj)
{
  int		x, y;

  x = obj->getPosCaseX();
  y = obj->getPosCaseY();
  
  for (std::list<IPhysicalObject *>::iterator it = _map[y][x].begin() ; it != _map[y][x].end() ; ++it)
  {
    if (*it == obj)
     return (it);
 }
 return (_map[y][x].begin());
}

std::list<IPhysicalObject *>::iterator  GameScene::findSpecInstance(IPhysicalObject *obj)
{
  int   x, y;

  Rocket *bomb = dynamic_cast<Rocket *>(obj);
  x = bomb->getXBeg();
  y = bomb->getYBeg();
  
  for (std::list<IPhysicalObject *>::iterator it = _map[y][x].begin() ; it != _map[y][x].end() ; ++it)
  {
    if (*it == obj)
     return (it);
 }
 return (_map[y][x].begin());
}
