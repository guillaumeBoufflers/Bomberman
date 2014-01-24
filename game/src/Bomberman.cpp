#include	"Bomberman.hh"

bool		Bomberman::isAzerty;
int		Bomberman::isArmageddon;

Bomberman::Bomberman()
{
  this->_infoGame["nbPlayers"] = 1;
  this->_infoGame["nbIa"] = 0;
  this->_infoGame["nbBombs"] = 1;
  this->_infoGame["rangeBombs"] = 1;
  this->_infoGame["difficult"] = MEDIUM;
  this->_infoGame["nbLife"] = 0;
  isAzerty = true;
  Bomberman::isArmageddon = 4;
}

Bomberman::~Bomberman()
{

}

void		Bomberman::initialize() {
	this->window_.setWidth(W_WIDTH);
	this->window_.setHeight(W_HEIGHT);
	this->window_.setTitle(W_TITLE);
	this->window_.create();

	/* On crée le gestionnaire de touches*/
	this->_keyController = KeyController::getInstance(&this->input_);

	/* On crée le gestionnaire de son et on lance la musique */
	SoundController *sound = SoundController::getInstance();
	sound->initialize();

	/* On crée le gestionnaire de l'horloge du jeu */
	Clock::getInstance(&this->gameClock_);

	/* On crée la caméra */
	this->_camera = new CameraView();

	this->_scenes[INTRO] = new IntroScene(this, this->_keyController, this->_camera);
	this->_scenes[INTRO]->initialize();

	this->_scenes[MENU] = new MainMenuScene(this, this->_keyController, this->_camera);
	this->_scenes[MENU]->initialize();

	this->_scenes[GENERAL_OPTIONS] = new GeneralOptionScene(this, this->_keyController, this->_camera);
	this->_scenes[GENERAL_OPTIONS]->initialize();

	this->_scenes[GAME_OPTIONS] = new GameOptionScene(this, this->_keyController, this->_camera);
	this->_scenes[GAME_OPTIONS]->initialize();

	this->_scenes[GAME] = NULL;

	this->_scenes[CREDITS] = new CreditsScene(this, this->_keyController, this->_camera);
	this->_scenes[CREDITS]->initialize();

	this->_scenes[OPTION_SOUND] = new OptionSoundScene(this, this->_keyController, this->_camera);
	this->_scenes[OPTION_SOUND]->initialize();

	this->_scenes[OPTION_GAME] = new OptionGameScene(this, this->_keyController, this->_camera);
	this->_scenes[OPTION_GAME]->initialize();

	this->_scenes[OPTION_GAME_ARCADE] = new OptionGameArcadeScene(this, this->_keyController, this->_camera);
	this->_scenes[OPTION_GAME_ARCADE]->initialize();
	
	this->_scenes[OPTION_GAME_ARMAGEDDON] = new OptionArmageddonScene(this, this->_keyController, this->_camera);
	this->_scenes[OPTION_GAME_ARMAGEDDON]->initialize();

	this->_scenes[PLAYER_ONE] = new PlayerOneWinScene(this, this->_keyController, this->_camera);
	this->_scenes[PLAYER_ONE]->initialize();

	this->_scenes[PLAYER_TWO] = new PlayerTwoWinScene(this, this->_keyController, this->_camera);
	this->_scenes[PLAYER_TWO]->initialize();

	this->_scenes[SCORES] = new ScoreScene(this, this->_keyController, this->_camera);
	this->_scenes[SCORES]->initialize();

	this->_scenes[IA] = new IaWinScene(this, this->_keyController, this->_camera);
	this->_scenes[IA]->initialize();

	this->_scenes[DRAW] = new DrawScene(this, this->_keyController, this->_camera);
	this->_scenes[DRAW]->initialize();

	this->_scenes[PAUSE] = new PauseScene(this, this->_keyController, this->_camera);
	this->_scenes[PAUSE]->initialize();

	/* On set la scene par défaut */
	this->setScene(INTRO);
}

void 		Bomberman::setScene(Bomberman::Scenes scene) {
	if (scene >= 0 && scene < NB_SCENES && this->_scenes[scene]) {
	  this->_scenes[scene]->initializeCamera();
	  this->_scene = scene;

	  if (scene != GAME && scene != PAUSE) {
	  	SoundController::getInstance()->setInGame(false);
	  } else {
	  	SoundController::getInstance()->setInGame(true);
	  }
	} else {
		throw new BombermanException("Invalid scene set.");
	}
}

void 		Bomberman::startNewGame(const std::string &mapFile) {
	GameScene *ptr;

	if (this->_scenes[GAME])
		delete this->_scenes[GAME];
	ptr = new GameScene(this, this->_keyController, this->_camera);
	ptr->initializeGame(mapFile, this->_infoGame);
	this->_scenes[GAME] = ptr;
	this->_scenes[GAME]->initialize();
	this->setScene(GAME);
}

void 		Bomberman::loadGame() {
	GameScene *ptr;
  	char  *cfile;
  	std::string tmp;

  	cfile = BUtils::openFileDialog("Please choose your saved game");
  	if (cfile) {
  		tmp = cfile;
  		std::ifstream filestream(cfile, std::ifstream::in);
  		if (filestream && BUtils::checkMd5(tmp)) {
			if (this->_scenes[GAME])
				delete this->_scenes[GAME];
			ptr = new GameScene(this, this->_keyController, this->_camera);
			ptr->loadGame(tmp);
			this->_scenes[GAME] = ptr;
			this->_scenes[GAME]->initialize();
			this->setScene(GAME);

  		} else {
  			BUtils::runDialog(GTK_MESSAGE_ERROR, "The map file cannot be opened or is invalid.");
  		}
  	} else {
  		BUtils::runDialog(GTK_MESSAGE_WARNING, "You haven't chosen a file.");
  	}
}

void 		Bomberman::closeWindow() {
	this->window_.close();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		Bomberman::update() {
	this->_scenes[this->_scene]->update();
}

void		Bomberman::draw() {
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->_scenes[this->_scene]->draw();
	usleep(FPS / (this->gameClock_.getElapsedTime()));
}

void		Bomberman::unload() {
	/* On détruit le SoundManager */
	SoundController *sound = SoundController::getInstance();
	delete sound;
}
