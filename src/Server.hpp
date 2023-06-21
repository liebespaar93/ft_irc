#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <sys/socket.h>
#include <queue>
#include <map>

#include "Socket.hpp"
#include "UserControl.hpp"
#include "ChannelControl.hpp"
#include "Cmd.hpp"

class Server : public UserControl, public ChannelControl
{
private:
	/* data */
	Socket *_server;
	std::string _password;
	std::map<std::string, Cmd *> _cmd_map;
	int _on;

	std::queue<Socket *> _socket;

	Server(){};
	Server(const Server &ref){};

	void ft_pollin(Socket *socket_front);
	void ft_server_check_socket_fd();
	void ft_connect_socket(Socket *accept_socket);

	/* parse */
	void ft_parse(std::string buf, int fd);
	void ft_set_cmd_map();

public:
	Server(std::string port_str, std::string password_str);
	Server &operator=(const Server &ref)
	{
		this->_server = ref._server;
		this->_password = ref._password;
		this->_cmd_map = ref._cmd_map;
		this->_on = ref._on;
		this->_socket = ref._socket;
		return *this;
	};
	~Server();

	void ft_server_on();

	std::string ft_get_password() { return this->_password; };

	void ft_server_input();
	void ft_user_destory(User *user);
};

#endif
