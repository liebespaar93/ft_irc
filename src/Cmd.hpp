#ifndef CMD_HPP
#define CMD_HPP

#include <map>
#include <string>

#include "Message.hpp"
#include "Server.hpp"

class Cmd
{
private:
	/* data */
	Cmd(const Cmd &ref){};
	Cmd &operator=(const Cmd &ref) { return *this; };

protected:
	Server	*_server;
	User 	*_user;
	
	int			_fd;

	std::string _cmd;
	std::string _client;
	std::string _server_name;
	std::string _channel;
	std::string _info;
	std::string _symbol;
	std::string _prefix;

	std::string _subject;

	std::string _send_msg = "";

public:
	Cmd(){};
	~Cmd(){};

	void ft_set_server(Server *server) {this->_server = server; };
	void ft_set_user(User *user) {this->_user = user; };

	void ft_send(){ send(this->_fd, this->_send_msg.c_str(), this->_send_msg.size(), 0); };
	virtual void ft_recv(std::vector<std::string> msg) = 0;

};

#endif
