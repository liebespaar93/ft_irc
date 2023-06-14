#include "Server.hpp"
#include "Logger.hpp"

Server::Server(std::string port, std::string password)
	: _password(password), _on(1)
{
	this->_server = new Socket("0.0.0.0", port.c_str());
	this->_server->ft_accept();

	Logger("Server Craete").ft_create();
}

Server::~Server()
{
	delete this->_server;
}