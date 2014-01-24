#include	"OptionSoundScene.hh"


OptionSoundScene::OptionSoundScene(Bomberman *bomberman, KeyController *controller, CameraView *camera) : _bomberman(bomberman), _keyController(controller), _camera(camera)
{
}

OptionSoundScene::~OptionSoundScene()
{

}

void	OptionSoundScene::initActionPtrs()
{
  this->_actions[OPTION_SOUND_NOTHING] = NULL;
  this->_actions[OPTION_SOUND_ON_FX] = &OptionSoundScene::soundOnFx;
  this->_actions[OPTION_SOUND_OFF_FX] = &OptionSoundScene::soundOffFx;
  this->_actions[OPTION_SOUND_ON_MUSIC] = &OptionSoundScene::soundOnMusic;
  this->_actions[OPTION_SOUND_OFF_MUSIC] = &OptionSoundScene::soundOffMusic;
  this->_actions[OPTION_SOUND_BACK] = &OptionSoundScene::back;
}

void		OptionSoundScene::update()
{
  int	action;
  
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    if ((action = (*it)->update()) != OPTION_SOUND_NOTHING && this->_actions[action])
      (this->*_actions[action])();
  SoundController::getInstance()->update();
}

void		OptionSoundScene::draw()
{
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->draw();
}

void		OptionSoundScene::initialize()
{
  this->initActionPtrs();
  this->_objects.push_back(new GDLBackground("medias/images/backgroundOptionSound.png", 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/on_button_active.png", "medias/buttons/on_button_active.png", "medias/buttons/on_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3, 435, 89, 62, OPTION_SOUND_NOTHING, OPTION_SOUND_ON_FX, 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/off_button.png", "medias/buttons/off_button_hover.png", "medias/buttons/off_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 * 1.5, 435, 118, 62, OPTION_SOUND_NOTHING, OPTION_SOUND_OFF_FX, 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/on_button_active.png", "medias/buttons/on_button_active.png", "medias/buttons/on_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3, 590, 89, 62, OPTION_SOUND_NOTHING, OPTION_SOUND_ON_MUSIC, 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/off_button.png", "medias/buttons/off_button_hover.png", "medias/buttons/off_button_active.png", GDLButton::GDL_BUTTON_RECT, W_WIDTH / 3 * 1.5, 590, 118, 62, OPTION_SOUND_NOTHING, OPTION_SOUND_OFF_MUSIC, 0));
  this->_objects.push_back(new GDLButton(this->_keyController, "medias/buttons/back_button_sound.png", "medias/buttons/back_button_sound_hover.png", "medias/buttons/back_button_sound_hover.png", GDLButton::GDL_BUTTON_RECT, 80, W_HEIGHT - 50, 110, 62, OPTION_SOUND_NOTHING, OPTION_SOUND_BACK, 0));
  for (std::vector<IGDLObject *>::iterator it = this->_objects.begin(); it != this->_objects.end(); ++it)
    (*it)->initialize();
}

void		OptionSoundScene::initializeCamera()
{
  if (this->_camera)
    this->_camera->initialize2d();
}

void		OptionSoundScene::soundOnFx()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;

      SoundController::getInstance()->setVolumeFx(100);  
      button1 = dynamic_cast<GDLButton *>(this->_objects[1]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[2]);
      if (button1 == 0 || button2 == 0)
	throw BombermanException("dynamic cast fail");
      button1->setHover("medias/buttons/on_button_active.png");
      button1->setSurvol("medias/buttons/on_button_active.png");
      button2->setHover("medias/buttons/off_button.png");
      button2->setSurvol("medias/buttons/off_button_hover.png");
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionSoundScene::soundOffFx()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;

      SoundController::getInstance()->setVolumeFx(0);  
      button1 = dynamic_cast<GDLButton *>(this->_objects[2]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[1]);
      if (button1 == 0 || button2 == 0)
	throw BombermanException("dynamic cast fail");
      button1->setHover("medias/buttons/off_button_active.png");
      button1->setSurvol("medias/buttons/off_button_active.png");
      button2->setHover("medias/buttons/on_button.png");
      button2->setSurvol("medias/buttons/on_button_hover.png");
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}


void		OptionSoundScene::soundOnMusic()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;

      SoundController::getInstance()->setVolumeMusic(100);  
      button1 = dynamic_cast<GDLButton *>(this->_objects[3]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[4]);
      if (button1 == 0 || button2 == 0)
	throw BombermanException("dynamic cast fail");
      button1->setHover("medias/buttons/on_button_active.png");
      button1->setSurvol("medias/buttons/on_button_active.png");
      button2->setHover("medias/buttons/off_button.png");
      button2->setSurvol("medias/buttons/off_button_hover.png");
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionSoundScene::soundOffMusic()
{
  try
    {
      GDLButton	*button1;
      GDLButton	*button2;

      SoundController::getInstance()->setVolumeMusic(0);  
      button1 = dynamic_cast<GDLButton *>(this->_objects[4]);
      button2 = dynamic_cast<GDLButton *>(this->_objects[3]);
      if (button1 == 0 || button2 == 0)
	throw BombermanException("dynamic cast fail");
      button1->setHover("medias/buttons/off_button_active.png");
      button1->setSurvol("medias/buttons/off_button_active.png");
      button2->setHover("medias/buttons/on_button.png");
      button2->setSurvol("medias/buttons/on_button_hover.png");
    }
  catch (const std::exception &e)
    {
      throw BombermanException("dynamic cast fail");
    }
}

void		OptionSoundScene::back()
{
  this->_bomberman->setScene(Bomberman::GENERAL_OPTIONS);
}
