#include	"GameOptionScene.hh"

GameOptionScene::GameOptionScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera), _validMap(false)
{
}

GameOptionScene::~GameOptionScene()
{

}

void		GameOptionScene::initActionPtrs()
{
  this->_actions[GAME_OPTION_NOTHING] = NULL;
  this->_actions[GAME_OPTION_PLAY] = &GameOptionScene::play;
  this->_actions[GAME_OPTION_BACK] = &GameOptionScene::back;
  this->_actions[GAME_ONE_PLAYER] = &GameOptionScene::onePlayer;
  this->_actions[GAME_TWO_PLAYER] = &GameOptionScene::twoPlayer;
  this->_actions[GAME_UP_IA] = &GameOptionScene::upIa;
  this->_actions[GAME_DOWN_IA] = &GameOptionScene::downIa;
  this->_actions[GAME_EASY] = &GameOptionScene::easy;
  this->_actions[GAME_MEDIUM] = &GameOptionScene::medium;
  this->_actions[GAME_HARD] = &GameOptionScene::hard;
  this->_actions[GAME_MAP] = &GameOptionScene::map;
  this->_actions[GAME_LOAD] = &GameOptionScene::load;
}

void		GameOptionScene::update()
{
  int	action;

  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != GAME_OPTION_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		GameOptionScene::draw()
{
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		GameOptionScene::initialize()
{
  this->initActionPtrs();
  this->_nb <<   this->_bomberman->_infoGame["nbIa"];
  this->_objects.push_back(new GDLBackground("medias/images/backgroundGameOption.png", 1));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/one_players_button_active.png", "medias/buttons/one_players_button_active.png", "medias/buttons/one_players_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 + 100, 210, 223, 62, GAME_OPTION_NOTHING, GAME_ONE_PLAYER, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/two_players_button.png", "medias/buttons/two_players_button_hover.png", "medias/buttons/two_players_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 * 2, 210, 223, 62, GAME_OPTION_NOTHING, GAME_TWO_PLAYER, 1));

  //diffcultes
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/ia_defensive.png", "medias/buttons/ia_defensive_hover.png", "medias/buttons/ia_defensive_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 + 50 , 400, 217, 62, GAME_OPTION_NOTHING, GAME_EASY, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/ia_normal_active.png", "medias/buttons/ia_normal_active.png", "medias/buttons/ia_normal_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 * 2 - 100, 400, 155, 62, GAME_OPTION_NOTHING, GAME_MEDIUM, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/ia_agressive.png", "medias/buttons/ia_agressive_hover.png", "medias/buttons/ia_agressive_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH - 200, 400, 214, 66, GAME_OPTION_NOTHING, GAME_HARD, 1));

  // // nb ia
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/fleche.png", "medias/buttons/fleche_hover.png", "medias/buttons/fleche_hover.png", GDLButton::GDL_BUTTON_TRIUP, W_WIDTH / 3 * 2, 280, 50, 30, GAME_OPTION_NOTHING, GAME_UP_IA, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/fleche.png", "medias/buttons/fleche_hover.png", "medias/buttons/fleche_hover.png", GDLButton::GDL_BUTTON_TRIDOWN, W_WIDTH / 3 * 2, 330, 50, 30, GAME_OPTION_NOTHING, GAME_DOWN_IA, 1));

 this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/chosse_map_button.png", "medias/buttons/chosse_map_button_hover.png", "medias/buttons/chosse_map_button_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 6, 600, 283, 65, GAME_OPTION_NOTHING, GAME_MAP, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/start_game_button.png", "medias/buttons/start_game_button_hover.png", "medias/buttons/start_game_button_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 6, 700, 264, 62, GAME_OPTION_NOTHING, GAME_OPTION_PLAY, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/load_game_button.png", "medias/buttons/load_game_button_hover.png", "medias/buttons/load_game_button_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 6, 800, 387, 65, GAME_OPTION_NOTHING, GAME_LOAD, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_credits.png", "medias/buttons/back_button_credits_hover.png", "medias/buttons/back_button_credits_hover.png", GDLButton::GDL_BUTTON_RECT, 100, W_HEIGHT - 50, 110, 62, GAME_OPTION_NOTHING, GAME_OPTION_BACK, 1));

  this->_objects.push_back(new GDLText(this->_nb.str(), GAME_OPTION_NOTHING, 420, 265, 60, 255, 255, 255));
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();

}

void		GameOptionScene::initializeCamera()
{
  if (this->_camera)
    this->_camera->initialize2d();
}

void		GameOptionScene::play()
{
  if (this->_validMap) {
    this->_validMap = false;
    if (this->_bomberman->_infoGame["nbPlayers"] + this->_bomberman->_infoGame["nbIa"] >= 2) {
      if (GameMap::isValidMap(this->_map, this->_bomberman->_infoGame["nbPlayers"] + this->_bomberman->_infoGame["nbIa"])) {
        this->_bomberman->startNewGame(this->_map);
      } else {
        BUtils::runDialog(GTK_MESSAGE_ERROR, "Your map file is not valid.\nMaybe you have set too many players for this map.\nPlease use the map generator to create valid map files.");
      }
    }
    else
      BUtils::runDialog(GTK_MESSAGE_WARNING, "Please add 2 players before starting the game.");
  } else {
    BUtils::runDialog(GTK_MESSAGE_INFO, "Please choose a valid map file before starting the game.");
  }
}

void		GameOptionScene::back()
{
  this->initializeCamera();
  this->_bomberman->setScene(Bomberman::MENU);
}

void		GameOptionScene::map()
{
  char  *cfile;
  std::string tmp;

  cfile = BUtils::openFileDialog("Please choose a map file");
  if (cfile) {
    std::ifstream filestream(cfile, std::ifstream::in);
    if (filestream) {
      if (filestream.is_open())
        filestream.close();
      tmp = cfile;
      if (GameMap::isValidMap(tmp, this->_bomberman->_infoGame["nbPlayers"] + this->_bomberman->_infoGame["nbIa"])) {
        this->_map = tmp;
        this->_validMap = true;
      } else {
        BUtils::runDialog(GTK_MESSAGE_ERROR, "Your map file is not valid.\nPlease use the map generator to create valid map files.");
      }
    } else {
      BUtils::runDialog(GTK_MESSAGE_ERROR, "The map file cannot be opened.");
    }
  } else {
    BUtils::runDialog(GTK_MESSAGE_WARNING, "You haven't chosen a file.");
  }
}

void		GameOptionScene::onePlayer()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;

      this->_bomberman->_infoGame["nbPlayers"] = 1;
      button1 = dynamic_cast<GDLButton *>(this->_objects[1]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[2]);
      if (button1 == 0 || button2 == 0)
        throw BombermanException("dynamic cast fail");
      button1->setHover("medias/buttons/one_players_button_active.png");
      button1->setSurvol("medias/buttons/one_players_button_active.png");
      button2->setHover("medias/buttons/two_players_button.png");
      button2->setSurvol("medias/buttons/two_players_button_hover.png");
      
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		GameOptionScene::twoPlayer()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;

      this->_bomberman->_infoGame["nbPlayers"] = 2;
      button1 = dynamic_cast<GDLButton *>(this->_objects[2]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[1]);
      if (button1 == 0 || button2 == 0)
        throw BombermanException("dynamic cast fail");
      button1->setHover("medias/buttons/two_players_button_active.png");
      button1->setSurvol("medias/buttons/two_players_button_active.png");
      button2->setHover("medias/buttons/one_players_button.png");
      button2->setSurvol("medias/buttons/one_players_button_hover.png");

    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		GameOptionScene::upIa()
{
  try
    {
      GDLText	*text;

      this->_bomberman->_infoGame["nbIa"] += 1;
      this->_nb.str(std::string());
      this->_nb <<  this->_bomberman->_infoGame["nbIa"];
      text = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 1]);
      if (text == 0)
        throw BombermanException("dynamic cast fail");
      text->setText(this->_nb.str());
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		GameOptionScene::downIa()
{
  try
    {
      GDLText	*text;
      
      if (this->_bomberman->_infoGame["nbIa"] >= 1)
	this->_bomberman->_infoGame["nbIa"] -= 1;
      this->_nb.str(std::string());
      this->_nb << this->_bomberman->_infoGame["nbIa"];
      text = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 1]);
      if (text == 0)
        throw BombermanException("dynamic cast fail");
      text->setText(this->_nb.str());
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		GameOptionScene::easy()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;
      GDLButton	*button3;

      this->_bomberman->_infoGame["difficult"] = EASY;
      button1 = dynamic_cast<GDLButton *>(this->_objects[3]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[4]);
      button3 = dynamic_cast<GDLButton *>(this->_objects[5]);
      if (button1 == 0 || button2 == 0 || button3 == 0)
	throw BombermanException("dynamic cast fail");

      button1->setHover("medias/buttons/ia_defensive_active.png");
      button1->setSurvol("medias/buttons/ia_defensive_active.png");     
      button2->setHover("medias/buttons/ia_normal.png");
      button2->setSurvol("medias/buttons/ia_normal_hover.png");
      button3->setHover("medias/buttons/ia_agressive.png");
      button3->setSurvol("medias/buttons/ia_agressive_hover.png");
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		GameOptionScene::medium()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;
      GDLButton	*button3;

      this->_bomberman->_infoGame["difficult"] = MEDIUM;
      button1 = dynamic_cast<GDLButton *>(this->_objects[4]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[3]);
      button3 = dynamic_cast<GDLButton *>(this->_objects[5]);
      if (button1 == 0 || button2 == 0 || button3 == 0)
	throw BombermanException("dynamic cast fail");
      button1->setHover("medias/buttons/ia_normal_active.png");
      button1->setSurvol("medias/buttons/ia_normal_active.png");
      button2->setHover("medias/buttons/ia_defensive.png");
      button2->setSurvol("medias/buttons/ia_defensive_hover.png");
      button3->setHover("medias/buttons/ia_agressive.png");
      button3->setSurvol("medias/buttons/ia_agressive_hover.png");
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		GameOptionScene::hard()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;
      GDLButton	*button3;

      this->_bomberman->_infoGame["difficult"] = HARD;
      button1 = dynamic_cast<GDLButton *>(this->_objects[5]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[3]);
      button3 = dynamic_cast<GDLButton *>(this->_objects[4]);
      if (button1 == 0 || button2 == 0 || button3 == 0)
	throw BombermanException("Dynamic cast fail");
      button1->setHover("medias/buttons/ia_agressive_active.png");
      button1->setSurvol("medias/buttons/ia_agressive_active.png");
      button2->setHover("medias/buttons/ia_defensive.png");
      button2->setSurvol("medias/buttons/ia_defensive_hover.png"); 
      button3->setHover("medias/buttons/ia_normal.png");
      button3->setSurvol("medias/buttons/ia_normal_hover.png");
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void      GameOptionScene::load()
{
  this->_validMap = false;
  this->_bomberman->loadGame();
}
