#ifndef CMD_HPP
#define CMD_HPP

#include <map>
#include <string>

#include "Message.hpp"

class Cmd
{
private:
	/* data */
	Cmd(const Cmd &ref){};
	Cmd &operator=(const Cmd &ref) { return *this; };

protected:
	int			_fd;
	std::string _cmd;
	std::string _client;
	std::string _server_name;

	std::string _send_msg = "";

public:
	Cmd(){};
	~Cmd(){};

	void ft_send(){ send(this->_fd, this->_send_msg.c_str(), this->_send_msg.size(), 0); };
	virtual void ft_recv(std::vector<std::string> msg) = 0;
};

#endif
