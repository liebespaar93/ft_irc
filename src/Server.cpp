#include "Server.hpp"
#include "Logger.hpp"
#include "Error.hpp"

Server::Server(std::string port, std::string password)
	: _password(password), _on(1)
{
	this->_server = new Socket("0.0.0.0", port.c_str());
	Logger("Server Craete").ft_create();
}

void Server::ft_server_on()
{
	Socket *accept_socket;
	while (this->_on && this->_socket.size() < 3)
	{
		accept_socket = this->_server->ft_accept();
		if (accept_socket)
			this->ft_connect_socket(accept_socket);
		this->ft_server_check_socket_fd();
		ft_server_input(); /////////////
	}
}

void Server::ft_connect_socket(Socket *accept_socket)
{
	this->_socket.push(accept_socket);
}

void Server::ft_server_check_socket_fd()
{
	int revents;
	int socket_size;
	Socket *socket_front;

	socket_size = this->_socket.size();

	while (socket_size--)
	{
		socket_front = this->_socket.front();
		this->_socket.pop();
		revents = socket_front->ft_poll();
		if (revents & POLLERR) 
			Logger("POLLERR").ft_error();
		else if ((revents & POLLRDNORM))
			this->ft_pollin(socket_front);
		else
			this->_socket.push(socket_front);
	}
}

void Server::ft_pollin(Socket *socket_front)
{
	int fd;
	char buf[4096];
	ssize_t len;
	int socket_send_loop;

	fd = socket_front->ft_get_socket_fd();
	len = recv(fd, &buf, 4095, 0);
	if (len < 0)
		throw Error("recv() failed");
	if (len == 0)
	{
		Logger("connect close").ft_socket(fd);
		delete socket_front;
		return;
	}
	buf[len] = '\0';
	if (len > 0 && buf[len - 1] == '\n')
		buf[--len] = '\0';

	if (len == 1 && buf[0] == '\n')
	{
		delete socket_front;
		return;
	}
	std::cout << buf << std::endl;
	this->_socket.push(socket_front);
}

Server::~Server()
{
	Socket *socket_del;

	while (!this->_socket.empty())
	{
		socket_del = this->_socket.front();
		this->_socket.pop();
		delete socket_del;
	}
	delete this->_server;
}






void Server::ft_server_input()
{
	std::string buf;
	struct pollfd pfd = {.fd = 0, .events = POLLIN};
	int ret_poll;
	int size = this->_socket.size();
	Socket * front = NULL;

	ret_poll = poll(&pfd, 1, 0);
	if (ret_poll > 0)
	{
		std::getline(std::cin, buf);
		buf.append("\r\n");
		while (size--)
		{
			front = this->_socket.front();
			send(front->ft_get_socket_fd(), buf.c_str(), buf.size(), 0);
			this->_socket.pop();
			this->_socket.push(front);

		}
		Logger("server send").ft_server_msg(4);
	}
}