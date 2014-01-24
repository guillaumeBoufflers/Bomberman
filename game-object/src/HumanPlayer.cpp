#include	"HumanPlayer.hh"
#include	"GameScene.hh"
#include  "Bomberman.hh"

HumanPlayer::HumanPlayer(int x, int y, int scale, int angle, std::string &mesh, ObjectType type, int id, int life, int range, int start) : APlayer(x, y, scale, angle, mesh, type, id, life, range, start)
{
  if (id == 0)
    {
      if (Bomberman::isAzerty == true)
       this->assignKeys(this->_ctrlP, gdl::Keys::Z, gdl::Keys::S, gdl::Keys::D, gdl::Keys::Q, gdl::Keys::Space, gdl::Keys::E, gdl::Keys::A, gdl::Keys::LShift);
      else
       this->assignKeys(this->_ctrlP, gdl::Keys::W, gdl::Keys::S, gdl::Keys::D, gdl::Keys::A, gdl::Keys::Space, gdl::Keys::E, gdl::Keys::Q, gdl::Keys::LShift);
      GameScene::p1Alive = true;
    }
  else
    {
      this->assignKeys(this->_ctrlP, gdl::Keys::Numpad8, gdl::Keys::Numpad5, gdl::Keys::Numpad6, gdl::Keys::Numpad4, gdl::Keys::Numpad0, gdl::Keys::Numpad9, gdl::Keys::Numpad7, gdl::Keys::Add);
      GameScene::p2Alive = true;
    }
  this->_keyController = KeyController::getInstance();
  if (!id)
    this->_helmet = gdl::Model::load("medias/models/helmet1.fbx");
  else
    this->_helmet = gdl::Model::load("medias/models/helmet2.fbx");
}

HumanPlayer::HumanPlayer(TiXmlAttribute **attr) : APlayer(attr)
{
  if (this->_id == 0)
    {
      if (Bomberman::isAzerty == true)
       this->assignKeys(this->_ctrlP, gdl::Keys::Z, gdl::Keys::S, gdl::Keys::D, gdl::Keys::Q, gdl::Keys::Space, gdl::Keys::E, gdl::Keys::A, gdl::Keys::LShift);
      else
       this->assignKeys(this->_ctrlP, gdl::Keys::W, gdl::Keys::S, gdl::Keys::D, gdl::Keys::A, gdl::Keys::Space, gdl::Keys::E, gdl::Keys::Q, gdl::Keys::LShift);
      GameScene::p1Alive = true;
    }
  else
    {
      this->assignKeys(this->_ctrlP, gdl::Keys::Numpad8, gdl::Keys::Numpad5, gdl::Keys::Numpad6, gdl::Keys::Numpad4, gdl::Keys::Numpad0, gdl::Keys::Numpad9, gdl::Keys::Numpad7, gdl::Keys::Add);
      GameScene::p2Alive = true;
    }
  this->_keyController = KeyController::getInstance();
  if (!this->_id)
    this->_helmet = gdl::Model::load("medias/models/helmet1.fbx");
  else
    this->_helmet = gdl::Model::load("medias/models/helmet2.fbx");
}

HumanPlayer::~HumanPlayer()
{

}

void  HumanPlayer::assignKeys(std::vector<gdl::Keys::Key> &tab, gdl::Keys::Key up, gdl::Keys::Key down, gdl::Keys::Key right, gdl::Keys::Key left, gdl::Keys::Key bomb , gdl::Keys::Key next ,gdl::Keys::Key prev, gdl::Keys::Key detonate)
{
  tab.push_back(up);
  tab.push_back(down);
  tab.push_back(left);
  tab.push_back(right);
  tab.push_back(bomb);
  tab.push_back(next);
  tab.push_back(prev);
  tab.push_back(detonate);
}

int		HumanPlayer::update()
{
  bool  hasMoved = false;

  this->checkStates();
  this->whatInCase();
  this->_hasDetonate = false;
  this->_model.update(*(Clock::getClock()));
  
  if (this->_keyController->isKeyDown(this->_ctrlP[0]) && !hasMoved)
  {
    this->goUp();
    hasMoved = true;    
  }
  if (this->_keyController->isKeyDown(this->_ctrlP[1]) && !hasMoved)
  {
    this->goDown();
    hasMoved = true;    
  }
  if (this->_keyController->isKeyDown(this->_ctrlP[2]) && !hasMoved)
  {
    this->goLeft();
    hasMoved = true;    
  }
  if (this->_keyController->isKeyDown(this->_ctrlP[3]) && !hasMoved)
  {
    this->goRight();
    hasMoved = true;    
  }
  if (!hasMoved)
    this->doNothing();
  if (this->_keyController->isKeyDown(this->_ctrlP[4]))
    this->putBomb();
  if (this->_timeChangingWeapon != 0)
  {
    this->_timeChangingWeapon++;
    if (this->_timeChangingWeapon == 10)
      this->_timeChangingWeapon = 0;
  }
  else
  {
    this->_timeChangingWeapon++;
    if (this->_keyController->isKeyDown(this->_ctrlP[5]))
      {
          std::string tmp("next");
          this->selectBomb(tmp);
      }
     else if (this->_keyController->isKeyDown(this->_ctrlP[6]))
      {
          std::string tmp("prev");
          this->selectBomb(tmp); 
      }
  }
  if (this->_keyController->isKeyDown(this->_ctrlP[7]))
  {
    this->detonateRemote();
  } 
  return (0);
}

void HumanPlayer::draw()
{
  if (this->_isAGhost && this->_timeGhost % 2 == 0)
    return ;
  glLoadIdentity();
  glTranslatef(this->_x, 0, this->_y);
  glRotatef(this->_roty, 0.0f, 1.0f, 0.0f);
  this->_model.draw();
  glLoadIdentity();
  glTranslatef(this->_x, 180, this->_y);
  glRotatef(this->_roty, 0.0f, 1.0f, 0.0f);
  this->_helmet.draw();
}
