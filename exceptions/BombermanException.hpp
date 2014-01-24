#ifndef 				__BOMBERMAN_EXCEPTION_HPP__
#define 				__BOMBERMAN_EXCEPTION_HPP__

#include 				<exception>
#include 				<string>

class 					BombermanException : public std::exception
{
private:
	const std::string 	_message;

public:
	virtual ~BombermanException() throw() {};
	
	BombermanException(const std::string &message) throw() : _message(message) {};

	virtual const char* what() const throw() {
		return this->_message.c_str();
	}

};

#endif
