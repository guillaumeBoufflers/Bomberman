#include		"PlayerOneWinScene.hh"

PlayerOneWinScene::PlayerOneWinScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera) {
}

PlayerOneWinScene::~PlayerOneWinScene()
{

}

void 		PlayerOneWinScene::initializeCamera() {
  if (this->_camera)
    this->_camera->initialize2d();
}

void 		PlayerOneWinScene::initActionPtrs() {
  this->_actions[PLAYER_ONE_WIN_NOTHING] = NULL;
  this->_actions[PLAYER_ONE_WIN_SCORE] = &PlayerOneWinScene::score;
  this->_actions[PLAYER_ONE_WIN_NEXT] = &PlayerOneWinScene::next;
}

void		PlayerOneWinScene::initialize() {
  this->initActionPtrs();

  /* On push des datas dans le modele du menu */
  /* La méthode initialize de l'objet est appellée lors du push dans le modele */
  this->_objects.push_back(new GDLBackground("medias/images/backgroundPlayerOne.png", 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/view_scores_button.png", "medias/buttons/view_scores_button_hover.png", "medias/buttons/view_scores_button_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 2, W_HEIGHT / 2 + 100, 559, 123, PLAYER_ONE_WIN_NOTHING, PLAYER_ONE_WIN_SCORE, 0));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_credits.png", "medias/buttons/back_button_credits_hover.png", "medias/buttons/back_button_credits_hover.png", GDLButton::GDL_BUTTON_RECT, 100, W_HEIGHT - 50, 110, 62, PLAYER_ONE_WIN_NOTHING, PLAYER_ONE_WIN_NEXT, 0));

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		PlayerOneWinScene::update() {
  int	action;

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != PLAYER_ONE_WIN_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		PlayerOneWinScene::draw() {
  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		PlayerOneWinScene::score()
{
  this->_bomberman->setScene(Bomberman::SCORES);
}

void		PlayerOneWinScene::next()
{
  this->_bomberman->setScene(Bomberman::MENU);
}
