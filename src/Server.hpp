#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <sys/socket.h>
#include <queue>

#include "Socket.hpp"

class Server
{
private:
	/* data */
	Socket *_server;
	std::string _password;
	int _on;

	std::queue<Socket *> _socket;

	Server(){};
	Server(const Server &ref){};
	Server &operator=(const Server &ref) { return *this; };

	void ft_pollin(Socket *socket_front);
	void ft_server_check_socket_fd();
	void ft_connect_socket(Socket *accept_socket);


public:
	Server(std::string port_str, std::string password_str);
	~Server();

	void ft_server_on();






	void ft_server_input();/////////
};

#endif
