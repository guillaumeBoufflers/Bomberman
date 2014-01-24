#include		"DrawScene.hh"

DrawScene::DrawScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera) {
}

DrawScene::~DrawScene()
{

}

void 		DrawScene::initializeCamera() {
  if (this->_camera)
    this->_camera->initialize2d();
}

void 		DrawScene::initActionPtrs() {
  this->_actions[DRAW_NOTHING] = NULL;
  this->_actions[DRAW_SCORE] = &DrawScene::score;
  this->_actions[DRAW_NEXT] = &DrawScene::next;
}

void		DrawScene::initialize() {
  this->initActionPtrs();

  /* On push des datas dans le modele du menu */
  /* La méthode initialize de l'objet est appellée lors du push dans le modele */
  this->_objects.push_back(new GDLBackground("medias/images/backgroundDraw.png", 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/view_scores_draw_button.png", "medias/buttons/view_scores_draw_button_hover.png", "medias/buttons/view_scores_draw_button_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH - 200, W_HEIGHT - 50, 281, 62, DRAW_NOTHING, DRAW_SCORE, 0));

  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_credits.png", "medias/buttons/back_button_credits_hover.png", "medias/buttons/back_button_credits_hover.png", GDLButton::GDL_BUTTON_RECT, 100, W_HEIGHT - 50, 110, 62, DRAW_NOTHING, DRAW_NEXT, 0));

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		DrawScene::update() {
  int	action;

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != DRAW_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		DrawScene::draw() {
  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		DrawScene::score()
{
  this->_bomberman->setScene(Bomberman::SCORES);
}

void		DrawScene::next()
{
  this->_bomberman->setScene(Bomberman::MENU);
}
