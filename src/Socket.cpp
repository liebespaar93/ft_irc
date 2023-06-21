#include <arpa/inet.h> // inet_addr
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "Socket.hpp"
#include "Logger.hpp"
#include "Error.hpp"

Socket::Socket(int fd, sockaddr *socket_info)
	: _fd(fd)
{
	this->_socket_info = *socket_info;
	this->_pfd.fd = this->_fd;
	this->_pfd.events = POLLSTANDARD | POLLNLINK;
	this->_pfd.revents = 0;
	Logger("socket create").ft_socket(this->_fd);
}

Socket::Socket(const char *IP, const char *port)
{
	struct addrinfo hints = {.ai_flags = AI_PASSIVE | SO_REUSEADDR, .ai_family = AF_INET, .ai_socktype = SOCK_STREAM, .ai_protocol = IPPROTO_TCP};
	if (getaddrinfo(NULL, port, &hints, &this->_info) != 0)
		throw Error("getaddrinfo() != 0");
	this->_socket_info = *this->_info->ai_addr;
	this->ft_create_socket();
	Logger("socket create").ft_socket(this->_fd);
}

Socket::~Socket()
{
	send(this->_fd, "", 0, 0);
	close(this->_fd);
	Logger("socket close").ft_socket_close(this->_fd);
}

void Socket::ft_create_socket()
{
	addrinfo *info;
	int y = 1;

	if ((this->_fd = socket(this->_info->ai_family, this->_info->ai_socktype, this->_info->ai_protocol)) == -1)
		throw Error("socket() == -1");
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int)) == -1)
		(close(_fd), freeaddrinfo(this->_info), throw Error("setsockopt() == -1"));
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
		(close(_fd), freeaddrinfo(this->_info), throw Error("fcntl() == -1"));
	if (bind(this->_fd, this->_info->ai_addr, this->_info->ai_addrlen) == -1)
		(close(_fd), freeaddrinfo(this->_info), throw Error("bind() == -1"));

	if (SOCONN > SOMAXCONN || listen(_fd, SOCONN) == -1)
		throw Error("listen() == -1");
	freeaddrinfo(this->_info);
	this->_pfd.fd = this->_fd;
	this->_pfd.events = POLLSTANDARD;
	this->_pfd.revents = 0;
}

Socket *Socket::ft_accept()
{
	Socket *client = NULL;
	int socket_fd;
	sockaddr ip4addr;
	socklen_t client_addr_size = sizeof(sockaddr);

	if (this->ft_poll() > 0)
	{
		if ((socket_fd = accept(this->_fd, &ip4addr, &client_addr_size)) == -1)
			throw Error("accept fd == -1");
		client = new Socket(socket_fd, &ip4addr);
		return client;
	}
	return (NULL);
}

int Socket::ft_poll()
{
	if (poll(&this->_pfd, 1, 0) == -1 && this->_pfd.revents & POLLERR)
		Logger("poll POLLERR").ft_error();
#ifdef DEBUG
	if (this->_pfd.revents)
	{
		std::cout << "fd : " << pfd.fd << std::endl;
		std::cout << "pfd.revents : " << pfd.revents << std::endl;
		std::cout << "pfd.events : " << pfd.events << std::endl;
	}
#endif
	return (this->_pfd.revents);
}

/**
 * socket function for client
 * 소켓 ip 에따라 검색하여 내가 요청한 인터넷 타입을 찾는다
 */
/*
void	Socket::ft_ip_check()
{
	int IP_result = inet_addr(this->_IP);
	if (IP_result == INADDR_NONE)
		throw Error("inet_addr failed and returned INADDR_NONE\n");
	if (IP_result == INADDR_ANY)
		throw Error("inet_addr failed and returned INADDR_NONE\n");
}

void	Socket::ft_find_socker()
{
	struct addrinfo	*prompt, *info;
	int				option_value = 1;

	if (getaddrinfo(this->_IP, this->_port, &this->_hints, &info) != 0)
		throw Error("getaddrinfo"); // gai_strerror()  getaddrinfo(IP, port, &this->_hints, &this->_info) need return value
	for (prompt = info;prompt != NULL; prompt = prompt->ai_next) //	_info->ai_next // 하나의 도메인에 여러개의 아이피가 존제할 수 있음
	{
		try
		{
			if ((this->_socket_fd = socket(prompt->ai_family, prompt->ai_socktype, prompt->ai_protocol)) == -1)
				throw Error("Error socker");
			if (setsockopt(this->_socket_fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(int)) == -1)
				throw Error("Error setsocketopt");
			break ;
		}
		catch ( const std::exception& e )
		{
			std::cerr << e.what() << '\n';
			if (this->_socket_fd)
				close(this->_socket_fd);
		}
	}
	if (prompt == NULL)
		throw Error("Error : getaddrinfo no socket");
	std::cout << "find socket and create " << std::endl;
	freeaddrinfo(info);
}
*/
