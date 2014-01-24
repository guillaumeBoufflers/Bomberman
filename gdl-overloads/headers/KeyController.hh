#ifndef					__KEYCONTROLLER_HH__
#define					__KEYCONTROLLER_HH__

#include				<list>
#include 				"common.hh"

class					KeyController
{
private:
  gdl::Input 	_input;
  KeyController(gdl::Input &input);

public:
  static KeyController	*getInstance(gdl::Input *input = NULL);
  
  ~KeyController();

  int 					getMouseX();
  int 					getMouseY();
  bool 					isMouseButtonDown(gdl::Mouse::Button);
  bool					isKeyDown(gdl::Keys::Key);
};

#endif
