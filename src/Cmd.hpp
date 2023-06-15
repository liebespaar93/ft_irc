#ifndef CMD_HPP
#define CMD_HPP

#include <map>
#include <string>

#include "Message.hpp"
#include "Server.hpp"

class Server;

class Cmd
{
private:
	/* data */
	Cmd(const Cmd &ref){};
	Cmd &operator=(const Cmd &ref) { return *this; };

protected:
	Server	*_server;
	User 	*_user;

	std::string _cmd;
	std::string _client;
	std::string _server_name;
	std::string _channel;
	std::string _info;
	std::string _symbol;
	std::string _prefix;

	std::string _subject;

	std::string _send_msg;

public:
	Cmd(){};
	~Cmd(){};

	void ft_set_client(std::string code){this->_client = this->_server_name + " " + code + " " + this->_user->ft_get_nick_name();} ;
	void ft_set_server(Server *server) {this->_server = server; };
	void ft_set_server_name(std::string server_name) {this->_server_name = server_name; };
	void ft_set_user(User *user) {this->_user = user; };

	void ft_send(){ send(this->_user->ft_get_fd(), this->_send_msg.c_str(), this->_send_msg.size(), 0); };
	virtual void ft_recv(std::vector<std::string> msg) = 0;

};

#endif
