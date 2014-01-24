#include 					"MainMenuScene.hh"

MainMenuScene::MainMenuScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera) {
}

MainMenuScene::~MainMenuScene() {

}

void 		MainMenuScene::initializeCamera() {
	if (this->_camera)
		this->_camera->initialize2d();
}

void 		MainMenuScene::initActionPtrs() {
	this->_actions[MAIN_MENU_NOTHING] = NULL;
	this->_actions[MAIN_MENU_PLAY] = &MainMenuScene::play;
	this->_actions[MAIN_MENU_OPTIONS] = &MainMenuScene::options;
	this->_actions[MAIN_MENU_CREDITS] = &MainMenuScene::credits;
	this->_actions[MAIN_MENU_SCORE] = &MainMenuScene::score;
	this->_actions[MAIN_MENU_QUIT] = &MainMenuScene::quit;
}

void		MainMenuScene::initialize() {
	this->initActionPtrs();

	/* On push des datas dans le modele du menu */
	/* La méthode initialize de l'objet est appellée lors du push dans le modele */
	this->_objects.push_back(new GDLBackground("medias/images/Background.png", 0));
	this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/play_button.png", "medias/buttons/play_button_hover.png", "medias/buttons/play_button_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH - 200, 250, 122, 84, MAIN_MENU_NOTHING, MAIN_MENU_PLAY, 0));
	this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/options_button.png", "medias/buttons/options_button_hover.png", "medias/buttons/options_button_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH - 200, 350, 214, 81, MAIN_MENU_NOTHING, MAIN_MENU_OPTIONS, 0));
	this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/quit_button.png", "medias/buttons/quit_button_hover.png", "medias/buttons/quit_button_hover.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH - 200, 450, 123, 78, MAIN_MENU_NOTHING, MAIN_MENU_QUIT, 0));
	this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/scores_button.png", "medias/buttons/scores_button_hover.png", "medias/buttons/scores_button_hover.png", GDLButton::GDL_BUTTON_RECT, 200, 450, 195, 78, MAIN_MENU_NOTHING, MAIN_MENU_SCORE, 0));
	this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/credits_button.png", "medias/buttons/credits_button_hover.png", "medias/buttons/credits_button_hover.png", GDLButton::GDL_BUTTON_RECT, 200, 550, 213, 78, MAIN_MENU_NOTHING, MAIN_MENU_CREDITS, 0));
	for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
		(*it)->initialize();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		MainMenuScene::update() {
	int	action;

	for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
		if ((action = (*it)->update()) != MAIN_MENU_NOTHING && this->_actions[action])
			(this->*_actions[action])();
	SoundController::getInstance()->update();
}

void		MainMenuScene::draw() {
	for (std::list<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
		(*it)->draw();
}

/* ====================================
 *              ACTIONS
 * ====================================
 */

void 		MainMenuScene::play() {
	this->_bomberman->setScene(Bomberman::GAME_OPTIONS);
}

void		MainMenuScene::options() {
	this->_bomberman->setScene(Bomberman::GENERAL_OPTIONS);
}

void 		MainMenuScene::quit() {
	this->_bomberman->closeWindow();
}

void		MainMenuScene::credits()
{
  this->_bomberman->setScene(Bomberman::CREDITS);
}


void		MainMenuScene::score()
{
  this->_bomberman->setScene(Bomberman::SCORES);
}
