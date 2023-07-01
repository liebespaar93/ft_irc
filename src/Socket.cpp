#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <ctime>

#include "Socket.hpp"
#include "Logger.hpp"
#include "Error.hpp"

Socket::Socket(){}
Socket &Socket::operator=(const Socket &ref)
{
	(void)ref;
	return *this;
}

Socket::Socket(int fd, sockaddr *socket_info)
	: _fd(fd), _time(time(NULL)), _ping_check(false), _recv_msg(""), _send_msg("")
{
	this->_socket_info = *socket_info;
	this->_pfd.fd = this->_fd;
	this->_pfd.events = POLLSTANDARD;
	this->_pfd.revents = 0;
	Logger("socket create").ft_socket(this->_fd);
}

Socket::Socket(const char *IP, const char *port)
	: _time(time(NULL)), _ping_check(false), _recv_msg("")
{
	(void)IP;
	struct addrinfo hints = {.ai_flags = AI_PASSIVE | SO_REUSEADDR, .ai_family = AF_INET, .ai_socktype = SOCK_STREAM, .ai_protocol = IPPROTO_TCP};
	if (getaddrinfo(NULL, port, &hints, &this->_info) != 0)
		throw Error("getaddrinfo() != 0");
	this->_socket_info = *this->_info->ai_addr;
	this->ft_create_socket();
	Logger("socket create").ft_socket(this->_fd);
}

Socket::~Socket()
{
	send(this->_fd, 0, 0, 0);
	close(this->_fd);
	Logger("socket close").ft_socket_close(this->_fd);
}

void Socket::ft_create_socket()
{
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

	if (this->ft_poll() & POLLIN)
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
	if (poll(&this->_pfd, 1, 100) == -1 && this->_pfd.revents & POLLERR)
		Logger("poll POLLERR").ft_error();
	return (this->_pfd.revents);
}

bool Socket::ft_ping()
{
	time_t now = time(NULL);
	if (this->_time + 300 > now)
		return (false);
	if ((this->_time + 360 < now))
		return (true);
	if (this->_ping_check)
		return (false);
	this->ft_append_send_msg("PING :life \r\n");
	this->_ping_check = true;
	return (false);
}

bool Socket::ft_pong(std::string msg)
{
	(void)msg;
	this->_time = time(NULL);
	this->_ping_check = false;
	return (true);
}

int Socket::ft_get_socket_fd() { return this->_fd; }
std::string Socket::ft_get_socket_IP() { return ((std::string)inet_ntoa(((sockaddr_in *)&this->_socket_info)->sin_addr)); }
void Socket::ft_set_time() { this->_time = time(NULL); }
time_t Socket::ft_get_time() { return this->_time; }

std::string Socket::ft_push_recv_msg(std::string recv_msg)
{
	this->_recv_msg += recv_msg;
	return this->_recv_msg;
}

void Socket::ft_set_recv_msg(std::string recv_msg) { this->_recv_msg = recv_msg; }
void Socket::ft_append_send_msg(std::string send_msg){ this->_send_msg += send_msg; }

void Socket::ft_send_msg()
{
	send(this->_fd, this->_send_msg.c_str(), this->_send_msg.size(), 0);
	this->_send_msg = "";
}
