#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

#include "Color.hpp"

class Logger
{
private:
	/* data */
	std::string _msg;

	Logger(){};
	Logger(const Logger &ref){};

	Logger &operator=(const Logger &ref) { return *this; };

public:
	Logger(std::string msg) { this->_msg = msg; };
	~Logger(){};

	void ft_error()
	{
		std::cerr << FG_ERROR << "[ERROR] " << FG_INFO << _msg << "\n"
				  << NO_COLOR;
	};

	void ft_create()
	{
		std::cout << FG_WARNING << "[CREATE] " << FG_LMAGENTA << _msg
				  << NO_COLOR << std::endl;
	};

	void ft_socket(int fd)
	{
		std::cout << FG_WARNING << "[CREATE] " << FG_LBLUE << "[ " << fd << " ] " << FG_INFO << _msg
				  << NO_COLOR << std::endl;
	}
	void ft_socket_close(int fd)
	{
		std::cout << FG_ERROR << "[CLOSE] " << FG_LBLUE << "[ " << fd << " ] " << FG_INFO << _msg
				  << NO_COLOR << std::endl;
	}
	void	ft_server_msg(int fd)
	{
		std::cout << FG_WARNING << "[SERVER] SEND" << FG_LBLUE << "[ " << fd << " ] " << FG_INFO << _msg
				  << NO_COLOR << std::endl;
	}
};

#endif
