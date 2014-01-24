#include		"IaWinScene.hh"

IaWinScene::IaWinScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera) {
}

IaWinScene::~IaWinScene()
{

}

void 		IaWinScene::initializeCamera() {
  if (this->_camera)
    this->_camera->initialize2d();
}

void 		IaWinScene::initActionPtrs() {
  this->_actions[IA_WIN_NOTHING] = NULL;
  this->_actions[IA_WIN_SCORE] = &IaWinScene::score;
  this->_actions[IA_WIN_NEXT] = &IaWinScene::next;
}

void		IaWinScene::initialize() {
  this->initActionPtrs();

  /* On push des datas dans le modele du menu */
  /* La méthode initialize de l'objet est appellée lors du push dans le modele */
  this->_objects.push_back(new GDLBackground("medias/images/backgroundIa.png", 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/view_scores_button.png", "medias/buttons/view_scores_button_hover.png", "medias/buttons/view_scores_button_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 2, W_HEIGHT / 2 + 100, 559, 123, IA_WIN_NOTHING, IA_WIN_SCORE, 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_credits.png", "medias/buttons/back_button_credits_hover.png", "medias/buttons/back_button_credits_hover.png", GDLButton::GDL_BUTTON_RECT, 100, W_HEIGHT - 50, 110, 62, IA_WIN_NOTHING, IA_WIN_NEXT, 0));

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		IaWinScene::update() {
  int	action;

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != IA_WIN_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		IaWinScene::draw() {
  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		IaWinScene::score()
{
  this->_bomberman->setScene(Bomberman::SCORES);
}

void		IaWinScene::next()
{
  this->_bomberman->setScene(Bomberman::MENU);
}
