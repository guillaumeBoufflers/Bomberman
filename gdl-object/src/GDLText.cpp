
#include	"GDLText.hh"

GDLText::GDLText(const std::string &text, int actionDefault, int x, int y, unsigned int size, unsigned char red, unsigned char green, unsigned char blue):
  _actionDefault(actionDefault)
{
  gdl::Color	_color(red, green, blue, 255);

  this->_text.setText(text);
  this->_text.setPosition(x, y);
  this->_text.setSize(size);
  this->_text.setColor(_color);
}

GDLText::~GDLText()
{

}

void	GDLText::initialize()
{

}

int	GDLText::update()
{
  return (this->_actionDefault);
}

void	GDLText::draw()
{
  this->_text.draw();
}

void	GDLText::setText(const std::string &str)
{
  this->_text.setText(str);
}

void	GDLText::setPosition(unsigned int x, unsigned int y)
{
  this->_text.setPosition(x, y);
}

void	GDLText::setSize(unsigned int size)
{
  this->_text.setSize(size);
}
