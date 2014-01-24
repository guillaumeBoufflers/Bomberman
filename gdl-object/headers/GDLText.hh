
#ifndef		__GDLTEXT_HH__
#define		__GDLTEXT_HH__

#include	"common.hh"
#include	"IGDLObject.hh"

class		GDLText : public IGDLObject
{
private:
  gdl::Text	_text;
  int		_actionDefault;
  void    setPosition(unsigned int x, unsigned int y);
  void    setSize(unsigned int size);
public:
  GDLText(const std::string &, int, int, int, unsigned int, unsigned char, unsigned char, unsigned char);
  virtual void	initialize();
  virtual int	update();
  virtual void	draw();
  virtual	~GDLText();
  void		setText(const std::string &str);
};
#endif
