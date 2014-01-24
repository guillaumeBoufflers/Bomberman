#include	"OptionGameArcadeScene.hh"


OptionGameArcadeScene::OptionGameArcadeScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera)
{
}

OptionGameArcadeScene::~OptionGameArcadeScene()
{

}

void	OptionGameArcadeScene::initActionPtrs()
{
  this->_actions[OPTION_GAME_ARCADE_NOTHING] = NULL;
  this->_actions[OPTION_GAME_ARCADE_BACK] = &OptionGameArcadeScene::back;
  this->_actions[OPTION_GAME_CLASSIC] = &OptionGameArcadeScene::classic;
  this->_actions[OPTION_GAME_ARMAGEDDON] = &OptionGameArcadeScene::armageddon;
  this->_actions[OPTION_UP_BOMB] = &OptionGameArcadeScene::upNbBomb;
  this->_actions[OPTION_DOWN_BOMB] = &OptionGameArcadeScene::downNbBomb;
  this->_actions[OPTION_UP_RANGE] = &OptionGameArcadeScene::upRangeBomb;
  this->_actions[OPTION_DOWN_RANGE] = &OptionGameArcadeScene::downRangeBomb;
  this->_actions[OPTION_UP_LIFE] = &OptionGameArcadeScene::upLife;
  this->_actions[OPTION_DOWN_LIFE] = &OptionGameArcadeScene::downLife;
  this->_actions[OPTION_AZERTY] = &OptionGameArcadeScene::azerty;
  this->_actions[OPTION_QWERTY] = &OptionGameArcadeScene::qwerty;
}

void		OptionGameArcadeScene::update()
{
  int	action;

  Bomberman::isArmageddon = 4;
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != OPTION_GAME_ARCADE_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		OptionGameArcadeScene::draw()
{
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		OptionGameArcadeScene::initialize()
{
  this->initActionPtrs();
  this->_nbLife << this->_bomberman->_infoGame["nbLife"];
  this->_nbBomb << this->_bomberman->_infoGame["nbBombs"];
  this->_nbRange << this->_bomberman->_infoGame["rangeBombs"];

  this->_objects.push_back(new GDLBackground("medias/images/backgroundOptionGame.png", 1));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/azerty_active.png", "medias/buttons/azerty_active.png", "medias/buttons/azerty_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3, 350, 233, 64, OPTION_GAME_ARCADE_NOTHING, OPTION_AZERTY, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/qwerty.png", "medias/buttons/qwerty_hover.png", "medias/buttons/qwerty_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 * 2, 350, 255, 64, OPTION_GAME_ARCADE_NOTHING, OPTION_QWERTY, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/classic_mode_button.png", "medias/buttons/classic_mode_button_hover.png", "medias/buttons/classic_mode_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 - 200, 450, 378, 78, OPTION_GAME_ARCADE_NOTHING, OPTION_GAME_CLASSIC, 1));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/carnage_button.png", "medias/buttons/carnage_button_hover.png", "medias/buttons/carnage_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 2, 450, 241, 81, OPTION_GAME_ARCADE_NOTHING, OPTION_GAME_ARMAGEDDON, 1));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/arcade_mode_button_active.png", "medias/buttons/arcade_mode_button_active.png", "medias/buttons/arcade_mode_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 * 2 + 200, 450, 397, 79, OPTION_GAME_ARCADE_NOTHING, OPTION_GAME_ARCADE_NOTHING, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/nb_bomb_text.png", "medias/buttons/nb_bomb_text.png", "medias/buttons/nb_bomb_text.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 - 100, 600, 232, 62, OPTION_GAME_ARCADE_NOTHING, OPTION_GAME_ARCADE_NOTHING, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/range_bomb_text.png", "medias/buttons/range_bomb_text.png", "medias/buttons/range_bomb_text.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 - 100, 700, 284, 62, OPTION_GAME_ARCADE_NOTHING, OPTION_GAME_ARCADE_NOTHING, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/nb_lifes_text.png", "medias/buttons/nb_lifes_text.png", "medias/buttons/nb_lifes_text.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 - 100 , 800, 200, 62, OPTION_GAME_ARCADE_NOTHING, OPTION_GAME_ARCADE_NOTHING, 1));

  //nb bomb
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/fleche.png", "medias/buttons/fleche_hover.png", "medias/buttons/fleche_hover.png", GDLButton::GDL_BUTTON_TRIUP, W_WIDTH / 3 * 2, 580, 50, 30, OPTION_GAME_ARCADE_NOTHING, OPTION_UP_BOMB, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/fleche.png", "medias/buttons/fleche_hover.png", "medias/buttons/fleche_hover.png", GDLButton::GDL_BUTTON_TRIDOWN, W_WIDTH / 3 * 2, 630, 50, 30, OPTION_GAME_ARCADE_NOTHING, OPTION_DOWN_BOMB, 1));
  //range bomb
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/fleche.png", "medias/buttons/fleche_hover.png", "medias/buttons/fleche_hover.png", GDLButton::GDL_BUTTON_TRIUP, W_WIDTH / 3 * 2, 680, 50, 30, OPTION_GAME_ARCADE_NOTHING, OPTION_UP_RANGE, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/fleche.png", "medias/buttons/fleche_hover.png", "medias/buttons/fleche_hover.png", GDLButton::GDL_BUTTON_TRIDOWN, W_WIDTH / 3 * 2, 730, 50, 30, OPTION_GAME_ARCADE_NOTHING, OPTION_DOWN_RANGE, 1));
  //nb life
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/fleche.png", "medias/buttons/fleche_hover.png", "medias/buttons/fleche_hover.png", GDLButton::GDL_BUTTON_TRIUP, W_WIDTH / 3 * 2, 780, 50, 30, OPTION_GAME_ARCADE_NOTHING, OPTION_UP_LIFE, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/fleche.png", "medias/buttons/fleche_hover.png", "medias/buttons/fleche_hover.png", GDLButton::GDL_BUTTON_TRIDOWN, W_WIDTH / 3 * 2, 830, 50, 30, OPTION_GAME_ARCADE_NOTHING, OPTION_DOWN_LIFE, 1));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_sound.png", "medias/buttons/back_button_sound_hover.png", "medias/buttons/back_button_sound_hover.png", GDLButton::GDL_BUTTON_RECT, 80, W_HEIGHT - 50, 110, 62, OPTION_GAME_ARCADE_NOTHING, OPTION_GAME_ARCADE_BACK, 1));
  this->_objects.push_back(new GDLText(this->_nbBomb.str(), OPTION_GAME_ARCADE_NOTHING, 500, 565, 60, 255, 255, 255));
  this->_objects.push_back(new GDLText(this->_nbRange.str(), OPTION_GAME_ARCADE_NOTHING, 500, 665, 60, 255, 255, 255));
  this->_objects.push_back(new GDLText(this->_nbLife.str(), OPTION_GAME_ARCADE_NOTHING, 500, 765, 60, 255, 255, 255));
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

void		OptionGameArcadeScene::initializeCamera()
{
  if (this->_camera)
    this->_camera->initialize2d();
}

void		OptionGameArcadeScene::back()
{
  this->initializeCamera();
  this->_bomberman->setScene(Bomberman::GENERAL_OPTIONS);
}

void		OptionGameArcadeScene::classic()
{
  this->_bomberman->setScene(Bomberman::OPTION_GAME);
}

void		OptionGameArcadeScene::armageddon()
{
  this->_bomberman->setScene(Bomberman::OPTION_GAME_ARMAGEDDON);
}

void		OptionGameArcadeScene::upNbBomb()
{
  try
    {
      GDLText	*text;
      
      if (this->_bomberman->_infoGame["nbBombs"] < 9)
	this->_bomberman->_infoGame["nbBombs"] += 1;
      this->_nbBomb.str(std::string());
      this->_nbBomb << this->_bomberman->_infoGame["nbBombs"];
      text = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 3]);
      if (text == 0)
        throw BombermanException("dynamic cast fail");
      text->setText(this->_nbBomb.str());
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionGameArcadeScene::downNbBomb()
{
  try
    {
      GDLText	*text;
      
      if (this->_bomberman->_infoGame["nbBombs"] >= 2)
	this->_bomberman->_infoGame["nbBombs"] -= 1;
      this->_nbBomb.str(std::string());
      this->_nbBomb << this->_bomberman->_infoGame["nbBombs"];
      text = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 3]);
      if (text == 0)
        throw BombermanException("dynamic cast fail");
      text->setText(this->_nbBomb.str());
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionGameArcadeScene::upRangeBomb()
{
  try
    {
      GDLText	*text;
      
      if (this->_bomberman->_infoGame["rangeBombs"] < 10)
	this->_bomberman->_infoGame["rangeBombs"] += 1;
      this->_nbRange.str(std::string());
      this->_nbRange << this->_bomberman->_infoGame["rangeBombs"];
      text = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 2]);
      if (text == 0)
        throw BombermanException("dynamic cast fail");
      text->setText(this->_nbRange.str());
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionGameArcadeScene::downRangeBomb()
{
    try
    {
      GDLText	*text;
      
      if (this->_bomberman->_infoGame["rangeBombs"] >= 2)
	this->_bomberman->_infoGame["rangeBombs"] -= 1;
      this->_nbRange.str(std::string());
      this->_nbRange << this->_bomberman->_infoGame["rangeBombs"];
      text = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 2]);
      if (text == 0)
	throw BombermanException("dynamic cast fail");
      text->setText(this->_nbRange.str());
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionGameArcadeScene::upLife()
{
    try
    {
      GDLText	*text;
      
      if (this->_bomberman->_infoGame["nbLife"] < 9)
	this->_bomberman->_infoGame["nbLife"] += 1;
      this->_nbLife.str(std::string());
      this->_nbLife << this->_bomberman->_infoGame["nbLife"];
      text = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 1]);
      if (text == 0)
	throw BombermanException("dynamic cast fail");
      text->setText(this->_nbLife.str());
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionGameArcadeScene::downLife()
{
  try
    {
      GDLText	*text;
      
      if (this->_bomberman->_infoGame["nbLife"] >= 1)
	this->_bomberman->_infoGame["nbLife"] -= 1;
      this->_nbLife.str(std::string());
      this->_nbLife << this->_bomberman->_infoGame["nbLife"];
      text = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 1]);
      if (text == 0)
	throw BombermanException("dynamic cast fail");
      text->setText(this->_nbLife.str());
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionGameArcadeScene::azerty()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;

      Bomberman::isAzerty = true;
      button1 = dynamic_cast<GDLButton *>(this->_objects[1]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[2]);
      if (button1 == 0 || button2 == 0)
        throw BombermanException("dynamic cast fail");
      button1->setHover("medias/buttons/azerty_active.png");
      button1->setSurvol("medias/buttons/azerty_active.png");
      button2->setHover("medias/buttons/qwerty.png");
      button2->setSurvol("medias/buttons/qwerty_hover.png");      
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionGameArcadeScene::qwerty()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;

      Bomberman::isAzerty = false;
      button1 = dynamic_cast<GDLButton *>(this->_objects[1]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[2]);
      if (button1 == 0 || button2 == 0)
        throw BombermanException("dynamic cast fail");
      button1->setHover("medias/buttons/azerty.png");
      button1->setSurvol("medias/buttons/azerty_hover.png");
      button2->setHover("medias/buttons/qwerty_active.png");
      button2->setSurvol("medias/buttons/qwerty_active.png");      
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}
