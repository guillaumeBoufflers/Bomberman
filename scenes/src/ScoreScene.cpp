#include		"ScoreScene.hh"
#include		"Score.hh"

ScoreScene::ScoreScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera) {
}

ScoreScene::~ScoreScene()
{

}

void 		ScoreScene::initializeCamera() {
  if (this->_camera)
    this->_camera->initialize2d();
}

void 		ScoreScene::initActionPtrs() {
  this->_actions[SCORE_NOTHING] = NULL;
  this->_actions[SCORE_MENU] = &ScoreScene::menu;
}

void		ScoreScene::initialize() {

  std::string   buffer;
  int		i = 0;

  this->initActionPtrs();
  
  Score::deleteInstance();
  this->_allScore = Score::getInstance()->getScore();
  this->_score = "";
  /* On push des datas dans le modele du menu */
  this->_objects.push_back(new GDLBackground("medias/images/backgroundScore.png", 1));
  /* La méthode initialize de l'objet est appellée lors du push dans le modele */
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_credits.png", "medias/buttons/back_button_credits_hover.png", "medias/buttons/back_button_credits_hover.png", GDLButton::GDL_BUTTON_RECT, 100, W_HEIGHT - 50, 110, 62, SCORE_NOTHING, SCORE_MENU, 1));
  for (std::vector<std::string>::iterator it = this->_allScore.begin(); it != this->_allScore.end(); ++it)
    {
      this->_score  += (*it) + "\n";
      if (i == 4)
  	break;
      i++;
    }
  this->_objects.push_back(new GDLText(this->_score, SCORE_NOTHING, 250, 350, 60, 255, 255, 255));
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

/* =====================================
 *           UPDATE DE LA VUE
 * =====================================
 */

void		ScoreScene::update() {

  try 
    {
      int		i = 0;
      int		action;

      for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
	if ((action = (*it)->update()) != SCORE_NOTHING && this->_actions[action])
	  (this->*_actions[action])();
      this->_allScore = Score::getInstance()->getScore();
      this->_score = "";
      for (std::vector<std::string>::iterator it = this->_allScore.begin(); it != this->_allScore.end(); ++it)
	{
	  this->_score  += (*it) + "\n";
	  if (i == 4)
	    break;
	  i++;
	}
      this->_scoreText = dynamic_cast<GDLText *>(this->_objects[this->_objects.size() - 1]);
      if (_scoreText == 0)
	throw BombermanException("dynamic cast fail");
      this->_scoreText->setText(this->_score);
      SoundController::getInstance()->update();
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		ScoreScene::draw() {
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		ScoreScene::menu()
{
  this->initializeCamera();
  this->_bomberman->setScene(Bomberman::MENU);
}
