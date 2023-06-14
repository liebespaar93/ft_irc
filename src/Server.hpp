#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <sys/socket.h>

#include "Socket.hpp"

class Server
{
private:
	/* data */
	Socket *_server;
	std::string _password;
	int _on;

	Server(){};
	Server(const Server &ref){};
	Server &operator=(const Server &ref) { return *this; };

public:
	Server(std::string port_str, std::string password_str);
	~Server();
};

#endif
