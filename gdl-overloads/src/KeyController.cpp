#include	"KeyController.hh"

KeyController::KeyController(gdl::Input &input) : _input(input)
{

}

KeyController::~KeyController()
{

}

KeyController 				*KeyController::getInstance(gdl::Input *input) {
	static KeyController 	*instance = NULL;

	if (!instance)
		instance = new KeyController(*input);
	return (instance);
}

int 			KeyController::getMouseX() {
	return (this->_input.getMousePositionX());
}

int 			KeyController::getMouseY() {
	return (this->_input.getMousePositionY());
}

bool 			KeyController::isMouseButtonDown(gdl::Mouse::Button button) {
	return (this->_input.isMouseButtonDown(button));
}

bool			KeyController::isKeyDown(gdl::Keys::Key key) {
	return (this->_input.isKeyDown(key));
}