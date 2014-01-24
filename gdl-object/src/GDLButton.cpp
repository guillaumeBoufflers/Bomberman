#include 			"GDLButton.hh"

GDLButton::GDLButton(KeyController *key, const std::string &base, const std::string &hover, const std::string &clicked, Type type, int x, int y, int width, int height, int actionDefault, int actionPressed, int reverse) : _keyController(key), _state(GDL_BUTTON_BASE), _x(x), _y(y), _width(width), _height(height), _baseSpritePath(base), _hoverSpritePath(hover), _clickedSpritePath(clicked), _type(type), _actionDefault(actionDefault), _actionPressed(actionPressed), _reverse(reverse) {
  this->_typ[0] = &GDLButton::drawRec;
  this->_typ[1] = &GDLButton::drawTri;
  this->_typ[2] = &GDLButton::drawTriInv;
}

GDLButton::~GDLButton() 
{

}

void 				GDLButton::initialize() 
{
  gdl::Image	_non;
  gdl::Image	_sur;
  gdl::Image	_enf;

  _non = gdl::Image::load(this->_baseSpritePath);
  _sur = gdl::Image::load(this->_hoverSpritePath);
  _enf = gdl::Image::load(this->_clickedSpritePath);
  this->_image.push_back(_non);
  this->_image.push_back(_sur);
  this->_image.push_back(_enf);
}

int 				GDLButton::update() {
  int	xMouse = this->_keyController->getMouseX();
  int	yMouse = this->_keyController->getMouseY();
  
  if (xMouse >= (this->_x - this->_width / 2) && xMouse <= (this->_x + this->_width / 2) &&
      yMouse >= (this->_y - (this->_height / 2)) && yMouse <= (this->_y  + (this->_height / 2)))
    {
      if (this->_keyController->isMouseButtonDown(gdl::Mouse::Left) == true)
	{
	  this->_state = GDL_BUTTON_CLICKED;
	  return (this->_actionPressed);
	}
      this->_state = GDL_BUTTON_HOVER;
      return (this->_actionDefault);
    }
  this->_state = GDL_BUTTON_BASE;
  return (this->_actionDefault);
}

void 				GDLButton::draw() 
{
  switch (this->_state)
  {
    case GDL_BUTTON_BASE:
    this->drawButton(this->_image[0]);
    break;
    case GDL_BUTTON_HOVER:
    this->drawButton(this->_image[1]);
    break;
    case GDL_BUTTON_CLICKED:
    this->drawButton(this->_image[2]);
    usleep(100000);
    break;
  }
}

void				GDLButton::drawButton(gdl::Image texture)
{
  texture.bind();
  (this->*_typ[this->_type])();
}

// le W_HEIGHT sert a pouvoir contourne le 0 0 de l opengl qui est en bas a gauche)

void				GDLButton::drawRec()
{
  glBegin(GL_QUADS);
  if (this->_reverse == 0)
    {
      // glTexCoord2f(0.0f, 0.0f);
      // //Vertex superieur gauche
      // glVertex3f(this->_x - (this->_width / 2.0) , W_HEIGHT - (this->_y - (this->_height / 2.0)), 0.0f);
      // ///vertex inferieur gauche
      // glTexCoord2f(0.0f, 1.0f);
      // glVertex3f(this->_x - (this->_width / 2.0),  W_HEIGHT - (this->_y + (this->_height / 2.0)), 0.0f);
      // /// Vertex inferieur droit
      // glTexCoord2f(1.0f, 1.0f);
      // glVertex3f(this->_x + (this->_width / 2.0),  W_HEIGHT - (this->_y + (this->_height / 2.0)), 0.0f);
      // /// Vertex superieur droit
      // glTexCoord2f(1.0f, 0.0f);
      // glVertex3f(this->_x + (this->_width / 2.0),  W_HEIGHT -  (this->_y - (this->_height /2.0)), 0.0f);

      glTexCoord2f(0.0f, 0.0f);
      //Vertex superieur gauche
      glVertex2f(this->_x - (this->_width / 2.0) , W_HEIGHT - (this->_y - (this->_height / 2.0)));
      ///vertex inferieur gauche
      glTexCoord2f(0.0f, 1.0f);
      glVertex2f(this->_x - (this->_width / 2.0),  W_HEIGHT - (this->_y + (this->_height / 2.0)));
      /// Vertex inferieur droit
      glTexCoord2f(1.0f, 1.0f);
      glVertex2f(this->_x + (this->_width / 2.0),  W_HEIGHT - (this->_y + (this->_height / 2.0)));
      /// Vertex superieur droit
      glTexCoord2f(1.0f, 0.0f);
      glVertex2f(this->_x + (this->_width / 2.0),  W_HEIGHT -  (this->_y - (this->_height /2.0)));     
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
}

void				GDLButton::drawTri()
{
  glBegin(GL_TRIANGLES);
  if (this->_reverse == 0)
    {
      ///vertex inferieur gauche
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(this->_x - (this->_width / 2), W_HEIGHT - this->_y - (this->_height / 2), 0.0f);
      /// Vertex inferieur droit
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(this->_x + (this->_width /2), W_HEIGHT- this->_y - (this->_height / 2), 0.0f);
      /// Vertex superieur droit
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(this->_x,  W_HEIGHT - this->_y + (this->_height /2), 0.0f);
    }
  else
    {
      ///vertex inferieur gauche
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(this->_x - (this->_width / 2), this->_y + (this->_height / 2), 0.0f);
      /// Vertex inferieur droit
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(this->_x + (this->_width /2), this->_y + (this->_height / 2), 0.0f);
      /// Vertex superieur droit
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(this->_x,  this->_y - (this->_height /2), 0.0f);
    }
  glEnd();
}

void				GDLButton::drawTriInv()
{
  glBegin(GL_TRIANGLES);
  if (this->_reverse == 0)
    {
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(this->_x - (this->_width / 2), W_HEIGHT - this->_y + (this->_height / 2), 0.0f);
      /// Vertex inferieur droit
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(this->_x + (this->_width /2), W_HEIGHT - this->_y + (this->_height / 2), 0.0f);
      /// Vertex superieur droit
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(this->_x, W_HEIGHT - this->_y - (this->_height /2), 0.0f);
    }
  else
    {
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(this->_x - (this->_width / 2), this->_y - (this->_height / 2), 0.0f);
      /// Vertex inferieur droit
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(this->_x + (this->_width /2), this->_y - (this->_height / 2), 0.0f);
      /// Vertex superieur droit
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(this->_x, this->_y + (this->_height /2), 0.0f);
    }
  glEnd();
}

void				GDLButton::setHover(const std::string & hover)
{
  gdl::Image	_non;

  this->_baseSpritePath = hover;
  _non = gdl::Image::load(this->_baseSpritePath);
  this->_image[0] = _non;
}

void				GDLButton::setSurvol(const std::string & survol)
{
  gdl::Image	_sur;

  this->_hoverSpritePath = survol;
  _sur = gdl::Image::load(this->_hoverSpritePath);
  this->_image[1] = _sur;
}
