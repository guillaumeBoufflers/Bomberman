#include		"CreditsScene.hh"

CreditsScene::CreditsScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera) {
}

CreditsScene::~CreditsScene() {

}

void 		CreditsScene::initializeCamera() {
  if (this->_camera)
    this->_camera->initialize2d();
}

void 		CreditsScene::initActionPtrs() {
  this->_actions[CREDITS_NOTHING] = NULL;
  this->_actions[CREDITS_BACK] = &CreditsScene::back;
}

void		CreditsScene::initialize() {
  this->initActionPtrs();

  /* On push des datas dans le modele du menu */
  /* La méthode initialize de l'objet est appellée lors du push dans le modele */
  this->_objects.push_back(new GDLBackground("medias/images/background_credit.png", 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_credits.png", "medias/buttons/back_button_credits_hover.png", "medias/buttons/back_button_credits_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH - 100, W_HEIGHT - 50, 110, 62, CREDITS_NOTHING, CREDITS_BACK, 0));

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		CreditsScene::update() {
  int	action;

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != CREDITS_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		CreditsScene::draw() {
  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		CreditsScene::back()
{
  this->_bomberman->setScene(Bomberman::MENU);
}
