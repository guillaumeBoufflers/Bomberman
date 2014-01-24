#include	"GeneralOptionScene.hh"


GeneralOptionScene::GeneralOptionScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera)
{
}

GeneralOptionScene::~GeneralOptionScene()
{

}

void	GeneralOptionScene::initActionPtrs()
{
  this->_actions[GENERAL_OPTION_NOTHING] = NULL;
  this->_actions[GENERAL_OPTION_BACK] = &GeneralOptionScene::back;
  this->_actions[GENERAL_OPTION_GAME] = &GeneralOptionScene::game;
  this->_actions[GENERAL_OPTION_SOUND] = &GeneralOptionScene::sound;
}

void		GeneralOptionScene::update()
{
  int	action;
  
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != GENERAL_OPTION_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		GeneralOptionScene::draw()
{
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		GeneralOptionScene::initialize()
{
  this->initActionPtrs();
  this->_objects.push_back(new GDLBackground("medias/images/background_options.png", 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/game_button.png", "medias/buttons/game_button_hover.png", "medias/buttons/game_button_hover.png", GDLButton::GDL_BUTTON_RECT, (W_WIDTH / 3) + 50, 450, 234, 112, GENERAL_OPTION_NOTHING, GENERAL_OPTION_GAME, 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/sound_button.png", "medias/buttons/sound_button_hover.png", "medias/buttons/sound_button_hover.png", GDLButton::GDL_BUTTON_RECT, (W_WIDTH / 3) + 50, 650, 271, 111, GENERAL_OPTION_NOTHING, GENERAL_OPTION_SOUND, 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_option.png", "medias/buttons/back_button_option_hover.png", "medias/buttons/back_button_option_hover.png", GDLButton::GDL_BUTTON_RECT, 80, W_HEIGHT - 50, 110, 62, GENERAL_OPTION_NOTHING, GENERAL_OPTION_BACK, 0));
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

void		GeneralOptionScene::initializeCamera()
{
  if (this->_camera)
    this->_camera->initialize2d();
}

void		GeneralOptionScene::back()
{
  this->_bomberman->setScene(Bomberman::MENU);
}

void		GeneralOptionScene::game()
{
  this->_bomberman->setScene(Bomberman::OPTION_GAME);
}

void		GeneralOptionScene::sound()
{
  this->_bomberman->setScene(Bomberman::OPTION_SOUND);
}
