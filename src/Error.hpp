#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

#include "Logger.hpp"

class Error
{
private:
	/* data */
	std::string _message;

public:
	Error() : _message("Error: default"){};
	Error(std::string errormessege) : _message("Error: " + errormessege){};
	~Error() throw() { return; };

	virtual const char *what() const throw()
	{
		Logger(this->_message).ft_error();
		return ("1");
	};
};

#endif
