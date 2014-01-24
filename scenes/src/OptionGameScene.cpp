#include	"OptionGameScene.hh"

OptionGameScene::OptionGameScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera)
{
}

OptionGameScene::~OptionGameScene()
{

}

void	OptionGameScene::initActionPtrs()
{
  this->_actions[OPTION_GAME_NOTHING] = NULL;
  this->_actions[OPTION_GAME_BACK] = &OptionGameScene::back;
  this->_actions[OPTION_GAME_ARCADE] = &OptionGameScene::arcade;
  this->_actions[OPTION_GAME_AZERTY] = &OptionGameScene::azerty;
  this->_actions[OPTION_GAME_QWERTY] = &OptionGameScene::qwerty;
  this->_actions[OPTION_GAME_ARMAGEDDON] = &OptionGameScene::armageddon;
}

void		OptionGameScene::update()
{
  int	action;

  Bomberman::isArmageddon = 4;
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != OPTION_GAME_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		OptionGameScene::draw()
{
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		OptionGameScene::initialize()
{
  this->initActionPtrs();
  this->_bomberman->_infoGame["nbBombs"] = 1;
  this->_bomberman->_infoGame["rangeBombs"] = 1;
  this->_bomberman->_infoGame["nbLife"] = 0;
  this->_objects.push_back(new GDLBackground("medias/images/backgroundOptionGame.png", 1));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/azerty_active.png", "medias/buttons/azerty_active.png", "medias/buttons/azerty_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3, 350, 233, 64, OPTION_GAME_NOTHING, OPTION_GAME_AZERTY, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/qwerty.png", "medias/buttons/qwerty_hover.png", "medias/buttons/qwerty_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 * 2, 350,255, 64, OPTION_GAME_NOTHING, OPTION_GAME_QWERTY, 1));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/classic_mode_button_active.png", "medias/buttons/classic_mode_button_active.png", "medias/buttons/classic_mode_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 - 200, 450, 378, 78, OPTION_GAME_NOTHING, OPTION_GAME_NOTHING, 1));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/carnage_button.png", "medias/buttons/carnage_button_hover.png", "medias/buttons/carnage_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 2, 450, 241, 81, OPTION_GAME_NOTHING, OPTION_GAME_ARMAGEDDON, 1));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/arcade_mode_button.png", "medias/buttons/arcade_mode_button_hover.png", "medias/buttons/arcade_mode_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 * 2 + 200, 450, 397, 79, OPTION_GAME_NOTHING, OPTION_GAME_ARCADE, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/nb_bomb_text.png", "medias/buttons/nb_bomb_text.png", "medias/buttons/nb_bomb_text.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 - 100, 600, 232, 62, OPTION_GAME_NOTHING, OPTION_GAME_NOTHING, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/range_bomb_text.png", "medias/buttons/range_bomb_text.png", "medias/buttons/range_bomb_text.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 - 100, 700, 284, 62, OPTION_GAME_NOTHING, OPTION_GAME_NOTHING, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/nb_lifes_text.png", "medias/buttons/nb_lifes_text.png", "medias/buttons/nb_lifes_text.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 - 100 , 800, 200, 62, OPTION_GAME_NOTHING, OPTION_GAME_NOTHING, 1));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_sound.png", "medias/buttons/back_button_sound_hover.png", "medias/buttons/back_button_sound_hover.png", GDLButton::GDL_BUTTON_RECT, 80, W_HEIGHT - 50, 110, 62, OPTION_GAME_NOTHING, OPTION_GAME_BACK, 1));
  this->_objects.push_back(new GDLText("1", OPTION_GAME_NOTHING, 500, 565, 60, 255, 255, 255));
  this->_objects.push_back(new GDLText("1", OPTION_GAME_NOTHING, 500, 665, 60, 255, 255, 255));
  this->_objects.push_back(new GDLText("0", OPTION_GAME_NOTHING, 500, 765, 60, 255, 255, 255));

  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

void		OptionGameScene::initializeCamera()
{
  if (this->_camera)
    this->_camera->initialize2d();
}

void		OptionGameScene::back()
{
  this->initializeCamera();
  this->_bomberman->setScene(Bomberman::GENERAL_OPTIONS);
}


void		OptionGameScene::arcade()
{
  this->_bomberman->setScene(Bomberman::OPTION_GAME_ARCADE);
}

void		OptionGameScene::armageddon()
{
  this->_bomberman->setScene(Bomberman::OPTION_GAME_ARMAGEDDON);
}

void		OptionGameScene::azerty()
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

void		OptionGameScene::qwerty()
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
