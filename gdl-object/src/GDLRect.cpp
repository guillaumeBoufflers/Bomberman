#include 			"GDLRectangle.hh"

GDLRectangle::GDLRectangle(float x, float y, float z, float width, float height, std::string SpritePath, int reverse, CameraView *camera) :
  _x(x), _y(y), _z(z), _width(width), _height(height), _SpritePath(SpritePath), _reverse(reverse), _camera(camera), _side(-1)
{
  _dir = 0;
}

GDLRectangle::GDLRectangle(float x, float y, float z, float width, float height, std::string SpritePath, int reverse, CameraView *camera, int side) :
  _x(x), _y(y), _z(z), _width(width), _height(height), _SpritePath(SpritePath), _reverse(reverse), _camera(camera), _side(side)
{
}

GDLRectangle::~GDLRectangle() 
{

}

void 				GDLRectangle::initialize() 
{
  this->_image = gdl::Image::load(this->_SpritePath);
}

int 				GDLRectangle::update()
{
  _dir = 0;
  return (0);
}

void 				GDLRectangle::draw() 
{
  if (_side == -1 || _dir == _side || !(this->_camera->isDualMode()))
    {
      this->_image.bind();
      this->drawRec();
    }
  else
    _dir = 1;
}

void				GDLRectangle::drawRec()
{
  glPushMatrix();
  glLoadIdentity();

  if (this->_camera->isDualMode() && _dir == 0)
    glTranslatef(this->_camera->getX() + (710 / 3) - 365, this->_camera->getY() - 800 , this->_camera->getZ() - 900);
  else if (this->_camera->isDualMode() && _dir == 1)
    glTranslatef(this->_camera->getX() + (710 / 2) - 115, this->_camera->getY() - 800 , this->_camera->getZ() - 900);
  else
    glTranslatef(this->_camera->getX()  + 710, this->_camera->getY() - 800, this->_camera->getZ() - 900);
  glRotatef(110, 1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  if (this->_reverse == 0)
    {
      glTexCoord2f(0.0f, 0.0f);
      //Vertex superieur gauche
      glVertex3f(this->_x - (this->_width / 2.0) , W_HEIGHT - (this->_y - (this->_height / 2.0)), this->_z);
      ///vertex inferieur gauche
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(this->_x - (this->_width / 2.0),  W_HEIGHT - (this->_y + (this->_height / 2.0)), this->_z);
      /// Vertex inferieur droit
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(this->_x + (this->_width / 2.0),  W_HEIGHT - (this->_y + (this->_height / 2.0)), this->_z);
      /// Vertex superieur droit
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(this->_x + (this->_width / 2.0),  W_HEIGHT -  (this->_y - (this->_height /2.0)), this->_z);

    }
  else
    {
      glTexCoord2f(0.0f, 0.0f);
      //Vertex superieur gauche
      glVertex3f(this->_x - (this->_width / 2.0) , (this->_y - (this->_height / 2.0)), 0.0f);
      ///vertex inferieur gauche
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(this->_x - (this->_width / 2.0), (this->_y + (this->_height / 2.0)), 0.0f);
      /// Vertex inferieur droit
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(this->_x + (this->_width / 2.0), (this->_y + (this->_height / 2.0)), 0.0f);
      /// Vertex superieur droit
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(this->_x + (this->_width / 2.0), (this->_y - (this->_height /2.0)), 0.0f);
    }
  glEnd();
  _dir = 1;
}

void			GDLRectangle::setX(float x)
{
  this->_xCamera = x;
}

void			GDLRectangle::setY(float y)
{
  this->_yCamera = y;
}

void			GDLRectangle::setSprite(const std::string & spritePath)
{
  this->_image = gdl::Image::load(spritePath);
}

void			GDLRectangle::setCoordX(float x)
{
  this->_x = x;
}
