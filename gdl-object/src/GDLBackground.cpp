#include	"GDLBackground.hh"

GDLBackground::GDLBackground(const std::string &img, int reverse):
  _reverse(reverse)
{
  this->_background = gdl::Image::load(img);
}

GDLBackground::~GDLBackground()
{

}

void		GDLBackground::initialize()
{
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, (GLdouble)W_WIDTH, 0.0, (GLdouble)W_HEIGHT);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
}

int		GDLBackground::update()
{
  return (0);
}

void		GDLBackground::setBackground(const std::string &img)
{
  this->_background = gdl::Image::load(img);
}

void		GDLBackground::draw()
{
  this->_background.bind();
  glBegin(GL_QUADS);
  if (this->_reverse == 0)
    {
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(0.0f, W_HEIGHT , 0.0f);
      /// Vertex inferieur gauche
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(0.0f, 0.0f, 0.0f);
      /// Vertex inferieur droit
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(W_WIDTH, 0.0f, 0.0f);
      /// Vertex superieur droit
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(W_WIDTH, W_HEIGHT, 0.0f);
    }
  else
    {
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(0.0f, 0, 0.0f);
      /// Vertex inferieur gauche
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(0.0f, W_HEIGHT, 0.0f);
      /// Vertex inferieur droit
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(W_WIDTH, W_HEIGHT, 0.0f);
      // /// Vertex superieur droit
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(W_WIDTH, 0, 0.0f);
    }
  glEnd();
}
