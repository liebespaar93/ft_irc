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

	void ft_channel_create(std::string channel_name)
	{
		std::cout << FG_MEMO << "[CREATE] " << FG_LMAGENTA << channel_name << " : " << FG_INFO << _msg
				  << NO_COLOR << std::endl;
	};

	void ft_channel_destory(std::string channel_name)
	{
		std::cout << FG_MEMO << "[DESTORY] " << FG_LMAGENTA << channel_name << " : "  << FG_INFO << _msg
				  << NO_COLOR << std::endl;
	}
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
	void	ft_cmd_msg(int fd)
	{
		std::cout << FG_WARNING << "[CMD] SEND" << FG_LBLUE << "[ " << fd << " ] " << FG_INFO << _msg
				  << NO_COLOR << std::endl;
	}
	void	ft_recv_msg(int fd)
	{
		std::cout << FG_GREEN << "[CMD] SEND" << FG_LBLUE << "[ " << fd << " ] " << FG_INFO << _msg
				  << NO_COLOR << std::endl;
	}

	void ft_join(std::string channel_name)
	{
		std::cout << FG_LCYAN << "[JOIN]" << FG_LBLUE << "[ " << channel_name << " ] " << FG_INFO << _msg
				  << NO_COLOR << std::endl;
	}
	void ft_leave(std::string channel_name)
	{
		std::cout << FG_RED << "[LEAVE]" << FG_LBLUE << "[ " << channel_name << " ] " << FG_INFO << _msg
				  << NO_COLOR << std::endl;
	}
};

#endif
