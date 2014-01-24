
#include		"PauseScene.hh"

PauseScene::PauseScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera) {
}

PauseScene::~PauseScene() {

}

void 		PauseScene::initializeCamera() {
  if (this->_camera)
    this->_camera->initialize2d();
}

void 		PauseScene::initActionPtrs() {
  this->_actions[PAUSE_NOTHING] = NULL;
  this->_actions[PAUSE_MENU] = &PauseScene::menu;
  this->_actions[PAUSE_SAVE] = &PauseScene::save;
  this->_actions[PAUSE_RESUME] = &PauseScene::resume;
}

void		PauseScene::initialize() {
  this->initActionPtrs();

  /* On push des datas dans le modele du menu */
  /* La méthode initialize de l'objet est appellée lors du push dans le modele */
  this->_objects.push_back(new GDLBackground("medias/images/backgroundPause.png", 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/quit_button_pause.png", "medias/buttons/quit_button_hover_pause.png", "medias/buttons/quit_button_hover_pause.png", GDLButton::GDL_BUTTON_RECT,300, W_HEIGHT - 100, 131, 84, PAUSE_NOTHING, PAUSE_MENU, 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/resume_game_button.png", "medias/buttons/resume_game_button_hover.png", "medias/buttons/resume_game_button_hover.png", GDLButton::GDL_BUTTON_RECT,300, W_HEIGHT / 2, 415, 88, PAUSE_NOTHING, PAUSE_RESUME, 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/save_exit_button.png", "medias/buttons/save_exit_button_hover.png", "medias/buttons/save_exit_button_hover.png", GDLButton::GDL_BUTTON_RECT,300, W_HEIGHT / 2 + 200 , 372, 87, PAUSE_NOTHING, PAUSE_SAVE, 0));
  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		PauseScene::update() {
  int	action;

  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != PAUSE_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		PauseScene::draw() {
  for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		PauseScene::menu()
{
  this->_bomberman->setScene(Bomberman::MENU);
}

void		PauseScene::save()
{
  char  *cfile;
  std::string tmp;

  cfile = BUtils::saveFileDialog("Please choose a file to save your game :");
  if (cfile) {
    Serialize   *serialiser = new Serialize();
    serialiser->serialize(GameScene::_map, GameScene::_alivePlayers, GameScene::_deadPlayers, cfile);
    this->_bomberman->setScene(Bomberman::MENU);

  } else {
    BUtils::runDialog(GTK_MESSAGE_WARNING, "You haven't choose a file.");
  }

}

void		PauseScene::resume()
{
  this->_bomberman->setScene(Bomberman::GAME);
}
