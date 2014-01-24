#include		"LoadingScene.hh"

LoadingScene::LoadingScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera) {
}

LoadingScene::~LoadingScene() {

}

void 		LoadingScene::initializeCamera() {
  if (this->_camera)
    this->_camera->initialize2d();
}

void 		LoadingScene::initActionPtrs() {
}

void		LoadingScene::initialize() {
  this->initActionPtrs();

  /* On push des datas dans le modele du menu */
  /* La méthode initialize de l'objet est appellée lors du push dans le modele */
  this->_objects.push_back(new GDLBackground("medias/images/backgroundLoading.png", 0));
  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		LoadingScene::update() {
  int	action;

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != LOADING_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		LoadingScene::draw() {
  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}
