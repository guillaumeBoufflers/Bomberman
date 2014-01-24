#include		"IntroScene.hh"

IntroScene::IntroScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera), _update(0), _nbScene(0) {
}

IntroScene::~IntroScene() {

}

void 		IntroScene::initializeCamera() {
  if (this->_camera)
    this->_camera->initialize2d();
}

void 		IntroScene::initActionPtrs() {
}

void		IntroScene::initialize() {
  this->initActionPtrs();

  /* On push des datas dans le modele du menu */
  /* La méthode initialize de l'objet est appellée lors du push dans le modele */
  this->_objects = new GDLBackground("medias/images/sprite1.png", 0);
  this->_images.push_back("medias/images/vid1.png");
  this->_images.push_back("medias/images/vid2.png");
  this->_images.push_back("medias/images/vid3.png");
  this->_images.push_back("medias/images/vid4.png");
  this->_images.push_back("medias/images/vid5.png");
  this->_images.push_back("medias/images/vid6.png");
  this->_images.push_back("medias/images/final.png");
  this->_images.push_back("medias/images/final.png");
  this->_objects->initialize();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		IntroScene::update() {
  this->_objects->update();
  this->_update += 1;
  SoundController::getInstance()->update();
  if (this->_update == 50)
    {
      this->_objects->setBackground(this->_images[this->_nbScene]);
      this->_nbScene += 1;
      this->_update = 0;
      if (this->_nbScene == 8)
	this->_bomberman->setScene(Bomberman::MENU);
    }
}

void		IntroScene::draw() {
  this->_objects->draw();
}
