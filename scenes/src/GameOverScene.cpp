#include	"GameOverScene.hh"


GameOverScene::GameOverScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera)
{
}

GameOverScene::~GameOverScene()
{

}

void	GameOverScene::initActionPtrs()
{
  this->_actions[GAME_OVER_NOTHING] = NULL;
  this->_actions[GAME_OVER_BACK] = &GameOverScene::back;
}

void		GameOverScene::update()
{
  int	action;
  
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != GAME_OVER_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		GameOverScene::draw()
{
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		GameOverScene::initialize()
{
  this->initActionPtrs();
  this->_objects.push_back(new GDLBackground("medias/images/background_gameover.png", 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_option.png", "medias/buttons/back_button_option_hover.png", "medias/buttons/back_button_option_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH - 150, W_HEIGHT - 100, 110, 62, GAME_OVER_NOTHING, GAME_OVER_BACK, 0));
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

void		GameOverScene::initializeCamera()
{
  if (this->_camera)
    this->_camera->initialize2d();
}

void		GameOverScene::back()
{
  this->_bomberman->setScene(Bomberman::MENU);
}
